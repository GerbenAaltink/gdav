#include "http_method.h"
#include "functions.h"

HTTP_METHOD http_method_from_str(char * method){
    HTTP_METHOD http_method = 0;
    for(http_method = HTTP_METHOD_GET; http_method < HTTP_METHOD_UNKNOWN; http_method++)
    {
        if(streq(method, HTTP_METHOD_STRINGS[http_method]))
            return http_method;
    }
    return HTTP_METHOD_UNKNOWN;
}