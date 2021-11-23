#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
enum ErrorsTypes {
    FILE_NOT_FOUND,
};

void error(char errorType) {
    switch (errorType) {
        case FILE_NOT_FOUND:
            printf("File not found");
            exit(FILE_NOT_FOUND);
        default:
            printf("Error");
            exit(666);
    }
}
FILE *getFile(char *filename) {
    FILE *input;
    input = fopen(filename, "r");
    if (input == NULL)
        error(FILE_NOT_FOUND);
    return input;
}
time_t timeFromString(char *str) {
    if (str == NULL)
        return 0;
    char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    struct tm time = {0};
    for (int i = 0; i < 12; ++i)
        if (!strcmp(months[i], str + 3)) {
            time.tm_mon = i;
            break;
        }
    time.tm_year = atoi(str + 7) - 1900;
    time.tm_mday = atoi(str);
    time.tm_hour = atoi(str + 12);
    time.tm_min = atoi(str + 15);
    time.tm_sec = atoi(str + 18);
    time.tm_isdst = -1;
    time.tm_gmtoff = ((str[22] - '0') * 10 + (str[23] - '0')) * 3600 + ((str[24] - '0') * 10 + (str[25] - '0')) * 60;
    return mktime(&time);
}
int main(int argc, char **argv) {
    return 0;
}