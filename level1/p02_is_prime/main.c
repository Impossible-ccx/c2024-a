#include <stdbool.h>
#include <stdio.h>
bool IsPrime(int input) {
    if (input == 1) return false;
    if (input == 2) return true;
    for (int i = 2; i * i <= input; i++) {
        if (input % i == 0) {
            return false;
        }
    }
    return true;
}
int main() {
    int input;
    scanf("%d", &input);
    if (IsPrime(input)) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
    return 0;
}