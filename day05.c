#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    unsigned long long start;
    unsigned long long end;
} Range;

Range ranges[185];
unsigned long long available_ids[1000];
int range_count = 0;
int id_count = 0;

int comparing_func(const void* a, const void* b) {
    Range *rangeA = (Range *) a;
    Range *rangeB = (Range *) b;
    if (rangeA->start < rangeB->start) return -1;
    if (rangeA->start > rangeB->start) return 1;
    return 0;
}
int main() {
    FILE *ftpr;
    ftpr = fopen("input.txt", "r");
    char* line = NULL;
    size_t len = 0;
    int parsing_ranges = 1;

    while(getline(&line, &len, ftpr) != -1) {
        if (line[0] == '\n' || line[0] == '\r') {
            parsing_ranges = 0;
            continue;
        }
        if (parsing_ranges) {
            // Step 1: Parse Ranges (e.g., "3-5")
            char *start_str = strtok(line, "-");
            char *end_str = strtok(NULL, "-");
            if (start_str && end_str) {
                ranges[range_count].start = strtoull(start_str, NULL, 10);
                ranges[range_count].end = strtoull(end_str, NULL, 10);
                range_count++;
            }
        } else {
            // Step 2: Parse IDs (e.g., "5")
            available_ids[id_count] = strtoull(line, NULL, 10);
            id_count++;
        }

    }

    qsort(ranges, range_count, sizeof(Range), comparing_func);
    int j = 0;
    for (int i = 1; i < range_count; i++) {
        if (ranges[i].start <= ranges[j].end) {
            if (ranges[i].end >= ranges[j].end) {
                ranges[j].end = ranges[i].end;
            }
        } else {
            j++;
            ranges[j] = ranges[i];
        }
    }
    range_count = j + 1;
    int count = 0;
    for (int i = 0; i < id_count; i++) {
        unsigned long long current_id = available_ids[i];
        int is_fresh = 0;
        for (int j = 0; j < range_count; j++) {

            if (current_id < ranges[j].start) {
                break;
            }

            if (current_id >= ranges[j].start && current_id <= ranges[j].end) {
                is_fresh = 1;
                break;
            }

        }
        if (is_fresh) count++;
    }
    unsigned long long part2Sum = 0;
    for (int i = 0; i < range_count; i++) {
        part2Sum += (ranges[i].end - ranges[i].start + 1);
    }
    //part 2
    printf("%d\n", count);
    printf("%llu\n", part2Sum);
    return 0;
}
