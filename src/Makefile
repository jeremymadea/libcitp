AR=ar
#CC=llvm-gcc
CC=gcc
#CFLAGS=-Wall -O2
CFLAGS=-DDEBUG -g -Wall
LFLAGS=-L. -lcitp

all: mediaserver lightingconsole

mediaserver: mediaserver.o citp.o parse.o ucsutils.o delete.o messages.o libcitp.a
	$(CC) $(CFLAGS) -o mediaserver mediaserver.o $(LFLAGS)

lightingconsole: lightingconsole.o libcitp.a
	$(CC) $(CFLAGS) -o lightingconsole messages.o lightingconsole.o $(LFLAGS)

mediaserver.o: mediaserver.c citp.h citptypes.h
	$(CC) $(CFLAGS) -o mediaserver.o mediaserver.c -c 

lightingconsole.o: lightingconsole.c citp.h citptypes.h
	$(CC) $(CFLAGS) -o lightingconsole.o lightingconsole.c -c

libcitp.a: citp.o parse.o delete.o ucsutils.o messages.o create.o build.o
	$(AR) rcs libcitp.a ucsutils.o build.o parse.o create.o delete.o citp.o
	
citp.o: citp.c citp.h
	$(CC) $(CFLAGS) -o citp.o citp.c -c 

parse.o: parse.c parse.h citptypes.h
	$(CC) $(CFLAGS) -o parse.o parse.c -c 

delete.o: delete.c delete.h citptypes.h
	$(CC) $(CFLAGS) -o delete.o delete.c -c 

ucsutils.o: ucsutils.c
	$(CC) $(CFLAGS) -o ucsutils.o ucsutils.c -c 

message.o: messages.c messages.h citptypes.h
	$(CC) $(CFLAGS) -o messages.o messages.c -c 

create.o: create.c create.h citptypes.h
	$(CC) $(CFLAGS) -o create.o create.c -c 

build.o: build.c citptypes.h
	$(CC) $(CFLAGS) -o build.o build.c -c 

clean:
	rm -f *.o mediaserver lightingconsole a.out libcitp.a





