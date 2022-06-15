#include"DataSetReader.h"

vector<vector<Team>> classifyByDoubleDummyResult(const vector<Team> &teams);
vector<vector<PartialGame>> classifyByDoubleDummyResult(const vector<PartialGame> &games);
vector<map<double, int>> countEachScoreAppearTime(const vector<vector<Team>> &teams);
vector<map<double, int>> countEachScoreAppearTime(const vector<vector<PartialGame>> &games);
vector<int> maximumAppearTimesOfEachScore(const vector<map<double, int>>);
vector<double> edgeOfEachScore(const vector<int>);
vector<double> edgeOfEachScore(const vector<double>);
int distanceOfPredictAndDDS(const Team, const vector<double>);
int distanceOfPredictAndDDS(const PartialGame, const vector<double>);
int PredictWinTricks(const Team &, const vector<double>);
map<int, int> gapOfWholeDataSet(const vector<Team>, const vector<double>, bool RealValue = false);
map<int, int> gapOfWholeDataSet(const vector<PartialGame>, const vector<double>, bool RealValue = false);
vector<double> meanAppearTimesOfEachScore(const vector<map<double, int>>);
vector<int> middleAppearTimesOfEachScore(const vector<map<double, int>>);
int realvalueOfPredictAndDDS(const Team team, const vector<double> gaps);
int realvalueOfPredictAndDDS(const PartialGame game, const vector<double> gaps);
//map<int, int> test(const vector<int>, const vector<double>, bool RealValue = false);


vector<double> MeanOfScore(const vector<vector<Team>> &teams);
