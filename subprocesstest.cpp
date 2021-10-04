#include"./Bridge.h"
#include"DataSetReader.h"
#define ll long long int

using namespace std;
int main(int argc, char* argv[]){
	string filename = "./data/dataForC";
	vector<Team> team;
	loadfile(filename, team);
	/*
	cout << team.size() << endl;
	for(auto x:team){
		cout << "Player 1:" << endl;
		for(auto i:x.player[0].hand.getcard()){
			for(auto card:i)cout << card << " ";
			cout << endl;
		}
		cout << endl;
		cout << "Player2:" << endl;
		for(auto i:x.player[1].hand.getcard()){
			for(auto card:i)cout << card << " ";
			cout << endl;
		}
		cout << "suit: " << x.suit << endl;
		cout << "DDS: " << x.DDSwin << endl;
		cout << "maker: " << x.maker << endl;
		cout << endl;
	}*/
	Experiment E = Experiment(team);
	if(argc > 1)E.setformulaid(stoi(argv[1]));
	/*
	for(int i = 0;i < (int)E.score.size();i++){
		cout << "DDS: " << E.DDS[i] << ", score: " << E.score[i] << endl;
	}*/
//	E.scorer();
//	cout << getcorr(E) << endl;
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
/*			for(int i = 0;i < (int)E.score.size();i++){
				vector<vector<int>> hand;
				hand = E.teams[i].player[1].hand.getcard();
				for(auto x:hand){
					for(auto z:x)cout << z << " ";
					cout << " | ";
				}
				cout << endl;
				hand = E.teams[i].player[0].hand.getcard();
				for(auto x:hand){
					for(auto z:x)cout << z << " ";
					cout << " | ";
				}
				cout << endl;
				cout << "DDS: " << E.teams[i].DDSwin << ", suit: " << E.teams[i].suit << endl;
				cout << "score: " << E.score[i] << endl;
			}*/
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

