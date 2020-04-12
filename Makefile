IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lpthread

_DEPS = pub.h battle.h fighters-map.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = pub.o battle.o fighters-map.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pub: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 