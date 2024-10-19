#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "db.h"

struct KeyValue* parseKV(const char* str) {
    struct KeyValue* pair = malloc(sizeof(struct KeyValue));
    char* key = malloc(strlen(str));
    char* value = malloc(strlen(str));
    int i = 0;
    while (str[i] != ',') {
        key[i] = str[i];
        i++;
    }
    key[i] = '\0';
    i++;
    int j = 0;
    while (str[i] != '\n') {
        value[j] = str[i];
        i++;
        j++;
    }
    value[j] = '\0';
    pair->key = key;
    pair->value = value;
    return pair;
}

void import_data(struct HashMap* map) {
    FILE *fptr;
    fptr = fopen("db.txt", "r");
    if (fptr == NULL) {
        fptr = fopen("db.txt", "w");
        if (fptr == NULL) {
            perror("ERROR: FAILURE FOPEN");
        }
        fclose(fptr);
        return;
    }
    
    char line[256];

    while (fgets(line, sizeof(line), fptr)) {
        struct KeyValue* pair = parseKV(line);
        put(map, pair->key, pair->value);
    }
    
    fclose(fptr);
}

void save_data(struct HashMap* map) {
    FILE *fptr;
    fptr = fopen("db.txt", "w");
    if (fptr == NULL) {
        perror("ERROR: FAILURE FOPEN");
    }

    for (int i = 0; i < map->length; i++) {
        if (map->keyValues[i] != NULL) {
            fprintf(fptr, "%s,%s\n", map->keyValues[i]->key, map->keyValues[i]->value);
        }
    }

    fclose(fptr);
}
