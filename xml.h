#pragma once

#include <stdlib.h>

int write_xml_node(char* dest, char* name, char* value);
int write_xml_node_int(char* dest, char* name, int value);
int write_xml_node_size(char* dest, char* name, size_t value);
const char* xml_response_node(char* root, char* path);
