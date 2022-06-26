CC=g++
CXXFLAGS=-std=c++2a -O3 -g -fPIC
LLLLLDFLAGS += -lboost_iostreams -lboost_system -lboost_filesystem
LDFLAGS= -Wl,-rpath,$(pwd)
LIBS = -L /usr/lib/x86_64-linux-gnu
pwd = `pwd -P`
Tools = libBridge.so libAnalysis.so libDataSetReader.so libepsMaker.so
target := analysisSubprocess subprocesstest accuracyChecker ValidateRichard check_whole_corr analysisByFourHand TraversFourPlayersEST TimesOfHCPScore HandCalculator check_whole_corr_Fixed test DistributionOfScoreAndDDSresult testFunc ScoreCalculator accuracyCheckerwithinterval TeamScorer accuracyCheckergen accuracyCheckerGdata 
OBJECTS = analysisSubprocess.o  subprocesstest.o  accuracyChecker.o  ValidateRichard.o  check_whole_corr.o analysisByFourHand.o  TraversFourPlayersEST.o  TimesOfHCPScore.o  HandCalculator.o  check_whole_corr_Fixed.o test.o  DistributionOfScoreAndDDSresult.o  testFunc.o ScoreCalculator.o accuracyCheckerwithinterval.o TeamScorer.o accuracyCheckergen.o

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

$(target): % : %.o $(Tools)
#	$(CC) $(CXXFLAGS) -c -o $@.o $@.cpp 
	$(CC) $(CXXFLAGS) $@.o -o $@ $(Tools) $(LDFLAGS) $(LLLLLDFLAGS)

clean:
	-rm $(target)
	-find . -type f -name "*.o" -exec rm {} \;
	-find . -type f -name "dep" -exec rm {} \;
	-find . -type f -name "*.so" -exec rm {} \;
