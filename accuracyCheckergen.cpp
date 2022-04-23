#include"./Analysis.h"
#include"./DataSetReader.h"
#include"bits/stdc++.h"
#define ll long long int
using namespace std;

bool IsTOOSmall(Team t){return t.DDSwin < 7;}

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
	while(getline(cin, s)){
		scorematrix_string.clear();
		scorematrix.clear();
		scorematrix_string = split(s, " ");
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
			vector<double> meanTimes = meanAppearTimesOfEachScore(cTT);
			vector<double> gaps = edgeOfEachScore(meanTimes);
			for(auto t:validate.teams){
				cout << t.DDSwin << " " << t.score << endl;
			}
//			makeGapEPS(cTT, "ana.py");
		}
	}
}
