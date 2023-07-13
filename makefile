
CC = gcc
CFLAGS = -std=c99 -Wl,--subsystem,windows -pedantic -I./include -shared

src = $(wildcard *.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d) 

.PHONY: build all clean

build: tiny-json.dll

all: clean build

clean:
	rm -rf $(dep)
	rm -rf $(obj)
	rm -rf *.dll

	
tiny-json.dll: tiny-json.o
	gcc $(CFLAGS) -o $@ $^

-include $(dep)

%.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@