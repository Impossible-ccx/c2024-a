#include <stdio.h>
#include<conio.h>
#include<windows.h>
#define my 4
#define mx 4
char map[20][20] = {
        {"##000"},
        {"##000"},
        {"##000"},
        {"##000"},
        {"##000"}
    };
int x = 4, y = 4;
void fps() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
void tps() {
    char ch = '\0';
    map[y][x] = 'Y';
    Sleep(40);
    ch = getch();
    if (ch == 'w') {
        if (y - 1 < 0 || map[x][y - 1] == '#') {
            ;
        }
        else {
            map[x][y] = '0';
            y -= 1;
            map[x][y] = 'Y';
        }
    }
    if (ch == 's') {
        if (y + 1 > my || map[x][y + 1] == '#') {
            ;
        }
        else {
            map[x][y] = '0';
            y += 1;
            map[x][y] = 'Y';
        }
    }
    if (ch == 'a') {
        if (x - 1 < 0 || map[x - 1][y] == '#') {
            ;
        }
        else {
            map[x][y] = '0';
            x -= 1;
            map[x][y] = 'Y';
        }
    }
    if (ch == 'd') {
        if (x + 1 > mx || map[x + 1][y] == '#') {
            ;
        }
        else {
            map[x][y] = '0';
            x += 1;
            map[x][y] = 'Y';
        }
    }
}
int main() {
    while (1) {
        tps();
        fps();
    }
    return 0;
}