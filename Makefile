CC = gcc
CFLAGS = -g -ansi -pedantic -Wformat -Wall
LIBS = `curl-config --libs`
DEPS = energyAppFunctions.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

energyApp: api_download.o energyApp.o
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f *.o energyApp
