#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


static void find_val(char* line, size_t start_idx,  size_t end_idx,int* best_val, ssize_t* best_pos) {
    *best_val = -1;
    *best_pos = -1;
    char ch = '0' - 1;
    for (size_t i = start_idx; i <= end_idx; i++) {
        if (line[i] == '9') {
            *best_val = 9;
            *best_pos = i + 1;
            return;
        }
        if (line[i] > ch) {
            ch = line[i];
            *best_val = ch - '0';
            *best_pos = i + 1;
        }
    }
}
int main(void) {
    FILE *ftpr;
    ftpr = fopen("input.txt", "r");
    char* line = NULL;
    size_t len = 0;
    long long unsigned sum = 0;
    int count = 0;
    while(1) {
        ssize_t read = getline(&line, &len, ftpr);
        if (read == -1) break;
        ssize_t last_valid_idx = read - 1;
        while (last_valid_idx >= 0 && !isdigit(line[last_valid_idx])) {
            last_valid_idx--;
        }
        count++;
        int val[12];
        size_t start_idx = 0;
        ssize_t end_idx = last_valid_idx;
        for (size_t i = 0; i < 12; i++) {
             end_idx = last_valid_idx - (11 - i);

            int best_val;
            ssize_t best_idx;

            find_val(line, start_idx, end_idx, &best_val, &best_idx);

            val[i] = best_val;

            start_idx = best_idx;
        }
        unsigned long long joltage = 0;
        for (int i = 0; i < 12; i++) {
            joltage = (joltage * 10) + val[i];
        }
        sum += joltage;
        printf("Bank number %d has max joltage: %llu\n", count, joltage);
    }
    free(line);
    printf("Sum of max joltage from each bank: %llu", sum);
    return 0;
}
