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
#include <pthread.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

typedef uint64_t result_t;

/* This structure stores info about each element in dara `arr`.
 * There exist, as much, 4001 different values as
 *   -2000 <= arr[i] <= 2000
 */
struct point
{
	int value;
	int freq;
};
typedef struct point point_t;

/* Calculates the result of query `q` applied over array sample */
result_t calculateQueryResult(size_t sample_len, point_t* restrict sample, const int q)
{
    result_t abs_sum = 0;
    
    for (size_t i = 0; i < sample_len; i++) {
	    abs_sum += sample[i].freq * abs(sample[i].value += q);
    }
    return abs_sum;
}

/** This maps a value into an index of the array of samples */
inline size_t map(int value) { return 2000 + value; }
//#define map(value) (2000 + (value))

/* This builds the sample from array `arr`: values and number 
 * of occurrences for each
 */  
void characterizeSample(size_t arr_count, int* restrict arr, size_t sample_len, point_t *sample) {
	size_t i, j;
	for (j = 0; j < sample_len; j++) {
		sample[j].freq = 0;
	}
	for (i = 0; i < arr_count; i++) {
		j = map(arr[i]);
		sample[j].value = arr[i];
		++sample[j].freq;
	}
	/*for (j = 0; j < sample_len; j++) {
		if (sample[j].freq) {
			printf("%d: %d\n", sample[j].value, sample[j].freq);
		}
	}*/
}

/*
 * Complete the 'playingWithNumbers' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
 */

result_t* playingWithNumbers(size_t arr_count, int* restrict arr, size_t queries_count, int* restrict queries, size_t* result_count) {
	*result_count = queries_count;

	// dynamically allocate space for vector `result`
	if (arr_count <= 0 || queries_count <= 0) { return NULL; }
	result_t *result = (result_t *)calloc(queries_count, sizeof(result_t));
	assert(result);
	
    // initial sum of the array
    result_t r = 0;
	size_t j;
	
	// characterize sample: compute frequency of each value
	int sample_len = 4001;
	point_t *sample = (point_t *)calloc(sample_len, sizeof(point_t));
	assert(sample!=NULL);
	characterizeSample(arr_count, arr, sample_len, sample);
	
    for (j = 0; j < queries_count; j++) {
        result[j] = calculateQueryResult(sample_len, sample, queries[j]);
    }
    
    free(sample);
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    int q = parse_int(ltrim(rtrim(readline())));

    char** queries_temp = split_string(rtrim(readline()));

    int* queries = malloc(q * sizeof(int));

    for (int i = 0; i < q; i++) {
        int queries_item = parse_int(*(queries_temp + i));

        *(queries + i) = queries_item;
    }

    int result_count;
    result_t* result = playingWithNumbers(n, arr, q, queries, (size_t *)&result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%lu", *(result + i));

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
