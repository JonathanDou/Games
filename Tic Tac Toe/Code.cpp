#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cmath>


sf::RenderWindow window(sf::VideoMode(330, 330), "Game");
sf::Event event;
sf::Texture nulltext;
sf::Texture xtext;
sf::Texture otext;
sf::Sprite null;
sf::Sprite x;
sf::Sprite o;
sf::Mouse mouse;

bool turn = true;
bool win = false;
std::string box[10][10];
int a;
int b;
int c = 0;

void load() {
    for(int y=0; y<3; y++) {
        for(int z=0; z<3; z++) {
            box[y][z] = c++;
        }
    }
    nulltext.loadFromFile("empty.png");
    xtext.loadFromFile("x.png");
    otext.loadFromFile("o.png");
    null.setTexture(nulltext);
    x.setTexture(xtext);
    o.setTexture(otext);
    c = 0;
}

void restart() {
    for(int y=0; y<3; y++) {
        for(int z=0; z<3; z++) {
            box[y][z] = c++;
        }
    }
    turn = true;
    win = false;
    c = 0;
}

void click() {
    a = floor((mouse.getPosition(window).x)/110);
    b = floor((mouse.getPosition(window).y)/110);
    if(box[a][b] != "o" && box[a][b] != "x") {
        if(turn == true) {
            box[a][b] = "o";
            turn = false;
        } else {
            box[a][b] = "x";
            turn = true;
        }
        c++;
    }
}

void check() {
    for(int z=0; z<3; z++) {
        if((box[z][0] == box[z][1]) && (box[z][0] == box[z][2])) {
            std::cout << box[z][0] << " wins!" << std::endl;
            Sleep(1000);
            restart();
        } else if((box[0][z] == box[1][z]) && (box[0][z] == box[2][z])) {
            std::cout << box[0][z] << " wins!" << std::endl;
            Sleep(1000);
            restart();
        } else if((box[0][0] == box[1][1]) && (box[0][0] == box[2][2])) {
            std::cout << box[1][1] << " wins!" << std::endl;
            Sleep(1000);
            restart();
        } else if((box[2][0] == box[1][1]) && (box[0][2] == box[2][0])) {
            std::cout << box[1][1] << " wins!" << std::endl;
            Sleep(1000);
            restart();
        } else if(c == 9) {
            std::cout << "tie game!" << std::endl;
            Sleep(1000);
            restart();
        }
    }
}

void draw() {
    window.clear();

    for(int n=0; n<3; n++) {
        for(int i=0; i<3; i++) {
            if(box[n][i] == "o") {
                o.setPosition((n)*110,(i)*110);
                window.draw(o);
            } else if(box[n][i] == "x") {
                x.setPosition((n)*110,(i)*110);
                window.draw(x);
            } else {
                null.setPosition((n)*110,(i)*110);
                window.draw(null);
            }
        }
    }

    window.display();
}

int main() {
    load();

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            click();
            if(win == false) {
                draw();
                check();
            }
        }

        draw();
    }
}
