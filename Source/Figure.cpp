#include "Headers/Figure.h"
void Figure::set(char type, bool player, int pos, bool moved){
    setType(type);
    setPlayer(player);
    setPosition(pos); 
    setMoved(moved); 
}

std::string Figure::toString(){
    std::string str;

    switch (m_type)
    {
        case 'K':
            str += "K";
            break;
        case 'Q':
            str += "Q";
            break;
        case 'R':
            str += "R";
            break;
        case 'B':
            str += "B";
            break;
        case 'N':
            str += "N";
            break;
        case 'P':
            str += "";
            break;
    }
    str += (char)((m_lastpos%8)+97);
    str += std::to_string(abs((m_lastpos / 8) - 8));
    str += (char)((m_position%8)+97);
    str += std::to_string(abs((m_position/8)-8));
    if (str.compare("Ke1g1")==0 || str.compare("Ke8g8")==0)str = "0-0";
    if (str.compare("Ke1c1")==0 || str.compare("Ke8c8")==0)str = "0-0-0";

    return str;

}

void Figure::move(){
    if(m_position<=-1 || 64<=m_position){
        m_position = -1;
        m_sprite.setPosition(Vector2f((m_position % 8) * 64.f + 32.f, (m_position / 8) * 64.f + 32.f));
        possibleMoves.clear();
        m_moved = true;
    }
    else{
        m_sprite.setPosition(Vector2f((m_position % 8) * 64.f + 32.f, (m_position / 8) * 64.f + 32.f));
        m_moved = true;
    }
    return;
}

void Figure::set(){
    m_sprite = Sprite();
    switch (m_type)
    {
        case 'K':
            m_sprite.setTexture(m_player ? FigureTextures::whiteKing : FigureTextures::blackKing);
            break;
        case 'Q':
            m_sprite.setTexture(m_player ? FigureTextures::whiteQueen : FigureTextures::blackQueen);
            break;
        case 'R':
            m_sprite.setTexture(m_player ? FigureTextures::whiteRook : FigureTextures::blackRook);
            break;
        case 'B':
            m_sprite.setTexture(m_player ? FigureTextures::whiteBishop : FigureTextures::blackBishop);
            break;
        case 'N':
            m_sprite.setTexture(m_player ? FigureTextures::whiteKnight : FigureTextures::blackKnight);
            break;
        case 'P':
            m_sprite.setTexture(m_player ? FigureTextures::whitePawn : FigureTextures::blackPawn);
            break;
    }
    m_sprite.setOrigin(Vector2f(m_sprite.getTexture()->getSize().x/2 , m_sprite.getTexture()->getSize().y/2));
    m_sprite.setScale(Vector2f(0.475f,0.475f));
}