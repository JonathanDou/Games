#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

int main() {
    int sizex = 31;
    int sizey = 41;
    srand(time(0));

    bool maze[sizex][sizey];
    int random;
    int c = 1;
    int b = 0;

    for(int i = 0; i < sizex; i++) {
        for(int j = 0; j < sizey; j++) {
            if(i == 0 || j == 0 || i == sizex-1 || j == sizey-1) {
                maze[i][j] = false;
            } else {
                maze[i][j] = true;
            }
        }
    }

    int num = (sizex-1)/2;
    int num2 = (sizey-1)/2;
    int num3 = (num-1)*(num2-1);
    int mazex = (rand()%(num-1)+1)*2;
    int mazey = (rand()%(num2-1)+1)*2;
    int startx = 2;
    int starty = 2;
    int endx = sizex-3;
    int endy = sizey-3;
    int moves[num*num2];
    bool moves2[5];

    maze[mazex][mazey] = false;
    maze[2][1] = false;
    maze[sizex-3][sizey-2] = false;

    while(c < num3) {
        if((maze[mazex+2][mazey] == true && mazex != sizex-3) || (maze[mazex-2][mazey] == true && mazex != 2) || (maze[mazex][mazey+2] == true && mazey != sizey-3) || (maze[mazex][mazey-2] == true && mazey != 2)) {
            moves2[1] = false;
            moves2[2] = false;
            moves2[3] = false;
            moves2[4] = false;
            if(maze[mazex+2][mazey] == true && mazex != sizex-3) {
                moves2[1] = true;
            }
            if(maze[mazex-2][mazey] == true && mazex != 2) {
                moves2[2] = true;
            }
            if(maze[mazex][mazey+2] == true && mazey != sizey-3) {
                moves2[3] = true;
            }
            if(maze[mazex][mazey-2] == true && mazey != 2) {
                moves2[4] = true;
            }
            while(true) {
                random = rand()%4+1;
                if(moves2[random] == true) {
                    moves[b] = random;
                    b++;
                    if(random == 1) {
                        maze[mazex+1][mazey] = false;
                        mazex = mazex + 2;
                    } else if(random == 2) {
                        maze[mazex-1][mazey] = false;
                        mazex = mazex - 2;
                    } else if(random == 3) {
                        maze[mazex][mazey+1] = false;
                        mazey = mazey + 2;
                    } else if(random == 4) {
                        maze[mazex][mazey-1] = false;
                        mazey = mazey - 2;
                    }
                    maze[mazex][mazey] = false;
                    c++;
                    break;
                }
            }
        } else {
            b--;
            if(moves[b] == 1) {
                mazex = mazex - 2;
            } else if(moves[b] == 2) {
                mazex = mazex + 2;
            } else if(moves[b] == 3) {
                mazey = mazey - 2;
            } else if(moves[b] == 4) {
                mazey = mazey + 2;
            }
        }
    }

    system("mode 650");

    for(int x = 1; x < sizex; x++) {
        for(int y = 1; y < sizey; y++) {
            if(x == startx && y == starty) {
                cout << "S ";
            } else if (x == endx && y == endy) {
                cout << "F ";
            } else if(maze[x][y] == true) {
                cout << ". ";
            } else {
                cout << "  ";
            }

        }


        cout << "\n";

    }

    system("pause");
}
