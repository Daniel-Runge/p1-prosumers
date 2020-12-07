CC = gcc
CFLAGS = -g -pedantic -Wformat -Wall
LIBS = `curl-config --libs` -ljson-c
DEPS = energyAppFunctions.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

energyApp: api_download.o store_data.o analyze.o printprogram.o energyApp.o HandleSettings.o HandleInput.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

exe: api_download.o store_data.o analyze.o printprogram.o energyApp.o
	x86_64-w64-mingw32-gcc -o energyApp.exe $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o energyApp
