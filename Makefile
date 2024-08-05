CC=gcc
STD=c99

INCLUDE=-Iinc/

CFLAGS=-std=$(STD) -O2

OUTDIR=bin

SRC=src/main.c src/pst.c
OUT=$(OUTDIR)/psttest.o


all: $(SRC)
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) -o $(OUT)

PHONY: clean

clean:
	rm -f ./*.o
