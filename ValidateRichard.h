#include <bits/stdc++.h>
using namespace std;
map<char, int> SuitOrder = {{'S', 0}, {'H', 1}, {'D', 2}, {'C', 3}, {'N', 4}};
map<char, int> PositionOrder = {{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
vector<vector<string>> loadDDSvalidateFile(string filename);
vector<string> getSuitandResult(fstream &f);
vector<vector<int>> stringDDStoINT(string);
map<int, int> DDSvalidate(vector<vector<string>> DDSdata);
int getSuit(string s);
int getPosition(string s);
int getResult(string s);
vector<int> disOfDDSandReality(vector<vector<int>> dds, vector<vector<int>> aGame);
map<int, double> showValidateResult(map<int, int> validatedData);
