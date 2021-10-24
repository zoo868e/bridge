#include"./Bridge.h"
#define ll long long int

using namespace std;

vector<string> split(const string &, const string &);
int cardtoint(char);
double correlationCoefficient(vector<double> X, vector<double> Y, int n);

void loadTeam(string filename, vector<Team> &team){
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

vector<string> load_trained_file(string filename){
	cout << "start load trained file\n";
	vector<string> ret;
	fstream f;
	f.open(filename, ios::in);
	string s;
	while(getline(f, s)){
		if(s[0] != 'H')
			ret.push_back(s);
	}
	f.close();
	cout << "completed\n";
	for(auto x:ret)
		cout << x << endl;
	return ret;
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

int main(int argc, char* argv[]){
	string filename = "./data/wholedataForC";
	vector<Team> team;
	loadTeam(filename, team);
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
	string trained_file_name = "./0921_f3";
	vector<string> trained_argument = load_trained_file(trained_file_name);
	for(auto s:trained_argument){
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

