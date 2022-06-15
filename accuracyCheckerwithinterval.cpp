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
	if(validate.formulaid == 6){
		int size = validate.teams.size();
		for(int i = 0;i < size;i++){
			for(int j = 0;j < 2;j++){
				int ps = 0;
				auto hand = validate.teams[i].player[j].hand.getcard();
				for(int k = 0;k < 4;k++){
					int a = 0;
					for(int c:hand[k])a += basicHCP[c];
					ps += a;
					validate.teams[i].player[j].HCP_suit[k] = a;
				}
				validate.teams[i].player[j].HCP = ps;
			}
		}
	}
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
		cout << "Here are the accurcy of large data set" << endl;
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
			cout << "The correlation coefficient is " << getcorr(validate) << endl;
			dividedTeam = classifyByDoubleDummyResult(validate.teams);
			cout << "divided Team is done!\n";
//			vector<map<double, int>> cTT = countEachScoreAppearTime(dividedTeam);
//			vector<double> meanTimes = meanAppearTimesOfEachScore(cTT);
			vector<double> meanTimes = MeanOfScore(dividedTeam);
			vector<double> gaps = edgeOfEachScore(meanTimes);
			cout << "s < " << gaps[0] << endl;
			for(int i = 1;i < 6;i++){
				cout << gaps[i - 1] << " <= s < " << gaps[i] << endl;
			}
			cout << gaps[5] << " < s" << endl;
			// Find the gap between the predicted win tricks and DDS
			map<int, int> result = gapOfWholeDataSet(validate.teams, gaps, true);

			int check = 0;
			for(auto item:result){
				check += item.second;
				if(abs(item.first) < 3)
					cout << "distance = " << item.first << ", occur " << item.second << " times" << ". Take up " << (double)round((double)item.second / validate.teams.size() * 10000) / 100 << "\% of whole Data Set\n";
			}
			cout << "There is " << check << " datas in Data Set\n";
			cout << "--------------------------------------------------------------------------" << endl;
			cout << "distance = " << 0 << ", totally occured " << result[0] << "times" << ". Take up " << (double)round((double)result[0] / check * 10000) / 100 << "\% of whole Data Set\n";
			int total = result[0];
			for(int i = 1;i < 3;i++){
				total += result[i] + result[-i];
				cout << "distance <= " << i << ", totally occured " << total << "times" << ". Take up " << (double)round((double)(total) / check * 10000) / 100 << "\% of whole Data Set\n";
			}
			cout << "--------------------------------------------------------------------------" << endl;
//			makeGapEPS(cTT, "ana.py");
		}
	}
}
