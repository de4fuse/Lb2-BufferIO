#include <stdio.h>
#include <stdlib.h>


int main() {
    int n = 10000000;

    for (int i = 0; i < n; i++)
    {
        int x = rand() % 1000000000;
        printf("%d ", x);
    }
    
}