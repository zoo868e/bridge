#include "Bridge.h"
#include "DataSetReader.h"
#include "Analysis.h"
#include "epsMaker.h"

using namespace std;
const vector<double> ArgumentOfFormulaTwo{1.045, 1.229, 1.629, 2.066, 2.912, 3.527, 1.019, 1.2, 0.5106, 0.2381, 0.2422, 2.043, 1.122, 0.01089, 0.3142, 2.107, 1.366};
const vector<double> HCPFormulaTwo{0, 0, 1, 2, 3, 3.527, 1.019, 1.2, 0.5106, 0.2381, 0.2422, 2.043, 1.122, 0.01089, 0.3142, 2.107, 1.366};

Gnuplot gp;

int main(int argc, char** argv){
	if(argc < 3){
		cerr << "Wrong number of argument" << endl;
		cerr << "Usage:" << endl;
		cerr << "\tTimeOfHCOScore <DataSet Filename> <formulaID>" << endl;
		return 1;
	}
	// Set the gnuplot initialization
	gp << "set term postscript eps enhanced color\n";
	setOutputFile(gp, "CheckMyMethodDistribution.eps");

	string InputFilename = argv[1];
	int formulaID = atoi(argv[2]);
	vector<PartialGame> Partialgames;
	loadPartialGames(InputFilename, Partialgames);
	Experiment PartialgameExperiment(Partialgames, formulaID);
	PartialgameExperiment.Set_scorematrix(ArgumentOfFormulaTwo);
	PartialgameExperiment.formulaid = -1;	// -1 is for test the HCP score distributed
	PartialgameExperiment.PartialGamePreScorer();
	vector<map<int, int>> countEachScoreAppearTime(14);
	for(auto game:PartialgameExperiment.Partialgames){
//		if(game.suit != 0)continue;
		int maker = game.maker;
		int NS = round(game.player[0].score + game.player[2].score), WE = round(game.player[1].score + game.player[3].score);
		if(maker){
			countEachScoreAppearTime[round(game.DDSwin)][WE]++;
//			countEachScoreAppearTime[13 - round(game.DDSwin)][NS]++;
		}
		else {
			countEachScoreAppearTime[round(game.DDSwin)][NS]++;
//			countEachScoreAppearTime[round(13 - game.DDSwin)][WE]++;
		}
	}
	vector<int> sum(14, 0);
	for(int i = 7;i < 14;i++){
		for(auto x:countEachScoreAppearTime[i]){
			sum[i] += x.second;
		}
	}
	for(int i = 7;i < 14;i++){
		cout << "Win tricks is " << i << endl;
		double tsum = 0;
		for(auto x:countEachScoreAppearTime[i]){
			cout << "score = " << x.first << " appear " << x.second << " times, the percentage is " << x.second * 100.0 / sum[i] << "\n";
			tsum += x.second * 100.0 / sum[i];
		}
		cout << "sum of percentage = " << tsum << endl;
		cout << "number of wintrick = " << i << ", is " << sum[i] << endl;
		cout << "--------------------------\n";
	}
	setTitle(gp, "My method with only HCP");
//	gp << "set xrange [0:*]" << endl;
	vector<double> dummy;
	plotLines(gp, countEachScoreAppearTime, dummy);
	/*	Only original HCP */
	/*
	PartialgameExperiment.formulaid = 2;
	PartialgameExperiment.Set_scorematrix(HCPFormulaTwo);
	PartialgameExperiment.formulaid = -1;
	PartialgameExperiment.PartialGamePreScorer();
	countEachScoreAppearTime.clear();
	countEachScoreAppearTime.resize(14);
	for(auto game:PartialgameExperiment.Partialgames){
//		if(game.suit != 0)continue;
		int maker = game.maker;
		int NS = round(game.player[0].score + game.player[2].score), WE = round(game.player[1].score + game.player[3].score);
		if(maker){
			countEachScoreAppearTime[round(game.DDSwin)][WE]++;
//			countEachScoreAppearTime[13 - round(game.DDSwin)][NS]++;
		}
		else {
			countEachScoreAppearTime[round(game.DDSwin)][NS]++;
//			countEachScoreAppearTime[round(13 - game.DDSwin)][WE]++;
		}
	}
	sum.clear();
	sum.resize(14, 0);
	for(int i = 7;i < 14;i++){
		for(auto x:countEachScoreAppearTime[i]){
			sum[i] += x.second;
		}
	}
	for(int i = 7;i < 14;i++){
		cout << "Win tricks is " << i << endl;
		double tsum = 0;
		for(auto x:countEachScoreAppearTime[i]){
			cout << "score = " << x.first << " appear " << x.second << " times, the percentage is " << x.second * 100.0 / sum[i] << "\n";
			tsum += x.second * 100.0 / sum[i];
		}
		cout << "sum of percentage = " << tsum << endl;
		cout << "number of wintrick = " << i << ", is " << sum[i] << endl;
		cout << "--------------------------\n";
	}
	setTitle(gp, "HCP");
	gp << "set yrange [0:0.25]" << endl;
	gp << "set xrange [0:60]" << endl;
	plotLines(gp, countEachScoreAppearTime, dummy);
	*/
	/*	My method with only HCP + suitHCP*/
	PartialgameExperiment.formulaid = 2;
	PartialgameExperiment.Set_scorematrix(ArgumentOfFormulaTwo);
	PartialgameExperiment.formulaid = -2;
	PartialgameExperiment.PartialGamePreScorer();
	countEachScoreAppearTime.clear();
	countEachScoreAppearTime.resize(14);
	for(auto game:PartialgameExperiment.Partialgames){
//		if(game.suit != 0)continue;
		int maker = game.maker;
		int NS = round(game.player[0].score + game.player[2].score), WE = round(game.player[1].score + game.player[3].score);
		if(maker){
			countEachScoreAppearTime[round(game.DDSwin)][WE]++;
//			countEachScoreAppearTime[13 - round(game.DDSwin)][NS]++;
		}
		else {
			countEachScoreAppearTime[round(game.DDSwin)][NS]++;
//			countEachScoreAppearTime[round(13 - game.DDSwin)][WE]++;
		}
	}
	sum.clear();
	sum.resize(14, 0);
	for(int i = 7;i < 14;i++){
		for(auto x:countEachScoreAppearTime[i]){
			sum[i] += x.second;
		}
	}
	for(int i = 7;i < 14;i++){
		cout << "Win tricks is " << i << endl;
		double tsum = 0;
		for(auto x:countEachScoreAppearTime[i]){
			cout << "score = " << x.first << " appear " << x.second << " times, the percentage is " << x.second * 100.0 / sum[i] << "\n";
			tsum += x.second * 100.0 / sum[i];
		}
		cout << "sum of percentage = " << tsum << endl;
		cout << "number of wintrick = " << i << ", is " << sum[i] << endl;
		cout << "--------------------------\n";
	}
	setTitle(gp, "My method only with suitHCP");
//	gp << "set yrange [0:0.25]" << endl;
	gp << "set xrange [*:*]" << endl;
	plotLines(gp, countEachScoreAppearTime, dummy);
	/*	My method with HCP + long */
	PartialgameExperiment.formulaid = -3;
	PartialgameExperiment.PartialGamePreScorer();
	countEachScoreAppearTime.clear();
	countEachScoreAppearTime.resize(14);
	for(auto game:PartialgameExperiment.Partialgames){
//		if(game.suit != 0)continue;
		int maker = game.maker;
		int NS = round(game.player[0].score + game.player[2].score), WE = round(game.player[1].score + game.player[3].score);
		if(maker){
			countEachScoreAppearTime[round(game.DDSwin)][WE]++;
//			countEachScoreAppearTime[13 - round(game.DDSwin)][NS]++;
		}
		else {
			countEachScoreAppearTime[round(game.DDSwin)][NS]++;
//			countEachScoreAppearTime[round(13 - game.DDSwin)][WE]++;
		}
	}
	sum.clear();
	sum.resize(14, 0);
	for(int i = 7;i < 14;i++){
		for(auto x:countEachScoreAppearTime[i]){
			sum[i] += x.second;
		}
	}
	for(int i = 7;i < 14;i++){
		cout << "Win tricks is " << i << endl;
		double tsum = 0;
		for(auto x:countEachScoreAppearTime[i]){
			cout << "score = " << x.first << " appear " << x.second << " times, the percentage is " << x.second * 100.0 / sum[i] << "\n";
			tsum += x.second * 100.0 / sum[i];
		}
		cout << "sum of percentage = " << tsum << endl;
		cout << "number of wintrick = " << i << ", is " << sum[i] << endl;
		cout << "--------------------------\n";
	}
	setTitle(gp, "My method only with long");
	/*
	gp << "set xrange [0:60]" << endl;
	*/
	plotLines(gp, countEachScoreAppearTime, dummy);
	/*	My method with HCP + short */
	PartialgameExperiment.formulaid = -4;
	PartialgameExperiment.PartialGamePreScorer();
	countEachScoreAppearTime.clear();
	countEachScoreAppearTime.resize(14);
	for(auto game:PartialgameExperiment.Partialgames){
//		if(game.suit != 0)continue;
		int maker = game.maker;
		int NS = round(game.player[0].score + game.player[2].score), WE = round(game.player[1].score + game.player[3].score);
		if(maker){
			countEachScoreAppearTime[round(game.DDSwin)][WE]++;
//			countEachScoreAppearTime[13 - round(game.DDSwin)][NS]++;
		}
		else {
			countEachScoreAppearTime[round(game.DDSwin)][NS]++;
//			countEachScoreAppearTime[round(13 - game.DDSwin)][WE]++;
		}
	}
	sum.clear();
	sum.resize(14, 0);
	for(int i = 7;i < 14;i++){
		for(auto x:countEachScoreAppearTime[i]){
			sum[i] += x.second;
		}
	}
	for(int i = 7;i < 14;i++){
		cout << "Win tricks is " << i << endl;
		double tsum = 0;
		for(auto x:countEachScoreAppearTime[i]){
			cout << "score = " << x.first << " appear " << x.second << " times, the percentage is " << x.second * 100.0 / sum[i] << "\n";
			tsum += x.second * 100.0 / sum[i];
		}
		cout << "sum of percentage = " << tsum << endl;
		cout << "number of wintrick = " << i << ", is " << sum[i] << endl;
		cout << "--------------------------\n";
	}
	setTitle(gp, "My method only with short");
	/*
	gp << "set xrange [0:60]" << endl;
	*/
	plotLines(gp, countEachScoreAppearTime, dummy);
	setCloseFile(gp);
	return 0;
}
