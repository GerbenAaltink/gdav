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
 - Cleaner mime type resolver. Most content is worthless.
 - Add created timestamp to PROPFIND
 - Add last modified timestamp to PROPFIND
 - Add disk usage information to propfind 
 - Fix PROPFIND root directory
 - Allow empty files for PUT (create)
 - Make index page more beautiful. Also sort files
 - Lock meganism
 - Mimetypes en URL encoder apart releasen
