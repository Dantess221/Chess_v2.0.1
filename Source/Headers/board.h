#ifndef _BOARD_H
#define _BOARD_H
#define NOMINMAX

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
using namespace sf;

class Board : public Drawable{

public:

    Board(Color col1 = Color::White, Color col2 = Color::Black);
    
    
    void load(Color col1 = Color::White, Color col2 = Color::Black);

private:

    std::array<RectangleShape, 64> boardSetting;
    
    
    virtual void draw(RenderTarget& e, RenderStates states) const;

};

#endif