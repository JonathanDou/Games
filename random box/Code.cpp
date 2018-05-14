#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <iostream>
#include <windows.h>

sf::RenderWindow window(sf::VideoMode(700, 500), "Random Box");
sf::Event event;

sf::Clock tanktimer;
sf::Clock falltimer;
sf::Clock jtimer;
sf::Clock btimer;
sf::Clock atimer;
sf::Clock ctimer;
sf::Clock etimer;
sf::Clock stimer;

sf::CircleShape tank;
sf::CircleShape bullet;
sf::CircleShape cenemy;
sf::CircleShape tenemy;

sf::RectangleShape gun;
sf::RectangleShape senemy;

sf::Text text;
sf::Text gametext;
sf::Text controls;

sf::Font font;
sf::FloatRect TextRect;

std::stringstream ss;
std::string scoretext;

int score;
bool start = false;

int x = 350;
int y = 490;
int bulletspeed = 8;
int tankspeed = 4;
double fallspeed = 7;
bool direction = true;
bool bfall = false;
bool jumpr = true;

bool gameover = false;

int bulletcount = 0;
int maxbullets = 5;

int jump = 0;
int maxjump = 3;

int bulletx[5];
int bullety[5];
bool bdirection[5];
bool bullets[5];

bool cenemyalive[100];
int cenemycount = 0;
int cenemyx[100];
int cenemyy[100];
int cenemyspeed[100];
int clife[100];
int cmax = 10;

bool senemyalive[100];
int senemycount = 0;
int senemyx[100];
int senemyy[100];
double senemyspeed[100];
int slife[100];
int smax = 5;

void load() {
    font.loadFromFile("font.ttf");

    text.setString("0");
    text.setFillColor(sf::Color::Green);
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(10,10);

    gametext.setFillColor(sf::Color::Green);
    gametext.setFont(font);
    gametext.setCharacterSize(50);
    gametext.setPosition(250,200);

    srand(time(0));

    controls.setString("Controls: Arrow Keys to Move, Z to Jump, X to Shoot");
    controls.setCharacterSize(20);
    controls.setFillColor(sf::Color::Green);
    controls.setFont(font);
    controls.setPosition(10,470);

    tank.setRadius(10);
    tank.setOrigin(10,10);
    tank.setFillColor(sf::Color::Blue);

    gun.setSize(sf::Vector2f(15,8));
    gun.setOrigin(0,4);
    gun.setFillColor(sf::Color::Green);

    bullet.setFillColor(sf::Color::Red);
    bullet.setRadius(5);
    bullet.setOrigin(5,5);

    cenemy.setFillColor(sf::Color::Yellow);
    cenemy.setRadius(20);
    cenemy.setOrigin(20,20);

    senemy.setFillColor(sf::Color::Green);
    senemy.setSize(sf::Vector2f(40,40));
    senemy.setOrigin(20,20);

    tenemy.setPointCount(3);
    tenemy.setRadius(20);
    tenemy.setOrigin(20,20);
    tenemy.setFillColor(sf::Color::Magenta);

    for(int i=0; i<100; i++) {
        cenemyalive[i] = false;
        cenemyspeed[i] = 2;

        senemyalive[i] = false;
    }
}

void tankmove() {
    if(tanktimer.getElapsedTime().asMilliseconds() > 10) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x = x - tankspeed;
            if(direction == true) {
                gun.rotate(180);
                direction = false;
            }
            tanktimer.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x = x + tankspeed;
            if(direction == false) {
                gun.rotate(180);
                direction = true;
            }
            tanktimer.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            if(jump != maxjump && jumpr == true && jtimer.getElapsedTime().asMilliseconds() > 100) {
                jump++;
                fallspeed = 7;
                bfall = true;
                jumpr = false;
                jtimer.restart();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if(bulletcount != maxbullets && btimer.getElapsedTime().asMilliseconds() > 200) {
                for(int n=0; n<maxbullets; n++) {
                    if(bullets[n] == false) {
                        bullets[n] = true;
                        bulletx[n] = x;
                        bullety[n] = y;
                        bdirection[n] = direction;
                        bulletcount++;
                        btimer.restart();
                        break;
                    }
                }
            }
        }
    }
}

void bulletmove() {
    if(atimer.getElapsedTime().asMilliseconds() > 10) {
        for(int i=0; i<maxbullets; i++) {
            if(bullets[i] == true) {
                if(bdirection[i] == true) {
                    bulletx[i] = bulletx[i] + bulletspeed;
                } else {
                    bulletx[i] = bulletx[i] - bulletspeed;
                }
                if(bulletx[i] > 700 || bulletx[i] < 0) {
                    bullets[i] = false;
                    bulletcount--;
                }
                for(int n=0; n<cmax; n++) {
                    if((cenemyalive[n] == true) && (abs(bulletx[i] - cenemyx[n]) < 15) && (abs(bullety[i] - cenemyy[n]) < 15) && bullets[i] == true) {
                        clife[n]--;
                        bullets[i] = false;
                        bulletcount--;
                        if(clife[n] == 0) {
                            cenemyalive[n] = false;
                            cenemycount--;
                            score++;
                        }
                        break;
                    }
                }
                for(int n=0; n<cmax; n++) {
                    if((senemyalive[n] == true) && (abs(bulletx[i] - senemyx[n]) < 20) && (abs(bullety[i] - senemyy[n]) < 20) && bullets[i] == true) {
                        slife[n]--;
                        bullets[i] = false;
                        bulletcount--;
                        if(slife[n] == 0) {
                            senemyalive[n] = false;
                            senemycount--;
                            score = score + 2;
                        }
                        break;
                    }
                }
            }
        }
        atimer.restart();
    }
}

void enemymove() {
    if(etimer.getElapsedTime().asMilliseconds() > 10) {
        for(int c=0; c<cmax; c++) {
            if(cenemyalive[c] == true) {
                if(cenemyx[c] > x) {
                    cenemyx[c] = cenemyx[c] - cenemyspeed[c];
                } else {
                    cenemyx[c] = cenemyx[c] + cenemyspeed[c];
                }
                if(abs(x-cenemyx[c]) < 25 && abs(y-cenemyy[c]) < 25) {
                    gameover = true;
                    Sleep(500);
                }
            }
        }

        for(int d=0; d<smax; d++) {
            if(senemyalive[d] == true) {
                if(senemyy[d] < 480) {
                    senemyy[d] = senemyy[d] + senemyspeed[d];
                    senemyspeed[d] = senemyspeed[d] + 0.2;
                    if(senemyy[d] > 480) {
                        senemyy[d] = 480;
                        senemyspeed[d] = 0;
                    }
                } else {
                    if(senemyx[d] > x) {
                        senemyspeed[d] = senemyspeed[d] - 0.2;
                    } else {
                        senemyspeed[d] = senemyspeed[d] + 0.2;
                    }
                    senemyx[d] = senemyx[d] + senemyspeed[d];
                }
                if(abs(x-senemyx[d]) < 30 && abs(y-senemyy[d]) < 30) {
                    gameover = true;
                    Sleep(500);
                }
            }
        }

        std::cout << senemycount;
        etimer.restart();

    }
}

void fall() {
    if(falltimer.getElapsedTime().asMilliseconds() > 5) {
        y = y - fallspeed;
        if(y > 490) {
            jump = 0;
            fallspeed = 7;
            y = 490;
            bfall = false;
        }
        fallspeed = fallspeed - 0.2;
        falltimer.restart();
    }
}

void cspawn() {
    if(ctimer.getElapsedTime().asMilliseconds() > 1000 && cenemycount != cmax) {
        for(int a=0; a<cmax; a++) {
            if(cenemyalive[a] == false) {
                if(rand()%2 == 0) {
                    cenemyx[a] = -20;
                    cenemyy[a] = 480;
                } else {
                    cenemyx[a] = 720;
                    cenemyy[a] = 480;
                }

                cenemyalive[a] = true;
                clife[a] = 1;
                cenemycount++;
                ctimer.restart();
                break;
            }
        }
    }
}

void sspawn() {
    if(stimer.getElapsedTime().asMilliseconds() > 3000 && senemycount != smax && score > 10) {
        for(int b=0; b<smax; b++) {
            if(senemyalive[b] == false) {
                senemyx[b] = rand()%660+20;
                senemyy[b] = -20;

                senemyalive[b] = true;
                slife[b] = 2;
                senemyspeed[b] = 0;
                senemycount++;
                stimer.restart();
                break;
            }
        }
    }
}

void gameend() {
    ss << score;
    ss >> scoretext;
    gametext.setString("Score: " + scoretext);
    ss.str("");
    ss.clear();

    TextRect = gametext.getLocalBounds();

    gametext.setOrigin(TextRect.width/2, TextRect.height/2);
    gametext.setPosition(350,230);

    window.clear();
    window.draw(gametext);
    window.display();
}

void draw() {

    ss << score;
    ss >> scoretext;
    text.setString(scoretext);
    ss.str("");
    ss.clear();


    tank.setPosition(x,y);
    gun.setPosition(x,y);
    window.clear();

    for(int z = 0; z<maxbullets; z++) {
        if(bullets[z] == true) {
            bullet.setPosition(bulletx[z],bullety[z]);
            window.draw(bullet);
        }
    }

    for(int i=0; i<cmax; i++) {
        if(cenemyalive[i] == true) {
            cenemy.setPosition(cenemyx[i], cenemyy[i]);
            window.draw(cenemy);
        }
    }

    for(int i=0; i<smax; i++) {
        if(senemyalive[i] == true) {
            senemy.setPosition(senemyx[i], senemyy[i]);
            window.draw(senemy);
        }
    }

    window.draw(text);
    window.draw(gun);
    window.draw(tank);
    window.display();
}

int main() {

     load();

     while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z) {
                jumpr = true;
            }
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                start = false;
            }
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                if(gameover == true || start == false) {
                    gameover = false;

                    for(int i=0; i<100; i++) {
                        cenemyalive[i] = false;
                        cenemyspeed[i] = 2;

                        senemyalive[i] = false;
                    }

                    x = 350;
                    y = 490;

                    score = 0;
                    cenemycount = 0;
                    senemycount = 0;

                    start = true;
                }
            }
        }

        if(start == true) {
            if(gameover == false) {
                if(bfall == true) {
                    fall();
                }
                tankmove();
                bulletmove();
                cspawn();
                sspawn();
                enemymove();
                draw();
            } else {
                gameend();
            }
        } else {
            gametext.setString("Press Space To Start");
            TextRect = gametext.getLocalBounds();

            gametext.setOrigin(TextRect.width/2, TextRect.height/2);
            gametext.setPosition(350,230);

            window.clear();
            window.draw(gametext);
            window.draw(controls);
            window.display();
        }
     }
}
