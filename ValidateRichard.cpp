#include"./DataSetReader.h"
#include<bits/stdc++.h>
#include"./Bridge.h"
#include"epsMaker.h"
#include"Analysis.h"
#include"ValidateRichard.h"

using namespace std;
vector<vector<string>> loadDDSvalidateFile(string filename){
	vector<vector<string>> ret;
	fstream f;
	f.open(filename);
	string text;
	vector<string> aGame;
	while(getline(f, text)){
		aGame.clear();
		vector<string> tmp;
		tmp = split(text, "|");
		aGame.push_back(tmp[1]);
		tmp = getSuitandResult(f);
		aGame.insert(aGame.end(), tmp.begin(), tmp.end());
		tmp = getSuitandResult(f);
		aGame.insert(aGame.end(), tmp.begin(), tmp.end());
		ret.push_back(aGame);
	}
	return ret;
}
vector<string> getSuitandResult(fstream &f){
	vector<string> ret;
	string text;
	getline(f, text);
	if(text[0] == 'P'){
		ret.push_back("P");
		return ret;
	}
	else{
		ret.push_back(text);
		getline(f, text);
		ret.push_back(text);
		return ret;
	}
}
vector<vector<int>> stringDDStoINT(string text){
	/*	return the DDS result
	 *	spade, Heart, Diamond, Club, No Trump, ...
	 *	|____________________________________|, ...
	 *					North
	 *	North, East, South, West
	 * */
	vector<vector<int>> ret(4, vector<int>(5, 0));
	vector<string> suit = split(text, "@");
	vector<string> hand;
	for(int i = 0;i < 5;i++){
		hand = split(suit[i], ",");
		for(int j = 0;j < 4;j++){
			ret[j][i] = stoi(hand[j]);
		}
	}
	return ret;
}
vector<int> disOfDDSandReality(vector<vector<int>> dds, vector<vector<int>> aGame){
	vector<int> ret;
	/*
	if(aGame.size() == 2 && aGame[0][0] == aGame[1][0] && aGame[0][1] == aGame[1][1]){
		int m = max(aGame[0][2], aGame[1][2]);
		ret.push_back(dds[aGame[0][1]][aGame[0][0]] - m);
	}
	else{*/
	for(auto x:aGame){
		ret.push_back(dds[x[1]][x[0]] - x[2]);
	}
	//}
	return ret;
}
map<int, int> DDSvalidate(vector<vector<string>> DDSdata){
	map<int, int> ret;
	vector<vector<int>> dds;
	vector<vector<int>> aGame;
	vector<int> dis;
	for(auto x:DDSdata){
		aGame.clear();
		dds = stringDDStoINT(x[0]);
		if(x[1][0] != 'P'){
			aGame.push_back(vector<int>({getSuit(x[1]), getPosition(x[1]), getResult(x[2])}));
			if(x[3][0] != 'P'){
				aGame.push_back(vector<int>({getSuit(x[3]), getPosition(x[3]), getResult(x[4])}));
			}
		}
		else if(x[2][0] != 'P'){
			aGame.push_back(vector<int>({getSuit(x[2]), getPosition(x[2]), getResult(x[3])}));
		}
		dis = disOfDDSandReality(dds, aGame);
		for(auto y:dis){
			ret[y]++;
		}
	}
	return ret;
}
int getSuit(string s){
	return SuitOrder[s[1]];
}
int getPosition(string s){
	if(s[3] == ':')return PositionOrder[s[4]];
	return PositionOrder[s[3]];
}
int getResult(string s){
	return stoi(s);
}
map<int, double> showValidateResult(map<int, int> validatedData){
	double totalResult = 0;
	map<int, double> ret;
	for(auto x:validatedData)totalResult += x.second;
	for(auto x:validatedData){
		ret[x.first] = round(x.second * 1000 / totalResult) / 1000;
	}
	return ret;
}
void plotMyHistogram(Gnuplot &gp, map<int, double> data){
	gp << "set xlabel \"DDS result - reality result\"\n";
	gp << "set ylabel \"percentage\"\n";
	gp << "set key samplen 2 spacing 2\n";
	vector<vector<pair<double, double>>> xy_pts;
	for(auto x:data){
		if(x.second == 0)continue;
		xy_pts.push_back(vector<pair<double, double>>({pair<double, double>(x.first, 0), pair<double, double>(x.first, x.second * 100)}));
	}
	gp << "plot ";
	int c = xy_pts.size();
	char a[100];
	for(auto line:xy_pts){
		memset(a, 0, sizeof(a));
		sprintf(a, "%.2f", line[1].second);
		gp << gp.file1d(line) << "w l lw 50 title \"" << a << "\"";
		if(c > 1){
			gp << ", ";
			c--;
		}
	}
	gp << endl;
}
int main(int argc, char** argv){
	Gnuplot gp;
	initEPS(gp, true);
	setOutputFile(gp, "DDSvalidate.eps");
	setTitle(gp, "DDS vs Reality");
	if(argc == 1){
		cerr << "You have to give me a file to validate.\n";
		cerr << "usage: ValidateRichard filename\n";
		return 1;
	}
	string filename = argv[1];
	vector<vector<string>> DDSdata;
	DDSdata = loadDDSvalidateFile(filename);
	map<int, int> validateResult;
	validateResult = DDSvalidate(DDSdata);
	map<int, double> showEPS;
	showEPS = showValidateResult(validateResult);
	plotMyHistogram(gp, showEPS);
	setCloseFile(gp);
	return 0;
}
