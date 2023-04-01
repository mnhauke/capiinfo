CC = /usr/bin/i686-w64-mingw32-gcc
WINDRES = /usr/bin/i686-w64-mingw32-windres

CFLAGS := -Wall

all: icon capiinfo.exe

icon:
	$(WINDRES) win32/capiinfo.rc capiinfo-res.o

capiinfo.exe: capiinfo.c
	$(CC) $(CFLAGS) capiinfo.c capiinfo-res.o -o $@

clean:
	rm -f capiinfo.exe capiinfo-res.o

copy:
	cp capiinfo.exe /data/VM-Transfer/mycapi/

