#include"Bridge.h"
#include"DataSetReader.h"

using namespace std;


int main(int argc, char* argv[]){
	if(argc != 2){
		cerr << "Need more argument\n";
		cerr << "./testFunc [data set file name]\n";
		return 1;
	}
	string filename = argv[1];
	cout << filename << endl;
	vector<Team> team;
	loadTeam(filename, team);
	if(team.size() == 0){
		cerr << "There are no any data here!!\n";
		return 1;
	}
	Experiment E = Experiment(team);
	string s;
	vector<string> matrixb;
	while(getline(cin, s)){
		matrixb.clear();
		matrixb = split(s, " ");
		for(int i = 0;i < (int)matrixb.size();i++){
			E.f_distributedistance[i] = stod(matrixb[i]);
		}
		for(int i = 0;i < (int)team.size();i++){
			cout << "-----hand-----" << endl;
			for(int j = 0;j < 2;j++){
				cout << "Player[" << j + 1 << "]" << endl;
				for(auto x:E.teams[i].player[j].hand.getcard()){
					for(auto card:x){
						cout << card << " ";
					}
					cout << endl;
				}
			}
			cout << "-----Trump suit-----" << endl;
			cout << E.teams[i].suit << endl;
			cout << "-----Trump suit length-----" << endl;
			cout << "Player[1]: " << E.teams[i].player[0].hand.distributed[E.teams[i].suit] << ", Player[2]: " << E.teams[i].player[1].hand.distributed[E.teams[i].suit] << endl;
			cout << "-----distributedistance score-----" << endl;
			cout << E.distributedistance(E.teams[i]) << endl;
		}
	}
	return 0;
}
