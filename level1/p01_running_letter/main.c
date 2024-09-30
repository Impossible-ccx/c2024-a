#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    bool reverse = false;
    for (int i = 0;;) {
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        printf("x");
        Sleep(150);
        if (reverse) {
            i--;
        }
        else {
            i++;
        }
        if (i > 20) {
            reverse = true;
        }
        if (i < 1) {
            reverse = false;
        }
        system("cls");
    }
    return 0;
}