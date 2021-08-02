IDIR = src
CC = gcc
CFLAGS = -I$(IDIR) -I/usr/local/include -Wall -Wpedantic

ODIR = obj
LDIR = lib

LIBS = -lsodium

STATIC_LIBS =

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(STATIC_LIBS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *~ $(IDIR)/*~
