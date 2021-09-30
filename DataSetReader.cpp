#include"DataSetReader.h"
void loadfile(string filename, vector<Team> &team){
	/* The first argument in file is the hand card of player 1 
	 * Second argument in file is the hand card of player 2
	 * Third argument in file is the number of win tricks
	 * Fourth argument in file indicate the trump suit
	 * Fifth argument in file indicate who make this deal
	 * */
	fstream f;
	f.open(filename, ios::in);
	string s;
	vector<string> vs;
	while(getline(f, s))vs.push_back(s);
	for(auto x:vs){
//		cout << x << endl;
		vector<string> info = split(x, " ");
		vector<vector<int>> hand1, hand2;
		hand1.resize(4);
		hand2.resize(4);
		vector<string> strhand1 = split(info[0], "."), strhand2 = split(info[1], ".");
		for(int i = 0;i < 4;i++){
			for(int j = 0;j < (int)strhand1[i].size();j++){
				hand1[i].push_back(cardtoint(strhand1[i][j]));
			}
			sort(hand1[i].begin(), hand1[i].end());
			for(int j = 0;j < (int)strhand2[i].size();j++){
				hand2[i].push_back(cardtoint(strhand2[i][j]));
			}
			sort(hand2[i].begin(), hand2[i].end());
		}
//		cout << info[2] << endl;
		team.push_back(Team(Player(Hand(hand1[0], hand1[1], hand1[2], hand1[3])), Player(Hand(hand2[0], hand2[1], hand2[2], hand2[3])), atof(info[2].c_str()), stoi(info[3]), stoi(info[4])));
	}
	f.close();

}

vector<string> split(const string &str, const string & delim){
	vector<string> res;
	if("" == str)return res;
	string strs = str + delim;
	size_t pos;
	size_t size = strs.size();
	for(size_t i = 0;i < size;i++){
		pos = strs.find(delim, i);
		if(pos < size){
			string s = strs.substr(i, pos - i);
			res.push_back(s);
			i = pos + delim.size() - 1;
		}
	}
	return res;
}

int cardtoint(char c){
	switch(c){
	case 'A':
		return 1;
	case 'K':
		return 13;
	case 'Q':
		return 12;
	case'J':
		return 11;
	case 'T':
		return 10;
	default:
		return c - '0';
	}
}

double getcorr(Experiment expe){
	return correlationCoefficient(expe.score, expe.DDS, expe.score.size());
}

double correlationCoefficient(vector<double> X, vector<double> Y, int n){
	double sum_X = 0, sum_Y = 0, sum_XY = 0;
	double squaresum_X = 0, squaresum_Y = 0;
	for(int i = 0;i < n;i++){
		sum_X += X[i];
		sum_Y += Y[i];
		sum_XY += X[i] * Y[i];
		squaresum_X += X[i] * X[i];
		squaresum_Y += Y[i] * Y[i];
	}
//	cout << "sum_X = " << sum_X << "\nsum_Y = " << sum_Y << "\nsum_XY = " << sum_XY << "\nsquaresum_X = " << squaresum_X << "\nsquaresum_Y = " << squaresum_Y << endl;
	
	double d = (double)sqrt((n * squaresum_X - sum_X * sum_X) * (n * squaresum_Y - sum_Y * sum_Y));
	double u = (double)(n * sum_XY - sum_X * sum_Y);
//	cout << "u = " << u << "\nd = " << d << endl;
	double corr;
	if(u == 0 && d == 0 && X.size() == 0)corr = -2;
	else if(u == 0)corr = 0;
	else corr = u / d;
//	cout << corr << endl;
	return corr;
}

bool useformula(string s){
	if(s == "n")
		return false;
	else return true;
}


