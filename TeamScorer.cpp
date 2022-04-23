/*	This program is aim to calculate the score of a team
 *	Usage:
 *		./TeamScorer [formula id] [the data set with [N, S, ddswin, trump suit, 0]]
 *	if you don't have dds result, you can just put 0 over there, it's not needed
 *	just I'm lazy to write another flexible data reader
 * */




#include"./Bridge.h"
#include"DataSetReader.h"
#define ll long long int





using namespace std;
int main(int argc, char* argv[]){
	if(argc < 3){
		cerr << "Usage:" << endl;
		cerr << "./TeamScorer [data set] [formula id]" << endl;
		return 1;
	}
	string filename = argv[1];
	vector<Team> team;
	loadTeam(filename, team);
	if(team.size() == 0){
		cout << "their are no any data here!!" << endl;
		return 1;
	}
	Experiment E = Experiment(team);
	E.setformulaid(stoi(argv[2]));
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
			for(auto t:E.teams){
				t.ShowHand();
				cout << "score = " << t.score << endl;
			}
		}
	}
	return 0;
}

