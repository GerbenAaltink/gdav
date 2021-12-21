CC = cc
CFLAGS = main.c
BIN = ./static

all: format summary convert compile
	
format:
	clang-format -i -style=WebKit *.c urls.h static.h
	@echo "Formatting files:"
	@ls *.c urls.h static.h -w 1

summary:
	@echo "Static files:"
	@ls *.html *.map *.css *.js -w 1
	$(du * -sch | grep total)

convert:
	@echo "Compiling files:"
	@ls *.c *.h -w 1
	@./build

compile:
	@$(CC) $(CFLAGS) -o $(BIN)
	@echo "Source files updated. Binary created: $(BIN)"
