#include <string.h>

#include "malloc.h"
#include "path.h"

#include "mimetype.h"
#include <sys/stat.h>

Path* path_info(char* path)
{

    Path* result = (Path*)httpc_malloc(sizeof(Path));
    result->extension = strchr(path, '.');
    result->name = strrchr(path, '/');

    if (result->name == NULL) {
        result->name = path;
    } else {
        result->name = result->name + 1;
    }
    result->path = path;
    result->relativePath = path;
    if (result->relativePath[0] == '/')
        result->relativePath++;
    struct stat stbuf;
    if (stat(path, &stbuf) == -1) {
        result->exists = false;
        result->size = 0;
        result->is_dir = false;
    } else {
        result->exists = true;
        result->is_dir = S_ISREG(stbuf.st_mode) == 0;
        if (result->is_dir) {
            result->mime_type = "unix/directory";
        } else {
            result->mime_type = (char*)get_mimetype(path);
        }

        result->size = stbuf.st_size;
    }
    return result;
}
