import socket 
import pathlib

class Client:

    def __init__(self, host, port, path="/"):
        self.host = host
        self.port = port 
        self.path = path 
        self.socket = socket.socket()
        self.on_progress = None
        
    def connect(self):
        self.socket.connect((self.host, self.port))

    def close(self):
        self.socket.close()

    def put(self, local_path, remote_path, on_progress):
        path = pathlib.Path(local_path)
        length = path.stat().st_size
        headers = f"PUT {remote_path} HTTP/1.1\r\nContent-Length: {length}\r\nConnection: Keep-Alive\r\n\r\n"


        self.socket.send(headers.encode())

        previous_percentage = 0
        bytes_sent = 0

        with path.open('rb') as f:
            while(True):
                data = f.read(1024)
                if not data:
                    break
                self.socket.send(data)
                bytes_sent += len(data)
                percentage = int((bytes_sent / length) * 100)
                if(percentage > previous_percentage):
                    print(f"Progress: {percentage}")
                    previous_percentage = percentage
                    if(on_progress):
                        on_progress(previous_percentage, percentage, local_path, remote_path)
        self.socket.recv(1024)        

    def __enter__(self):
        self.connect()
        return self

    def __exit__(self, *args, **kwargs):
        self.close()