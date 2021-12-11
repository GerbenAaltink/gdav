#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
char * headers_parse(char * content){
    regex_t regex;
    regcomp(&regex, ".*\r\n\r\n", 0);
    int match = !regexec(&regex, content, 0, NULL, 0);
    if(match){
        printf("JA\n");
    }

    regfree(&regex);
}*/


char * safe_strstr(char * pdata, char * needle){
    char * data = malloc(strlen(pdata) + 1);
    strcpy(data, pdata);
    return strstr(data, needle);
}

int str_index(char * pdata, char *needle) {
    char * data = pdata;
    char * left = strstr(data, needle);
    if(!left)
        return -1;
    int result = strlen(data) - strlen(left);
    return result;
}

int str_index2(char * pdata, char *needle){
    char * found = safe_strstr(pdata, needle);
    if(!found)
        return -1;
    int result = strlen(pdata) - strlen(found);
    return result;
}

bool headers_parse(char * content, char * headers, char * body) {
    char * content_body = strstr(content, "\r\n\r\n");
    if(!content_body)
        return false;
    content_body = content_body + 4;
    strcpy(body, content_body);
    int headersSize = strlen(content) - strlen(content_body);
    strncpy(headers, content, headersSize);
    return true;

}

char * header_value(char * headers, char *name){
    int startIndex = str_index(headers, name) + strlen(name) + 2;
    char * result = malloc(strlen(headers) + 2);
    strcpy(result, headers);
    result = result + startIndex;
    int endIndex = str_index(result, "\r\n");
    if(endIndex != -1)
        result[endIndex] = 0;
    return result;
}

char * join(char * args[]) {
    printf("%d,%d\n", sizeof(args), strlen(args[0]));
    int count = sizeof(args) * sizeof(args[0]);
    printf("%d\n", count);
    char * result = malloc(sizeof(args) + 1);
    int i;
    while(true){
        strcat(result, args[i]);
        printf("%d:%d\n", strlen(result), sizeof(args));
        if(strlen(result) == count)
            break;
        i++;
    }
    return result;
}



int main() {
    char * headers = "GET / HTTP/1.1\r\n";
    char wii[3][] = {"GGGGGGGGGGGG","BBBB","GGGGGGGGGGGG"};
    char * http_content = "GET /pony.txt HTTP/1.1\r\n"
        "Content-Type: text/json\r\n"
        "Content-Length: 255\r\n\r\n\r\n"
        "My Bodyyy";
    char * http_content2 = "GET /pony.txt HTTP/1.1\r\n"
        "Content-Type: text/json\r\n"
        "Content-Length: 13370";
    char result[2048];
    char body[2048];
    int res = headers_parse(http_content, result, body);
    printf("%d _%s_ %s\n", res, result, body);

    printf("(%s)\n", safe_strstr(http_content, "\r\n\r\n"));

    printf("(%s)\n", safe_strstr(http_content, "\r\n"));
    printf("(%s)\n", safe_strstr(http_content, "asfsaf"));
    printf("%s\n", header_value(http_content, "Content-Length"));

    printf("%s\n", header_value(http_content2, "Content-Length"));

    printf("%d %d\n", str_index(http_content, "GET"), str_index2(http_content, "GET"));
    printf("%d %d\n", str_index(http_content, " "), str_index2(http_content, " "));
    printf("%d %d\n", str_index(http_content, "\r\n"), str_index2(http_content, "\r\n"));

    printf("%s", http_content);

}