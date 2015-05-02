# Andrew Wilder

TARGET = hashmaptest
CFILES = $(wildcard *.c)
OFILES = $(CFILES:%.c=%.o)

LD = gcc
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Wextra -Werror
LFLAGS =

all : $(OFILES)
	@echo "[LD] Linking $(TARGET)"
	@$(LD) $^ -o $(TARGET) $(LFLAGS)

%.o : %.c
	@echo "[CC] $@"
	@$(CC) -c $(CFLAGS) $^ -o $@

clean :
	@echo "Removing binaries"
	@rm -f *.o $(TARGET)

release : CFLAGS += -O2
release : clean all

debug : CFLAGS += -g
debug : clean all
debug :
	@echo "!!!!! Built using debug flag !!!!!"

