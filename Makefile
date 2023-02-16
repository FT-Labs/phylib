

SRC = device.c duration.c get_line_from_file.c xatonum.c
OBJ = ${SRC:.c=.o}

CC = gcc
CFLAGS = -std=gnu99 -pedantic

dur:
	${CC} -c ${CFLAGS} duration.c

all:
	echo

%.o: %.c
	${CC} -c ${CFLAGS} $<

.PHONY: all
