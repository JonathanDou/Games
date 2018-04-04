
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <sstream>
#include <iostream>
#include <ctime>

sf::RenderWindow window(sf::VideoMode(700, 500), "Pong");
sf::Event event;

sf::Clock btimer;
sf::Clock ptimer;
sf::Clock ctimer;
sf::Clock stimer;
sf::Clock dtimer;

sf::Text ptext;
sf::Text ctext;
sf::Text gametext;

sf::Font font;

sf::RectangleShape player;
sf::RectangleShape computer;
sf::CircleShape ball;

std::stringstream ss;
std::stringstream ss2;
std::string scorep;
std::string scorec;

int playerspeed = 5;
int computerspeed = 5;
double ballspeed = 5;
double ballacceleration = 0.5;

double ballvelocityx;
double ballvelocityy;

double ballx;
double bally;

int playerx;
int playery;

int computerx;
int computery;

int pscore = 0;
int cscore = 0;

bool start = false;
bool play = false;

void load() {
    srand(time(0));
    font.loadFromFile("font.ttf");

    player.setFillColor(sf::Color::Blue);
    player.setSize(sf::Vector2f(20,100));
    player.setOrigin(10,50);

    computer.setFillColor(sf::Color::Red);
    computer.setSize(sf::Vector2f(20,100));
    computer.setOrigin(10,50);

    ball.setFillColor(sf::Color::Green);
    ball.setRadius(10);
    ball.setOrigin(10,10);

    gametext.setFillColor(sf::Color::Green);
    gametext.setString("Arrow Keys to Move.\nSpace to Serve Ball.\nPress Space to Start.");
    gametext.setCharacterSize(40);
    gametext.setFont(font);
    gametext.setOrigin(gametext.getLocalBounds().width/2, gametext.getLocalBounds().height/2);
    gametext.setPosition(350,250);

    ctext.setFillColor(sf::Color::Red);
    ctext.setCharacterSize(30);
    ctext.setFont(font);
    ctext.setPosition(665,15);

    ptext.setFillColor(sf::Color::Blue);
    ptext.setCharacterSize(30);
    ptext.setFont(font);
    ptext.setPosition(20,15);
}

void gamestart() {
    window.clear();
    window.draw(gametext);
    window.display();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        play = true;
        Sleep(200);
    }
}

void reset() {
    playerx = 50;
    playery = 250;

    computerx = 650;
    computery = 250;

    ballx = 70;
    bally = 250;

    ballspeed = 5;
    ballvelocityx = 1;
    ballvelocityy = ((double)(rand()%21)/10) - 1;

    ss << pscore;
    ss >> scorep;
    ptext.setString(scorep);
    ss.str("");
    ss.clear();

    ss << cscore;
    ss >> scorec;
    ctext.setString(scorec);
    ss.str("");
    ss.clear();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        start = true;
    }
}

void playermove() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playery < 450) {
        playery = playery + playerspeed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playery > 50) {
        playery = playery - playerspeed;
    }
}

void computermove() {
    if(computery < bally && computery < 450) {
        computery = computery + computerspeed;
    }
    if(computery > bally && computery > 50) {
        computery = computery - computerspeed;
    }
}

void ballmove() {
    ballx = ballx + ballvelocityx*ballspeed;
    bally = bally + ballvelocityy*ballspeed;
}

void draw() {
    player.setPosition(playerx,playery);
    computer.setPosition(computerx, computery);
    ball.setPosition(ballx, bally);

    window.clear();
    window.draw(ptext);
    window.draw(ctext);
    window.draw(player);
    window.draw(computer);
    window.draw(ball);
    window.display();
}

void playerwin() {
    pscore++;
    reset();
    draw();
    start = false;
}

void computerwin() {
    cscore++;
    reset();
    ballx = 630;
    bally = 250;
    draw();
    Sleep(1000);
    ballvelocityx = -1;
    ballvelocityy = ((double)(rand()%21)/10) - 1;
}

void check() {
    if(dtimer.getElapsedTime().asMilliseconds() > 200) {
        if((playerx - ballx) > -20 && (playerx - ballx) < 0 && abs(playery - bally) < 60) {
            ballvelocityx = -ballvelocityx;
            ballvelocityy = (bally - playery)/50;
            dtimer.restart();
        }
        if((computerx - ballx) < 20 && (computerx - ballx) > 0 && abs(computery - bally) < 60) {
            ballvelocityx = -ballvelocityx;
            ballvelocityy = (bally - computery)/50;
            dtimer.restart();
        }
    }
    if(bally > 490 || bally < 10) {
        ballvelocityy = -ballvelocityy;
    }
    if(ballx > 710) {
        playerwin();
    }
    if(ballx < -10) {
        computerwin();
    }
}

void run() {
    if(btimer.getElapsedTime().asMilliseconds() > 16) {
        ballmove();
        btimer.restart();
        check();
    }
    if(ptimer.getElapsedTime().asMilliseconds() > 16) {
        playermove();
        ptimer.restart();
    }
    if(ctimer.getElapsedTime().asMilliseconds() > 16) {
        computermove();
        ctimer.restart();
    }
    if(stimer.getElapsedTime().asSeconds() > 3) {
        ballspeed = ballspeed + ballacceleration;
        stimer.restart();
    }
}

int main() {

     load();

     while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if(play == true) {
            if(start == true) {
                run();
                draw();
            } else {
                reset();
                draw();
            }
        } else {
            gamestart();
        }
     }
}
