#include <stdlib.h>
#include "lock.h"
#include <stdbool.h>
#include "utlist.h"
#include <uuid/uuid.h>
#include "malloc.h"
// libuuid1 / uuid-dev
#include <string.h>

extern Lock * locks;

Lock * lock_create(char * path) {
    Lock * lock = (Lock *)malloc(sizeof(Lock));
    strcpy(lock->path, path);
    uuid_t id;
    uuid_generate_random(id);
    char uuidstr[37];
    uuid_unparse(id,lock->id);
    DL_APPEND(locks, lock);
    return lock;
}

bool lock_cmp_id(Lock * a, Lock * b) {
    return strcmp(a->id, b->id);
}

bool lock_cmp_path(Lock * a, Lock * b) {
    return strcmp(a->path, b->path);
}


bool lock_delete(char * id) {
    Lock * found;
    Lock filter;
    strcpy(filter.id, id);
    DL_SEARCH(locks, found, &filter, lock_cmp_id);
    if(found){
        DL_DELETE(locks, found);
        return true;
    }else{
        return false;
    }
}

Lock * lock_check(char * path) {
    Lock * found;
    Lock filter;
    strcpy(filter.path, path);
    DL_SEARCH(locks, found, &filter, lock_cmp_path);
    return found;
}


