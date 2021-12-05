#include "Bridge.h"
#include "DataSetReader.h"

using namespace std;

const vector<double> ArgumentOfFormulaTwo{1.045, 1.229, 1.629, 2.066, 2.912, 3.527, 1.019, 1.2, 0.5106, 0.2381, 0.2422, 2.043, 1.122, 0.01089, 0.3142, 2.107, 1.366};

int main(){
	string input;
	vector<Game> G;
	vector<PartialGame> P;
	vector<vector<int>> DDSWON(4, vector<int>(5, 0));
	vector<string> info, strhand;
	vector<vector<vector<int>>> hand(4, vector<vector<int>>(4));
	Player player[4];
	Experiment E(P, 2);
	E.Set_scorematrix(ArgumentOfFormulaTwo);
//	E.setformulaid(-1);
	while(getline(cin, input)){
		hand.clear();
		hand.resize(4, vector<vector<int>>(4));
		P.clear();
		G.clear();
		info = split(input, " ");
		for(int i = 0;i < 4;i++){
			strhand = split(info[i], ".");
			for(int j = 0;j < 4;j++){
				for(auto x:strhand[j])
					hand[i][j].push_back(cardtoint(x));
				sort(hand[i][j].begin(), hand[i][j].end());
			}
		}
		for(int i = 0;i < 4;i++)
			player[i] = Player(Hand(hand[i][0], hand[i][1], hand[i][2], hand[i][3]));
		G.push_back(Game(player[0], player[1], player[2], player[3], DDSWON));
		E.games = G;
		E.GameScorer();
		cout << setw(10) << "Spade" << setw(10) << "Heart" << setw(10) << "Diamond" << setw(10) << "Club" << setw(10) << "No Trump" << endl;
		for(auto game:E.games){
			for(auto player:game.ScoreForPlayers){
				for(auto score:player)
					cout << setw(10) << score;
				cout << endl;
			}
			cout << "################" << endl;
			for(auto player:game.Players){
				for(auto suit:player.hand.getcard()){
					for(auto card:suit)
						cout << card << " ";
					cout << endl;
				}
				cout << "----------------" << endl;
			}
		}
	}
	return 0;
}
