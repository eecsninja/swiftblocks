PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
LIBDIR=$(PREFIX)/lib
DATADIR=$(PREFIX)/share/swiftblocks

all:
	make -C Source PREFIX=$(PREFIX) DATADIR=$(DATADIR)

install:
	install -m 755 Source/swiftblocks $(BINDIR)
	install -m 755 fmod/libfmod-3.61.so $(LIBDIR)
	mkdir -p $(DATADIR)/gfx
	mkdir -p $(DATADIR)/sound
	install -m 644 Resources/Graphics/* $(DATADIR)/gfx
	install -m 644 Resources/Sound/* $(DATADIR)/sound
