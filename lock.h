#include <stdbool.h>

typedef struct Lock {
    char path[4068];
    char id[64];
    char user[512];
    struct Lock * prev;
    struct Lock * next;
} Lock;

Lock * locks;

Lock * lock_create(char * path);
bool lock_delete(char * id);
Lock * lock_check(char * path);
