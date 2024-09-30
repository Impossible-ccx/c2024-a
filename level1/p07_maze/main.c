#include <stdio.h>
#include<conio.h>
char map[20][20];
void fps() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
int main() {
   
    
    getch();
    return 0;
}