from ctypes import *
so_file = "./httpc.so"
my_functions = CDLL(so_file)
print(type(my_functions))
print(my_functions);
print(my_functions.__dict__)
my_functions.loglevel = 2;
my_functions.log_debug("AAAAAA\n\n");
#print(my_functions.parseRequest("GET / HTTP/1.1\r\nContent-Length: 10\r\nDepth: 0\r\n\r\n"))