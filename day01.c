#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *fptr;
    fptr  = fopen("input.txt", "r");

    char *line = NULL;
    size_t len = 0;

    int current_val = 50;
    char rotation;
    int value;
    int count = 0;
    while(getline(&line, &len, fptr) != -1) {
        if (sscanf(line, "%c%d", &rotation, &value) == 2) {
            if (rotation == 'L') {
                int moduloed = (current_val - value);
                int wraps = moduloed / 100;
                if (moduloed < 0 && moduloed % 100 != 0) {
                    wraps--;
                    if (current_val == 0) {
                        wraps++;
                    }
                }
                count += abs(wraps);
                current_val = ((moduloed % 100) + 100) % 100;
                if (current_val == 0) {
                    count++;
                }
            } else {
                int moduloed = (current_val + value);
                int wraps = moduloed / 100;
                count += wraps;
                current_val = moduloed % 100;
            }

            printf("Dial pointing at: %d \n", current_val);
        }
    }
    free(line);

    printf("Pointed at 0 %d times.", count);
}



