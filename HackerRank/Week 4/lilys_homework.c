#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

int cmpAsc(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
int cmpDesc(const void* a, const void* b) { return (*(int*)b - *(int*)a); }

// Function to calculate minimum swaps needed to transform arr -> sorted[]
int minSwaps(int n, int* arr, int* sorted) {
    int* index = malloc((1000001) * sizeof(int)); // using large enough size for mapping values to indices
    for (int i = 0; i < n; i++) {
        index[arr[i]] = i;
    }

    int swaps = 0;
    int* temp = malloc(n * sizeof(int));
    memcpy(temp, arr, n * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (temp[i] != sorted[i]) {
            swaps++;

            int correctValue = sorted[i];
            int toSwapIndex = index[correctValue];

            // update index before swapping
            index[temp[i]] = toSwapIndex;
            index[correctValue] = i;

            // swap
            int t = temp[i];
            temp[i] = temp[toSwapIndex];
            temp[toSwapIndex] = t;
        }
    }

    free(temp);
    free(index);
    return swaps;
}

int lilysHomework(int arr_count, int* arr) {
    int* sortedAsc = malloc(arr_count * sizeof(int));
    int* sortedDesc = malloc(arr_count * sizeof(int));

    memcpy(sortedAsc, arr, arr_count * sizeof(int));
    memcpy(sortedDesc, arr, arr_count * sizeof(int));

    qsort(sortedAsc, arr_count, sizeof(int), cmpAsc);
    qsort(sortedDesc, arr_count, sizeof(int), cmpDesc);

    int swapsAsc = minSwaps(arr_count, arr, sortedAsc);
    int swapsDesc = minSwaps(arr_count, arr, sortedDesc);

    free(sortedAsc);
    free(sortedDesc);

    return (swapsAsc < swapsDesc) ? swapsAsc : swapsDesc;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));
    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));
        *(arr + i) = arr_item;
    }

    int result = lilysHomework(n, arr);
    fprintf(fptr, "%d\n", result);

    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) break;
        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;
        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) return '\0';
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) return '\0';
    } else {
        data = realloc(data, data_length + 1);
        if (!data) return '\0';
        else data[data_length] = '\0';
    }
    return data;
}

char* ltrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;
    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) return splits;
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
