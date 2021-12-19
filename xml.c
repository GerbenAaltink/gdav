#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "malloc.h"
#include "path.h"
#include "url.h"
#include "xml.h"


//http://www.chiark.greenend.org.uk/doc/libg2c0/cpp.html
int write_xml_node(char* dest, char* name, char* value)
{
    csprintf(dest, "<D:%s>%s</D:%s>", name, value, name);
    return strlen(dest);
}

int write_xml_node_int(char* dest, char* name, int value)
{
    
    char chars[10];
    sprintf(chars, "%d", value);
    return write_xml_node(dest, name, chars);
}


const char * xml_response_node(char* path)
{
    Path* info = path_info(path);

    char prop[10240];
    bzero(prop, sizeof(prop));

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

    char status[10240];

    bzero(status, sizeof(status));
    write_xml_node(status, "status", "HTTP/1.1 200 OK");

    char props[10240];

    bzero(props, sizeof(props));
    write_xml_node(props, "prop", prop);

    char propstat[10240];

    bzero(propstat, sizeof(propstat));
    write_xml_node(propstat, "propstat", strcat(props, status));

    char href[10240];

    bzero(href, sizeof(href));
    char url[10240];

    bzero(url, sizeof(url));
    sprintf(url, "/%s", info->path);
    write_xml_node(href, "href", (char*)url_encode(url));

    static char response[10240];

    bzero(response, sizeof(response));

    write_xml_node(response, "response", strcat(href, propstat));
    
    return response;
}