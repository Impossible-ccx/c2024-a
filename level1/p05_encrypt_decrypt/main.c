#include <stdio.h>
//不理解题面，上课做的题吗？姑且用凯撒编码，并假定输入是小写字母
char str[100];
void encrypt(int index) {
    for (int i = 0; str[i] != 0; i++) {
        str[i] += index;
        if (str[i] > 'x') {
            str[i] -= 26;
        }
    }
}
void decrypt(int index) {
    for (int i = 0; str[i] != 0; i++) {
        str[i] -= index;
        if (str[i] < 'a') {
            str[i] += 26;
        }
    }
}
int main() {
    scanf("%s", &str);
    encrypt(9);
    printf("%s\n", str);
    decrypt(9);
    printf("%s", str);
    return 0;
}