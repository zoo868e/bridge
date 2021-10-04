CC=g++
CXXFLAGS=-std=c++17 -O3
dep:
	gcc -lstdc++ -M *.cpp > dep

-include dep 

all: analysisSubprocess subprocesstest

analysisSubprocess:analysisSubprocess.o Bridge.o Analysis.o DataSetReader.o
subprocesstest:subprocesstest.o Bridge.o Analysis.o DataSetReader.o
clean:
	-find . -type f -name "*.o" -exec rm {} \;
	-find . -type f -name "dep" -exec rm {} \;
	-find . -type f -executable -name "*" -exec rm {} \;
