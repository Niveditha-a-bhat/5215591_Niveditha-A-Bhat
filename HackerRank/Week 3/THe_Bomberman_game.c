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

/*
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 *  3. INTEGER grid_count
 */

char** detonate(char** grid, int rows, int cols);

char** bomberMan(int n, int grid_count, char** grid, int* result_count) {
    *result_count = grid_count;
    int rows = grid_count;
    int cols = strlen(grid[0]);
    
    if (n == 1) {
        return grid;
    }
    
    if (n % 2 == 0) {
        // All bombs state
        char** result = malloc(rows * sizeof(char*));
        for (int i = 0; i < rows; i++) {
            result[i] = malloc((cols + 1) * sizeof(char));
            for (int j = 0; j < cols; j++) {
                result[i][j] = 'O';
            }
            result[i][cols] = '\0';
        }
        return result;
    }
    
    // For odd seconds, the pattern repeats every 4 seconds
    char** state1 = detonate(grid, rows, cols);  // n=3
    
    if (n == 3) {
        return state1;
    }
    
    char** state2 = detonate(state1, rows, cols);  // n=5
    
    if (n == 5) {
        // Free state1 memory
        for (int i = 0; i < rows; i++) {
            free(state1[i]);
        }
        free(state1);
        return state2;
    }
    
    // For n > 5 and odd, the pattern repeats every 4 seconds
    if ((n - 3) % 4 == 0) {
        // Same as state1 (n=3)
        for (int i = 0; i < rows; i++) {
            free(state2[i]);
        }
        free(state2);
        return state1;
    } else {
        // Same as state2 (n=5)
        for (int i = 0; i < rows; i++) {
            free(state1[i]);
        }
        free(state1);
        return state2;
    }
}

char** detonate(char** grid, int rows, int cols) {
    // First create a grid of all bombs
    char** result = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        result[i] = malloc((cols + 1) * sizeof(char));
        for (int j = 0; j < cols; j++) {
            result[i][j] = 'O';
        }
        result[i][cols] = '\0';
    }
    
    // Now detonate bombs from the original grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'O') {
                // This bomb detonates, clearing itself and neighbors
                result[i][j] = '.';
                if (i > 0) result[i-1][j] = '.';
                if (i < rows-1) result[i+1][j] = '.';
                if (j > 0) result[i][j-1] = '.';
                if (j < cols-1) result[i][j+1] = '.';
            }
        }
    }
    
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int r = parse_int(*(first_multiple_input + 0));

    int c = parse_int(*(first_multiple_input + 1));

    int n = parse_int(*(first_multiple_input + 2));

    char** grid = malloc(r * sizeof(char*));

    for (int i = 0; i < r; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    int result_count;
    char** result = bomberMan(n, r, grid, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}