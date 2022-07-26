#include"./Analysis.h"
#include"./DataSetReader.h"
#include"bits/stdc++.h"
#define ll long long int
using namespace std;

bool IsTOOSmall(Team t){return t.DDSwin < 7;}
double roundto(double src, int decimal){
	double d = pow(10, decimal);
	return round(src * d) / d;
}

int main(int argc, char* argv[]){
	vector<Team> teams;
	if(argc <= 2){
		cerr << "You miss some parameters, you have to give me two parameters" << endl;
		cerr << "./analysis [data set filename] [formula ID wanna validate]" << endl;
		return 1;
	}
	string filename = argv[1];
	loadTeam(filename, teams);
	Experiment validate(teams);
	validate.setformulaid(stoi(argv[2]));
	for(int i = 0;i < (int)validate.teams.size();i++){
		if((int)round(validate.teams[i].DDSwin) >= 7)continue;
		validate.teams.erase(validate.teams.begin() + i);
		validate.DDS.erase(validate.DDS.begin() + i);
		i--;
	}
	vector<string> scorematrix_string;
	vector<double> scorematrix;
	string s;
	vector<vector<Team>> dividedTeam;
	vector<map<double, int>> cTT;
	vector<double> meanTimes, gaps;
	map<int, int> result;
	while(getline(cin, s)){
		validate.setformulaid(stoi(s));
		int formulaid = stoi(s);
		string formula_name = "";
		if(formulaid % 10){
			formula_name += validate.HCP_name[formulaid % 10];
		}
		formulaid /= 10;
		if(formulaid % 10){
			if(formula_name.size() > 0)
				formula_name += " + ";
			formula_name += validate.suitHCP_name[formulaid % 10];
		}
		formulaid /= 10;
		if(formulaid % 10){
			if(formula_name.size() > 0)
				formula_name += " + ";
			formula_name += validate.dis_name[formulaid % 10];
		}
		formulaid /= 10;
		if(formulaid % 10){
			if(formula_name.size() > 0)
				formula_name += " + ";
			formula_name += validate.long_name[formulaid % 10];
		}
		formulaid /= 10;
		if(formulaid % 10){
			if(formula_name.size() > 0)
				formula_name += " + ";
			formula_name += validate.short_name[formulaid % 10];
		}
		getline(cin, s);
		scorematrix_string.clear();
		scorematrix.clear();
		dividedTeam.clear();
		cTT.clear();
		meanTimes.clear();
		gaps.clear();
		result.clear();
		scorematrix_string = split(s, " ");
		for(int i = 0;i < (int)scorematrix_string.size();i++){
			scorematrix.push_back(stod(scorematrix_string[i]));
		}
		int ercode = validate.nSet_scorematrix(scorematrix);
		if(ercode != 0){
			cerr << "--Wrong size of scorematrix--Size = " << ercode << endl;
			return 2;
		}
		else{
			validate.nScorer();
			// Find the gap of continuous win tricks
			dividedTeam = classifyByDoubleDummyResult(validate.teams);
//			cTT = countEachScoreAppearTime(dividedTeam);
//			vector<int> middleTimes = middleAppearTimesOfEachScore(cTT);
			meanTimes = MeanOfScore(dividedTeam);
//			meanTimes = meanAppearTimesOfEachScore(cTT);
			gaps = edgeOfEachScore(meanTimes);
			// Find the gap between the predicted win tricks and DDS
			result = gapOfWholeDataSet(validate.teams, gaps, true);
			int check = 0;
			for(auto item:result){
				check += item.second;
			}
			int total = result[0];
			double factor = (double)total / check;
			cout << formula_name << " & " << validate.needed_para << " & " << roundto(getcorr(validate), 3) << " & " << roundto(factor, 3) << " & ";
			total += result[-1] + result[1];
			factor = (double)total / check;
			cout << roundto(factor, 3) << " & ";
			total += result[-2] + result[2];
			factor = (double)total / check;
			cout << roundto(factor, 3) << "\\\\\\hline\n";
//			makeGapEPS(cTT, "ana.py");
		}
	}
}
