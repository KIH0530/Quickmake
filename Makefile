CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic
LDFLAGS := -lm

quickmake: quick-make.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f quickmake.exe
