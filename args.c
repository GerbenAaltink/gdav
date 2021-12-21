#include <stdlib.h>

#include "args.h"
#include "functions.h"

void args_clean(int argc, char *argv[]){
    for(int i = 0; i < argc; i++)
        strcpy(argv[i], strtrim(argv[i],'""'));
}

bool arg_isset(int argc, char* argv[], char* name)
{
    for (int i = 0; i < argc; i++) {
        if (streq(argv[i], name))
            return true;
    }
    return false;
}

LOGLEVEL get_log_level_arg(int argc, char* argv[])
{
    if (arg_isset(argc, argv, "--debug"))
        return LOGLEVEL_DEBUG;
    if (arg_isset(argc, argv, "--info"))
        return LOGLEVEL_INFO;
    if (arg_isset(argc, argv, "--error"))
        return LOGLEVEL_ERROR;
    return LOGLEVEL_INFO;
}

int get_port_arg(int argc, char* argv[], int default_value)
{
    if (argc > 1)
        if (!streq(argv[1], "-"))
            return atoi(argv[1]);
    return default_value;
}
