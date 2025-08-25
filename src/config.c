#include "config.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

void parse_config(ConfigLine* results, char* file) {
  // Check input parameters
  if (results == NULL || file == NULL) {
    printf("Error: NULL parameter passed to parse_config\n");
    return;
  }

  char* temp = malloc(SIZE * sizeof(char*));
  if (temp == NULL) {
    printf("Error: malloc failed\n");
    return;
  }

  for (int i = 0; i < LINE; i++) {
    results[i].scp    = 0;
    results[i].fields = (char**) malloc(FIELDS * sizeof(char*));
    for (int j = 0; j < FIELDS; j++) {
      results[i].fields[j] = (char*) malloc(SIZE * sizeof(char*));
    }
    results[i].count_fields = 0;
  }

  FILE* file_ptr = fopen(file, "r");
  if (file_ptr == NULL) {
    printf("Error: Could not open file '%s'\n", file);
    free(temp);
    return;
  }

  int cur_char;

  bool scp_parsed = false;

  int arr_index    = 0;
  int result_index = 0;
  int field_index  = 0;

  while ((cur_char = fgetc(file_ptr)) != EOF) {
    // <scp>:field1:field2:el,el1,el2;
    // in scope
    // in field
    // in arr

    if (!scp_parsed) {
      while (cur_char != ':') {
        temp[arr_index++] = (char) cur_char;
        cur_char          = fgetc(file_ptr);
      }
      temp[arr_index]           = '\0';
      arr_index                 = 0;
      scp_parsed                = true;
      results[result_index].scp = extract_scp(temp);
    }

    if (scp_parsed == true && cur_char == ':') {
      while ((cur_char = fgetc(file_ptr)) != ':') {
        temp[arr_index++] = (char) cur_char;
      }
      temp[arr_index] = '\0';
      strcpy(results[result_index].fields[field_index], temp);
      results[result_index].count_fields++;
    }

    if (cur_char == ';') {
      result_index++;
      results[result_index].count_arr++;
    }
  }

  fclose(file_ptr);
  free(temp);
}
