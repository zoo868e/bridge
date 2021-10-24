#include "Bridge.h"
#include "DataSetReader.h"

using namespace std;

int main(int argc, char** argv){
	if(argc < 3){
		cerr << "Need more arguments\n";
		cerr << "analysisByFourHand <file name> <formula ID>\n";
		return 1;
	}
	vector<Game> game;
	loadGame(argv[1], game);
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
	return 0;
}
