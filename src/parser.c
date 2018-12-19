#define _CRT_SECURE_NO_WARNINGS
#include "parser.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* loads the file at the given path into memory */
bool load_ini_file(struct ini_parser* p, const char* path) {
  p->file = fopen(path, "r");
  if (p->file == NULL)
    return false;
  p->data.count = 0;
  return true;
}

/* return value of matching pair with the given key and section */
char* get_ini_value(struct ini_parser* p, const char* sec, const char* key) {
  for (int i = 0; i < (int)p->data.count; i++) {
    if (strcmp(p->data.pair_data[i].section, sec) != 0)
      continue;
    if (strcmp(p->data.pair_data[i].key, key) == 0) {
      return p->data.pair_data[i].value;
    }
  }
  return "";
}

bool parse_line(char* line, pair* c) {
  int equal_index = strchr(line, '=')-line;
  if (equal_index < 0) return false;
  int len = strlen(line);
  char* key = malloc(sizeof(char) * equal_index);
  char* value = malloc(sizeof(char) * len - equal_index);
  int key_start = 0;
  int value_start = 0;
  for (int i = 0; i < len - 1; i++) {
    if (key_start < equal_index && line[i] != ' ')
      key[key_start++] = line[i];
    if (i > equal_index)
      value[value_start++] = line[i];
  }
  key[key_start] = '\0';
  value[value_start] = '\0';
  c->key = key;
  c->value = value;
  return true;
}

/* map infomation in the file text to usable format */
void parse_ini(struct ini_parser* p) {
  /* initial values */
  char* line = malloc(sizeof(char) * 256);
  char* current_section = "root";

  /* iterate each line in the config file */
  while (fgets(line, 256, p->file) != NULL) {
    size_t len = strlen(line);
    char front = *line;  // first character for the line
    /* skip ini comments */
    if (front == ';')
      continue;

    /* map sections of the ini */
    else if (front == '[') {
      line++;
      current_section = malloc(sizeof(char) * (len + 1));
      strncpy(current_section, line, len - 3);
      current_section[len-3] = '\0';
      continue;
    }

    pair current_pair;  // struct for this line's info

    /* find the key and value of the line */
    if (!parse_line(line, &current_pair)) continue;
    current_pair.section = current_section;

    /* check if this value is different */
    if (p->data.count + 1 <= p->data.max_count) {
      pair prev = p->data.pair_data[p->data.count];
      if (strcmp(prev.section, current_pair.section) == 0 &&
          strcmp(prev.key, current_pair.key) == 0)
        if (strcmp(prev.value, current_pair.value) != 0)
          p->changed = true;
    }

    /* add pair to the array */
    p->data.pair_data[p->data.count] = current_pair;
    p->data.count++;

    /* adjust max count */
    if (p->data.count > p->data.max_count)
      p->data.max_count = p->data.count;

    /* reset line */
    line[0] = '\0';
  }
}
