CC = gcc
CFLAGS1 = -g
CFLAGS2 = -g -c -Wall
LIBS = `curl-config --libs`
DEPS = energyAppFunctions.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS2)

energyApp: energyApp.o
	$(CC) $(CFLAGS1) -o $@ $< $(LIBS)

clean:
	rm -f *.o energyApp
