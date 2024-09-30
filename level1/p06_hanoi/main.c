#include <stdio.h>
void SolveHan(int height, char target, char location, char help) {
    if (height != 1) {
		SolveHan(height - 1, help, location, target);
        printf("%c->%c\n", location, target);
        SolveHan(height - 1, target, help, location);
        return;
    }
    else {
        printf("%c->%c\n", location, target);
    }
}
int main() {

    SolveHan(3,'C','A','B');
    return 0;
}