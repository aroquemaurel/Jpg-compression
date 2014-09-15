.PHONY:all tests

TARGETS=./compressor

all: $(TARGETS)

clean:
	@rm -f bin/*.o *~ $(TARGETS) dep/*.d

CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O3
sources=$(wildcard *.c)

# compile
bin/%.o: src/%.c
	gcc -c $(CFLAGS) src/$*.c -o bin/$*.o

dep/%.d: src/%.c	
	echo “make $@“
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	@sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

echo:
	echo $(sources)

compressor: bin/main.o bin/dct-idct.o bin/image.o
	$(CC) $(CFLAGS) $^ -o ./$@ -lm

tests:
	./tests/test_script.sh


include $(sources:.c=.d)
