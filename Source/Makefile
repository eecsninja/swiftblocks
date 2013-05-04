PREFIX=/usr/local
SND_PATH=\"$(DATADIR)/sound/\"
GFX_PATH=\"$(DATADIR)/gfx/\"
CONFIG_FILE=\"/tmp/swiftblocks.cfg\"
CC=gcc
CXX=g++
CCFLAGS=`echo \`sdl-config --cflags\`` -I../fmod/inc
CXXFLAGS=`echo \`sdl-config --cflags\`` -I../fmod/inc -DGFX_PATH=$(GFX_PATH) -DSND_PATH=$(SND_PATH) -DCONFIG_FILE=$(CONFIG_FILE)
LDFLAGS=`echo \`sdl-config --libs\`` -lSDL_image -L../fmod -lfmod-3.61

all: Blocks.o ConfigParser.o Gameplay.o Logfile.o Main.o Menu.o Util.o BFont.o
	$(CXX) $(LDFLAGS) -o swiftblocks Blocks.o ConfigParser.o Gameplay.o Logfile.o Main.o Menu.o Util.o BFont.o

Blocks.o: Blocks.cpp Blocks.h
	$(CXX) $(CXXFLAGS) -c Blocks.cpp

ConfigParser.o: ConfigParser.cpp ConfigParser.h
	$(CXX) $(CXXFLAGS) -c ConfigParser.cpp

Gameplay.o: Gameplay.cpp Gameplay.h
	$(CXX) $(CXXFLAGS) -c Gameplay.cpp

Logfile.o: Logfile.cpp Logfile.h
	$(CXX) $(CXXFLAGS) -c Logfile.cpp

Main.o: Main.cpp Main.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

Menu.o: Menu.cpp Menu.h
	$(CXX) $(CXXFLAGS) -c Menu.cpp

Util.o: Util.cpp Util.h
	$(CXX) $(CXXFLAGS) -c Util.cpp

BFont.o: ../BFont/BFont.cpp ../BFont/BFont.h
	$(CXX) $(CXXFLAGS) -c ../BFont/BFont.cpp -o BFont.o
