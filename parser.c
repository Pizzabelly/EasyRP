#include "parser.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

/* loads the file at the given path into memory */
bool load_ini_file(struct ini_parser* p, const char* path) {
    p->file_data = fopen(path, "r");
    if (p->file_data == NULL) return false;
    p->data.count = 0;
    return true;
}

/* return value of matching pair with the given key and section */
char* get_ini_value(struct ini_parser* p, const char* sec, const char* key) {
    for (int i=0; i < (int)p->data.count; i++) {
        if (strcmp(p->data.pair_data[i].section, sec) != 0) continue;
        if (strcmp(p->data.pair_data[i].key, key) == 0) {
            return p->data.pair_data[i].value;
        }
    }
    return "";
}

/* map infomation in the file text to usable format */
void parse_ini(struct ini_parser* p) {
    /* initial values */
    char* line = malloc(sizeof(char) * 256);
    char* current_section = "root";

    /* iterate each line in the config file */
    while(fgets(line, 256, p->file_data) != NULL) {
        char front = *line; // first character for the line

        /* skip ini comments */
        if (front == ';') continue;

        /* map sections of the ini */
        else if (front == '[') {
            line++;
            current_section = malloc(strlen(line) + 1);
            memcpy(current_section, line, strlen(line) - 2);
            continue;
        }

        /* set values for this line if applicable */
        pair current_pair; // struct for this line's info
        current_pair.section = current_section;

        /* find the key and value of the line */
        char* key = malloc(sizeof(char) * 128);
        char* value = malloc(sizeof(char) * 256);
        sscanf(line, "%[^=]=%[^\n] ", key, value); 
        current_pair.key = key;
        current_pair.value = value;

        /* check if this value is different */
        printf("%s, %s\n", current_pair.section, current_pair.key);
        char* prev_value = get_ini_value(p, current_pair.section, current_pair.key);
        printf("%s\n", prev_value);
        if (strcmp(prev_value, "") != 0) {
            printf("test\n");
            if (strcmp(prev_value, value) != 0) p->changed = true; 
        } 
        
        /* add pair to the array */
        p->data.pair_data[p->data.count] = current_pair;
        p->data.count++;
        line[0] = '\0'; // reset line
    }
}
