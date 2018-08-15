#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <fstream>

sf::RenderWindow window(sf::VideoMode(700, 500), "Random Box");
sf::Event event;

std::fstream file;

sf::SoundBuffer buffer;
sf::Sound music;

sf::Clock sbosstimer;
sf::Clock cbosstimer;
sf::Clock tbosstimer;
sf::Clock pbosstimer;
sf::Clock pbosstimer2;
sf::Clock bombtimer;
sf::Clock pbombtimer;
sf::Clock bombmovetimer;
sf::Clock pbombmovetimer;
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
sf::RectangleShape gun;
sf::CircleShape bullet;

sf::CircleShape cenemy;
sf::RectangleShape senemy;
sf::CircleShape tenemy;

sf::RectangleShape tbossbomb;
sf::CircleShape pbossbomb;

sf::CircleShape cboss;
sf::RectangleShape sboss;
sf::CircleShape tboss;
sf::CircleShape pboss;

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

bool tbossalive = false;
bool tbossfight = false;
double tbossspeedx = 0;
int tbosshp;
double tbossx;
double tbossy;

bool pbossalive = false;
bool pbossfight = false;
double pbossspeedx = 0;
int pbosshp;
double pbossx;
double pbossy;

bool bombalive[5];
double bombspeed[5];
double bombx[5];
double bomby[5];

bool pbombalive[10];
double pbombspeedx[10];
double pbombspeedy[10];
double pbombx[10];
double pbomby[10];

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
bool gamewon = false;

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

    gametext.setFillColor(sf::Color::Green);
    gametext.setFont(font);
    gametext.setCharacterSize(50);
    gametext.setString("Loading...");

    TextRect = gametext.getLocalBounds();

    gametext.setOrigin(TextRect.width/2, TextRect.height/2);
    gametext.setPosition(350,230);
    window.clear();
    window.draw(gametext);
    window.display();

    buffer.loadFromFile("random music.wav");
    music.setBuffer(buffer);
    music.setLoop(true);

    text.setString("0");
    text.setFillColor(sf::Color::Green);
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(10,10);

    high.setFillColor(sf::Color::Green);
    high.setFont(font);
    high.setCharacterSize(20);
    high.setPosition(670,10);

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

    tboss.setFillColor(sf::Color::Magenta);
    tboss.setRadius(75);
    tboss.setOrigin(75,75);
    tboss.setPointCount(3);

    tbossbomb.setFillColor(sf::Color::Magenta);
    tbossbomb.setSize(sf::Vector2f(50,50));
    tbossbomb.setOrigin(25,25);

    pboss.setFillColor(sf::Color::Cyan);
    pboss.setRadius(65);
    pboss.setOrigin(65,65);
    pboss.setPointCount(5);

    pbossbomb.setFillColor(sf::Color::Cyan);
    pbossbomb.setRadius(25);
    pbossbomb.setOrigin(25,25);

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
                    if((tenemyalive[n] == true) && (abs(bulletx[i] - tenemyx[n]) < 35) && ((bullety[i] - tenemyy[n]) < 30) && ((tenemyy[n] - bullety[i]) < 55) && bullets[i] == true) {
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
                            score = score + 50;
                            ttimer.restart();
                            stimer.restart();
                        }
                    }
                }
                if(tbossalive == true) {
                    if((abs(bulletx[i] - tbossx) < 25) && (abs(bullety[i] - tbossy) < 60) && bullets[i] == true && tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        tbosshp = tbosshp - 1;
                        bullets[i] = false;
                        bulletcount--;
                        if(tbosshp == 0) {
                            tbossalive = false;
                            score = score + 50;
                            ttimer.restart();
                            stimer.restart();
                        }
                    }
                }
                if(pbossalive == true) {
                    if((abs(bulletx[i] - pbossx) < 50) && (abs(bullety[i] - pbossy) < 50) && bullets[i] == true && tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        pbosshp = pbosshp - 1;
                        bullets[i] = false;
                        bulletcount--;
                        if(pbosshp == 0) {
                            tbossalive = false;
                            score = score + 100;
                            gamewon = true;
                            gameover = true;
                        }
                    }
                    for(int n=0; n<10; n++) {
                        if(pbombalive[n] == true && abs(bulletx[i] - pbombx[n]) < 25 && (abs(bullety[i] - pbomby[n]) < 25) && bullets[i] == true) {
                            pbombalive[n] = false;
                            bullets[i] = false;
                            bulletcount--;
                            score = score + 1;
                            break;
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
    if(ttimer.getElapsedTime().asSeconds() > tspawntime && tenemycount != tmax && score >= 20) {
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

    if(cbossalive == true && (tenemycount == 0 && cenemycount == 0 && senemycount == 0)) {
        cboss.setPosition(cbossx,cbossy);
        window.draw(cboss);
    }

    if(sbossalive == true && (tenemycount == 0 && cenemycount == 0 && senemycount == 0)) {
        sboss.setPosition(sbossx,sbossy);
        window.draw(sboss);
    }

    if(tbossalive == true && (tenemycount == 0 && cenemycount == 0 && senemycount == 0)) {
        tboss.setPosition(tbossx,tbossy);
        window.draw(tboss);
        for(int i=0; i<5; i++) {
            if(bombalive[i] == true) {
                tbossbomb.setPosition(bombx[i],bomby[i]);
                window.draw(tbossbomb);
            }
        }
    }

    if(pbossalive == true && (tenemycount == 0 && cenemycount == 0 && senemycount == 0)) {
        pboss.setPosition(pbossx,pbossy);
        window.draw(pboss);
        for(int i=0; i<10; i++) {
            if(pbombalive[i] == true) {
                pbossbomb.setPosition(pbombx[i],pbomby[i]);
                window.draw(pbossbomb);
            }
        }
    }

    window.draw(gun);
    window.draw(tank);
    window.display();
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
            draw();
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
            draw();
            Sleep(500);
        }

        sbosstimer.restart();
    }
}

void tbossmove() {
    if(tbosstimer.getElapsedTime().asMilliseconds() > 10) {
        if(tbossx < -100) {
            tboss.setRotation(90);
            tbossspeedx = 5;
            tbossy = rand()%370+65;
        }
        if(tbossx > 800) {
            tboss.setRotation(270);
            tbossspeedx = -5;
            tbossy = rand()%370+65;
        }

        if(abs(x-tbossx) < 50 && abs(y-tbossy) < 35) {
            gameover = true;
            draw();
            Sleep(500);
        }

        tbossx = tbossx + tbossspeedx;
        tbosstimer.restart();
    }

}

void bombspawn() {
    if(bombtimer.getElapsedTime().asMilliseconds() >= 500) {
        for(int b=0; b<5; b++) {
            if(bombalive[b] == false) {
                bombalive[b] = true;
                bombx[b] = tbossx;
                bomby[b] = tbossy;
                bombspeed[b] = 4;
                break;
            }
        }
        bombtimer.restart();
    }
}

void bombmove() {
    if(bombmovetimer.getElapsedTime().asMilliseconds() >= 10) {
        for(int b=0; b<5; b++) {
            if(bombalive[b] == true) {
                bomby[b] = bomby[b] + bombspeed[b];
                bombspeed[b] = bombspeed[b] + 0.1;
                if(bomby[b] > 475) {
                    bombalive[b] = false;
                }
                if(abs(x-bombx[b]) < 35 && abs(y-bomby[b]) < 35) {
                    gameover = true;
                    draw();
                    Sleep(500);
                }
            }
        }
        bombmovetimer.restart();
    }
}

void pbombspawn() {
    if(pbombtimer.getElapsedTime().asMilliseconds() >= 500) {
        for(int b=0; b<10; b++) {
            if(pbombalive[b] == false) {
                pbombalive[b] = true;
                pbombx[b] = pbossx;
                pbomby[b] = pbossy+15;
                if(pbombx[b] < x) {
                    pbombspeedx[b] = 3;
                } else {
                    pbombspeedx[b] = -3;
                }
                pbombspeedy[b] = -1.5;
                break;
            }
        }
        for(int b=0; b<10; b++) {
            if(pbombalive[b] == false) {
                pbombalive[b] = true;
                pbombx[b] = pbossx;
                pbomby[b] = pbossy;
                if(pbombx[b] < x) {
                    pbombspeedx[b] = 1.5;
                } else {
                    pbombspeedx[b] = -1.5;
                }
                pbombspeedy[b] = -3;
                break;
            }
        }
        pbombtimer.restart();
    }
}

void pbombmove() {
    if(pbombmovetimer.getElapsedTime().asMilliseconds() >= 10) {
        for(int b=0; b<10; b++) {
            if(pbombalive[b] == true) {
                pbombx[b] = pbombx[b] + pbombspeedx[b];

                if(pbomby[b] < 475) {
                    pbomby[b] = pbomby[b] + pbombspeedy[b];
                    pbombspeedy[b] = pbombspeedy[b] + 0.05;
                    if(pbomby[b] > 475) {
                        pbomby[b] = 475;
                    }
                }

                if(pbombx[b] > 725 || pbombx[b] < -25) {
                    pbombalive[b] = false;
                }

                if(abs(x-pbombx[b]) < 25 && abs(y-pbomby[b]) < 25) {
                    gameover = true;
                    draw();
                    Sleep(500);
                    break;
                }

            }
        }

        pbombmovetimer.restart();
    }
}

void pbossmove() {
    if(pbosstimer.getElapsedTime().asMilliseconds() > 10) {
        if((int)(pbosstimer2.getElapsedTime().asSeconds())%10 < 5) {
            if(pbossx < x) {
                pbossx = pbossx + pbossspeedx;
            } else {
                pbossx = pbossx - pbossspeedx;
            }
        } else {
            pbombspawn();
        }
        if(abs(x-pbossx) < 50 && abs(y-pbossy) < 50) {
            gameover = true;
            draw();
            Sleep(500);
        }
        pbosstimer.restart();
    }
}

void gameend() {
    ss << score;
    ss >> scoretext;

    if(gamewon == false) {
        gametext.setString("Score: " + scoretext);
    } else {
        gametext.setString("YOU BEAT THE GAME!\nScore: " + scoretext);
    }
    ss.str("");
    ss.clear();

    TextRect = gametext.getLocalBounds();

    gametext.setOrigin(TextRect.width/2, TextRect.height/2);
    gametext.setPosition(350,230);

    window.clear();
    window.draw(gametext);
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
                    music.play();
                    gameover = false;
                    cbossfight = false;
                    cbossalive = false;
                    sbossfight = false;
                    sbossalive = false;
                    tbossfight = false;
                    tbossalive = false;
                    pbossfight = false;
                    pbossalive = false;
                    gamewon = false;

                    for(int i=0; i<100; i++) {
                        cenemyalive[i] = false;
                        cenemyspeed[i] = 2;

                        senemyalive[i] = false;

                        tenemyalive[i] = false;

                        if(i<5) {
                            bullets[i] = false;
                        }
                    }

                    for(int i=0; i<5; i++) {
                        bombalive[i] = false;
                        pbombalive[i] = false;
                        pbombalive[9-i] = false;
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

                if(cbossalive == false && sbossalive == false && tbossalive == false && pbossalive == false) {
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
                if(score >= 250 && tbossfight == false) {
                    tbossalive = true;
                    tbossfight = true;
                    tbosshp = 50;
                    tbossx = (rand()%2)*1100-200;
                    tbossy = rand()%370+65;
                }
                if(tbossalive == true) {
                    if(tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        tbossmove();
                        if(gameover == false) {
                            bombspawn();
                            bombmove();
                        }
                    }
                }
                if(score >= 350 && pbossfight == false) {
                    pbossalive = true;
                    pbossfight = true;
                    pbosshp = 100;
                    pbossx = (rand()%2)*500+100;
                    pbossy = 450;
                    pbossspeedx = 2;
                    pbosstimer2.restart();
                }
                if(pbossalive == true) {
                    if(tenemycount == 0 && cenemycount == 0 && senemycount == 0) {
                        pbossmove();
                        pbombmove();
                    }
                }
            } else {
                gameend();
                music.stop();
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
            music.stop();
        }
    }
}