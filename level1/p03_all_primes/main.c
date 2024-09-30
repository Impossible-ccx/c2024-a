#include <stdio.h>
#include <stdbool.h>
int prime[800];
int sqrPrime[800];
int numP = 1;
void CheckPrime() {
    prime[0] = 2;
    sqrPrime[0] = 4;
	for (int p = 3; p <= 1000; p += 2) {
        for (int i = 0;;i++) {
            if (p % prime[i] == 0) {
                break;
            }
            if (sqrPrime[i] > p) {
                prime[numP] = p;
                sqrPrime[numP] = p * p;
                numP++;
                break;
            }
        }
    }
}
int main() {
    CheckPrime();
    for (int i = 0; i < numP; i++)
    {
        printf("%d\n", prime[i]);
    }
    return 0;
}