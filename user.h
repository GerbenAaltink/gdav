#pragma once
#include <stdbool.h>

typedef struct User {
    char username[256];
    char password[256];
    char root[4096];
    struct User * next;
    struct User * prev;
} User;

User * users;

int user_count;

char user_file[4096];

bool user_write_file(char * path);
bool user_load_file(char * path);

bool user_cli_useradd(int argc, char *argv[]);
bool user_cli(int argc, char *argv[]);

User * user_get(char * username);
User * user_get_or_create(char * username);
bool user_delete(char * username);
bool user_save(User * user);
