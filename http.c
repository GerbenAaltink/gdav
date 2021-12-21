#include "xml.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "html.h"
#include "http.h"
#include "log.h"
#include "malloc.h"
#include "mimetype.h"
#include "path.h"
#include "static/static.h"
#include <sys/stat.h>

HTTP_STATUS http_status_response(Client* client, int status, char* message,
    char* body)
{
    char response[100 + strlen(body)];
    sprintf(response, "HTTP/1.1 %d %s\r\nContent-Length: %zu\r\n\r\n", status,
        message, strlen(body));
    if (strlen(body))
        strcat(response, body);
    return sendAll(client, response) > 0 ? HTTP_OK : HTTP_ERROR;
}

HTTP_STATUS http_response_200(Client* client)
{
    return http_status_response(client, 201, "OK", "OK");
}

HTTP_STATUS http_response_201(Client* client)
{
    return http_status_response(client, 201, "OK", "OK");
}
HTTP_STATUS http_response_404(Client* client)
{
    return http_status_response(client, 404, "Not Found", "Not Found");
}

HTTP_STATUS http_response_401(Client* client){
    char response[] = "HTTP/1.1 401 Unauthorized\r\n"
        "WWW-Authenticate: Basic realm=\"WebDav\"\r\n"
        "Content-Length: 0\r\n\r\n"
        "\r\n";
    return sendAll(client, response) > 0 ? HTTP_OK : HTTP_ERROR;
}

HTTP_STATUS http_html_index(Client* client)
{
    char document[1024 * 1024];
    size_t content_length = html_index(document, client->request->realPath);
    char response[sizeof(document) + 1024];
    sprintf(response, "HTTP/1.1 200 OK\r\n"
                      "Content-Length: %zu\r\n"
                      "Content-Type: text/html\r\n\r\n%s",
        content_length, document);
    return sendAll(client, response) > 0 ? HTTP_OK : HTTP_ERROR;
}

HTTP_STATUS http_options(struct client_info* client)
{
    Path * info = path_info(client->request->realPath);
    if(!info->exists)
    {
        free(info);
        return http_response_404(client);
    } 
    char response[] = "HTTP/1.1 200 OK\r\n"
                     "Content-Length: 0\r\n"
                     "Content-Type: text/xml\r\n"
                     "Allow: GET, HEAD, PUT, POST, DELETE, PROPFIND, PROPPATCH, "
                     "MKCOL, LOCK, UNLOCK, MOVE, COPY\r\n"
                     "DAV: 1,2\r\n"
                     "MS-Author-Via: DAV\r\n\r\n";
    return sendAll(client, response) > 0 ? 1 : 2;
}

HTTP_STATUS http_mkcol(Client* client)
{
    Path* info = path_info(client->request->realPath);
    bool exists = info->exists;
    httpc_free(info);
    if (exists == false)
        mkdir(client->request->realPath, 0700);
    char response[200];
    sprintf(response, "HTTP/1.1 201 OK\r\nContent-Length: 2\r\n\r\nOK");
    return sendAll(client, response) > 0 ? HTTP_OK : HTTP_ERROR;
}

HTTP_STATUS http_head(Client* client)
{
    Path* info = path_info(client->request->realPath);
    bool exists = info->exists;
    size_t size = info->size;
    httpc_free(info);
    if (!exists) {
        return http_response_404(client);
    }
    char response[200];
    sprintf(response,
        "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\nContent-Type: %s\r\n\r\n",
        size, get_mimetype(client->request->realPath));
    return sendAll(client, response) > 0 ? HTTP_OK : HTTP_ERROR;
}

HTTP_STATUS http_delete(struct client_info* client)
{
    Path* info = path_info(client->request->realPath);
    if (info->exists == false) {
        httpc_free(info);
        return http_response_404(client);
    }
    if (info->is_dir == 1)
        rmdir(info->path);
    else
        unlink(info->path);
    httpc_free(info);
    return http_response_201(client);
}

int drain(Client* client)
{
    if (client->request->contentLength == 0)
        return 0;

    int size = client->request->contentLength - client->request->bytesLeft;
    if (size < 1)
        return 0;
    char buff[size + 1];
    int received = 0;
    while (received != size)
        received += recv(client->socket, buff, size - received, 0);
    return received;
}

HTTP_STATUS http_put(struct client_info* client)
{
    LOG_DEBUG("#%d PUT %zu/%zu/%zu/%zu/%zu\n", client->socket, client->bodyReceived, client->progress->size, client->request->contentLength, client->received, strlen(client->request->headers));
    
    

    if (client->request->bytesLeft == 0 && client->request->contentLength != 0) {
        // No data received
        client->writing = false;
        client->reading = true;
        return 0;
    }
    Path* info = path_info(client->request->realPath);
    bool exists = info->exists;

    if (!exists && client->request->contentLength == 0) {
        // Create mode for empty file
        FILE* f = fopen(info->path, "wb+");
        fclose(f);
    }

    if (client->progress->size != client->request->contentLength && client->request->bytesLeft) {
        if (exists && client->progress->size == 0) {
            unlink(info->path);
        }
        FILE* fd = fopen(info->path, "ab+");
        fseek(fd, 0L, SEEK_END);
        fwrite(client->request->body, sizeof(char), client->request->bytesLeft, fd);
        fclose(fd);
        client->progress->size += client->request->bytesLeft;
        client->request->bytesLeft = 0;

    }

    httpc_free(info);
    
    client->reading = true;
    client->writing = false;
        
    if (client->progress->size == client->request->contentLength) {
        client->progress->size = 0;
        client->request->bytesLeft = 0;
       
        return http_response_200(client);
    }
    return 0;
}

char* join_path(char* pDirectory, char* pName)
{
    char* result = httpc_malloc(strlen(pDirectory) + strlen(pName) + 3);
    strcpy(result, pDirectory);
    if (pDirectory[strlen(pDirectory) - 1] != '/')
        strcat(result, "/");
    strcat(result, pName);
    return result;
}

bool valid_path(char* pName)
{
    return strcmp(pName, ".") != 0 && strcmp(pName, "..") != 0;
}

int http_propfind(struct client_info* client)
{

    Path* info = path_info(client->request->realPath);

    if (info->exists == false) {
        httpc_free(info);
        return http_response_404(client);
    }
    char content[1024*1024];
    char xml_header[] = "<?xml version=\"1.0\" encoding=\"utf-8\" "
                        "?><D:multistatus xmlns:D=\"DAV:\">";
    strcpy(content, xml_header);

    // TODO: move int conversion to request
    int depth = strncmp(client->request->depth, "0", 1) == 0 ? 0 : 1;
    if (info->is_dir == 0 || depth == 0) {
        strcat(content, xml_response_node(info->path, client->request->path));
    } else {
        strcat(content, xml_response_node(info->path, client->request->path));

        DIR* d;
        struct dirent* dir;
        d = opendir(info->path);

        while ((dir = readdir(d)) != NULL) {
            if (!valid_path(dir->d_name))
                continue;
            char* realPath = join_path(info->path, dir->d_name);
            char* relativePath = join_path(client->request->path, dir->d_name);
            strcat(content, xml_response_node(realPath, relativePath));
            httpc_free(realPath);
            httpc_free(relativePath);
        }
        closedir(d);
        free(dir);
    }

    char xml_footer[] = "</D:multistatus>";
    strcat(content, xml_footer);

    char document[strlen(content)+1024];
    sprintf(document,
        "HTTP/1.1 207 OK\r\nContent-Length: %zu\r\n"
        "Content-Type: text/xml; charset=\"utf-8\"\r\n"
        "\r\n%s",
        strlen(content), content);


    int status = sendAll(client, document) < 1 ? 2 : 1;

    httpc_free(info);

    return status;
}

HTTP_STATUS http_response_static(Client* client)
{
    char* content = gdav_static_blob(client->request->path);
    int length = strlen(content);
    char headers[1024];
    if (client->progress->size == 0) {
        sprintf(headers, "HTTP/1.1 200 OK\r\n"
                         "Content-Length: %zu\r\n"
                         "Content-Type: %s\r\n"
                         "\r\n",
            strlen(content), get_mimetype(client->request->path));
        if (sendAll(client, headers) < 1) {
            return 2;
        }
    }
    char* data = content + client->progress->size;

    int bytes_left = strlen(data);
    int buffer_size = SOCKET_WRITE_BUFFER_SIZE > bytes_left ? bytes_left : SOCKET_WRITE_BUFFER_SIZE;
    int sent = sendAllN(client, data, buffer_size);

    //int result = sendAll(client, data) < 1 ? 2 : 1;
    free(content);
    if (sent < 1) {
        return 2;
    }
    client->progress->size += sent;
    if (client->progress->size == length) {
        return 1;
    }
    return 0;
}

HTTP_STATUS http_route_get(Client* client)
{
    if (streq(client->request->path, "/ping"))
        return http_status_response(client, 200, "PONG", "PONG");
    if (gdav_static_match(client->request->path) != -1) {
        return http_response_static(client);
    }

    Path* info = path_info(client->request->realPath);
    bool exists = info->exists;
    bool is_dir = info->is_dir;
    size_t fileSize = info->size;
    httpc_free(info);
    if (!exists) {
        return http_response_404(client);
    }
    if (is_dir) {
        return http_html_index(client);
    }

    char buffer[65];

    size_t range_end = client->request->is_range && client->request->range_end > 0 ? client->request->range_end : fileSize - 1;
    size_t content_length = client->request->is_range ? range_end - client->request->range_start + 1 : fileSize;

    if (client->progress->size == 0) {

        int http_status = client->request->is_range ? 206 : 200;
        sprintf(buffer, "HTTP/1.1 %d OK\r\n", http_status);
        if (sendAll(client, buffer) < 1)
            return 2;

        sprintf(buffer, "Content-Length: %zu\r\n", content_length);
        if (sendAll(client, buffer) < 1)
            return 2;

        sprintf(buffer, "Content-Type: %s\r\n",
            get_mimetype(client->request->realPath));
        if (sendAll(client, buffer) < 1)
            return 2;

        sprintf(buffer, "Accept-Ranges: bytes\r\n");
        if (sendAll(client, buffer) < 1)
            return 2;

        if (client->request->is_range) {
            sprintf(buffer, "Content-Range: bytes %zu-%zu/%zu\r\n", client->request->range_start, range_end, fileSize);
            if (sendAll(client, buffer) < 1)
                return 2;
        }

        strcpy(buffer, "\r\n");
        if (sendAll(client, buffer) < 1)
            return 2;
    }

    if (content_length != client->progress->size) {
        FILE* fd = fopen(client->request->realPath, "rb");
        size_t offset = client->request->is_range ? client->request->range_start : 0;
        fseek(fd, offset + client->progress->size, SEEK_SET);
        int buffSize = SOCKET_WRITE_BUFFER_SIZE > content_length - client->progress->size
            ? content_length - client->progress->size
            : SOCKET_WRITE_BUFFER_SIZE;
        char buff[SOCKET_WRITE_BUFFER_SIZE];
        long chunkSize = fread(buff, 1, buffSize, fd);
        fclose(fd);
        int bytesSent = sendAllN(client, buff, chunkSize);
        if (bytesSent < 1)
            return 2;
        client->progress->size += bytesSent;
    }
    LOG_DEBUG("Progress: get %ld/%ld\n", client->progress->size, content_length);
    if (client->request->is_range) {
        LOG_INFO("#%d Range %zu-%zu/%zu\n", client->socket, client->request->range_start, range_end, fileSize);
        LOG_INFO("Progress: get %ld/%ld %ld\n", client->progress->size, content_length, range_end - client->request->range_start);
    }
    if (client->progress->size == content_length) {
        return 1;
    }
    
    client->reading = false;
    client->writing = true;
    return 0;
}
