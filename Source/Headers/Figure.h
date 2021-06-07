#ifndef _FIGURE_H
#define _FIGURE_H
#define NOMINMAX

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Textures.h"
using namespace sf;
class Figure : public Drawable{

public:

    Figure(char type='P', bool player=true, int pos=-1, bool moved=false)
    : m_type{type}, m_player{player},
        m_position{ -1 }, m_moved{ true }, enPassant{ -1 }
    { }

    void set(char type, bool player, int pos, bool moved=false);

    void setType(char ch){m_type = ch; set();}
    char getType()       {return m_type;}

    void setPlayer(bool bl){m_player = bl; set();}
    bool getPlayer()       {return m_player;}

    void setPosition(int pos) {
        m_lastpos = m_position;
        m_position = pos; 
        move();
    }
    int getPosition()        {return m_position;}

    void setMoved(bool moved){m_moved = moved;}
    bool getMoved()           {return m_moved;}

    void setEnPassant(int x){enPassant = x;}
    int getEnPassant()      {return enPassant;}

    std::vector<int>& getPossibleMoves(){return possibleMoves;}
    std::vector<int>& getDangerMoves(){return dangerMoves;}

    std::string toString();

private:
    Sprite m_sprite;
    std::vector<int> possibleMoves;
    std::vector<int> dangerMoves;

    char m_type; 
    bool m_player; 
    int m_position; 
    int m_lastpos;
    int enPassant;
    bool m_moved;

    void set();
    void move();

    virtual void draw(RenderTarget& e, RenderStates states) const
    {   e.draw(m_sprite);  }
};

#endif