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

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

char* isValid(char* s) {
    int freq[26] = {0};
    int len = strlen(s);
    
    // Count frequency of each character
    for (int i = 0; i < len; i++) {
        freq[s[i] - 'a']++;
    }
    
    // Find min and max frequencies (ignoring zeros)
    int min_freq = INT_MAX;
    int max_freq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            if (freq[i] < min_freq) min_freq = freq[i];
            if (freq[i] > max_freq) max_freq = freq[i];
        }
    }
    
    // Count occurrences of min and max frequencies
    int count_min = 0, count_max = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            if (freq[i] == min_freq) count_min++;
            if (freq[i] == max_freq) count_max++;
        }
    }
    
    // Check validity conditions
    if (min_freq == max_freq) {
        // All characters have same frequency
        return "YES";
    } else if (max_freq - min_freq == 1) {
        // Only one character has frequency one more than others
        if (count_max == 1) {
            return "YES";
        } else if (min_freq == 1 && count_min == 1) {
            // Only one character has frequency 1, others are same
            return "YES";
        } else {
            return "NO";
        }
    } else if (min_freq == 1 && count_min == 1) {
        // Only one character has frequency 1, others are same
        return "YES";
    } else {
        return "NO";
    }
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

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

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}