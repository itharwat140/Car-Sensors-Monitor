#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int count;
FILE *file;
unsigned int oldSensors[15], newSensors[15];

int buildArrays();

int findActiveSensors();

int updateArray();

int convert(long long);

int main() {
    buildArrays();

    while (true) {

        char tempChunk[17] = "";
        int i = 0;
        int x = 0;

        file = fopen("C:\\Users\\islam\\Downloads\\Car\\SensorData.txt", "r");
        while ((count = getc(file)) != EOF) {
            char tmp = (char) count;
            size_t len = strlen(tempChunk);
            snprintf(tempChunk + len, sizeof tempChunk - len, "%count", tmp);
            x++;
            if (x == 16) {
                newSensors[i] = convert(atoll(tempChunk));
                memset(&tempChunk[0], 0, sizeof(tempChunk));
                x = 0;
                i++;
            }
        }
        fclose(file);
        printf("\n--------------------");
        findActiveSensors();
        updateArray();
    }
}

int findActiveSensors() { // Check and alarm switched sensors
    int i, j, n = 0;
    for (i = 0; i <= 15; i++) {
        if (newSensors[i] != oldSensors[i]) {
            unsigned int tempXor = newSensors[i] ^ oldSensors[i];
            for (j = 0; j <= 15; j++) {
                if ((tempXor & (1 << j)) != 0) {
                    printf("\nsensor %d switched ", n);
                    n++;
                }
            }
        }
    }
    return 0;
}

int delay(int number_of_seconds) { // Creates a time delay
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
    return 0;
}

int buildArrays() {
    int i;
    for (i = 0; i <= 15; i++) {
        oldSensors[i] = 0;
        newSensors[i] = 0;
    }
    return 0;
}

int updateArray() {
    int i;
    for (i = 0; i < 15; i++) {
        oldSensors[i] = newSensors[i];
    }
    return 0;
}

int convert(long long n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = (int) n % 10;
        n /= 10;
        dec += (int) (rem * pow(2, i));
        ++i;
    }
    return dec;
}