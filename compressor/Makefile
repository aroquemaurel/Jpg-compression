.PHONY:all tests

TARGETS=compressor

all: $(TARGETS)

clean:
	@rm -f *.o *~ $(TARGETS) *.d

CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -fgnu89-inline -O3 
sources=$(wildcard *.c)

# compile
%.o: %.c %.h
	gcc -c $(CFLAGS) $*.c -o $*.o

%.d: %.c	
	echo “make $@“
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

echo:
	echo $(sources)

compressor: main.o dct-idct.o image.o linearization.o block.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

tests:
	make && ./test_script.sh


include $(sources:.c=.d)
