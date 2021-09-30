#include"./Analysis.h"
#include"./DataSetReader.h"
#include"bits/stdc++.h"
#define ll long long int
using namespace std;
int main(int argc, char* argv[]){
	vector<Team> teams;
	if(argc < 2){
		cerr << "You miss some parameters, you have to give me tow parameters" << endl;
		cerr << "./analysis [data set filename] [formula ID wanna validate]" << endl;
		return 1;
	}
	string filename = argv[1];
	loadfile(filename, teams);
	Experiment validate(teams);
	validate.setformulaid(stoi(argv[2]));
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
			dividedTeam = classifyByDoubleDummyResult(validate.teams);
			int count = 0;
			for(int i = 0;i < 7;i++){
				count += dividedTeam[i].size();
				cout << "DDSwin = " << i + 1 << " have " << dividedTeam[i].size() << "teams" << endl;
			}
			cout << "Total " << count << " teams" << endl;
			vector<map<double, int>> cTT = countEachScoreAppearTime(dividedTeam);
		}
	}
}
