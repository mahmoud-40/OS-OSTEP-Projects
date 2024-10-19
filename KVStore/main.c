#include <stdio.h>
#include "hashmap.h"
#include "db.h"

#define SIZE 200

int main(int argc, char *argv[]) {
    struct HashMap* map = initHashMap(SIZE);
    import_data(map); 

    for (int i = 1; i < argc; i++) {
        work(map, argv[i]);  
    }

    save_data(map); 
    freeHashMap(map);

    return 0;
}
