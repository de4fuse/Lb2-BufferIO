#include <unistd.h>
#include <time.h>
#include <stdio.h>


int read_char(char* c) {
    return read(0, c, 1);
}


void read_int(int* a) {
    int r = 0;
    char c;

    while(read_char(&c) && c >= '0' && c <= '9') {
        r = r * 10 + (c - 48);
    }

    *a = r;
}


void input(char* f, void* a) {
    int i = 0;

    while(f[i] != '\0') {
        if(f[i] == '%') {
            ++i;

            if(f[i] == 'd') {
                read_int((int*) a);
            }
        }

        ++i;
    }
}


int main() {
    int t1 = time(NULL);

    for(int i = 0; i < 10000000; ++i) {
        int a;
        input("%d", &a);
    }

    int t2 = time(NULL);

    int t = t2 - t1;

    printf("Time = %d\n", t);

    return 0;
}