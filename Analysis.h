#include"Bridge.h"

vector<vector<Team>> classifyByDoubleDummyResult(const vector<Team> &teams);
vector<map<double, int>> countEachScoreAppearTime(const vector<vector<Team>> &teams);
vector<int> maximumAppearTimesOfEachScore(const vector<map<double, int>>);
vector<double> edgeOfEachScore(const vector<int>);
int distanceOfPredictAndDDS(const Team, const vector<double>);
map<int, int> gapOfWholeDataSet(const vector<Team>, const vector<double>);
void makeGapEPS(const vector<map<double, int>>, const string);
