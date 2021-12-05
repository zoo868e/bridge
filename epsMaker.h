#include "gnuplot-iostream.h"
#include <bits/stdc++.h>
using namespace std;
void initEPS(Gnuplot& gp, bool useColor);
void setOutputFile(Gnuplot& gp, string filename);
void setTitle(Gnuplot& gp, string title);
void plotLines(Gnuplot& gp, vector<map<double, int>> eachScoreAppearTimes, vector<double> gaps);
void plotLines(Gnuplot& gp, vector<map<int, int>> eachScoreAppearTimes, vector<double> gaps);
void setCloseFile(Gnuplot& gp);
