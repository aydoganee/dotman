#ifndef CONFIG_H
#define CONFIG_H

#include "cli.h"
const int SIZE   = 60;
const int FIELDS = 5;
const int LINE   = 20;

typedef struct {
  ScpType scp;
  char**  fields;
  int     count_fields;  // position of the arr in fields. if there is no arr -1
  int     count_arr;
} ConfigLine;

void parse_config(ConfigLine* result, char* file);

#endif
