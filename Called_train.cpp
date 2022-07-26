#include"./Analysis.h"
#include"./DataSetReader.h"
#include"bits/stdc++.h"
using namespace std;

double roundto(double src, int decimal){
	double d = pow(10, decimal);
	return round(src * d) / d;
}

vector<double> get_default_para(int formulaid){
	vector<double> ret;
	if(formulaid % 100000 == 44002){
		ret = {1, 1, 1.5, 2, 2.5, 1, 1, 2.5, 1.5, 0.5};
	}
	return ret;
}

int main(int argc, char* argv[]){
	vector<Team> teams;
	if(argc <= 2){
		cerr << "You miss some parameters, you have to give me two parameters" << endl;
		cerr << "./Called_train [data set filename] [formula ID wanna validate]" << endl;
		return 1;
	}
	string filename = argv[1];
	loadTeam(filename, teams);
	if(teams.size() == 0){
		cerr << "There is no data over " << filename << endl;
		return 2;
	}
	Experiment E(teams);
	int formulaid = stoi(argv[2]);
	E.setformulaid(formulaid);
	vector<string> scorematrix_string;
	vector<double> scorematrix;
	vector<double> default_scorematrix = get_default_para(formulaid);
	if(default_scorematrix.size() == 0){
		cerr << "the formula haven't been trained, so it can't be fine-tune in any way.\n";
		return 4;
	}
	string s;
	double ans;
	while(getline(cin, s)){
		scorematrix_string.clear();
		scorematrix.clear();
		scorematrix = default_scorematrix;
		scorematrix_string = split(s, " ");
		for(int i = 0;i < (int)scorematrix_string.size(); i++){
			scorematrix.push_back(stod(scorematrix_string[i]));
		}
		int ercode = E.nSet_scorematrix(scorematrix);
		if(ercode != 0){
			cerr << "--Wrong size of scorematrix--Size = " << ercode << endl;
			return 3;
		}
		else{
			E.nScorer();
			ans = getcorr(E);
			cout << ans << endl;
			if(ans == -2){
				cerr << "Experiment:" << endl;
				cerr << "len(score): " << E.score.size() << endl;
				cerr << "score = ";
				for(auto x:E.score) cerr << x << " ";
				cerr << endl;
			}
		}
	}
}
