#pragma once

int write_xml_node(char* dest, char* name, char* value);
int write_xml_node_int(char* dest, char* name, int value);
const char* xml_response_node(char* path);
