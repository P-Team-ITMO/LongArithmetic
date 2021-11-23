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
int main(int argc, char **argv) {
    return 0;
}