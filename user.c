#include "user.h"
#include <stdbool.h>

#include "malloc.h"
#include "utlist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
extern User * users;
extern char user_file[4096];
extern int user_count;

bool user_cli_userdel(int argc, char *argv[]) {
    if(argc < 2)
        return false;

    char username[256];
    if(argc < 3){
        char line[256];
        printf("Username[256]: ");
        readline(line, sizeof(line)-1, stdin);
        strncpy(username, line, strlen(line) - 1);
    }else{
        strcpy(username, argv[2]);
    }
    if(!user_get(username))
    {
        printf("User \"%s\" not found in \"%s\"\n", username, user_file);
        return false;
    }else{
        user_delete(username);
        user_write_file(NULL);
        printf("User \"%s\" deleted from \"%s\"\n", username, user_file);
        return true;
    }
}

bool user_cli_useradd(int argc, char *argv[]) {
    if(argc < 2)
        return false;
    User * user;


    char username[256];
    char password[256];
    char root[4096];

    if(argc > 2){
        user = user_get_or_create(argv[2]);
    }else{

        printf("Username[256]: ");
        readline(username, sizeof(username)-1, stdin);
        user = user_get_or_create(strtrimr(username, '\n'));
    }
    if(argc >= 3)
    {
        strcpy(password,argv[3]);
    }else{
        printf("Password[256]: ");
        readline(password, sizeof(password) - 1, stdin);
    }
    
    if(argc >= 4)
    {
        strcpy(root, argv[4]);
    }else{
        printf("Directory[4096]: ");
        readline(root, sizeof(root)-1, stdin);
    }
    
    strcpy(user->password, strtrimr(password, '\n'));
    strcpy(user->root, strtrimr(root, '\n'));

    user_write_file(NULL);
    
    printf("Saved user \"%s\" in %s\n", user->username, user_file);

    return true;
}


bool user_cli_userlist(){
    User * user;
    int index = 0;
    DL_FOREACH(users, user) printf("%d\t%s\t\t%s\t\t%s\n",
        ++index,
        user->username,
        user->password,
        user->root        
    );
    return true;
}

bool user_cli(int argc, char *argv[]){
    if(argc == 1)
        return false;
    
    char * action = argv[1];
    if(!strcmp(action, "useradd")){
        user_cli_useradd(argc, argv);    
        return true;
    }else if(!strcmp(action, "userdel")) {
        user_cli_userdel(argc, argv);
        return true;
    }else if(!strcmp(action , "userlist")){
        user_cli_userlist();
        return true;
    }else if(!strcmp(action, "useredit")) {
        user_cli_useradd(argc, argv);
        return true;
    }
    return false;
}

bool user_load_file(char * path) {
    if(path)
        strcpy(user_file, path);
    
    User * tmp;
    DL_FOREACH(users, tmp) DL_DELETE(users, tmp);

    char devider[] = ";";
    FILE * fd = fopen(user_file, "r");
    if(!fd)
        return false;

    size_t read = 0;
    size_t max_length = 5000;
    char line[max_length];
    user_count = 0;
    while((read = readline(line, max_length - 1, fd)) != -1){
        if(strlen(line) < 4)
            continue;
        strtrimr(line,'\n');

        User * user = httpc_malloc(sizeof(User));
        strcpy(user->username, strtok(line, devider));
        strcpy(user->password, strtok(NULL, devider));
        strcpy(user->root, strtok(NULL, devider));
        
        DL_APPEND(users, user);
        
        bzero(line, max_length);
        user_count++;
    }
    fclose(fd);
    return true;
}

void user_write_line(FILE * fd, char * devider, User * user) {
   fwrite(user->username, sizeof(char), strlen(user->username), fd);
   fwrite(devider, sizeof(char), strlen(devider), fd);
   fwrite(user->password, sizeof(char), strlen(user->password), fd);
   fwrite(devider, sizeof(char), strlen(devider), fd);
   fwrite(user->root, sizeof(char), strlen(user->root), fd);
   char nl[] = "\n";
   fwrite(nl, sizeof(char), strlen(nl), fd);
}

bool user_write_file(char * path){
    if(path)
        strcpy(user_file, path);
    char devider[] = ";";
    User * user;
    FILE * fd = fopen(user_file, "w+");
    DL_FOREACH(users, user) user_write_line(fd, devider, user);
    fclose(fd);
    return true;
}

int user_username_cmp(User * user1, User * user2) {
    return strcmp(user1->username, user2->username);
}

bool user_delete(char * username){
    User * found = user_get(username);
    if(found)
    {
        DL_DELETE(users, found);
        httpc_free(found);
        return true;
    }
    return false;
}

User * user_get(char * username){
    User * found;
    User filter;
    strcpy(filter.username, username);
    DL_SEARCH(users, found, &filter, user_username_cmp);
    return found;
}
User * user_get_or_create(char * username){
    User * user = user_get(username);
    if(!user){
        user = httpc_malloc(sizeof(User));
        strcpy(user->username, username);
        DL_APPEND(users, user);
    }
    return user;
}


bool user_save(User * user){
    //User * record = user_get_or_create(user->username);
    //strcpy(record->username, user->username);
    //strcpy(record->password, user->password);
    //strcpy(record->root, user->root);
    if(user->root[strlen(user->root)-1] == '/')
        user->root[strlen(user->root) -1] = 0;
    if(strlen(user->root) == 0)
        strcpy(user->root, ".");
    
    return user;
}

bool user_test(){
    char test_file[] = "users_test.txt";

    // File does not exist yet
    assert(!user_load_file(test_file));
    
    // Add User
    User * user = user_get_or_create("test@user.nl");
    strcpy(user->password, "testpw");
    strcpy(user->root,"/home/");
    user_save(user);
    assert(!strcmp(user->root, "/home"));

    // Save user file
    user_write_file(test_file);

    // Delete User
    user_delete(user->username);

    // Save file
    return true;
} 
