ifeq ($(CROSS_COMPILE),)
	CROSS_COMPILE := arm-none-linux-gnueabi-
endif
ifeq ($(ARCH), arm)
	CC := $(CROSS_COMPILE)gcc
else
	CC := gcc
endif

PROG := devkmem
SRC := $(PROG).c

all:
	$(CC) $(SRC) -o $(PROG)

clean:
	rm -f $(PROG)
