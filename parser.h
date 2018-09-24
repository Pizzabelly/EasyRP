#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef PARSER_H
#define PARSER_H
typedef struct {
    char* section;
    char* key;
    char* value;
} pair;

typedef struct {
    uint32_t count;
    pair pair_data[100];
} ini_t;

struct ini_parser {
    ini_t data;
    FILE* file_data;
    bool changed;
    char* path;
};

void parse_ini(struct ini_parser* p);
bool load_ini_file(struct ini_parser* p, const char* path);
char* get_ini_value(struct ini_parser* p, const char* sec, const char* key);
#endif
