CC=g++
CXXFLAGS=-std=c++2a -O3 -g -fPIC
LLLLLDFLAGS += -lboost_iostreams -lboost_system -lboost_filesystem
LDFLAGS= -Wl,-rpath,$(pwd)
LIBS = -L /usr/lib/x86_64-linux-gnu
pwd = `pwd -P`
Tools = libBridge.so libAnalysis.so libDataSetReader.so libepsMaker.so
target := main AppearTimesOfCombinations RandomConclusion
OBJECTS = main.o AppearTimesOfCombinations.o RandomConclusion.o

dep:
	gcc -lstdc++ -M *.cpp > dep

-include dep 

all: $(target)

tools: $(Tools)

libBridge.so:Bridge.o
	g++ -shared -o libBridge.so Bridge.o
libAnalysis.so:Analysis.o
	g++ -shared -o libAnalysis.so Analysis.o
libDataSetReader.so:DataSetReader.o Bridge.o
	g++ -shared -o libDataSetReader.so DataSetReader.o Bridge.o
libepsMaker.so:epsMaker.o
	g++ -shared -o libepsMaker.so epsMaker.o

$(target): $(OBJECTS) $(Tools)
	$(CC) $(CXXFLAGS) $@.o -o $@ $(Tools) $(LDFLAGS) $(LLLLLDFLAGS)

clean:
	-rm $(target)
	-find . -type f -name "*.o" -exec rm {} \;
	-find . -type f -name "dep" -exec rm {} \;
	-find . -type f -name "*.so" -exec rm {} \;
