CC=g++
CXXFLAGS=-std=c++17 -O3 -g
LLLLLDFLAGS += -lboost_iostreams -lboost_system -lboost_filesystem
LIBS = -L /usr/lib/x86_64-linux-gnu
Tools = Bridge.o Analysis.o DataSetReader.o epsMaker.o
target := analysisSubprocess subprocesstest accuracyChecker ValidateRichard check_whole_corr analysisByFourHand TraversFourPlayersEST TimesOfHCPScore HandCalculator check_whole_corr_Fixed test DistributionOfScoreAndDDSresult testFunc
dep:
	gcc -lstdc++ -M *.cpp > dep

-include dep 

all: $(target)

ValidateRichard:ValidateRichard.o Bridge.o Analysis.o DataSetReader.o epsMaker.o 
	$(CC) -o $@ $^ $(LLLLLDFLAGS)
analysisSubprocess:analysisSubprocess.o Bridge.o Analysis.o DataSetReader.o epsMaker.o
	$(CC) -o $@ $^ $(LLLLLDFLAGS)
subprocesstest:subprocesstest.o Bridge.o Analysis.o DataSetReader.o 
accuracyChecker:accuracyChecker.o Bridge.o Analysis.o DataSetReader.o
check_whole_corr:check_whole_corr.o Bridge.o
check_whole_corr_Fixed:check_whole_corr_Fixed.o Bridge.o DataSetReader.o
analysisByFourHand: analysisByFourHand.o Bridge.o DataSetReader.o
TraversFourPlayersEST: TraversFourPlayersEST.o Bridge.o DataSetReader.o Analysis.o
TimesOfHCPScore: TimesOfHCPScore.o Bridge.o DataSetReader.o Analysis.o epsMaker.o
	$(CC) -o $@ $^ $(LLLLLDFLAGS)
HandCalculator: HandCalculator.o Bridge.o DataSetReader.o
test: test.o Bridge.o DataSetReader.o
DistributionOfScoreAndDDSresult: DistributionOfScoreAndDDSresult.o Bridge.o DataSetReader.o
testFunc: testFunc.o Bridge.o DataSetReader.o
clean:
	-rm $(target)
	-find . -type f -name "*.o" -exec rm {} \;
	-find . -type f -name "dep" -exec rm {} \;
