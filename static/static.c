
#include "static.h"

#include "urls.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int gdav_static_match(char * url){
    for(int i = 0; i < gdav_static_urls_count; i++){
        if(strcmp(gdav_static_urls[i],url) == 0)
            return i;
    }
    return -1;
}

char * gdav_static_blob(char * url){
     int index = gdav_static_match(url);
     const char * data = gdav_static_blobs[index];
     const int size = strlen(data) + 1;
     char * result = malloc(size);
     strcpy(result, data);
     return result;
}
