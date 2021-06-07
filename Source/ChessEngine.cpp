#include "Headers/ChessEngine.h"

ChessEngine::ChessEngine(Color bordCol1 = Color::White, Color bordCol2 = Color::Black)
: board(bordCol1,bordCol2)
{

    font.loadFromFile("Textures/text.ttf");
    
    
    infoRestart.setFillColor(Color(49,46,43));
    infoRestart.setOutlineThickness(-5.f);
    infoRestart.setOutlineColor(Color(39,37,34));
    infoRestart.setPosition(Vector2f(540.f,5.f));
    infoRestart.setSize(Vector2f(200.f, 50.f));

    textRestart.setFont(font);
    textRestart.setString("New Game");
    textRestart.setCharacterSize(20);
    textRestart.setStyle(Text::Bold);
    textRestart.setFillColor(Color(156,155,153));
    textRestart.setPosition(infoRestart.getPosition().x + 50.f, infoRestart.getPosition().y + 14.f);

    textTurn.setFont(font);
    textTurn.setCharacterSize(24);
    textTurn.setStyle(Text::Bold);
    textTurn.setFillColor(Color::White);
    textTurn.setPosition(530.f, 70.f);


    textLastMove.setFont(font);
    textLastMove.setCharacterSize(24);
    textLastMove.setStyle(Text::Bold);
    textLastMove.setFillColor(Color::White);
    textLastMove.setPosition(530.f, 110.f);


    restart();

}

void ChessEngine::restart() {

    selected = false;
    playerTurn = true;
    playerTurnCheck = false;
    mate = false;
    turn = 1;
    Side = playerTurn;

    Figures_B[0].set('R', false, 7);
    Figures_B[1].set('N', false, 6);
    Figures_B[2].set('B', false, 5);
    Figures_B[3].set('K', false, 4);
    Figures_B[4].set('Q', false, 3);
    Figures_B[5].set('B', false, 2);
    Figures_B[6].set('N', false, 1);
    Figures_B[7].set('R', false, 0);


    Figures_W[0].set('R', true, 56);
    Figures_W[1].set('N', true, 57);
    Figures_W[2].set('B', true, 58);
    Figures_W[3].set('Q', true, 59);
    Figures_W[4].set('K', true, 60);
    Figures_W[5].set('B', true, 61);
    Figures_W[6].set('N', true, 62);
    Figures_W[7].set('R', true, 63);


    for (int i = 8; i < 16; i++) {
        Figures_W[i].set('P', true, 48 + (i - 8));
        Figures_B[i].set('P', false, 15 - (i - 8));
    }

    FindPossibleMoves();

    textLastMove.setString(" ");


}

void ChessEngine::updateInfo(){

    if (!mate && playerTurnCheck)lastMove += "+";
    if (mate) if (playerTurnCheck)lastMove += "#"; else lastMove += "  1/2";
    textTurn.setString("Turn: " + std::to_string(turn));
    textLastMove.setString(lastMove);

}



void ChessEngine::draw(RenderTarget& e, RenderStates states) const {
    e.clear(Color(49, 46, 43));

    e.draw(board);
    e.draw(infoRestart);
    e.draw(textRestart);
    e.draw(textTurn);
    e.draw(textLastMove);

    if ((selectedFigure != NULL) && (selected)) {
        for (size_t i = 0; i < possibleMovesSquares.size(); ++i) {
            e.draw(possibleMovesSquares.at(i));
        }
    }
    for (size_t i = 0; i < 16; ++i) {
        e.draw(Figures_W[i]);
        e.draw(Figures_B[i]);
    }
}

void ChessEngine::createMovesSquares(){

    if(selectedFigure == NULL)
        return;

    possibleMovesSquares.clear();

    for(size_t i=0; i<selectedFigure->getPossibleMoves().size();++i){
        RectangleShape tmp;
        tmp.setPosition(Vector2f((selectedFigure->getPossibleMoves().at(i) % 8) * 64.f , (selectedFigure->getPossibleMoves().at(i) / 8) * 64.f));
        tmp.setSize(Vector2f(64.f, 64.f));
        tmp.setFillColor(Color(246, 220, 121, 150));
        possibleMovesSquares.push_back(tmp);
    }

    RectangleShape tmp;
    tmp.setPosition(Vector2f((selectedFigure->getPosition() % 8) * 64.f , (selectedFigure->getPosition() / 8) * 64.f));
    tmp.setSize(Vector2f(64.f, 64.f));
    tmp.setFillColor(Color(119, 148, 82, 150));
    possibleMovesSquares.push_back(tmp);

    return;

}



bool ChessEngine::Select(int pos){
    for(size_t i=0; i<16; i++){
        if(playerTurn){ 
            if(Figures_W[i].getPosition() == pos){
                selectedFigure = &Figures_W[i];
                selected = true;
                break;
            }
        }
        else{ 
            if(Figures_B[i].getPosition() == pos){
                selectedFigure = &Figures_B[i];
                selected = true;
                break;
            }
        }
        selected = false;
    }

    if(!selected){
        selectedFigure = NULL;
        possibleMovesSquares.clear();
        return selected;
    }


    createMovesSquares();

    return selected;
}


void ChessEngine::Moving(int pos){
    bool validMove{false};

    if((selectedFigure == NULL) || !selected ) 
        return;
    
    
    for(size_t i=0;i<selectedFigure->getPossibleMoves().size();++i){
        if(pos == selectedFigure->getPossibleMoves().at(i)){
            validMove = true;
            break;
        }
    }

    if(validMove){

        if((selectedFigure->getType() == 'K') && (!selectedFigure->getMoved())){
            if(selectedFigure->getPlayer()){ 
                
                if(pos == 62)
                    Figures_W[7].setPosition(61);
                else if(pos == 58)
                    Figures_W[0].setPosition(59);
            }
            else{ 
                
                if(pos == 6)
                   Figures_B[0].setPosition(5);
                else if(pos == 2)
                   Figures_B[7].setPosition(3);
            }
        } 
        
        if((selectedFigure->getType() == 'P')){
            if(!selectedFigure->getMoved()){
                if(pos == (selectedFigure->getPosition() - 16)){
                    selectedFigure->setEnPassant(selectedFigure->getPosition() - 8);
                }
                else if(pos == (selectedFigure->getPosition() + 16)){
                    selectedFigure->setEnPassant(selectedFigure->getPosition() + 8);
                }
            }
            else{
                for(size_t i=0; i<16; i++){
                    if(playerTurn){
                        if(pos ==Figures_B[i].getEnPassant())
                           Figures_B[i].setPosition(pos);
                    }
                    else{
                        if(pos == Figures_W[i].getEnPassant())
                            Figures_W[i].setPosition(pos);
                    }
                }
            }
        }
        if(selectedFigure->getMoved()){
            for(size_t i=0; i<16; i++){
                Figures_W[i].setEnPassant(-1);
               Figures_B[i].setEnPassant(-1);
            }
        }

        selectedFigure->setPosition(pos);
        lastMove = selectedFigure->toString();
        for(size_t i=0; i<16; i++){
            if(selectedFigure->getPlayer()){ 
                if(Figures_B[i].getPosition() == pos){
                   Figures_B[i].setPosition(-1);
                    break;
                }
            }
            else{ 
                if(Figures_W[i].getPosition() == pos){
                    Figures_W[i].setPosition(-1);
                    break;
                }
            }
        }
        
        if(playerTurnCheck){
            playerTurnCheck = false;
        }

        playerTurn = !playerTurn;
        FindPossibleMoves();

    }
    
    selectedFigure = NULL;
    selected = false;
}

void ChessEngine::FindPossibleMoves(){

    Figure* tmpFigure;

    
    for(size_t x=0; x<32; x++){
        
        if(x<16)
            tmpFigure = &Figures_W[x];
        else
            tmpFigure = &Figures_B[x-16];
        tmpFigure->getPossibleMoves().clear();
        tmpFigure->getDangerMoves().clear();

        if(tmpFigure->getPosition() == -1)
            continue;

        
        switch (tmpFigure->getType())
        {
            case 'K':
                FindKingMoves(tmpFigure);
                break;
            case 'Q':
                FindQueenMoves(tmpFigure);
                break;
            case 'R':
                FindRookMoves(tmpFigure);
                break;
            case 'B':
                FindBishopMoves(tmpFigure);
                break;
            case 'N':
                FindKnightMoves(tmpFigure);
                break;
            case 'P':
                FindPawnMoves(tmpFigure);
                break;
        }
    }

    for(size_t x = 0; x < 16; x++){
        if(playerTurn){
            eraseMoves(&Figures_W[x]);
        }
        else{
            eraseMoves(&Figures_B[x]);
        }
    }

    checkMate();
    updateInfo();
    turn++;
}

void ChessEngine::eraseMoves(Figure* tmpFigure){

    if(tmpFigure->getPosition() == -1)
        return;


    if(tmpFigure->getPlayer() == playerTurn){
        
        
        
        for(size_t i = 0; i<16; i++){
            for(size_t j = 0; j<tmpFigure->getPossibleMoves().size();++j){

                if(tmpFigure->getPlayer()){ 
                    if(tmpFigure->getPossibleMoves().at(j) == Figures_W[i].getPosition()){
                        tmpFigure->getPossibleMoves().erase( tmpFigure->getPossibleMoves().begin() + j );
                        break;
                    }
                }
                else{ 
                    if(tmpFigure->getPossibleMoves().at(j) ==Figures_B[i].getPosition()){
                        tmpFigure->getPossibleMoves().erase( tmpFigure->getPossibleMoves().begin() + j );
                        break;
                    } 
                }
            }
        }

        
        if(tmpFigure->getType() == 'K'){
            for(size_t j=0; j < tmpFigure->getPossibleMoves().size(); j++){
                for(size_t i=0; i < 16; i++){
                    int o{0};
                    if(tmpFigure->getPlayer()){ 
                        for(o=0; o <Figures_B[i].getPossibleMoves().size();o++){
                            if(tmpFigure->getPossibleMoves().at(j) ==Figures_B[i].getPossibleMoves().at(o)){
                                tmpFigure->getPossibleMoves().erase( tmpFigure->getPossibleMoves().begin() + j-- );
                                break;
                            }
                        }
                        if( (o !=Figures_B[i].getPossibleMoves().size()))
                            break;;
                    }
                    else{ 
                        for(o=0; o < Figures_W[i].getPossibleMoves().size();o++){
                            if(tmpFigure->getPossibleMoves().at(j) == Figures_W[i].getPossibleMoves().at(o)){
                                tmpFigure->getPossibleMoves().erase( tmpFigure->getPossibleMoves().begin() + j-- );
                                break;
                            }
                        }
                        if( (o != Figures_W[i].getPossibleMoves().size()))
                            break;;
                    }
                }
            }
        }


        
        if(tmpFigure->getType() != 'K'){
            for(size_t i=0; i<16; i++){
                if     ( playerTurn && (Figures_B[i].getDangerMoves().size() > 1) ){
                    for(size_t j=0; j<Figures_B[i].getDangerMoves().size(); j++){
                        if(Figures_B[i].getDangerMoves().at(j) == tmpFigure->getPosition()){
                            std::vector<int> tmpMoves;
                            for(size_t x=0; x<tmpFigure->getPossibleMoves().size(); x++){
                                for(size_t k=0; k<Figures_B[i].getDangerMoves().size(); k++){
                                    if(tmpFigure->getPossibleMoves().at(x) ==Figures_B[i].getDangerMoves().at(k))
                                        tmpMoves.push_back( tmpFigure->getPossibleMoves().at(x) );
                                }
                            }
                            tmpFigure->getPossibleMoves().clear();
                            tmpFigure->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                }
                else if(!playerTurn && (Figures_W[i].getDangerMoves().size() > 1) ){
                    for(size_t j=0; j<Figures_W[i].getDangerMoves().size(); j++){
                        if(Figures_W[i].getDangerMoves().at(j) == tmpFigure->getPosition()){
                            std::vector<int> tmpMoves;
                            for(size_t x=0; x<tmpFigure->getPossibleMoves().size(); x++){
                                for(size_t k=0; k<Figures_W[i].getDangerMoves().size(); k++){
                                    if(tmpFigure->getPossibleMoves().at(x) == Figures_W[i].getDangerMoves().at(k))
                                        tmpMoves.push_back( tmpFigure->getPossibleMoves().at(x) );
                                }
                            }
                            tmpFigure->getPossibleMoves().clear();
                            tmpFigure->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                }
            }
        }


    }
}


void ChessEngine::FindKingMoves(Figure* tmpFigure){

    int piecePos{tmpFigure->getPosition()};
    tmpFigure->getPossibleMoves().clear();

    if((piecePos / 8) != 0){
        tmpFigure->getPossibleMoves().push_back(piecePos - 8);
        if((piecePos % 8) != 0)
            tmpFigure->getPossibleMoves().push_back(piecePos - 9);
        if((piecePos % 8) != 7)
            tmpFigure->getPossibleMoves().push_back(piecePos - 7);
    }
    if((piecePos / 8) != 7){
        tmpFigure->getPossibleMoves().push_back(piecePos + 8);
        if((piecePos % 8) != 0)
            tmpFigure->getPossibleMoves().push_back(piecePos + 7);
        if((piecePos % 8) != 7)
            tmpFigure->getPossibleMoves().push_back(piecePos + 9);
    }
    if((piecePos % 8) != 0)
        tmpFigure->getPossibleMoves().push_back(piecePos - 1);
    if((piecePos % 8) != 7)
        tmpFigure->getPossibleMoves().push_back(piecePos + 1);


    
}





void ChessEngine::FindQueenMoves(Figure* tmpFigure){

    int piecePos{tmpFigure->getPosition()};
    int posCounter{1};

    bool dangerMove{false};
    bool finishLoop{false};

    tmpFigure->getPossibleMoves().clear();
    tmpFigure->getDangerMoves().clear();

    
    while( ((piecePos-posCounter) >= 0) && ((piecePos/8) == ((piecePos-posCounter)/8)) ){
        
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if(  ( Figures_W[i].getPosition() == (piecePos-posCounter) ) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }
        
        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }

        }
        
        posCounter += 1;
    }


    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 1;
    while( (piecePos/8) == ((piecePos+posCounter)/8) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter) ) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }

        }
        
        posCounter += 1;
    }
    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while(((piecePos-posCounter) >= 0) && (posCounter < 64) && ((piecePos%8) == ((piecePos-posCounter)%8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos-posCounter)) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }        
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }

        }

        posCounter += 8;
    }
    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while(((piecePos+posCounter) <= 63) && (posCounter < 64) && ((piecePos%8) == ((piecePos+posCounter)%8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }
        
        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }
    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while( ((piecePos-posCounter) >= 0) && (((piecePos-posCounter) % 8) < (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos-posCounter)) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }
    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while( ((piecePos+posCounter) <= 63) && (((piecePos+posCounter) % 8) > (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }        
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }
    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while( ((piecePos-posCounter) >= 0) && (((piecePos-posCounter) % 8) > (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos-posCounter)) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }        
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }
    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while( ((piecePos+posCounter) <= 63) && (((piecePos+posCounter) % 8) < (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }        
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    if(!dangerMove) tmpFigure->getDangerMoves().clear();

    
    if(!tmpFigure->getDangerMoves().empty()){
        int collisions{0};
        for(size_t j=0; j<tmpFigure->getDangerMoves().size(); j++){
            for(size_t i=0; i<16; i++){
                if(tmpFigure->getDangerMoves().at(j) ==Figures_B[i].getPosition()){
                    collisions++;
                    if(!tmpFigure->getPlayer())
                        collisions++;
                }
                if(tmpFigure->getDangerMoves().at(j) == Figures_W[i].getPosition()){
                    collisions++;
                    if(tmpFigure->getPlayer())
                        collisions++;
                }
            }
        }

        if(collisions > 2)
            tmpFigure->getDangerMoves().clear();
    }

    tmpFigure->getDangerMoves().push_back( tmpFigure->getPosition() );
    
}





void ChessEngine::FindRookMoves(Figure* tmpFigure){

    int piecePos = tmpFigure->getPosition();
    int posCounter{1};

    bool dangerMove{false};
    bool finishLoop{false};

    tmpFigure->getPossibleMoves().clear();
    tmpFigure->getDangerMoves().clear();

    
    while( ((piecePos-posCounter) >= 0) && ((piecePos/8) == ((piecePos-posCounter)/8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos-posCounter)) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }
        
        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 1;
    }

    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 1;
    while( (piecePos/8) == ((piecePos+posCounter)/8) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }        
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }
        
        posCounter += 1;
    }

    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while(((piecePos-posCounter) >= 0) && (posCounter < 64) && ((piecePos%8) == ((piecePos-posCounter)%8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos-posCounter)) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }

    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while(((piecePos+posCounter) <= 63) && (posCounter < 64) && ((piecePos%8) == ((piecePos+posCounter)%8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }

    if(!dangerMove) tmpFigure->getDangerMoves().clear();

    
    if(!tmpFigure->getDangerMoves().empty()){
        int collisions{0};
        for(size_t j=0; j<tmpFigure->getDangerMoves().size(); j++){
            for(size_t i=0; i<16; i++){
                if(tmpFigure->getDangerMoves().at(j) ==Figures_B[i].getPosition()){
                    collisions++;
                    if(!tmpFigure->getPlayer())
                        collisions++;
                }
                if(tmpFigure->getDangerMoves().at(j) == Figures_W[i].getPosition()){
                    collisions++;
                    if(tmpFigure->getPlayer())
                        collisions++;
                }
            }
        }

        if(collisions > 2)
            tmpFigure->getDangerMoves().clear();
    }

    tmpFigure->getDangerMoves().push_back( tmpFigure->getPosition() );
    
}





void ChessEngine::FindBishopMoves(Figure* tmpFigure){

    
    int piecePos{tmpFigure->getPosition()};
    int posCounter{9};

    bool dangerMove{false};
    bool finishLoop{false};

    tmpFigure->getPossibleMoves().clear();
    tmpFigure->getDangerMoves().clear();

    
    while( ((piecePos-posCounter) >= 0) && (((piecePos-posCounter) % 8) < (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos-posCounter)) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while( ((piecePos+posCounter) <= 63) && (((piecePos+posCounter) % 8) > (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while( ((piecePos-posCounter) >= 0) && (((piecePos-posCounter) % 8) > (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos-posCounter)) || (Figures_B[i].getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    
    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while( ((piecePos+posCounter) <= 63) && (((piecePos+posCounter) % 8) < (piecePos % 8)) ){
        if(!finishLoop){
            for(size_t i = 0; i<16; i++){
                if( (Figures_W[i].getPosition() == (piecePos+posCounter)) || (Figures_B[i].getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            tmpFigure->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            
            tmpFigure->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) ==Figures_B[3].getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == Figures_W[4].getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    if(!dangerMove) tmpFigure->getDangerMoves().clear();
    
    
    if(!tmpFigure->getDangerMoves().empty()){
        int collisions{0};
        for(size_t j=0; j<tmpFigure->getDangerMoves().size(); j++){
            for(size_t i=0; i<16; i++){
                if(tmpFigure->getDangerMoves().at(j) ==Figures_B[i].getPosition()){
                    collisions++;
                    if(!tmpFigure->getPlayer())
                        collisions++;
                }
                if(tmpFigure->getDangerMoves().at(j) == Figures_W[i].getPosition()){
                    collisions++;
                    if(tmpFigure->getPlayer())
                        collisions++;
                }
            }
        }

        if(collisions > 2)
            tmpFigure->getDangerMoves().clear();
    }
    
    tmpFigure->getDangerMoves().push_back( tmpFigure->getPosition() );
    

}





void ChessEngine::FindKnightMoves(Figure* tmpFigure){

    tmpFigure->getPossibleMoves().clear();

    int piecePos{tmpFigure->getPosition()};

    if((piecePos / 8) != 0 ){
        if((piecePos % 8) >= 2 )
            tmpFigure->getPossibleMoves().push_back(piecePos - 10);
        if( (piecePos % 8) <= 5 )
            tmpFigure->getPossibleMoves().push_back(piecePos - 6);
        if((piecePos / 8) != 1){
            if((piecePos % 8) >= 1 )
                tmpFigure->getPossibleMoves().push_back(piecePos - 17);
            if((piecePos % 8) <= 6 )
                tmpFigure->getPossibleMoves().push_back(piecePos - 15);
        }
    }
    if((piecePos / 8) != 7){
        if((piecePos % 8) >= 2 )
            tmpFigure->getPossibleMoves().push_back(piecePos + 6);
        if( (piecePos % 8) <= 5 )
            tmpFigure->getPossibleMoves().push_back(piecePos + 10);
        if((piecePos / 8) != 6){
            if((piecePos % 8) >= 1 )
                tmpFigure->getPossibleMoves().push_back(piecePos + 15);
            if((piecePos % 8) <= 6 )
                tmpFigure->getPossibleMoves().push_back(piecePos + 17);
        }
    }

    tmpFigure->getDangerMoves().clear();

    for(size_t i = 0; i < tmpFigure->getPossibleMoves().size(); i++){

        if(!playerTurn){
            if( (tmpFigure->getPossibleMoves().at(i)) ==Figures_B[3].getPosition() )
                tmpFigure->getDangerMoves().push_back( tmpFigure->getPossibleMoves().at(i) );
        }
        else{
            if( (tmpFigure->getPossibleMoves().at(i)) == Figures_W[4].getPosition() )
                tmpFigure->getDangerMoves().push_back( tmpFigure->getPossibleMoves().at(i) );
        }

    }

    tmpFigure->getDangerMoves().push_back( tmpFigure->getPosition() );

}




void ChessEngine::FindPawnMoves(Figure* tmpFigure){

    
    tmpFigure->getPossibleMoves().clear();

    int piecePos{tmpFigure->getPosition()};
    
    if (tmpFigure->getPlayer()){ 
        if((piecePos / 8) != 0){
            int i{0};
            for(i = 0; i<16;++i){
                if((Figures_W[i].getPosition() == (piecePos - 8) ) || (Figures_B[i].getPosition() == (piecePos - 8) ))
                    break;
            }
            if((i == 16) && playerTurn){
                tmpFigure->getPossibleMoves().push_back(piecePos - 8);

                if(!tmpFigure->getMoved()){
                    for(i = 0; i<16;++i){
                        if((Figures_W[i].getPosition() == (piecePos - 16) ) || (Figures_B[i].getPosition() == (piecePos - 16) ))
                            break;
                    }
                    if(i == 16)
                        tmpFigure->getPossibleMoves().push_back(piecePos - 16);
                }
            }

            if((piecePos % 8) != 0){
                for(i = 0; i<16; i++){
                    if( !playerTurn || (Figures_B[i].getPosition() == (piecePos - 9)) || (Figures_W[i].getPosition() == (piecePos - 9)) ){
                        tmpFigure->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    }
                    else if((Figures_B[i].getEnPassant() == (piecePos - 9)) && (Figures_B[i].getEnPassant() != -1)){
                        tmpFigure->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    }
                }
            }

            if((piecePos % 8) != 7){
                for(i = 0; i<16; i++){
                    if( !playerTurn || (Figures_B[i].getPosition() == (piecePos - 7)) || (Figures_W[i].getPosition() == (piecePos - 7)) ){
                        tmpFigure->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    }
                    else if((Figures_B[i].getEnPassant() == (piecePos - 7)) && (Figures_B[i].getEnPassant() != -1)){
                        tmpFigure->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    }
                }                    
            }

        }
        else{ 
            tmpFigure->set('Q', tmpFigure->getPlayer(), tmpFigure->getPosition(), true);
            FindQueenMoves(tmpFigure);
            return;
        }
        

    }
    else{ 

        if((piecePos / 8) != 7){
            int i{0};
            for(i = 0; i<16;++i){
                if((Figures_W[i].getPosition() == (piecePos + 8) ) || (Figures_B[i].getPosition() == (piecePos + 8) ))
                    break;
            }
            if((i == 16) && !playerTurn){
                tmpFigure->getPossibleMoves().push_back(piecePos + 8);

                if(!tmpFigure->getMoved()){
                    for(i = 0; i<16;++i){
                        if((Figures_W[i].getPosition() == (piecePos + 16) ) || (Figures_B[i].getPosition() == (piecePos + 16) ))
                            break;
                    }
                    if(i == 16)
                        tmpFigure->getPossibleMoves().push_back(piecePos + 16);
                }
            }

            if((piecePos % 8) != 0){
                for(i = 0; i<16; i++){
                    if( playerTurn || (Figures_W[i].getPosition() == (piecePos + 7)) || (Figures_B[i].getPosition() == (piecePos + 7)) ){
                        tmpFigure->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    }
                    else if((Figures_W[i].getEnPassant() == (piecePos + 7)) && (Figures_W[i].getEnPassant() != -1)){
                        tmpFigure->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    }
                }                    
            }

            if((piecePos % 8) != 7){
                for(i = 0; i<16; i++){
                    if( playerTurn || (Figures_W[i].getPosition() == (piecePos + 9)) || (Figures_B[i].getPosition() == (piecePos + 9)) ){
                        tmpFigure->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    }
                    else if((Figures_W[i].getEnPassant() == (piecePos + 9)) && (Figures_W[i].getEnPassant() != -1)){
                        tmpFigure->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    }
                }                    
            }

        }
        else{ 
            tmpFigure->set('Q', tmpFigure->getPlayer(), tmpFigure->getPosition(), true);
            FindQueenMoves(tmpFigure);
            return;
        }
    }

    tmpFigure->getDangerMoves().clear();

    for(size_t i = 0; i < tmpFigure->getPossibleMoves().size(); i++){

        if(!playerTurn){
            if( (tmpFigure->getPossibleMoves().at(i)) ==Figures_B[3].getPosition() )
                tmpFigure->getDangerMoves().push_back( tmpFigure->getPossibleMoves().at(i) );
        }
        else{
            if( (tmpFigure->getPossibleMoves().at(i)) == Figures_W[4].getPosition() )
                tmpFigure->getDangerMoves().push_back( tmpFigure->getPossibleMoves().at(i) );
        }

    }

    tmpFigure->getDangerMoves().push_back( tmpFigure->getPosition() );

}





void ChessEngine::FindCastling(Figure* tmpFigure){

    if( playerTurnCheck || (tmpFigure->getType() != 'K') || tmpFigure->getMoved() || (tmpFigure->getPlayer() != playerTurn))
        return;

    
    if(tmpFigure->getPlayer()){ 
        
        if(!Figures_W[7].getMoved()){
            int i{0};
            for(i=0;i<16;++i){
                if((Figures_W[i].getPosition() == 61) || (Figures_W[i].getPosition() == 62)){
                    i=17;
                    break;
                }
                if((Figures_B[i].getPosition() == 61) || (Figures_B[i].getPosition() == 62)){
                    i = 17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<Figures_B[i].getPossibleMoves().size(); j++){
                        if((Figures_B[i].getPossibleMoves().at(j) == 61) || (Figures_B[i].getPossibleMoves().at(j) == 62) || (Figures_B[i].getPossibleMoves().at(j) == 60)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                
                tmpFigure->getPossibleMoves().push_back(62);
            }
        }

        if(!Figures_W[0].getMoved()){
            int i{0};
            for(i=0;i<16;++i){
                if((Figures_W[i].getPosition() == 57) || (Figures_W[i].getPosition() == 58) || (Figures_W[i].getPosition() == 59)){
                    i=17;
                    break;
                }
                if((Figures_B[i].getPosition() == 57) || (Figures_B[i].getPosition() == 58) || (Figures_B[i].getPosition() == 59)){
                    i =17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<Figures_B[i].getPossibleMoves().size(); j++){
                        if((Figures_B[i].getPossibleMoves().at(j) == 58) || (Figures_B[i].getPossibleMoves().at(j) == 59) || (Figures_B[i].getPossibleMoves().at(j) == 60)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                tmpFigure->getPossibleMoves().push_back(58);
            }
        }
    }
    else{ 
        
        if(!Figures_B[7].getMoved()){
            int i{0};
            for(i=0;i<16;++i){
                if((Figures_W[i].getPosition() == 3) || (Figures_W[i].getPosition() == 2) || (Figures_W[i].getPosition() == 1)){
                    i=17;
                    break;
                }
                if((Figures_B[i].getPosition() == 3) || (Figures_B[i].getPosition() == 2) || (Figures_B[i].getPosition() == 1)){
                    i=17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<Figures_W[i].getPossibleMoves().size(); j++){
                        if((Figures_W[i].getPossibleMoves().at(j) == 3) || (Figures_W[i].getPossibleMoves().at(j) == 2) || (Figures_W[i].getPossibleMoves().at(j) == 4)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                tmpFigure->getPossibleMoves().push_back(2);
            }
        }

        if(!Figures_B[0].getMoved()){
            int i{0};
            for(i=0;i<16;++i){
                if((Figures_W[i].getPosition() == 5) || (Figures_W[i].getPosition() == 6)){
                    i=17;
                    break;
                }
                if((Figures_B[i].getPosition() == 5) || (Figures_B[i].getPosition() == 6)){
                    i=17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<Figures_W[i].getPossibleMoves().size(); j++){
                        if((Figures_W[i].getPossibleMoves().at(j) == 5) || (Figures_W[i].getPossibleMoves().at(j) == 6) || (Figures_W[i].getPossibleMoves().at(j) == 4)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                tmpFigure->getPossibleMoves().push_back(6);
            }
        }
    }
}




void ChessEngine::checkMate(){

    Figure* check1{NULL};
    Figure* check2{NULL};


    for(size_t i = 0; i<16; i++){
        if(playerTurn){ 
            for(size_t j=0; j <Figures_B[i].getPossibleMoves().size(); j++){
                if(Figures_W[4].getPosition() ==Figures_B[i].getPossibleMoves().at(j)){
                    if(check1 == NULL){
                        playerTurnCheck = true;
                        check1 = &Figures_B[i];
                        break;
                    }
                    else if(check2 == NULL){
                        
                        check2 = &Figures_B[i];
                        break;
                    }
                }
            }
        }
        else{ 
            for(size_t j=0; j < Figures_W[i].getPossibleMoves().size(); j++){
                if(Figures_B[3].getPosition() == Figures_W[i].getPossibleMoves().at(j)){
                    if(check1 == NULL){
                        playerTurnCheck = true;
                        check1 = &Figures_W[i];
                        break;
                    }
                    else if(check2 == NULL){
                        check2 = &Figures_W[i];
                        break;
                    }
                }
            }
        }

        if(check2 != NULL)
            break;
    }


    if(playerTurnCheck){
        if(check2 != NULL){
            if(playerTurn)
                for(size_t i=0; i<16; i++)
                    if(Figures_W[i].getType() != 'K')
                        Figures_W[i].getPossibleMoves().clear();
            else
                for(size_t i=0; i<16; i++)
                    if(Figures_B[i].getType() != 'K')
                       Figures_B[i].getPossibleMoves().clear();
        }
        else{ 

            for(size_t j=0; j<16; j++){
                std::vector<int> tmpMoves;

                if(playerTurn){
                    if(Figures_W[j].getType() == 'K')
                        continue;
                    for(size_t o = 0; o < Figures_W[j].getPossibleMoves().size(); o++){
                        if(Figures_W[j].getPossibleMoves().empty())
                            break;
                        for(size_t i=0; i < check1->getDangerMoves().size(); i++){
                            if((Figures_W[j].getPossibleMoves().at(o) == check1->getDangerMoves().at(i)) ){
                                tmpMoves.push_back( Figures_W[j].getPossibleMoves().at(o) );
                                break;
                            }
                        }
                    }

                    Figures_W[j].getPossibleMoves().clear();
                    Figures_W[j].getPossibleMoves() = tmpMoves;
                }
                else{ 
                    if(Figures_B[j].getType() == 'K')
                        continue;
                    for(size_t o = 0; o <Figures_B[j].getPossibleMoves().size(); o++){
                        if(Figures_B[j].getPossibleMoves().empty())
                            break;
                        for(size_t i=0; i < check1->getDangerMoves().size(); i++){ 
                            if((Figures_B[j].getPossibleMoves().at(o) == check1->getDangerMoves().at(i)) ){
                                tmpMoves.push_back(Figures_B[j].getPossibleMoves().at(o) );
                                break;
                            }
                        }
                    }
                   Figures_B[j].getPossibleMoves().clear();
                   Figures_B[j].getPossibleMoves() = tmpMoves;
                }
            }
        }


        Figure* curKing;
        if(playerTurn){
            curKing = &Figures_W[4];
        }
        else{
            curKing = &Figures_B[3];
        }
        if(check1 != NULL){
            if((check1->getType() == 'Q') || (check1->getType() == 'R' || (check1->getType() == 'B'))){
                int checkPos{check1->getPosition()};

                if((check1->getType() == 'Q') || (check1->getType() == 'R')){
                    for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                        if(curKing->getPossibleMoves().at(i) != checkPos){
                            if     ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            else if((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                    if(curKing->getPossibleMoves().at(i) != checkPos){
                        if((curKing->getPosition()%8) < (checkPos%8)){ 
                            if((curKing->getPosition()/8) < (checkPos/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                        else if((checkPos%8) < (curKing->getPosition()%8) ){ 
                            if((curKing->getPosition()/8) < (checkPos/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }
        if(check2 != NULL){
            if((check2->getType() == 'Q') || (check2->getType() == 'R' || (check2->getType() == 'B'))){
                int checkPos{check2->getPosition()};

                if((check2->getType() == 'Q') || (check2->getType() == 'R')){
                    for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                        if(curKing->getPossibleMoves().at(i) != checkPos){
                            if     ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            else if((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                    if(curKing->getPossibleMoves().at(i) != checkPos){
                        if((curKing->getPosition()%8) < (checkPos%8)){ 
                            if((curKing->getPosition()/8) < (checkPos/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                        else if((checkPos%8) < (curKing->getPosition()%8) ){ 
                            if((curKing->getPosition()/8) < (checkPos/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ 
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }

    }
    else{
        FindCastling(&Figures_W[4]);
        FindCastling(&Figures_B[3]);
    }

    
    int i{0};
    for(i=0; i<16; i++){
        if(playerTurn){
            if(!Figures_W[i].getPossibleMoves().empty())
                break;
        }
        else{
            if(!Figures_B[i].getPossibleMoves().empty())
                break;
        }
    }
    if(i==16){ 
        mate = true;
    }

}