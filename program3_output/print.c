#include <unistd.h>
#include <time.h>
#include <stdio.h>


char outBuf[4096]; // Буфер для тимчасового зберігання даних перед виведенням

int outPos = 0; // Поточна позиція запису у вихідному буфері


// Додає один символ у вихідний буфер.
// Якщо буфер заповнений, його вміст виводиться системним викликом write().
void printBuffer(char c) {
    if(outPos == sizeof(outBuf)) { // Якщо буфер заповнений, виводимо всі накопичені дані
        write(1, outBuf, outPos);
        outPos = 0;
    }

    // Записуємо символ у буфер і переходимо до наступної позиції
    outBuf[outPos++] = c;
}



// Перетворює ціле число на послідовність символів і передає кожен символ у вихідний буфер
void printInt(int a) {
    if(a != 0) {
        char s[10]; // Тимчасовий масив для зберігання цифр числа
        int i = 0;

        while(a > 0) {
            s[i++] = (a % 10) + 48;
            a /= 10;
        }

        while(i > 0) { // Виводимо цифри у правильному порядку
            printBuffer(s[--i]);
        }
    } else {
        printBuffer('0');
    }
}


void printStr(char* s) { // Послідовно передає символи рядка у вихідний буфер
    int i = 0;

    while(s[i] != '\0') {
        printBuffer(s[i++]);
    }
}


void printChar(char* c) { // Передає один символ у вихідний буфер
    printBuffer(*c);
}


// Власна функція виведення.
// Аналізує форматний рядок та залежно від специфікатора викликає функцію для відповідного типу даних
void print(char* f, void* a) {
    int i = 0;

    while(f[i] != '\0') {
        if(f[i] == '%') { // Якщо знайдено %, визначаємо тип даних
            ++i;

            if(f[i] == 'd') { // %d - виведення цілого числа
                printInt(*(int*) a);
            }

            if(f[i] == 's') { // %s - виведення символьного рядка
                printStr((char*) a);
            }

            if(f[i] == 'c') { // %c - виведення одного символу
                printChar((char*) a);
            }
        } else {
            printBuffer(f[i]); // Символи форматного рядка, які не є специфікаторами, також додаються у вихідний буфер
        }

        ++i;
    }
}


int main() {
    int startTime = time(NULL);

    for(int i = 0; i < 10000000; ++i) {
        int a = i;
        print("%d ", &a);
    }

    write(1, outBuf, outPos);

    int stopStime = time(NULL);

    int timeResult = stopStime - startTime;

    printf("\nTime = %d\n", timeResult);

    return 0;
}