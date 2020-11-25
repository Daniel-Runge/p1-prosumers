CC = clang
CFLAGS1 = -g
CFLAGS2 = -g -c -Wall
LIBS = `curl-config --libs`

energyApp: energyApp.o
	$(CC) $(CFLAGS1) -o $@ $< $(LIBS)

energyApp.o: energyApp.c
	$(CC) $(CFLAGS2) $<

clean:
	rm -f energyApp.o energyApp