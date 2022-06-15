#include"./Analysis.h"
#include"./DataSetReader.h"
#define ll long long int
#define formulaid 19
using namespace std;

bool IsTOOSmall(Team t){return t.DDSwin < 7;}

int main(int argc, char* argv[]){
	vector<Team> teams;
	if(argc <= 1){
		cerr << "You miss some parameters, you have to give me two parameters" << endl;
		cerr << "./analysis [data set filename]" << endl;
		return 1;
	}
	string filename = argv[1];
	loadTeam(filename, teams);
	Experiment validate(teams);
	validate.setformulaid(formulaid);
	for(int i = 0;i < (int)validate.teams.size();i++){
		if((int)round(validate.teams[i].DDSwin) >= 7)continue;
		validate.teams.erase(validate.teams.begin() + i);
		validate.DDS.erase(validate.DDS.begin() + i);
		i--;
	}
	vector<string> scorematrix_string;
	vector<double> scorematrix(validate.FormulaArgumentSize[formulaid], 0);
	string s;
	vector<vector<Team>> dividedTeam;
	vector<map<double, int>> cTT;
	vector<double> meanTimes, gaps;
	map<int, int> result;
	scorematrix[0] = 0.5;
	scorematrix[1] = 0.75;
	scorematrix[2] = 1.25;
	scorematrix[3] = 2;
	scorematrix[4] = 2.75;
	scorematrix[5] = 1.1;
	scorematrix[6] = 0;
	scorematrix[7] = 3.75;
	scorematrix[8] = 2;
	scorematrix[9] = 1;
	scorematrix[10] = 0.5;
	for(double i = 0;i <= 4;i += 0.1){
		for(double j = 0;j <= 4;j += 0.1){
			scorematrix[11] = i;
			scorematrix[12] = j;
			dividedTeam.clear();
			cTT.clear();
			meanTimes.clear();
			gaps.clear();
			result.clear();
			int ercode = validate.Set_scorematrix(scorematrix);
			int d_size = validate.teams.size();
			if(ercode != 0){
				cerr << "--Wrong size of scorematrix--Size = " << ercode << endl;
				return 2;
			}
			else{
				validate.scorer();
				// Find the gap of continuous win tricks
				dividedTeam = classifyByDoubleDummyResult(validate.teams);
				meanTimes = MeanOfScore(dividedTeam);
				gaps = edgeOfEachScore(meanTimes);
				// Find the gap between the predicted win tricks and DDS
				result = gapOfWholeDataSet(validate.teams, gaps, true);
				cout << i << " " << j << " " << getcorr(validate) << " " << (double)round((double)result[0] / d_size * 10000) / 100;
				int total = result[0];
				for(int i = 1;i < 3;i++){
					total += result[i] + result[-i];
					cout << " " << (double)round((double)(total) / d_size * 10000) / 100;
				}
				cout << endl;	
			}
		}
	}
	return 0;
}
