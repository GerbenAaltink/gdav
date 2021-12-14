
#include "html.h"
#include "functions.h"
#include "url.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t html_index(char* document, char* path)
{
    char normalized_path[2048];
    normalized_path[0] = 0;
    strcpy(normalized_path, path);

    if (path[strlen(normalized_path)] != '/') {
        strcat(normalized_path, "/");
    }

    strcpy(document, "<DOCTYPE HTML!>\n");
    csprintf(document, "%s", "<HEAD>");
    csprintf(document, "<TITLE>%s</TITLE>", path);
    csprintf(document, "%s", "</HEAD>");
    csprintf(document, "<BODY>");
    csprintf(document, "<b>%s</b><br />\n", path);
    DIR* dir = opendir(path);
    struct dirent* d;
    while ((d = readdir(dir)) != NULL) {
        if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
            continue;
        char full_path[2048];
        full_path[0] = 0;
        sprintf(full_path, "%s%s", normalized_path, d->d_name);
        csprintf(document, "<a href=\"/%s\">%s</a><br />\n", url_encode(full_path), d->d_name);
    }
    closedir(dir);
    csprintf(document, "</BODY>\n");
    csprintf(document, "</HTML>\n");

    return strlen(document);
}