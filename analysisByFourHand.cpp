#include "Bridge.h"
#include "DataSetReader.h"

using namespace std;
const vector<double> ArgumentOfFormulaTwo{1.045, 1.229, 1.629, 2.066, 2.912, 3.527, 1.019, 1.2, 0.5106, 0.2381, 0.2422, 2.043, 1.122, 0.01089, 0.3142, 2.107, 1.366};

int main(int argc, char** argv){
	if(argc < 3){
		cerr << "Need more arguments\n";
		cerr << "analysisByFourHand <file name> <formula ID>\n";
		return 1;
	}
	vector<Game> game;
	vector<PartialGame> partialgames;
//	loadGame(argv[1], game);
	loadPartialGames(argv[1], partialgames);
	Experiment PartialgameExperiment(partialgames, atoi(argv[2]));
	PartialgameExperiment.Set_scorematrix(ArgumentOfFormulaTwo);
	PartialgameExperiment.setFixformulaid(3);
//	PartialgameExperiment.PartialGamePreScorer();
	/*
	for(auto game:PartialgameExperiment.Partialgames){
		for(auto player:game.player){
			cout << "player: " << endl;
			auto hand = player.getPlayer();
			auto cards = hand.first.getcard();
			for(auto s:cards){
				for(auto c:s)cout << c << " ";
				cout << endl;
			}
			cout << player.score << endl;
			cout << "------------------\n";
		}
		cout << "suit = " << game.suit << endl;
		cout << "DDSwin = " << game.DDSwin << endl;
		cout << "Maker = " << game.maker << endl << endl;
	}*/
	string input;
	vector<string> scorematrixb;
	vector<double> scorematrix;
	while(getline(cin, input)){
		scorematrixb.clear();
		scorematrix.clear();
		scorematrixb = split(input, " ");
		for(int i = 0;i < (int)scorematrixb.size();i++){
			scorematrix.push_back(stod(scorematrixb[i]));
		}
		int ercode = PartialgameExperiment.Set_FixFormulaArgumentList(scorematrix);
		if(ercode){
			cerr << "--Wrong size of scorematrix--" << endl;
			cerr << "Need " << PartialgameExperiment.FixFormulaArgumentSize[PartialgameExperiment.formulaid] << " parameters and you give " << ercode << " parameters." << endl;
		}
		else{
			PartialgameExperiment.PartialGameTrainScorer();
			double ans = getcorr(PartialgameExperiment);
			cout << ans << endl;
			if(ans == -2){
				cout << "Experiment: " << endl;
				cout << "len(score): " << PartialgameExperiment.score.size() << endl;
				cout << "score = ";
				for(auto x:PartialgameExperiment.score)cout << x << " ";
				cout << endl;
			}
		}
	}
	/*
	for(auto g:game){
		auto gameinfo = g.getGame();
		auto dds = gameinfo.second;
		auto players = gameinfo.first;
		cout << "dds win tricks\n";
		for(auto s:dds){
			for(auto w:s)cout << w << " ";
			cout << endl;
		}
		cout << "card distributed\n";
		for(auto player:players){
			cout << "player: " << endl;
			auto hand = player.getPlayer();
			auto cards = hand.first.getcard();
			for(auto s:cards){
				for(auto c:s)cout << c << " ";
				cout << endl;
			}
			cout << "----------------" << endl;
		}
	}
	Experiment FourHand(game, 2);
	FourHand.Set_scorematrix(ArgumentOfFormulaTwo);
	FourHand.GameScorer();
	*/
	return 0;
}
