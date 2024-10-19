#ifndef DB_H
#define DB_H

#include "hashmap.h"

struct KeyValue* parseKV(const char* str);
void import_data(struct HashMap* map);
void save_data(struct HashMap* map);

#endif
