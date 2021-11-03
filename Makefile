CC=g++
CXXFLAGS=-std=c++17 -O3 -g
LDFLAGS += -lboost_iostreams -lboost_system -lboost_filesystem
LIBS = -L /usr/lib/x86_64-linux-gnu
Tools = Bridge.o Analysis.o DataSetReader.o epsMaker.o
dep:
	gcc -lstdc++ -M *.cpp > dep

-include dep 

all: analysisSubprocess subprocesstest accuracyChecker ValidateRichard checkWholeCorr analysisByFourHand TraversFourPlayersEST

ValidateRichard:ValidateRichard.o Bridge.o Analysis.o DataSetReader.o epsMaker.o 
	$(CC) -o $@ $^ $(LDFLAGS)
analysisSubprocess:analysisSubprocess.o Bridge.o Analysis.o DataSetReader.o epsMaker.o
	$(CC) -o $@ $^ $(LDFLAGS)
subprocesstest:subprocesstest.o Bridge.o Analysis.o DataSetReader.o 
accuracyChecker:accuracyChecker.o Bridge.o Analysis.o DataSetReader.o
checkWholeCorr:check_whole_corr.o Bridge.o
analysisByFourHand: analysisByFourHand.o Bridge.o DataSetReader.o
TraversFourPlayersEST: TraversFourPlayersEST.o Bridge.o DataSetReader.o Analysis.o
clean:
	-find . -type f -name "*.o" -exec rm {} \;
	-find . -type f -name "dep" -exec rm {} \;
	-find . -type f -executable -name "*" -exec rm {} \;
