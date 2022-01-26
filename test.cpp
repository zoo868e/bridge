#include"./Bridge.h"
#include"DataSetReader.h"
#define ll long long int

using namespace std;
int main(int argc, char* argv[]){
	string filename = "./data/dataForC";
	vector<Team> team;
	loadTeam(filename, team);
	if(team.size() == 0){
		cout << "their are no any data here!!" << endl;
		return 1;
	}
	Experiment E = Experiment(team);
	if(argc > 1)E.setformulaid(stoi(argv[1]));
	/*
	if(E.formulaid == 6){
		int size = E.teams.size();
		for(int i = 0;i < size;i++){
			for(int j = 0;j < 2;j++){
				int ps = 0;
				auto hand = E.teams[i].player[j].hand.getcard();
				for(int k = 0;k < 4;k++){
					int a = 0;
					for(int c:hand[k])a += basicHCP[c];
					ps += a;
					E.teams[i].player[j].HCP_suit[k] = a;
				}
				E.teams[i].player[j].HCP = ps;
			}
		}
	}
	*/
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
		int ercode = E.Set_scorematrix(scorematrix);
		if(ercode != 0)cout << "--Wrong size of scorematrix--Size = " << ercode << endl;
		else{
			E.scorer();
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

