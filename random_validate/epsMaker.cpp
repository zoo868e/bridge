#include"./epsMaker.h"
void initEPS(Gnuplot& gp, bool useColor){
	if(useColor)
		gp << "set term postscript eps enhanced color\n";
	else
		gp << "set term postscript eps enhanced\n";

}
void setOutputFile(Gnuplot& gp, string filename){
	gp << "set output \"" << filename << "\"\n";
}
void setTitle(Gnuplot& gp, string title){
	gp << "set title \"" << title << "\"\n";
}
void plotLines(Gnuplot& gp, vector<map<double, int>> eachScoreAppearTimes, vector<double> gaps = {}){
	gp << "plot";
	const int N = eachScoreAppearTimes.size();
	double height = 0;
	vector<vector<pair<double, double>>> xy_pts(N);
	for(int i = 0;i < N;i++){
		int datasize = 0;
		for(auto score:eachScoreAppearTimes[i])
			datasize += score.second;
		for(auto score:eachScoreAppearTimes[i]){
			xy_pts[i].push_back(make_pair(score.first, (double)score.second / datasize));
			height = height > (double)score.second / datasize ? height:(double)score.second / datasize;
		}
	}
	vector<vector<pair<double, double>>> xy_gaps;
	for(auto x:gaps){
		xy_gaps.push_back(vector<pair<double, double>>({pair<double, double>(x, 0), pair<double, double>(x, height)}));
	}
	for(int i = 0;i < N;i++){
		gp << gp.file1d(xy_pts[i]) << "with lines title \'" << i + 7 << "\',";
	}
	for(auto line:xy_gaps){
		gp << gp.file1d(line) << "with lines notitle lt rgb \"black\", ";
	}
	gp << endl;
}
void plotLines(Gnuplot& gp, vector<map<int, int>> eachScoreAppearTimes, vector<double> gaps = {}){
	gp << "plot";
	const int N = eachScoreAppearTimes.size();
	double height = 0;
	vector<vector<pair<double, double>>> xy_pts(N);
	for(int i = 0;i < N;i++){
		int datasize = 0;
		for(auto score:eachScoreAppearTimes[i])
			datasize += score.second;
		for(auto score:eachScoreAppearTimes[i]){
			xy_pts[i].push_back(make_pair(score.first, (double)score.second / datasize));
			height = height > (double)score.second / datasize ? height:(double)score.second / datasize;
		}
	}
	vector<vector<pair<double, double>>> xy_gaps;
	for(auto x:gaps){
		xy_gaps.push_back(vector<pair<double, double>>({pair<double, double>(x, 0), pair<double, double>(x, height)}));
	}
	for(int i = 0;i < N;i++){
		if(i < 7)
			gp << gp.file1d(xy_pts[i]) << "with linespoints linetype 0 title \'" << i << "\',";
		else
			gp << gp.file1d(xy_pts[i]) << "with linespoints title \'" << i << "\',";
	}
	for(auto line:xy_gaps){
		gp << gp.file1d(line) << "with lines notitle lt rgb \"black\", ";
	}
	gp << endl;
}
void setCloseFile(Gnuplot& gp){
	gp << "set output\n";
}
void plotSplitLines(Gnuplot& gp, vector<double> gaps){
	vector<vector<pair<double, double>>> xy_pts;
	for(auto x:gaps){
		xy_pts.push_back(vector<pair<double, double>>({pair<double, double>(x, 0), pair<double, double>(x, 1)}));
	}
	for(auto line:xy_pts){
		gp << "plot" << gp.file1d(line) << "with lines, ";
	}
	gp << endl;
}
