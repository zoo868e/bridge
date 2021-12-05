#include "Bridge.h"
#include "DataSetReader.h"
#include "Analysis.h"

using namespace std;
const vector<double> ArgumentOfFormulaTwo{1.045, 1.229, 1.629, 2.066, 2.912, 3.527, 1.019, 1.2, 0.5106, 0.2381, 0.2422, 2.043, 1.122, 0.01089, 0.3142, 2.107, 1.366};

int main(int argc, char** argv){
	// check the argument number
	if(argc < 3){
		cerr << "Need more arguments\n";
		cerr << "analysisByFourHand <file name> <formula ID>\n";
		return 1;
	}
	// initialize the parameter
	vector<Game> game;
	vector<PartialGame> partialgames;
	string input;
	vector<string> scorematrixb;
	vector<double> scorematrix;
	int DataSetSize;
	// these parameters are for Analysis.h
	vector<vector<PartialGame>> dividedGame;
	vector<map<double, int>> cTT;
	vector<int> middleTimes;
	vector<double> gapsMiddle;
	map<int, int> result;
	// these parameters are for output the result
	ofstream f0, f1, f2, f01, f012, f;
	double ret, di, dj, g0, g1, g2;
	// load the data set
	loadPartialGames(argv[1], partialgames);
	DataSetSize = partialgames.size();
	Experiment PartialgameExperiment(partialgames, atoi(argv[2]));
	// load the score matrix
	PartialgameExperiment.Set_scorematrix(ArgumentOfFormulaTwo);
	// calculate the original score of each player
	PartialgameExperiment.PartialGamePreScorer();
	// calculate the 0, 0 first and make this number be a const
	scorematrix = {0, 0};
	PartialgameExperiment.Set_FixFormulaArgumentList(scorematrix);
	PartialgameExperiment.PartialGameTrainScorer();
	dividedGame = classifyByDoubleDummyResult(PartialgameExperiment.Partialgames);
	cTT = countEachScoreAppearTime(dividedGame);
	middleTimes = middleAppearTimesOfEachScore(cTT);
	gapsMiddle = edgeOfEachScore(middleTimes);
	map<int, int> ZeroResult = gapOfWholeDataSet(PartialgameExperiment.Partialgames, gapsMiddle);
	const double Zero0 = round(ZeroResult[0] * 1000.0 / DataSetSize) / 10.0;
	const double Zero1 = round((ZeroResult[1] + ZeroResult[-1]) * 1000.0 / DataSetSize) / 10.0;
	const double Zero2 = round((ZeroResult[2] + ZeroResult[-2]) * 1000.0 / DataSetSize) / 10.0;
	const double zero_ans = getcorr(PartialgameExperiment);
	// set the output file name
	string filename_exact = "./result/FourGuysFormula1ArgumetTraverseEXACT.dat";
	string filename_one = "./result/FourGuysFormula1ArgumetTraverseONE.dat";
	string filename_two = "./result/FourGuysFormula1ArgumetTraverseTWO.dat";
	string filename_corr = "./result/FourGuysFormula1ArgumetTraverseCORR.dat";
	string filename_e_o = "./result/FourGuysFormula1ArgumetTraverseEXACTandONE.dat";
	string filename_e_o_t = "./result/FourGuysFormula1ArgumetTraverseEXACTandONEandTWO.dat";
	f0.open(filename_exact);
	f1.open(filename_one);
	f2.open(filename_two);
	f01.open(filename_e_o);
	f012.open(filename_e_o_t);
	f.open(filename_corr);
	for(int i = -100;i <= 100;i++){
		for(int j = 0;j <= 100;j++){
			di = (double)i / 100;
			dj = (double)j / 100;
			if(i == 0){
				cout << di << " " << dj << " " << zero_ans << endl;
				f << di << " " << dj << " " << zero_ans << endl;
				f0 << di << " " << dj << " " << Zero0 << endl;
				cout << "gap = 0 :" << di << " " << dj << " " << Zero0 << endl;
				f1 << di << " " << dj << " " << Zero1 << endl;
				cout << "gap = 1 :" << di << " " << dj << " " << Zero1 << endl;
				f2 << di << " " << dj << " " << Zero2 << endl;
				cout << "gap = 2 :" << di << " " << dj << " " << Zero2 << endl;
				f01 << di << " " << dj << " " << Zero0 + Zero1 << endl;
				cout << "gap = 0 + 1 :" << di << " " << dj << " " << Zero0 + Zero1 << endl;
				f012 << di << " " << dj << " " << Zero0 + Zero1 + Zero2 << endl;
				cout << "gap = 0 + 1 + 2:" << di << " " << dj << " " << Zero0 + Zero1 + Zero2 << endl;
				continue;
			}
			scorematrix.clear();
			scorematrix = {di, dj};
			PartialgameExperiment.Set_FixFormulaArgumentList(scorematrix);
			PartialgameExperiment.PartialGameTrainScorer();
			ret = getcorr(PartialgameExperiment);
			dividedGame = classifyByDoubleDummyResult(PartialgameExperiment.Partialgames);
			cTT = countEachScoreAppearTime(dividedGame);
			middleTimes = middleAppearTimesOfEachScore(cTT);
			gapsMiddle = edgeOfEachScore(middleTimes);
			result = gapOfWholeDataSet(PartialgameExperiment.Partialgames, gapsMiddle);
			g0 = round(result[0] * 1000.0 / DataSetSize) / 10.0;
			g1 = round((result[1] + result[-1]) * 1000.0 / DataSetSize) / 10.0;
			g2 = round((result[2] + result[-2]) * 1000.0 / DataSetSize) / 10.0;
			cout << di << " " << dj << " " << ret << endl;
			f << di << " " << dj << " " << ret << endl;
			f0 << di << " " << dj << " " << g0 << endl;
			cout << "gap = 0 :" << di << " " << dj << " " << g0 << endl;
			f1 << di << " " << dj << " " << g1 << endl;
			cout << "gap = 1 :" << di << " " << dj << " " << g1 << endl;
			f2 << di << " " << dj << " " << g2 << endl;
			cout << "gap = 2 :" << di << " " << dj << " " << g2 << endl;
			f01 << di << " " << dj << " " << g0 + g1 << endl;
			cout << "gap = 0 + 1 :" << di << " " << dj << " " << g0 + g1 << endl;
			f012 << di << " " << dj << " " << g0 + g1 + g2 << endl;
			cout << "gap = 0 + 1 + 2 :" << di << " " << dj << " " << g0 + g1 + g2 << endl;
		}
	}
	f.close();
	f0.close();
	f1.close();
	f2.close();
	f01.close();
	f012.close();
	return 0;
}
