#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

FILE *file;
bool sensors[235];
int count = 0, lower = 0, upper = 235;

int buildSensors();

int delay(int);

int convertRandomSensors();

int main() {
    srand(time(NULL));
    buildSensors();
    while (true) {
        delay(1);
        convertRandomSensors();
    }
}

int convertRandomSensors() { // Switches 20 random sensors true>false / false>true
    for (count = 0; count < 21; count++) {
        int x = (rand() % (upper - lower + 1)) + lower;
        if (sensors[x] == true) {
            sensors[x] = false;
        } else {
            sensors[x] = true;
        }
    }
    file = fopen("C:\\Users\\islam\\Downloads\\Car\\SensorData.txt", "w"); 
    for (count = 0; count < 236; count++) {
        if (sensors[count]) {
            fwrite("1", sizeof(char), 1, file);
        } else {
            fwrite("0", sizeof(char), 1, file);
        }
    }
    fclose(file);
    return 0;
}

int buildSensors() { // Creates 236 sensors and writes them to a file with random outcome on true/false
    file = fopen("C:\\Users\\islam\\Downloads\\Car\\SensorData.txt", "w");
    for (count = 0; count < 236; count++) {
        sensors[count] = rand() % 2;
        if (sensors[count]) {
            fwrite("1", sizeof(char), 1, file);
        } else {
            fwrite("0", sizeof(char), 1, file);
        }
    }
    fclose(file);
    return 0;
}

int delay(int number_of_seconds) { // Creates a time delay
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
    return 0;
}