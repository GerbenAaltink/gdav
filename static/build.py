#!/usr/bin/env python3

import pathlib
import os 
import json

root_url = "/$gdav/static/"

#urls = {}

files = {}

for f in pathlib.Path(".").glob("*"):
    if not f.suffix in ['.css', '.js','.html','.map']:
        continue
    underscore_name = f.name.replace(".","_")
    header_path = underscore_name + ".h"
    url = root_url + f.name
    os.system(f"xxd -i {f.name} {header_path}")
#    urls[root_url + f.name] = f.name.replace("_", ".")
    define_name = "GDAV_STATIC_URL_" + underscore_name.upper()  
    files[underscore_name] = url
    with open(header_path, 'a') as fio:
        fio.write("\n")
        fio.write(define_name + " = ")
        fio.write(f"\"{url}\";")
        fio.write("\n");

with open('urls.h', 'w+') as fio:
    for f in files.keys():
        fio.write(f"#include \"{f}.h\"\n")
    fio.write("\n")

    fio.write("const char * gdav_static_urls[] = ")
    carray = json.dumps([str(f) for f in files.values()],indent=2)
    carray = "{" + carray.strip("[").strip("]") + "};"
    fio.write(carray)
    fio.write("\n")
    
    fio.write("const unsigned char * gdav_static_blobs[] = ")
    #carray =  json.dumps([str(f) for f in files.keys()], indent=2)
    carray = "{" + ",\n  ".join(list(files.keys())) + "};"
    fio.write(carray)
    fio.write("\n")

    url_count = len(files.values())

    fio.write(f"const int gdav_static_urls_count = {url_count};")
    fio.write("\n")

os.system("tcc main.c -o gdav_static")
exit(0)
lines = []
for url, target in urls.items():
    lines.append(f"FRONTEND_URL_{target.upper()} = \"{url}\"")
