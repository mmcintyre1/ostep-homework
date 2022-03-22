CC = clang
CFLAGS = -Weverything

all: null.out

clean:
	rm -f ./*.out

%.out: %.c
	$(CC) -g -o $@ $< $(CFLAGS)