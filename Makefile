CC = tcc 
CFLAGS =  *.c -o httpc
BIN =  ./httpc
PORT = 8888
BENCHMARK = ab -c 10 -n 2000

shared:
	cc -fPIC -shared -o httpc.so *.c

testd:
	gcc tests/*.c -o tests.o 
	./tests.o
build:
	$(CC) $(CFLAGS) 

static:
	cc *.c -static -o httpc-static

run:
	$(CC) $(CFLAGS) 
	./httpc 8888 --log-recv

deploy:
	scp httpc root@5.79.65.195:/root/httpc

debug:
	DEBUG=1 $(CC) $(CFLAGS) -bench -d -Wall -bt 10 -g -v -vv -MD -D"DEBUG=1"
	$(BIN) $(PORT) --debug

valgrind: debug
	valgrind ./httpc

info:
	$(CC) $(CFLAGS) 
	$(BIN) $(PORT) --info

link:
	echo "<html><body><pre>" > public/index.html
	tcc *.c -E >> public/index.html 
	echo "</pre></body></html>" >> public/index.html
	cat public/index.html 

all: link build static shared

bench_propfind:
	$(BENCHMARK) -m PROPFIND http://localhost:8888/public/

bench_get:
	$(BENCHMARK) -m GET http://localhost:8888/public/index.html

bench_ping:
	$(BENCHMARK) -m GET http://localhost:8888/ping/
