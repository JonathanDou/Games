#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <fstream>

sf::RenderWindow window(sf::VideoMode(700, 500), "Random Box");
sf::Event event;

std::fstream file;

sf::Clock sbosstimer;
sf::Clock cbosstimer;
sf::Clock tanktimer;
sf::Clock falltimer;
sf::Clock jtimer;
sf::Clock btimer;
sf::Clock atimer;
sf::Clock ctimer;
sf::Clock etimer;
sf::Clock stimer;
sf::Clock ttimer;

sf::CircleShape tank;
sf::CircleShape bullet;
sf::CircleShape cenemy;
sf::CircleShape tenemy;

sf::CircleShape cboss;

sf::RectangleShape gun;
sf::RectangleShape senemy;

sf::RectangleShape sboss;

sf::Text text;
sf::Text gametext;
sf::Text high;
sf::Text controls;

sf::Font font;
sf::FloatRect TextRect;

std::stringstream ss;
std::string scoretext;
std::string hightext;

bool cbossalive = false;
bool cbossfight = false;
double cbossspeed = 0;
int cbosshp;
double cbossx;
double cbossy = 400;

bool sbossalive = false;
bool sbossfight = false;
double sbossspeedx = 0;
double sbossspeedy = 0;

int sbosshp;
double sbossx;
double sbossy = 450;

int cspawntime = 1000;
int sspawntime = 3000;
int tspawntime = 7;

int score;
bool start = false;

double angle;

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
int maxjump = 2;

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

bool tenemyalive[100];
int tenemycount = 0;
int tenemyx[100];
int tenemyy[100];
double tenemyspeed[100];
int tlife[100];
int tmax = 3;
int highscore;

void load() {
    font.loadFromFile("font.ttf");

    text.setString("0");
    text.setFillColor(sf::Color::Green);
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(10,10);

    high.setFillColor(sf::Color::Green);
    high.setFont(font);
    high.setCharacterSize(20);
    high.setPosition(670,10);

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
    tenemy.setRadius(60);
    tenemy.setOrigin(60,60);
    tenemy.setFillColor(sf::Color::Magenta);

    cboss.setFillColor(sf::Color::Yellow);
    cboss.setRadius(100);
    cboss.setOrigin(100,100);

    sboss.setFillColor(sf::Color::Green);
    sboss.setSize(sf::Vector2f(100,100));
    sboss.setOrigin(50,50);

    for(int i=0; i<100; i++) {
        cenemyalive[i] = false;
        cenemyspeed[i] = 2;

        senemyalive[i] = false;

        tenemyalive[i] = false;
        tenemyspeed[i] = 2;
    }
}

void tankmove() {
    if(tanktimer.getElapsedTime().asMilliseconds() > 10) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (x > 10)) {
            x = x - tankspeed;
            if(direction == true) {
                gun.rotate(180);
                direction = false;
            }
            tanktimer.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (x < 690)) {
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
            if(bulletcount != maxbullets && btimer.getElapsedTime().asMilliseconds() > 150) {
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
                    if((cenemyalive[n] == true) && (abs(bulletx[i] - cenemyx[n]) < 20) && (abs(bullety[i] - cenemyy[n]) < 20) && bullets[i] == true) {
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
                for(int n=0; n<smax; n++) {
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
                for(int n=0; n<tmax; n++) {
                    if((tenemyalive[n] == true) && (abs(bulletx[i] - tenemyx[n]) < 35) && ((bullety[i] - tenemyy[n]) < 35) && ((tenemyy[n] - bullety[i]) < 55) && bullets[i] == true) {
                        tlife[n]--;
                        bullets[i] = false;
                        bulletcount--;
                        if(tlife[n] == 0) {
                            tenemyalive[n] = false;
                            tenemycount--;
                            score = score + 5;
                        }
                        break;
                    }
                }
                if(cbossalive == true) {
                    if((abs(bulletx[i] - cbossx) < 60) && (abs(bullety[i] - cbossy) < 100) && bullets[i] == true && tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        cbosshp = cbosshp - 1;
                        bullets[i] = false;
                        bulletcount--;
                        if(cbosshp == 0) {
                            cbossalive = false;
                            score = score + 50;
                            ttimer.restart();
                            stimer.restart();
                        }
                    }
                }
                if(sbossalive == true) {
                    if((abs(bulletx[i] - sbossx) < 50) && (abs(bullety[i] - sbossy) < 50) && bullets[i] == true && tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        sbosshp = sbosshp - 1;
                        bullets[i] = false;
                        bulletcount--;
                        if(sbosshp == 0) {
                            sbossalive = false;
                            score = score + 75;
                            ttimer.restart();
                            stimer.restart();
                        }
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
                if(abs(x-senemyx[d]) < 25 && abs(y-senemyy[d]) < 25) {
                    gameover = true;
                    Sleep(500);
                }
            }
        }

        for(int e=0; e<tmax; e++) {
            if(tenemyalive[e] == true) {
                if(x-tenemyx[e] != 0) {
                    angle = 180*(atan((y-tenemyy[e])/(x-tenemyx[e])))/M_PI;
                }

                if(tenemyx[e] < x) {
                    tenemyx[e] = tenemyx[e] + abs(tenemyspeed[e]*cos(angle));
                } else {
                    tenemyx[e] = tenemyx[e] - abs(tenemyspeed[e]*cos(angle));
                }
                if(tenemyy[e] < y) {
                    tenemyy[e] = tenemyy[e] + abs(tenemyspeed[e]*sin(angle));
                } else {
                    tenemyy[e] = tenemyy[e] - abs(tenemyspeed[e]*sin(angle));
                }

                if(abs(x-tenemyx[e]) < 30 && abs(y-tenemyy[e]) < 40) {
                    gameover = true;
                    Sleep(500);
                }
            }
        }

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
    if(ctimer.getElapsedTime().asMilliseconds() > cspawntime && cenemycount != cmax) {
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
    if(stimer.getElapsedTime().asMilliseconds() > sspawntime && senemycount != smax && score >= 5) {
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

void tspawn() {
    if(ttimer.getElapsedTime().asSeconds() > tspawntime && tenemycount != tmax && score >= 25) {
        for(int c=0; c<tmax; c++) {
            if(tenemyalive[c] == false) {

                tenemyx[c] = 740*(rand()%2)-40;
                tenemyy[c] = rand()%250+230;

                tenemyalive[c] = true;
                tlife[c] = 5;
                tenemycount++;
                ttimer.restart();
                break;
            }
        }

    }
}

void cbossmove() {
    if(cbosstimer.getElapsedTime().asMilliseconds() > 10) {

        if(cbossx > 350) {
            cbossspeed = cbossspeed - 0.1;
        } else {
            cbossspeed = cbossspeed + 0.1;
        }

        cbossx = cbossx + cbossspeed;

        if(abs(x-cbossx) < 60 && abs(y-cbossy) < 100) {
            gameover = true;
            Sleep(500);
        }

        cbosstimer.restart();
    }
}

void sbossmove() {
    if(sbosstimer.getElapsedTime().asMilliseconds() > 10) {
        if(sbossx <= 50) {
            sbossspeedx = 5;
        } else if (sbossx >= 650) {
            sbossspeedx = -5;
        }

        if(sbossy == 450) {
            sbossspeedy = -5;
        } else if(sbossy > 450) {
            sbossy = 450;
            sbossspeedy = 0;
        } else {
            sbossspeedy = sbossspeedy + 0.1;
        }

        sbossx = sbossx + sbossspeedx;
        sbossy = sbossy + sbossspeedy;

        if(abs(x-sbossx) < 50 && abs(y-sbossy) < 50) {
            gameover = true;
            Sleep(500);
        }

        sbosstimer.restart();
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

    for(int i=0; i<tmax; i++) {
        if(tenemyalive[i] == true) {
            tenemy.setPosition(tenemyx[i], tenemyy[i]);
            window.draw(tenemy);
        }
    }

    window.draw(text);
    window.draw(high);

    if(cbossalive == true) {
        cboss.setPosition(cbossx,cbossy);
        window.draw(cboss);
    }

    if(sbossalive == true) {
        sboss.setPosition(sbossx,sbossy);
        window.draw(sboss);
    }

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
                    cbossfight = false;
                    cbossalive = false;
                    sbossfight = false;
                    sbossalive = false;

                    for(int i=0; i<100; i++) {
                        cenemyalive[i] = false;
                        cenemyspeed[i] = 2;

                        senemyalive[i] = false;

                        tenemyalive[i] = false;

                        if(i<5) {
                            bullets[i] = false;
                        }
                    }

                    x = 350;
                    y = 490;

                    score = 0;
                    cenemycount = 0;
                    senemycount = 0;
                    tenemycount = 0;

                    start = true;
                    bulletcount = 0;

                    cspawntime = 1000;
                    sspawntime = 3000;
                    tspawntime = 7;
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

                if(cbossalive == false && sbossalive == false) {
                    cspawn();
                    sspawn();
                    tspawn();
                }
                enemymove();
                draw();

                if(score >= 50 && cbossfight == false) {
                    cbossalive = true;
                    cbossfight = true;
                    cbosshp = 50;
                    cbossx = (rand()%2)*600+50;
                    cbossspeed = 0;
                }
                if(cbossalive == true) {
                    if(tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        cbossmove();
                    }
                }
                if(score >= 150 && sbossfight == false) {
                    sbossalive = true;
                    sbossfight = true;
                    sbosshp = 50;
                    sbossx = (rand()%2)*600+50;
                    sbossy = 450;
                    sbossspeedy = 0;
                }
                if(sbossalive == true) {
                    if(tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        sbossmove();
                    }
                }
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
