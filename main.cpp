#include <iostream>
#include "fcgio.h"
#include <stdlib.h>
#include <unistd.h>
#include "fcgio.h"

using namespace std;

enum {
    GRID_WIDTH = 10,
    GRID_HEIGHT = 10,

    MAP_GRASS = 0,
    MAP_WALL = 1,
    MAP_WATER = 2,
    MAP_GROUND = 3,
    MAP_CLEAR = 4,

};
int grid[GRID_HEIGHT][GRID_WIDTH];

void fillGrid();

int main(void) {
    // Backup the stdio streambufs
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        cout << "Content-type: text/plain;charset=utf-8\r\n\r\n";
        srand(time(0));
        for (int step = 0; step < 10; step++) {
            fillGrid();
            for (int i = 0; i < GRID_HEIGHT; i++) {
                for (int j = 0; j < GRID_WIDTH; j++) {
                    switch(grid[i][j]) {
                        case MAP_GRASS:
                            cout << "-";
                            break;
                        case MAP_WALL:
                            cout << "#";
                            break;
                        case MAP_WATER:
                            cout << "^";
                            break;
                        case MAP_GROUND:
                            cout << ".";
                            break;
                        case MAP_CLEAR:
                            cout << " ";
                            break;
                    }
                    cout << " ";
                }
                cout << "\r\n";
            }
            cout << "\r\n";
        }
        // Note: the fcgi_streambuf destructor will auto flush
    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}

void fillGrid()
{
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            int left = -1;
            int top = -1;

            //nothing on top
            if (i != 0) {
                top = i - 1;
            }

            //nothing on left
            if (j != 0) {
                left = j - 1;
            }

            if (left != -1 && top != -1) {
                //top,left available
                int x = grid[i][j-1];
                int y = grid[i-1][j];
                int random = rand() % 2;

                if (random == 0) {
                    grid[i][j] = x;
                } else {
                    grid[i][j] = y;
                }
                // cout << "random " << random << endl;
            } else if (left != -1 && top == -1) {
                //only on left side something is present
                // grid[i][j] = grid[i][j - 1];
                grid[i][j] = MAP_GRASS;
            } else if (left == -1 && top != -1) {
                //only on top something is present
                // grid[i][j] = grid[i - 1][j];
                grid[i][j] = MAP_WALL;
            } else {
                //
                grid[i][j] = MAP_CLEAR;
            }
            // int random = rand() % 5;
            // grid[i][j] = random;
        }
    }
}
