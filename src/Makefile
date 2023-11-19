IDIR = ../include/
CC = gcc
CFLAGS = -I$(IDIR)
soothsayer: parser.o autoc.o weighted_rec.o
	gcc parser.o weighted_rec.o autoc.o $(CFLAGS) -o soothsayer
parser.o: parser.c
	gcc -c parser.c $(CFLAGS)
weighted_rec.o: weighted_rec.c
	gcc -c weighted_rec.c $(CFLAGS)
autoc.o: autoc.c
	gcc -c autoc.c $(CFLAGS)
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o soothsayer
