#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

#define GREEN "\033[0;32m"
#define PINK "\033[0;35m"
#define RESET "\033[0m"

struct HashMap* initHashMap(int length) {
    struct HashMap* map = malloc(sizeof(struct HashMap));
    map->length = length;
    map->keyValues = calloc(length, sizeof(struct KeyValue*));
    return map;
}

unsigned long hash_function(const char* key, int length) {
    unsigned long hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key - '0');
        key++;
    }
    return hash % length;
}

void freeHashMap(struct HashMap* map) {
    for (int i = 0; i < map->length; i++) {
        if (map->keyValues[i] != NULL) {
            free(map->keyValues[i]);
        }
    }
    free(map->keyValues);
    free(map);
}

void put(struct HashMap* map, const char* key, const char* value) {
    unsigned long idx = hash_function(key, map->length);
    struct KeyValue* pair = malloc(sizeof(struct KeyValue));
    pair->key = strdup(key);
    pair->value = strdup(value);
    map->keyValues[idx] = pair;
}

void get(struct HashMap* map, const char* key) {
    unsigned long idx = hash_function(key, map->length);
    if (map->keyValues[idx] == NULL) {
        printf(PINK "ERROR: Key Not Found\n" RESET);
        return;
    }
    printf(GREEN "Key: %s, Value: %s\n" RESET, map->keyValues[idx]->key, map->keyValues[idx]->value);
}

void delete(struct HashMap* map, const char* key) {
    unsigned long idx = hash_function(key, map->length);
    if (map->keyValues[idx] != NULL) {
        free(map->keyValues[idx]);
        map->keyValues[idx] = NULL;
        printf(GREEN "Key: %s Deleted\n" RESET, key);
    } else {
        printf(PINK "ERROR: Key Not Found\n" RESET);
    }
}

void print(struct HashMap* map) {
    for (int i = 0; i < map->length; i++) {
        if (map->keyValues[i] != NULL) {
            printf("Key: %s, Value: %s\n", map->keyValues[i]->key, map->keyValues[i]->value);
        }
    }
}

void clear(struct HashMap* map) {
    for (int i = 0; i < map->length; i++) {
        if (map->keyValues[i] != NULL) {
            free(map->keyValues[i]);
            map->keyValues[i] = NULL;
        }
    }
    printf(GREEN "All Keys Deleted\n" RESET);
}

void work(struct HashMap* map, char* input) {
    char* command = strtok(input, ",");
    char* key = strtok(NULL, ",");
    char* value = strtok(NULL, ",");
    
    if (command == NULL) {
        printf(PINK "ERROR: Invalid Command\n" RESET);
        exit(0);
    }

    if (command[0] == 'p') {
        if (key == NULL || value == NULL) {
            printf(PINK "ERROR: Invalid Command\n" RESET);
            exit(0);
        }
        put(map, key, value);
        printf(GREEN "Key: %s, Value: %s - Added\n" RESET, key, value);
    } else if (command[0] == 'g') {
        if (key == NULL) {
            printf(PINK "ERROR: Invalid Command\n" RESET);
            exit(0);
        }
        get(map, key);
    } else if (command[0] == 'd') {
        if (key == NULL) {
            printf(PINK "ERROR: Invalid Command\n" RESET);
            exit(0);
        }
        delete(map, key);
    } else if (command[0] == 'c') {
        clear(map);
    } else if (command[0] == 'a') {
        print(map);
    }
}
