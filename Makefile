CC=gcc
CFLAGS=-Wall -Werror -Wvla -O0 -std=c11 -g -fsanitize=address
LDFLAGS=-lm
BINARIES=main

all: $(BINARIES)

.PHONY: clean
clean:
	rm -f $(BINARIES)
	find . -type p -delete	

git:
	git add .
	git commit -m "m"
	git push