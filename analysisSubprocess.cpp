#include"./Analysis.h"
#include"./DataSetReader.h"
#include"bits/stdc++.h"
#include"epsMaker.h"
using namespace std;
Gnuplot gp;
int main(int argc, char* argv[]){
	gp << "set term postscript eps enhanced color\n";
	vector<Team> teams;
	if(argc < 3){
		cerr << "You miss some parameters, you have to give me tow parameters" << endl;
		cerr << "./analysis [data set filename] [formula ID wanna validate]" << endl;
		return 1;
	}
	string filename = argv[1];
	loadTeam(filename, teams);
	Experiment validate(teams);
	validate.setformulaid(stoi(argv[2]));
	string epsFilename = argv[3];
	vector<string> scorematrix_string;
	vector<double> scorematrix;
	string s;
	vector<vector<Team>> dividedTeam;
	int experimentTimes = 0;
	setOutputFile(gp, epsFilename);
	while(getline(cin, s)){
		experimentTimes++;
		scorematrix_string.clear();
		scorematrix.clear();
		scorematrix_string = split(s, " ");
		if(scorematrix_string[0] == "END")break;
		for(int i = 0;i < (int)scorematrix_string.size();i++){
			scorematrix.push_back(stod(scorematrix_string[i]));
		}
		int ercode = validate.Set_scorematrix(scorematrix);
		if(ercode != 0){
			cerr << "--Wrong size of scorematrix--Size = " << ercode << endl;
			return 2;
		}
		else{
			validate.scorer();
			// Find the gap of continuous win tricks
			dividedTeam = classifyByDoubleDummyResult(validate.teams);
			vector<map<double, int>> cTT = countEachScoreAppearTime(dividedTeam);
			vector<int> maxTimes = maximumAppearTimesOfEachScore(cTT);
			vector<double> meanTimes = meanAppearTimesOfEachScore(cTT);
			vector<int> middleTimes = middleAppearTimesOfEachScore(cTT);
			vector<double> gaps = edgeOfEachScore(maxTimes);
			vector<double> gapsMean = edgeOfEachScore(meanTimes);
			vector<double> gapsMiddle = edgeOfEachScore(middleTimes);
/*
			cout << "gaps: ";
			for(auto x:gaps){
				cout << x << " ";
			}
			cout << endl << "gapsMean: ";
			for(auto x:gapsMean){
				cout << x << " ";
			}
			cout << endl << "gapsMiddle: ";
			for(auto x:gapsMiddle){
				cout << x << " ";
			}
			cout << endl;
*/
			// Find the gap between the predicted win tricks and DDS
			map<int, int> result = gapOfWholeDataSet(validate.teams, gaps);
			cout << "Use the Mode to split\n";
			int check = 0;
			for(auto item:result){
				check += item.second;
				cout << "distance = " << item.first << ", occur " << item.second << " times" << ". Take up " << (double)item.second / validate.teams.size() * 100 << "\% of whole Data Set\n";
			}
			cout << "There is " << check << " datas in Data Set\n";
			// Find the gap between the predicted win tricks and DDS
			result.clear();
			result = gapOfWholeDataSet(validate.teams, gapsMean);
			cout << "Use the Mean to split\n";
			check = 0;
			for(auto item:result){
				check += item.second;
				cout << "distance = " << item.first << ", occur " << item.second << " times" << ". Take up " << (double)item.second / validate.teams.size() * 100 << "\% of whole Data Set\n";
			}
			cout << "There is " << check << " datas in Data Set\n";
			// Find the gap between the predicted win tricks and DDS
			result.clear();
			result = gapOfWholeDataSet(validate.teams, gapsMiddle);
			cout << "Use the Median to split\n";
			check = 0;
			for(auto item:result){
				check += item.second;
				cout << "distance = " << item.first << ", occur " << item.second << " times" << ". Take up " << (double)item.second / validate.teams.size() * 100 << "\% of whole Data Set\n";
			}
			cout << "There is " << check << " datas in Data Set\n";
			cout << "--------------------------------------------------------------------------" << endl;
			setTitle(gp, "Turns: " + to_string(experimentTimes));
			plotLines(gp, cTT, gapsMean);
//			makeGapEPS(cTT, "ana.py");
		}
	}
	setCloseFile(gp);
}
