#include "Headers/Textures.h"

Texture FigureTextures::loadTexture(std::string str){
    Texture tmp;
    if (!tmp.loadFromFile(str))
        std::cout << "Error loading file\n";
    return tmp;
}

Texture FigureTextures::blackKing = FigureTextures::loadTexture("Textures/KingBlack.png");
Texture FigureTextures::blackQueen = FigureTextures::loadTexture("Textures/QueenBlack.png");
Texture FigureTextures::blackRook = FigureTextures::loadTexture("Textures/RookBlack.png");
Texture FigureTextures::blackKnight = FigureTextures::loadTexture("Textures/KnightBlack.png");
Texture FigureTextures::blackBishop = FigureTextures::loadTexture("Textures/BishopBlack.png");
Texture FigureTextures::blackPawn = FigureTextures::loadTexture("Textures/PawnBlack.png");

Texture FigureTextures::whiteKing = FigureTextures::loadTexture("Textures/KingWhite.png");
Texture FigureTextures::whiteQueen = FigureTextures::loadTexture("Textures/QueenWhite.png");
Texture FigureTextures::whiteRook = FigureTextures::loadTexture("Textures/RookWhite.png");
Texture FigureTextures::whiteKnight = FigureTextures::loadTexture("Textures/KnightWhite.png");
Texture FigureTextures::whiteBishop = FigureTextures::loadTexture("Textures/BishopWhite.png");
Texture FigureTextures::whitePawn = FigureTextures::loadTexture("Textures/PawnWhite.png");
