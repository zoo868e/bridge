#include"bits/stdc++.h"
#include"Bridge.h"
vector<string> split(const string &, const string &);
int cardtoint(char);
double correlationCoefficient(vector<double> X, vector<double> Y, int n);
void loadTeam(string filename, vector<Team> &team);
void loadGame(string filename, vector<Game> &games);
double getcorr(Experiment expe);
vector<vector<int>> stringDDStoINT(string text);
