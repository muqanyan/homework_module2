CC = g++
CFLAGS = -std=c++11

all: init destroy set check

init: init.cpp
    $(CC) $(CFLAGS) -o init init.cpp

destroy: destroy.cpp
    $(CC) $(CFLAGS) -o destroy destroy.cpp

set: set.cpp
    $(CC) $(CFLAGS) -o set set.cpp

check: check.cpp
    $(CC) $(CFLAGS) -o check check.cpp

clean:
    rm -f init destroy set check

