CC = gcc
CFLAGS = -g -ansi -pedantic -Wformat -Wall
LIBS = `curl-config --libs`
DEPS = energyAppFunctions.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

energyApp: energyApp.o api_download.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f *.o energyApp
