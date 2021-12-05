#include"./Bridge.h"
#include"./DataSetReader.h"
#define ll long long int
const vector<double> ArgumentOfFormulaTwo{1.045, 1.229, 1.629, 2.066, 2.912, 3.527, 1.019, 1.2, 0.5106, 0.2381, 0.2422, 2.043, 1.122, 0.01089, 0.3142, 2.107, 1.366};

using namespace std;

vector<string> split(const string &, const string &);
int cardtoint(char);
double correlationCoefficient(vector<double> X, vector<double> Y, int n);
int main(int argc, char* argv[]){
	string filename = "./data/wholedataofGameForC";
	vector<PartialGame> Partialgames;
	loadPartialGames(filename, Partialgames);
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
	Experiment E = Experiment(Partialgames);
	if(argc > 1)E.setformulaid(stoi(argv[1]));
	E.Set_scorematrix(ArgumentOfFormulaTwo);
	E.setFixformulaid(3);
//	E.PartialGamePreScorer();
	/*
	for(int i = 0;i < (int)E.score.size();i++){
		cout << "DDS: " << E.DDS[i] << ", score: " << E.score[i] << endl;
	}*/
//	E.scorer();
//	cout << getcorr(E) << endl;
	string s;
	vector<string> scorematrixb;
	vector<double> scorematrix;
//	string trained_file_name = "./0921_f3";
//	vector<string> trained_argument = load_trained_file(trained_file_name);
	while(getline(cin, s)){
		scorematrixb.clear();
		scorematrix.clear();
		scorematrixb = split(s, " ");
		for(int i = 0;i < (int)scorematrixb.size();i++){
			scorematrix.push_back(stod(scorematrixb[i]));
		}
		int ercode = E.Set_FixFormulaArgumentList(scorematrix);
		if(ercode != 0)cout << "--Wrong size of scorematrix--Size = " << ercode << endl;
		else{
			E.PartialGameTrainScorer();
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

