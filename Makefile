CC = tcc 
CFLAGS =  *.c static/static.c -o httpc
BIN =  ./httpc
PORT = 8888
BENCHMARK = ab -c 10 -n 2000 -P x:x

shared:
	cc -fPIC -shared -o httpc.so *.c

testd:
	gcc tests/*.c -o tests.o 
	./tests.o

static:
	cd static/
	make
	cd ..
	#cc *.c -static -o httpc-static

build: static
	$(CC) $(CFLAGS) 

run: static
	$(CC) $(CFLAGS) 
	./httpc 8888 --log-recv

deploy:
	scp httpc root@5.79.65.195:/root/httpc

debug: static
	DEBUG=1 $(CC) $(CFLAGS) -bench -d -Wall -bt 10 -g -v -vv -MD -D"DEBUG=1"
	$(BIN) $(PORT) --debug

valgrind: debug
	valgrind ./httpc

info: static
	$(CC) $(CFLAGS) 
	$(BIN) $(PORT) --info

link:
	echo "<html><body><pre>" > public/index.html
	tcc *.c -E >> public/index.html 
	echo "</pre></body></html>" >> public/index.html
	cat public/index.html 

all: link build static shared

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

