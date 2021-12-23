# WebDav server written in C by Gerben Aaltink

WebDav server based on selectors. 
Goals:
 - concurrency without blocking
 - low memory footprint 
 - compatible with gfs (Thunar file manager build-in client on Linux)
 - compatible with cadaver (CLI webdav client on Linux)

All operations are performed within one thread. 
By smart chunking requests do not block eachother. 

### Usage
 Make sure gcc is installed. You can check this by executing `gcc -v`. This project is tested with gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04).
 Execute in root: `make run`. This will create an executable named httpc. 
 For debugging:
   - `httpc 8888 --debug`
 Other parameters are mentioned at startup.
 You can now access dav://localhost:8888/ in your file manager. But probably you'll need to create a user first.

#### User management
 - Create:  `./httpc useradd`
 - Delete:  `./httpc userdel [username]` argument is optional.
 - List:    `./httpc userlist`
 - Update:  `./httpc useredit`

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
 - PUT on non-existing parent path crashes
 - Clean up request.c (Range header bug, strcpy for body should be memcpy, received is unused, tokenizedData can be pointer(saves a copy), remove commented code)
 - Remove warnings user.c 
 - .. protection
 - if first parameter starts with -- do not parse port
 - Request parsing crash if request top line corrupt
