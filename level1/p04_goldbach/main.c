#include <stdio.h>
#include <stdbool.h>
bool primeBin[2000];
int prime[800];
int sqrPrime[800];
int numP = 1;
void CheckPrime(int range) {
    prime[0] = 2;
    sqrPrime[0] = 4;
    for (int p = 3; p <= range; p += 2) {
        for (int i = 0;; i++) {
            if (p % prime[i] == 0) {
                break;
            }
            if (sqrPrime[i] > p) {
                prime[numP] = p;
                sqrPrime[numP] = p * p;
                primeBin[p] = true;
                numP++;
                break;
            }
        }
    }
}
bool ProveGe(int range) {
    CheckPrime(range);
    for (int i = 2; i <= range; i += 2) {
		for (int j = 0; ; j++) {
            if (primeBin[i - prime[j]]) break;
            if (prime[j] < i) return false;
        }
    }
    return true;
}
int main() {
    if (ProveGe(100)) {
        printf("true");
    }
    else {
        printf("false");
    }
    return 0;
}