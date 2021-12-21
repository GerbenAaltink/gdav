#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "json.h"

char * json_escape_string(char * str){
   char result[strlen(str) * 2 + 1];
    result[0] = 0;
    for(int i = 0; i < strlen(str); i++) {
        char chrstr[2];
        chrstr[0] = str[i];
        chrstr[1] = 0;
        //chrstr[1] = 0;
        if(str[i] == '"')
        {
            strcat(result, "\\\"");
        }else if(str[i] == '\n'){
            strcat(result, "\\n"); 
        }else if(str[i] == '\\') {
            strcat(result, "\\");
        }
        else {
            strcat(result, chrstr);
        }
    }
    bzero(str, sizeof(str));
    strcpy(str, result);
    return str;
}

char * json_unescape_string(char * str){
    char result[strlen(str) + 1];
    result[0] = 0;
    for(int i = 0; i < strlen(str); i++){
        char strchar[2];
        strchar[0] = str[i];
        strchar[1] = 0;
        if(str[i] == '\\' && i  < strlen(str)){
            char nextChar = str[i + 1];
            if(nextChar == 'n')
            {
                strchar[0] = '\n';
                i++;
            }else if(nextChar == '"') {
                strchar[0] = '"';
                i++;
            }else if(nextChar == '\\'){
                strchar[0] = '\\';
                i++;
            }
        }
        strcat(result, strchar);
        
    }
    bzero(str, sizeof(str));
    strcpy(str, result);
    return str;
}




char * json_key_value(char * str, char * key, char * value){
    bzero(str, sizeof(str));
    char strkey[strlen(key) * 2 + 1];
    strcpy(strkey, key);
    char strvalue[strlen(value) * 2 + 1];
    strcpy(strvalue, value);
    json_escape_string(strkey);
    json_escape_string(strvalue);
    sprintf(str, "\"%s\":\"%s\"", strkey, strvalue);
    return str;
}



char * json_object(char * result, int count, char *values[]){
    bzero(result, sizeof(result));
    strcpy(result, "{");
    char buff[4096] = ""; 
    for(int i = 0; i < count * 2; i++){
        bzero(buff, sizeof(buff));
        strcat(result, json_key_value(buff, values[i], values[i + 1]));
        i++;
        strcat(result, ",");
    }
    result[strlen(result) - 1] = '}';
    result[strlen(result)] = 0;
    return result;
}

char * json_array(char * result, int count, char *values[]){
    bzero(result,sizeof(result));
    strcpy(result, "[");
    for(int i = 0; i < count; i++){
        strcat(result, values[i]);
        strcat(result, ",");
    }
    result[strlen(result) - 1] = ']';
    result[strlen(result)] = 0;
    return result;
}

int test_json() {
    char json_str[] = "aa\n\"\n";
     printf("1:'%s'\n", json_escape_string(json_str));
    printf("1:'%s'\n", json_unescape_string(json_str));
    printf("2:'%s'\n", json_escape_string(json_str));
    printf("2:'%s'\n", json_unescape_string(json_str));
   printf("1:'%s'\n", json_escape_string(json_str));
    printf("1:'%s'\n", json_unescape_string(json_str));
    printf("2:'%s'\n", json_escape_string(json_str));
    printf("2:'%s'\n", json_unescape_string(json_str));
    char result[4096];
    printf(json_key_value(result, json_str, json_str));

    char *kv[] =  {"a","b","c\"","d\nG"};
    char json_obj_str[4096];
    printf("%s\n", json_object(json_obj_str, 2, kv));
        
    printf("%s\n", json_array(result, 2, (char *[]){json_obj_str, json_obj_str}));

}
