
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
 FILE *ftpr;

 ftpr = fopen("input.txt", "r");
 char *line = NULL;
 size_t len = 0;
 getline(&line, &len, ftpr);
 char* inner;
 char* outer;
 char* token = strtok_r(line, ",", &outer);
 size_t sum = 0;

 while(token != NULL) {
  //determine invalid IDs here

  char* start = strtok_r(token, "-", &inner);
  char* end = strtok_r(NULL, "-", &inner);

  size_t startval = strtol(start, NULL, 10);
  size_t endval = strtol(end, NULL, 10);

  for (size_t i = startval; i <= endval; i++) {
   size_t lenghtTillcomma = strlen(token) + 1;
   char current[lenghtTillcomma];
   sprintf(current,"%zu",  i);
   len = strlen(current);
   int invalid = 0;
   for (size_t d = 1; d <= len / 2; d++) {
    if (len % d != 0) continue;
    invalid = 1;
    for (size_t j = d; j < len; j++) {
     if (current[j] != current[j % d]) {
      invalid = 0;
     }
    }
    if (invalid) {
     printf("Invalid id: %zu\n", i);
     sum += i; // invalid ID found
     break;
    }
   }
  }
  token = strtok_r(NULL, ",", &outer);
 }
  printf("Sum of all invalid IDs: %zu", sum);
  return 0;
 }


