all: manager savesync clean

manager: manager.o ini.h
	g++ -o manager manager.o ini.h -std=c++20

savesync: savesync.o ini.h
	g++ -o savesync savesync.o ini.h -std=c++20

clean: 
	rm -f *o