CC=gcc
CFLAGS=-pipe -O3 -Iinclude -Wall -Wno-builtin-declaration-mismatch
LIBS=-L./SDL2main.lib -lopengl32 # DEBUG
# LIBS=-Wl,-subsystem,windows -mwindows -L./SDL2main.lib # RELEASE
OUT=quick-cas.exe
COMP=$(CC) $(CFLAGS) -c $<
LINK=$(CC) *.o SDL2.dll -o $(OUT) $(LIBS)

include build.mk

clean:
	rm *.o $(OUT)

