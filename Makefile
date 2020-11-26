CC = gcc
CFLAGS = -g -pedantic -Wformat -Wall
LIBS = `curl-config --libs`
DEPS = energyAppFunctions.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -ljson-c

energyApp: api_download.o store_data.o analyze.o printprogram.o energyApp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) -ljson-c

clean:
	rm -f *.o energyApp
