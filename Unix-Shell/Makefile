COMMANDS := $(patsubst src/commands/%.c,build/bin/%,$(wildcard src/commands/*.c))

all: build/main $(COMMANDS)

build/main: src/shell/main.c
	gcc -o $@ $<

build/bin/%: src/commands/%.c
	gcc -o $@ $<
