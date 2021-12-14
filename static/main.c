#include <stdio.h>
#include <stdlib.h>
#include "static.c"

int print_blob(char * url) {
    int match = gdav_static_match(url);
    if(match == -1){
        printf("NOT FOUND\n");
        return 0;
    }
    printf("%s\n", gdav_static_blob(url));
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc == 2){
        printf("%s\n",argv[1]);
        return !print_blob(argv[1]);        
    }
        
    printf("Static urls:\n");
    for(int i = 0; i < gdav_static_urls_count; i++){
        printf("%d: %s\n", i, gdav_static_urls[i]);
    }
    
    while(1){
        printf("Type url: ");
        char buff[256];
        fgets(buff, 255, stdin);
        buff[strlen(buff) - 1] = 0;
        print_blob(buff);
    }
    //printf("%s", vuetify_js);

}
