#ifndef _FIGURE_TEXTURES_H
#define _FIGURE_TEXTURES_H
#define NOMINMAX

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace sf;

class FigureTextures{
public:
    static Texture blackKing;
    static Texture blackQueen;
    static Texture blackRook;
    static Texture blackKnight;
    static Texture blackBishop;
    static Texture blackPawn;

    static Texture whiteKing;
    static Texture whiteQueen;
    static Texture whiteRook;
    static Texture whiteKnight;
    static Texture whiteBishop;
    static Texture whitePawn;

    static Texture loadTexture(std::string str);
};

#endif