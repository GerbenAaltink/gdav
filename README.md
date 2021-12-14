# WebDav server written in C by Gerben Aaltink

WebDav server based on selectors. 
Goals:
 - concurrency without blocking
 - low memory footprint 
 - compatible with gfs (Thunar file manager build-in client on Linux)
 - compatible with cadaver (CLI webdav client on Linux)

All operations are performed within one thread. 
By smart chunking requests do not block eachother. 

### Supported methods:
 - PROPFIND
 - PUT
 - DELETE
 - MKCOL
 - GET
 - OPTIONS
 - HEAD

### Missing methods:
 - MOVE
 - COPY
 - LOCK

### Backlog:
 - Add created timestamp to PROPFIND
 - Add last modified timestamp to PROPFIND
 - Add disk usage information to PROPFIND 
 - Fix PROPFIND root directory. / does not work.
 - Make index page more beautiful. Also sort files
 - Lock meganism
 - Create gist for Mimetype
 - Create gist for url encoder/decoder 
 - Clean up request.c (Range header bug, strcpy for body should be memcpy, received is unused, tokenizedData can be pointer(saves a copy), remove commented code)
