#ifndef _CHESSChessEngine_H
#define _CHESSChessEngine_H
#define NOMINMAX

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "board.h"
#include "Figure.h"
using namespace sf;

class ChessEngine: public Drawable{
private:
    Board board;
    std::array<Figure, 16> Figures_W;
    std::array<Figure, 16>Figures_B;
    Figure* selectedFigure;
    std::vector<RectangleShape> possibleMovesSquares;
    std::string lastMove;

    RectangleShape infoRestart;


    Font font;
    Text textRestart;
    Text textTurn;
    Text textSituation;
    Text textLastMove;

    bool selected;
    bool playerTurn; 
    bool playerTurnCheck;
    bool mate;
    int turn;

    void createMovesSquares();

    void FindPossibleMoves();
    void FindKingMoves(Figure* tmpFigure);
    void FindQueenMoves(Figure* tmpFigure);
    void FindRookMoves(Figure* tmpFigure);
    void FindBishopMoves(Figure* tmpFigure);
    void FindKnightMoves(Figure* tmpFigure);
    void FindPawnMoves(Figure* tmpFigure);
    void FindCastling(Figure* tmpFigure);

    void eraseMoves(Figure* tmpFigure);

    void checkMate();

    void updateInfo();

    virtual void draw(RenderTarget& e, RenderStates states) const;

public:

    bool Side;

    ChessEngine(Color bordCol1, Color bordCol2);

    bool getSelected(){return selected;}

    bool getMate(){return mate;}

    bool Select(int pos);

    void Moving(int pos);

    void restart();
    


};


#endif