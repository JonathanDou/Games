#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>

sf::RenderWindow window(sf::VideoMode(700, 500), "Random Box");
sf::Event event;
sf::Clock tanktimer;
sf::Clock falltimer;
sf::Clock jtimer;
sf::Clock btimer;
sf::Clock atimer;
sf::CircleShape tank;
sf::CircleShape bullet;
sf::RectangleShape gun;

int x = 350;
int y = 490;
int bulletspeed = 8;
int tankspeed = 4;
double fallspeed = 7;
bool direction = true;
bool bfall = false;
bool jumpr = true;

int bulletcount = 0;
int maxbullets = 5;

int jump = 0;
int maxjump = 3;

int bulletx[5];
int bullety[5];
bool bdirection[5];
bool bullets[5];

void load() {
    tank.setRadius(10);
    tank.setOrigin(10,10);
    tank.setFillColor(sf::Color::Blue);
    gun.setSize(sf::Vector2f(15,8));
    gun.setOrigin(0,4);
    gun.setFillColor(sf::Color::Green);
    bullet.setFillColor(sf::Color::Red);
    bullet.setRadius(5);
    bullet.setOrigin(5,5);
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(jump != maxjump && jumpr == true && jtimer.getElapsedTime().asMilliseconds() > 100) {
                jump++;
                fallspeed = 7;
                bfall = true;
                jumpr = false;
                jtimer.restart();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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
            }
            if(bulletx[i] > 700 || bulletx[i] < 0) {
                bullets[i] = false;
                bulletcount--;
            }
        }
        atimer.restart();
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

void draw() {
    tank.setPosition(x,y);
    gun.setPosition(x,y);
    window.clear();
    for(int z = 0; z<maxbullets; z++) {
        if(bullets[z] == true) {
            bullet.setPosition(bulletx[z],bullety[z]);
            window.draw(bullet);
        }
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
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
                jumpr = true;
            }
        }
        if(bfall == true) {
            fall();
        }
        tankmove();
        bulletmove();
        draw();

     }

}
