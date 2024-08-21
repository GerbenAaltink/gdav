CC = gcc
CFLAGS =  *.c static/static.c -o httpc -Wall -luuid
BIN =  ./httpc
PORT = 8888
BENCHMARK = ab -c 10 -n 2000 -P root:root

all: static_resources build

shared:
	cc -fPIC -shared -o httpc.so *.c

testd:
	gcc tests/*.c -o tests.o 
	./tests.o


build: test
	$(CC) $(CFLAGS) 

static_resources:
	$(MAKE) -C static/ all
	#cc *.c -static -o httpc-static
release: static_resources test
	# static does not work with tcc
	$(CC) $(CFLAGS) -static

run: build
	$(BIN) $(PORT)  

deploy: release
	scp httpc root@5.79.65.195:/root/httpc

debug: static_resources tests
	DEBUG=1 $(CC) $(CFLAGS) -Wall -g -MD -D"DEBUG=1"
	$(BIN) $(PORT) --debug --log-recv --log-send

valgrind: release
	valgrind -s $(BIN) $(PORT) --debug

test:
	$(MAKE) -C tests all

link:
	echo "<html><body><pre>" > public/index.html
	tcc *.c -E >> public/index.html 
	echo "</pre></body></html>" >> public/index.html
	cat public/index.html 

format:
	clang-format -i -style=WebKit *.c *.h

bench: bench_propfind bench_get bench_ping

bench_propfind:
	@echo $BENCHMARK
	$(BENCHMARK) -m PROPFIND http://localhost:8888/public/

bench_get:
	@echo $BENCHMARK
	$(BENCHMARK) -m GET http://localhost:8888/public/index.html

bench_ping:
	@echo $BENCHMARK
	$(BENCHMARK) -m GET http://localhost:8888/ping

