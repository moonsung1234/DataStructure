
#include "string.h"

int readLine(char* buffer) {
    char c;
    int i = 0;

    while((c = getchar()) != '\n') {
        buffer[i++] = c;
    }

    buffer[i] = '\0';

    return i;
}