#include"Analysis.h"

vector<vector<Team>> classifyByDoubleDummyResult(const vector<Team> &teams){
	/*	input : the data set will be classify
	 *	return the classified data set
	 * */
	vector<vector<Team>> ret(7, vector<Team>());
	for(auto team:teams){
		ret[(int)ceil(team.DDSwin) - 7].push_back(team);
	}
	/*
	for(int i = 0;i < 7;i++){
		cout << "In analysis ret[" << i + 1 << "] have " << ret[i].size() << " datas\n";
	}
	*/
	return ret;
}
vector<map<double, int>> countEachScoreAppearTime(const vector<vector<Team>> &teams){
	/*	input : the whole data have to count the score appear times.
	 *	return the appear times of each score between every win tricks.
	 * */
	vector<map<double, int>> ret(7, map<double, int>());
	for(int i = 0;i < 7;i++){
		for(auto team:teams[i]){
			ret[i][round(team.score)]++;
		}
	}
	/*
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
	*/
	return ret;
}

vector<int> maximumAppearTimesOfEachScore(const vector<map<double, int>> EachScoreAppearTimes){
	/*	input : the appear times of each score between every win tricks.
	 *	return the maximum appear times of each score between every win tricks.
	 * */
	vector<int> ret;
	for(auto x:EachScoreAppearTimes){
		map<double, int>::iterator best = max_element(x.begin(), x.end(), [](const pair<double, int>& a, const pair<double, int>& b)->bool{return a.second < b.second;});
		ret.push_back(best->first);
	}
	return ret;
}

vector<double> edgeOfEachScore(const vector<int> maxAppearTimes){
	/*	input : the maximum appear times of score in each win tricks.
	 *	return the edge of each adjacent win tricks.
	 * */
	vector<double> ret;
	for(int i = 1;i < (int)maxAppearTimes.size();i++){
		ret.push_back(maxAppearTimes[i - 1] + ((double)(maxAppearTimes[i] - maxAppearTimes[i - 1])) / 2);
	}
	return ret;
}

int distanceOfPredictAndDDS(const Team team, const vector<double> gaps){
	/*	input : the particular data and the gaps between the adjacent win tricks
	 *	return the distance of predict win tricks and Double Dummy Result
	 * */
	int DDS = round(team.DDSwin), predict = 7, score = team.score;
	for(auto x:gaps){
		if(score < x)break;
		predict++;
	}
	return abs(DDS - predict);
}
map<int, int> gapOfWholeDataSet(const vector<Team> teams, const vector<double> gaps){
	/*	input : the whole data and the gaps between the adjacent win tricks
	 *	return the count of each distance between predict win tricks and Double Dummy Result
	 * */
	map<int, int> ret;
	for(auto team:teams)
		ret[distanceOfPredictAndDDS(team, gaps)]++;
	return ret;
}
void makeGapEPS(const vector<map<double, int>> EachScoreAppearTime, const string filename){
	/*	Haven't complete
	 * */
	ofstream f;
	f.open(filename);
	for(auto x:EachScoreAppearTime){
		for(auto z:x)
			f << z.first << ":" << z.second << " ";
		f << endl;
	}
	f.close();
	for(auto x:EachScoreAppearTime){
		cout << "__________________________\n";
		for(auto z:x)
			cout << "Score = " << z.first << ", occur " << z.second << " times.\n";
	}
}
