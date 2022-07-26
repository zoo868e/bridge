#include"./Bridge.h"
#include"DataSetReader.h"
#define ll long long int

using namespace std;
int main(int argc, char* argv[]){
	vector<Team> team;
	string filename = "./data/dataForCofsection42";
	if(argc > 2)filename = argv[2];
	loadTeam(filename, team);
	if(team.size() == 0){
		cout << "their are no any data here!!" << endl;
		return 1;
	}

	Experiment E = Experiment(team);
	if(argc > 1)E.setformulaid(stoi(argv[1]));
	for(int i = 0;i < (int)E.teams.size();i++){
		if((int)round(E.teams[i].DDSwin) >= 7)continue;
		E.teams.erase(E.teams.begin() + i);
		E.DDS.erase(E.DDS.begin() + i);
		i--;
	}

	string s;
	vector<string> scorematrixb;
	vector<double> scorematrix;
	while(getline(cin, s)){
		scorematrixb.clear();
		scorematrix.clear();
		scorematrixb = split(s, " ");
		for(int i = 0;i < (int)scorematrixb.size();i++){
			scorematrix.push_back(stod(scorematrixb[i]));
		}
		int ercode = E.nSet_scorematrix(scorematrix);
		if(ercode != 0)cout << "--Wrong size of scorematrix--Size = " << ercode << endl;
		else{
			E.nScorer();
			double ans = getcorr(E);
			cout << ans << endl;
			if(ans == -2){
				cout << "Experiment:" << endl;
				cout << "len(score): " << E.score.size() << endl;
				cout << "score = ";
				for(auto x:E.score)cout << x << " ";
				cout << endl;
			}
		}
	}
	return 0;
}

