#include<bits/stdc++.h>
#include"DataSetReader.h"
#include<algorithm>

using namespace std;

const vector<string> FULLCARD = {"AKQJT98765432","AKQJT98765432","AKQJT98765432","AKQJT98765432"};

int main(int argc, char** argv){
	if(argc < 2){
		cerr << "You have to give me a file to translate.\n";
		return 1;
	}
	fstream f;
	f.open(argv[1]);
	string text;
	while(getline(f, text)){
		if((text[0] >= '0' && text[0] <= '9') || text[0] == 'P'){
			cout << text << endl;
		}
		else{
			vector<string> hand = FULLCARD;
			vector<string> player = split(text, ":");
			cout << player[0] << ":";
			for(int i = 1;i < 4;i++){
				cout << player[i] << " ";
				vector<string> player_hand = split(player[i], ".");
				for(int j = 0;j < 4;j++){
					for(auto x:player_hand[j])
						hand[j].erase(remove(hand[j].begin(), hand[j].end(), x), hand[j].end());
				}
			}
			for(auto x:hand)cout << x << ".";
			cout << endl;
		}
	}
	f.close();
	return 0;
}
