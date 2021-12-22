#include "args.h"
#include "humanize.h"
#include "log.h"
#include "malloc.h"
#include "server.h"
#include "stats.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "user.h"

#define SEND_FILE_BUFFER_SIZE 4096

void set_log_level_arg(int argc, char* argv[])
{
    LOG_DEBUG("Log level compiled: %d\n", loglevel);
    loglevel = get_log_level_arg(argc, argv);
    LOG_INFO("Log level is set to %d\n", loglevel);
    set_log_level(loglevel);
}

void exit_handler(int signum)
{
    printf("%s\n", strstat(stats));
    char* humanized_allocated = humanize_bytes(httpc_allocated);
    char* humanized_freed = humanize_bytes(httpc_freed);
    char* humanized_allocated_max = humanize_bytes(httpc_allocated_max);

    printf("Allocated:\t%s\tFreed:\t%s\tMax usage:\t%s\n", humanized_allocated, humanized_freed, humanized_allocated_max);
    free(humanized_allocated);
    free(humanized_freed);
    free(humanized_allocated_max);
    exit(0);
}

void helptext()
{
    printf("WebDav Server - Gerben Aaltink - %s %s\n\n", __DATE__, __TIME__);
    printf("[PORT]          Port number. Defuults to 8888.\n");
    printf("--log-recv      Log data received from client.\n");
    printf("--log-send      Log data sent from client.\n");
    printf("--debug         Show debug messages.\n");
    printf("--info          Show info messages.\n");
    printf("--error         Show only errors. Production mode.\n");
    printf("--stats         Show stats after every closing connection.\n\n");
}

#ifndef TESTING
int main(int argc, char* argv[])
{
    
    args_clean(argc, argv);

    user_load_file(USER_FILE); 
    if(user_cli(argc, argv))
    {
        return 0;
    }
    helptext();
    signal(SIGINT, exit_handler);
    signal(SIGPIPE, SIG_IGN);
    set_log_level_arg(argc, argv);
    char port[6];
    sprintf(port, "%d", get_port_arg(argc, argv, 8888));
    LOG_RECV = arg_isset(argc, argv, "--log-recv");
    LOG_SEND = arg_isset(argc, argv, "--log-send");
    LOG_STATS = arg_isset(argc, argv, "--log-stats");
    LOG_INFO("Listening on port %s %s\n", port, __FUNCTION__);
    serve("0.0.0.0", port);
    return 1;
}
#endif
