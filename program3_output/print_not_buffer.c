#include <unistd.h>
#include <time.h>
#include <stdio.h>


void print_out(char c) {
    write(1, &c, 1);
}


void print_int(int a) {
    if(a != 0) {
        char s[10];
        int i = 0;

        while(a > 0) {
            s[i++] = (a % 10) + 48;
            a /= 10;
        }

        while(i > 0) {
            print_out(s[--i]);
        }
    } else {
        print_out('0');
    }
}


void print_line(char* s) {
    int i = 0;

    while(s[i] != '\0') {
        print_out(s[i++]);
    }
}


void print_char(char* c) {
    print_out(*c);
}


void print(char* f, void* a) {
    int i = 0;

    while(f[i] != '\0') {
        if(f[i] == '%') {
            ++i;

            if(f[i] == 'd') {
                print_int(*(int*) a);
            }

            if(f[i] == 's') {
                print_line((char*) a);
            }

            if(f[i] == 'c') {
                print_char((char*) a);
            }
        } else {
            print_out(f[i]);
        }

        ++i;
    }
}


int main() {
    int t1 = time(NULL);

    for(int i = 0; i < 10000000; ++i) {
        int a = i;
        print("%d ", &a);
    }

    int t2 = time(NULL);

    int t = t2 - t1;

    printf("\nTime = %d\n", t);

    return 0;
}