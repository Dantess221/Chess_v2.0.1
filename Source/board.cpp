#include "Headers/board.h"

Board::Board(Color col1, Color col2){
    load(col1,col2);
}


void Board::load(Color col1, Color col2){
    for(size_t i=0; i<8;++i){

        bool tmpColor = ((i % 2)==0)?true:false;

        for(size_t j=0; j<8;++j){

            boardSetting[j + (i * 8)].setPosition(Vector2f( j*64.f , i*64.f ));
            boardSetting[j + (i * 8)].setSize(Vector2f(64.f, 64.f));
            boardSetting[j + (i * 8)].setFillColor(tmpColor ? col1 : col2);
            
            tmpColor = !tmpColor;
        }
    }
}


void Board::draw(RenderTarget& e, RenderStates states) const{
    for(size_t i=0;i<64;++i){
        e.draw(boardSetting[i]);
    }
}