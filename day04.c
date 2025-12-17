#include <inttypes.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *ftpr;
    ftpr = fopen("input.txt", "r");
    int N = 135;
    char* line = NULL;
    size_t len = 0;
    int count = 0;
    char **lines = malloc(N * sizeof(char *));
    if (!lines) return 1;

    while (count < N && getline(&line, &len, ftpr) != -1) {

        line[strcspn(line, "\r\n")] = 0;

        lines[count++] = strdup(line);
    }
    free(line);
    fclose(ftpr);
    int sum = 0;

while(1) {
    int subSum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int c = 0;
            if (lines[i][j] == '@') {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    c += lines[i - 1][j - 1] == '@';

                }
                if (i + 1 < N && j - 1 >= 0) {
                    c += lines[i + 1][j - 1] == '@';
                }
                if (i - 1 >= 0 && j + 1 < N) {
                    c += lines[i - 1][j + 1] == '@';
                }
                if (i + 1 < N && j + 1 < N) {
                    c += lines[i + 1][j + 1] == '@';
                }
                if (i + 1 < N) {
                    c += lines[i + 1][j] == '@';
                }
                if (j + 1 < N) {
                    c += lines[i][j + 1] == '@';
                }
                if (i - 1 >= 0) {
                    c += lines[i - 1][j] == '@';
                }
                if (j - 1 >= 0) {
                    c += lines[i][j - 1] == '@';
                }
                if (c < 4) {
                    printf("Fewer than 4 toilet papers at [%d, %d]\n", i, j);
                    lines[i][j] = 'X';
                    subSum++;
                }
            }
        }
    }
    sum += subSum;
    if (subSum == 0) {
        break;
    }

}
    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("%d\n", sum);
    return 0;
  }
