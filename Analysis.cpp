#include"Analysis.h"

vector<vector<Team>> classifyByDoubleDummyResult(const vector<Team> &teams){
	vector<vector<Team>> ret(7, vector<Team>());
	for(auto team:teams){
		ret[(int)ceil(team.DDSwin) - 7].push_back(team);
	}
	for(int i = 0;i < 7;i++){
		cout << "In analysis ret[" << i + 1 << "] have " << ret[i].size() << " datas\n";
	}
	return ret;
}
vector<map<double, int>> countEachScoreAppearTime(const vector<vector<Team>> &teams){
	vector<map<double, int>> ret(7, map<double, int>());
	for(int i = 0;i < 7;i++){
		for(auto team:teams[i]){
			ret[i][round(team.score)]++;
		}
	}
	for(int i = 0;i < 7;i++){
		cout << "When DDSwin is " << i << endl;
		for(auto t:ret[i]){
			cout << "the score " << t.first << " occur " << t.second << " times\n";
		}
	}
	for(int i = 0;i < 7;i++){
		map<double, int>::iterator best = max_element(ret[i].begin(), ret[i].end(), [](const pair<double, int>&a, const pair<double, int>&b)->bool{return a.second < b.second;});
		cout << "the mode when get " << i + 1 << " tricks is : " << best->first << " and appear " << best->second << " times"  << endl;
	}
	return ret;
}
