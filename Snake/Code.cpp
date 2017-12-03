#include <SFML/Graphics.hpp>
#include <ctime>
#include <sstream>

bool game = false;
std::stringstream ss;
int snakelength;
sf::Text text;

void endgame() {
    game = false;
    ss << snakelength;
    text.setString("Your Score: " + ss.str());
}

int main() {

    sf::RenderWindow window(sf::VideoMode(400, 300), "Snake");

    bool start = false;
    std::string score;
    int snakex[200];
    int snakey[200];
    int d;
    int speed;

    sf::RectangleShape snake(sf::Vector2f(20,20));
    snake.setFillColor(sf::Color::Blue);
    snake.setOrigin(10,10);

    sf::RectangleShape bite(sf::Vector2f(20,20));
    bite.setFillColor(sf::Color::Green);
    bite.setOrigin(10,10);

    sf::Font font;
    font.loadFromFile("font.ttf");

    text.setFillColor(sf::Color::Blue);
    text.setCharacterSize(38);
    text.setPosition(20,20);
    text.setFont(font);

    srand(time(0));
    int bitex;
    int bitey = 0;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

        }

        if(game == true && start == true) {

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                d = 1;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                d = 2;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                d = 3;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                d = 4;
            }

            if(bitex == snakex[snakelength-1] && bitey == snakey[snakelength-1] && (clock()-speed)>65) {
                snakelength++;
                if(d == 1) {
                    snakey[snakelength-1] = snakey[snakelength-2] - 20;
                    snakex[snakelength-1] = snakex[snakelength-2];
                } else if(d == 2) {
                    snakex[snakelength-1] = snakex[snakelength-2] + 20;
                    snakey[snakelength-1] = snakey[snakelength-2];
                } else if(d == 3) {
                    snakey[snakelength-1] = snakey[snakelength-2] + 20;
                    snakex[snakelength-1] = snakex[snakelength-2];
                } else if(d == 4) {
                    snakex[snakelength-1] = snakex[snakelength-2] - 20;
                    snakey[snakelength-1] = snakey[snakelength-2];
                }

                bitex = 0;
                speed = clock();

                while(bitex == 0) {
                    bitex = (rand()%20)*20+10;
                    bitey = (rand()%15)*20+10;
                    for(int b = 0; b<snakelength; b++) {
                        if(bitex == snakex[b] && bitey == snakey[b]) {
                            bitex = 0;
                        }
                    }
                }

            } else if((clock()-speed)>65) {
                for(int a = 0; a<snakelength-1; a++) {
                    snakex[a] = snakex[a+1];
                    snakey[a] = snakey[a+1];
                }
                if(d == 1) {
                    snakey[snakelength-1] = snakey[snakelength-1] - 20;
                } else if(d == 2) {
                    snakex[snakelength-1] = snakex[snakelength-1] + 20;
                } else if(d == 3) {
                    snakey[snakelength-1] = snakey[snakelength-1] + 20;
                } else if(d == 4) {
                    snakex[snakelength-1] = snakex[snakelength-1] - 20;
                }

                speed = clock();
            }
            bite.setPosition(bitex,bitey);

            window.clear();
            window.draw(bite);
            for(int i = 0; i<snakelength; i++) {
                snake.setPosition(snakex[i],snakey[i]);
                window.draw(snake);
            }
            window.display();

            if(snakex[snakelength-1] == -10 || snakex[snakelength-1] == 410 || snakey[snakelength-1] == -10 || snakey[snakelength-1] == 310) {
                endgame();
            }
            for(int z=0; z<snakelength-1; z++) {
                if(snakex[snakelength-1] == snakex[z] && snakey[snakelength-1] == snakey[z]) {
                    endgame();
                }

            }
        } else {
            if(start == false) {
                text.setString("Press Space to Start\nArrow Keys to Move");
            }
            window.clear();
            window.draw(text);
            window.display();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                game = true;
                start = true;
                ss.str("");
                snakelength = 5;
                d = 2;
                for(int x = 0; x<snakelength; x++) {
                    snakex[x] = 10+20*x;
                    snakey[x] = 150;
                }
                speed = clock();
            }

            if(game == true) {
                bitex = 0;
                while(bitex == 0) {
                    bitex = (rand()%20)*20+10;
                    bitey = (rand()%15)*20+10;
                    for(int b = 0; b<snakelength; b++) {
                        if(bitex == snakex[b] && bitey == snakey[b]) {
                            bitex = 0;
                        }
                    }
                }
            }

        }
    }
}