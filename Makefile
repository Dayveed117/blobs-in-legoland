all: prog

CC = gcc
CFLAGS = -std=c99 -Wall -g

prog: obj/main.o obj/pixel.o obj/frame.o obj/blob.o obj/io.o
	${CC} ${CFLAGS} $^ -o $@

obj/main.o: src/main.c src/pixel.h src/frame.h src/blob.h src/io.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/pixel.o: src/pixel.c src/pixel.h
	${CC} ${CFLAGS} -c $< -o $@

obj/frame.o: src/frame.c src/frame.h src/pixel.h
	${CC} ${CFLAGS} -c $< -o $@

obj/blob.o: src/blob.c src/blob.h src/pixel.h src/frame.h
	${CC} ${CFLAGS} -c $< -o $@

obj/io.o : src/io.c src/io.h
	${CC} ${CFLAGS} -c $< -o $@

run: prog
	./prog

.PHONY: clean

clean:
	rm -rf obj/* prog
