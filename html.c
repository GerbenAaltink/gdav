
#include "html.h"
#include "functions.h"
#include "url.h"
#include "sockets.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t html_index(char* document, Client * client)
{
    char normalized_path[2048];
    czero(normalized_path);

    strcpy(normalized_path, client->request->path);
    if (normalized_path[strlen(normalized_path) - 1] != '/') {
        strcat(normalized_path, "/");
    }

    strcpy(document, "<DOCTYPE HTML!>\n");
    csprintf(document, "%s", "<HEAD>");
    csprintf(document, "<TITLE>%s</TITLE>", client->request->path);
    csprintf(document, "%s", "</HEAD>");
    csprintf(document, "<BODY>");
    csprintf(document, "<b>%s</b><br />\n", client->request->path);
    DIR* dir = opendir(client->request->realPath);
    struct dirent* d;
    while ((d = readdir(dir)) != NULL) {
        if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
            continue;
        char full_path[4096];
        czero(full_path);
        csprintf(full_path, "%s%s", normalized_path, d->d_name);
        csprintf(document, "<a href=\"%s\">%s</a><br />\n", url_encode(full_path), d->d_name);
    }
    closedir(dir);
    csprintf(document, "</BODY>\n");
    csprintf(document, "</HTML>\n");

    return strlen(document);
}
