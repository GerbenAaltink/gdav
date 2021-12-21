CC = cc
CFLAGS =  *.c static/static.c -o httpc -Wall
BIN =  ./httpc
PORT = 8888
BENCHMARK = ab -c 10 -n 2000 -P root:root

all: build

shared:
	cc -fPIC -shared -o httpc.so *.c

testd:
	gcc tests/*.c -o tests.o 
	./tests.o

static:
	$(MAKE) -C static/ all
	#cc *.c -static -o httpc-static

build:
	$(CC) $(CFLAGS) 

run: static build
	$(BIN) $(PORT)  

deploy: static build
	scp httpc root@5.79.65.195:/root/httpc

debug: static
	DEBUG=1 $(CC) $(CFLAGS) -Wall -g -MD -D"DEBUG=1"
	$(BIN) $(PORT) --debug

valgrind: static build
	valgrind $(BIN) $(PORT) --debug

test:
	$(MAKE) -C tests all

link:
	echo "<html><body><pre>" > public/index.html
	tcc *.c -E >> public/index.html 
	echo "</pre></body></html>" >> public/index.html
	cat public/index.html 

format:
	clang-format -i -style=WebKit *.c *.h
			
bench_propfind:
	@echo $BENCHMARK
	$(BENCHMARK) -m PROPFIND http://localhost:8888/public/

bench_get:
	@echo $BENCHMARK
	$(BENCHMARK) -m GET http://localhost:8888/public/index.html

bench_ping:
	@echo $BENCHMARK
	$(BENCHMARK) -m GET http://localhost:8888/ping

