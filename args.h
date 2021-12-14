#pragma once
#include "log.h"
#include <stdbool.h>

bool arg_isset(int argc, char* argv[], char* name);

LOGLEVEL get_log_level_arg(int argc, char* argv[]);

int get_port_arg(int argc, char* argv[], int default_value);