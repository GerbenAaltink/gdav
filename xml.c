#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "malloc.h"
#include "path.h"
#include "url.h"
#include "xml.h"

int write_xml_node(char* dest, char* name, char* value)
{
    //char startTag[1000];
    csprintf(dest, "<D:%s>%s</D:%s>", name, value, name);
    //sprintf(startTag, "<D:%s>%s</D:%s>", name, value, name);
    //strcat(dest, startTag);
    return strlen(dest);
}

int write_xml_node_int(char* dest, char* name, int value)
{
    char chars[10];
    sprintf(chars, "%d", value);
    return write_xml_node(dest, name, chars);
}

char* xml_response_node(char* path)
{
    Path* info = path_info(path);

    char* prop = (char*)calloc(9000, sizeof(char));
    write_xml_node(prop, "displayname", info->name);

    write_xml_node_int(prop, "iscollection", info->is_dir ? 1 : 0);
    if (info->is_dir) {
        write_xml_node(prop, "getcontentlength", "-DIR-");
    } else {
        write_xml_node_int(prop, "getcontentlength", info->size);
    }
    write_xml_node_int(prop, "isroot", strcmp(path, "/") == 0 ? 1 : 0);
    write_xml_node_int(prop, "ishidden", strncmp(info->name, ".", 1) ? 1 : 0);

    write_xml_node(prop, "getcontenttype", info->mime_type);
    if (info->is_dir) {
        write_xml_node(prop, "resourcetype", "<D:collection />");
    }

    char* status = (char*)calloc(100, sizeof(char));
    write_xml_node(status, "status", "HTTP/1.1 200 OK");

    char* props = (char*)calloc(4096, sizeof(char));
    write_xml_node(props, "prop", prop);

    char* propstat = (char*)calloc(4096, sizeof(char));
    write_xml_node(propstat, "propstat", strcat(props, status));

    char* href = (char*)calloc(1024, sizeof(char));
    char url[1024];
    sprintf(url, "/%s", info->path);
    write_xml_node(href, "href", (char*)url_encode(url));

    char* response = (char*)calloc(4069, sizeof(char));

    write_xml_node(response, "response", strcat(href, propstat));
    free(prop);
    free(props);
    free(status);
    free(propstat);
    free(href);
    httpc_free(info);
    return response;
}
