CC = clang
CFLAGS = -Weverything

all: null.out forget_to_free.out data_array.out print_release.out funny_release.out

clean:
	rm -f ./*.out

%.out: %.c
	$(CC) -g -o $@ $< $(CFLAGS)