#pragma once

char * json_escape_string(char * str);
char * json_unescape_string(char * str);
char * json_key_value(char * str, char * key, char * value);
char * json_object(char * result, int count, char *values[]);
char * json_array(char * result, int count, char *values[]);
