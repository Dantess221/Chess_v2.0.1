#define NOMINMAX

#include <iostream>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "Headers/ChessEngine.h"
#include "Utils/ChessBot/Position.h"
#include "Utils/ChessBot/UI.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

    ChessEngine ChessGame(Color(240,217,181,255),Color(181,136,99,255));

    ContextSettings settings;
    settings.antialiasingLevel = 3000;
    settings.depthBits = 2;

    RenderWindow Render(VideoMode(768,512), "Chess by Nikita Bylym", Style::Titlebar | Style::Close, settings);

    Render.setVerticalSyncEnabled(true);

    //Position* position = new Position();
    //UI* opp = new UI(position);

    while(Render.isOpen()){
        
        Event e;

        while(Render.pollEvent(e)){

            if (e.type == Event::Closed) {
                Render.close();
            }
            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
            {
                if ((0 <= e.mouseButton.x) && (e.mouseButton.x <= 512) && (0 <= e.mouseButton.y) && (e.mouseButton.y <= 512)) {
                    unsigned int Button_Pos{ (e.mouseButton.x / 64) + ((e.mouseButton.y / 64) * (8 * (512 / Render.getSize().y))) };

                    if (!ChessGame.getSelected())
                        ChessGame.Select(Button_Pos);
                    else
                        ChessGame.Moving(Button_Pos);

                }
                else if ((545 <= e.mouseButton.x) && (e.mouseButton.x <= 735) && (10 <= e.mouseButton.y) && (e.mouseButton.y <= 50)) {
                    ChessGame.restart();
                }

            }
        }

        Render.draw(ChessGame);
        Render.display();
    }
}