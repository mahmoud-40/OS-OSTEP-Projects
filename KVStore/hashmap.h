#ifndef HASHMAP_H
#define HASHMAP_H

struct KeyValue {
    char* key;
    char* value;
};

struct HashMap {
    int length;
    struct KeyValue** keyValues;
};

struct HashMap* initHashMap(int length);
unsigned long hash_function(const char* key, int length);
void freeHashMap(struct HashMap* map);
void put(struct HashMap* map, const char* key, const char* value);
void get(struct HashMap* map, const char* key);
void delete(struct HashMap* map, const char* key);
void print(struct HashMap* map);
void clear(struct HashMap* map);
void work(struct HashMap* map, char* input);

#endif
