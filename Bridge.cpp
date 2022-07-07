#include"Bridge.h"
Experiment::Experiment(vector<Team> teams, int _formulaid){
			this->teams = teams;
			this->formulaid = _formulaid;
			this->needed_para = this->HCPSize[_formulaid % 10] + this->suitHCPSize[(_formulaid / 10) % 10] + this->distriSize[(_formulaid / 100) % 10] + this->longSize[(_formulaid / 1000) % 10] + this->shortSize[(_formulaid / 10000) % 10] + this->CHCPSize[(_formulaid / 100000) % 10] + this->CShortSize[(_formulaid / 1000000) % 10] + this->CDisSize[(_formulaid / 10000000) % 10] + this->CLongSize[(_formulaid / 100000000) % 10];
			this->Fixformulaid = 1;
			this->long4card.clear();
			this->long4card.resize(2);
			for(int i = 0;i < 14;i++){
				this->HCPlist[0][i] = basicHCP[i];
				this->HCPlist[1][i] = basicHCP[i];
				this->lenlist[0][i] = basiclen[i];
				this->lenlist[1][i] = basiclen[i];
				this->Hlenlist[0][i] = 0;
				this->Hlenlist[1][i] = 0;
				this->Dlenlist[0][i] = 0;
				this->Dlenlist[1][i] = 0;
			}
			for(int i = 0;i < (int)teams.size();i++){
				DDS.push_back(teams[i].DDSwin);
			}
			memset(this->AssestScore, 0, sizeof(this->AssestScore));
			this->AssestScore[0] = 2;
			this->AssestScore[1] = 1;
			for(int i = 5;i < (int)(sizeof(this->AssestScore) / sizeof(double));i++)
				this->AssestScore[i] = 1;
		}
void Experiment::setformulaid(int _formulaid){
			this->formulaid = _formulaid;
			this->needed_para = this->HCPSize[_formulaid % 10] + this->suitHCPSize[(_formulaid / 10) % 10] + this->distriSize[(_formulaid / 100) % 10] + this->longSize[(_formulaid / 1000) % 10] + this->shortSize[(_formulaid / 10000) % 10] + this->CHCPSize[(_formulaid / 100000) % 10] + this->CShortSize[(_formulaid / 1000000) % 10] + this->CDisSize[(_formulaid / 10000000) % 10] + this->CLongSize[(_formulaid / 100000000) % 10];
		}
void Experiment::foo(){
	cout << "You don't need re-link it" << endl;
	vector<int> b;
	for(int i = 0;i < 10;i++)
		b.push_back(i);
	for(auto x:b)
		cout << x << " ";
	cout << endl;
}

void Experiment::bar(){
	cout << "1212121212" << endl;
}
vector<vector<int>> Hand::getcard(){
	vector<vector<int>> ret;
	ret.push_back(this->spade);
	ret.push_back(this->heart);
	ret.push_back(this->diamond);
	ret.push_back(this->club);
	return ret;
}

pair<Hand, string> Player::getPlayer(){
	pair<Hand, string> ret;
	ret.first = this->hand;
	ret.second = this->position;
	return ret;
}

vector<Player> Game::getPlayer(){
	vector<Player> ret;
	ret.push_back(this->South);
	ret.push_back(this->West);
	ret.push_back(this->North);
	ret.push_back(this->East);
	return ret;
}

pair<vector<Player>, vector<vector<int>>> Game::getGame(){
	pair<vector<Player>, vector<vector<int>>> ret;
	ret.first = this->getPlayer();
	vector<vector<int>> t;
	t.push_back(this->SouthDDS);
	t.push_back(this->WestDDS);
	t.push_back(this->NorthDDS);
	t.push_back(this->EastDDS);
	ret.second = t;
	return ret;
}

void Game::Set_long(){
	/*	{[North and South], [West and East]}
	 *	[length of longest suit, the suit, the win tricks]
	 * */
	vector<float> NS, WE;
	NS.resize(3);
	WE.resize(3);
	NS[0] = -1, NS[1] = 0, NS[2] = 0;
	WE[0] = -1, WE[1] = 0, WE[2] = 0;
	vector<vector<int>> suit;
	suit.push_back(this->South.hand.distributed);
	suit.push_back(this->West.hand.distributed);
	suit.push_back(this->North.hand.distributed);
	suit.push_back(this->East.hand.distributed);
	for(int i = 0;i < 4;i++){
		int lsn = suit[0][i] + suit[2][i];
		int lwe = suit[1][i] + suit[3][i];
		if(lsn > NS[1]){
			NS[1] = lsn;
			NS[0] = i;
			NS[2] = (this->SouthDDS[i] + this->NorthDDS[i]) / 2;
		}
		else if(lsn == NS[1]){
			if(NS[2] < (this->SouthDDS[i] + this->NorthDDS[i]) / 2){
				NS[0] = i;
				NS[2] = (this->SouthDDS[i] + this->NorthDDS[i]) / 2;
			}
		}
		if(lwe > WE[1]){
			WE[1] = lwe;
			WE[0] = i;
			WE[2] = (this->WestDDS[i] + this->EastDDS[i]) / 2;
		}
		else if(lwe == WE[1]){
			if(WE[2] < (this->WestDDS[i] + this->EastDDS[i]) / 2){
				WE[0] = i;
				WE[2] = (this->WestDDS[i] + this->EastDDS[i]) / 2;
			}
		}
	}
	this->longest = pair<vector<float>, vector<float>>(NS, WE);
}

int Experiment::Set_scorematrix(vector<double> scorematrix){
	/* Set the score matrix by new formula parameters
	 * If the input size is 
	 * 	1. 28, 56, 84, 112:
	 * 		set the parameters to the traditional discrete method matrix
	 * 	2. 26 and the formulaid = 1: Only use the HCPlist[0] and the formula
	 * 		set the prefix 14 parameters to HCPlist[0]
	 * 		set the remaining parameters to f1list
	 * 		f1list = {trump, non-trump} and each element have 5 parameters
	 * 		parameters in each element = 
	 * 			[base1, linear1, base2, base3 for exponential, exponent, linear2]
	 * 	3. 17 and the formulaid = 2: Only use the HCPlist[0] and other formula
	 * 		set the first parameter to HCPlist[0][2~8]
	 * 				second parameter to HCPlist[0][9-10]
	 * 				third parameter to HCPlist[0][11]
	 * 				forth parameter to HCPlist[0][12]
	 * 				fifth parameter to HCPlist[0][13]
	 * 		and set the HCPlist[0][1] to 4
	 * 		and set the remaining parameters to f2list
	 * 		f2list = {trump, non-trump} and each element have 6 parameters
	 * 		element in f2list = 
	 * 			[linear suitHCPsum, exponent suitHCPsum, linear long, exponent long, linear short, exponent short]
	 * 	else: print the error message and terminate the process
	 * */
	int s = scorematrix.size();
	/*
	if(s == 28){
		for(int i = 0;i < 14;i++){
			this->HCPlist[0][i] = scorematrix[i];
			this->HCPlist[1][i] = scorematrix[14 + i];
		}
	}
	else if(s == 56){
		for(int i = 0;i < 14;i++){
			this->HCPlist[0][i] = scorematrix[i];
			this->HCPlist[1][i] = scorematrix[14 + i];
			this->lenlist[0][i] = scorematrix[28 + i];
			this->lenlist[1][i] = scorematrix[42 + i];
		}
	}
	else if(s == 84){
		for(int i = 0;i < 14;i++){
			this->HCPlist[0][i] = scorematrix[i];
			this->HCPlist[1][i] = scorematrix[14 + i];
			this->lenlist[0][i] = scorematrix[28 + i];
			this->lenlist[1][i] = scorematrix[42 + i];
			this->Hlenlist[0][i] = scorematrix[56 + i];
			this->Hlenlist[1][i] = scorematrix[70 + i];
		}
	}
	else if(s == 112){
		for(int i = 0;i < 14;i++){
			this->HCPlist[0][i] = scorematrix[i];
			this->HCPlist[1][i] = scorematrix[14 + i];
			this->lenlist[0][i] = scorematrix[28 + i];
			this->lenlist[1][i] = scorematrix[42 + i];
			this->Hlenlist[0][i] = scorematrix[56 + i];
			this->Hlenlist[1][i] = scorematrix[70 + i];
			this->Dlenlist[0][i] = scorematrix[84 + i];
			this->Dlenlist[1][i] = scorematrix[98 + i];
		}
	}
	else */if(s == 26 && this->formulaid == 1){
		for(int i = 0;i < 14;i++)
			this->HCPlist[0][0] = scorematrix[i];
		for(int i = 0;i < 6;i++){
			this->f1list[0][i] = scorematrix[i + 14];
			this->f1list[1][i] = scorematrix[i + 20];
		}
	}
	else if(s == 17 && this->formulaid == 2){
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		for(int i = 0;i < 6;i++){
			this->FormulaArgumentList[0].push_back(scorematrix[5 + i]); 	// If is trump suit
			this->FormulaArgumentList[1].push_back(scorematrix[11 + i]);	// If not trump suit
		}
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->f_long[0][0] = this->FormulaArgumentList[0][2];
		this->f_long[0][1] = this->FormulaArgumentList[0][3];
		this->f_long[1][0] = this->FormulaArgumentList[1][2];
		this->f_long[1][1] = this->FormulaArgumentList[1][3];
		this->f_short[0][0] = this->FormulaArgumentList[0][4];
		this->f_short[0][1] = this->FormulaArgumentList[0][5];
		this->f_short[1][0] = this->FormulaArgumentList[1][4];
		this->f_short[1][1] = this->FormulaArgumentList[1][5];
	}
	else if(s == 9 && this->formulaid == 3){
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList[0].push_back(scorematrix[5]);
		this->FormulaArgumentList[0].push_back(scorematrix[6]);
		this->FormulaArgumentList[1].push_back(scorematrix[7]);
		this->FormulaArgumentList[1].push_back(scorematrix[8]);
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
	}
	else if(s == 11 && this->formulaid == 4){
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList[0].push_back(scorematrix[5]);
		this->FormulaArgumentList[0].push_back(scorematrix[6]);
		this->FormulaArgumentList[0].push_back(scorematrix[7]);
		this->FormulaArgumentList[1].push_back(scorematrix[8]);
		this->FormulaArgumentList[1].push_back(scorematrix[9]);
		this->FormulaArgumentList[1].push_back(scorematrix[10]);
		this->f_dist[0][0] = this->FormulaArgumentList[0][0];
		this->f_dist[0][1] = this->FormulaArgumentList[0][1];
		this->f_dist[0][2] = this->FormulaArgumentList[0][2];
		this->f_dist[1][0] = this->FormulaArgumentList[1][0];
		this->f_dist[1][1] = this->FormulaArgumentList[1][1];
		this->f_dist[1][2] = this->FormulaArgumentList[1][2];
	}
	else if(s == 15 && this->formulaid == 5){
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList[0].push_back(scorematrix[5]);
		this->FormulaArgumentList[0].push_back(scorematrix[6]);
		this->FormulaArgumentList[1].push_back(scorematrix[7]);
		this->FormulaArgumentList[1].push_back(scorematrix[8]);
		this->FormulaArgumentList[0].push_back(scorematrix[9]);
		this->FormulaArgumentList[0].push_back(scorematrix[10]);
		this->FormulaArgumentList[0].push_back(scorematrix[11]);
		this->FormulaArgumentList[1].push_back(scorematrix[12]);
		this->FormulaArgumentList[1].push_back(scorematrix[13]);
		this->FormulaArgumentList[1].push_back(scorematrix[14]);
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->f_dist[0][0] = this->FormulaArgumentList[0][2];
		this->f_dist[0][1] = this->FormulaArgumentList[0][3];
		this->f_dist[0][2] = this->FormulaArgumentList[0][4];
		this->f_dist[1][0] = this->FormulaArgumentList[1][2];
		this->f_dist[1][1] = this->FormulaArgumentList[1][3];
		this->f_dist[1][2] = this->FormulaArgumentList[1][4];
	}
	else if(this->formulaid == 6 && s == 12){
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		for(int i = 0;i < 6;i++){
			this->FormulaArgumentList[0].push_back(scorematrix[i]);
			this->FormulaArgumentList[1].push_back(scorematrix[i + 6]);
		}
		for(int i = 0;i < 2;i++){
			for(int j = 0;j < 2;j++){
				this->f_suitHCP[i][j] = this->FormulaArgumentList[i][j];
				this->f_long[i][j] = this->FormulaArgumentList[i][j + 2];
				this->f_short[i][j] = this->FormulaArgumentList[i][j + 4];
			}
		}
	}
	else if(s == 19 && this->formulaid == 7){
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		for(int i = 0;i < 6;i++){
			this->FormulaArgumentList[0].push_back(scorematrix[5 + i]); 	// If is trump suit
			this->FormulaArgumentList[1].push_back(scorematrix[11 + i]);	// If not trump suit
		}
		this->long4card[0] = scorematrix[17];
		this->long4card[1] = scorematrix[18];
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->f_long[0][0] = this->FormulaArgumentList[0][2];
		this->f_long[0][1] = this->FormulaArgumentList[0][3];
		this->f_long[1][0] = this->FormulaArgumentList[1][2];
		this->f_long[1][1] = this->FormulaArgumentList[1][3];
		this->f_short[0][0] = this->FormulaArgumentList[0][4];
		this->f_short[0][1] = this->FormulaArgumentList[0][5];
		this->f_short[1][0] = this->FormulaArgumentList[1][4];
		this->f_short[1][1] = this->FormulaArgumentList[1][5];
//		cout << "Set correctly\n";
	}
	else if(s == 21 && this->formulaid == 8){
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		for(int i = 0;i < 8;i++){
			this->FormulaArgumentList[0].push_back(scorematrix[5 + i]); 	// If is trump suit
			this->FormulaArgumentList[1].push_back(scorematrix[13 + i]);	// If not trump suit
		}
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->tf_long[0][0] = this->FormulaArgumentList[0][2];
		this->tf_long[0][1] = this->FormulaArgumentList[0][3];
		this->tf_long[0][2] = this->FormulaArgumentList[0][4];
		this->tf_long[1][0] = this->FormulaArgumentList[1][2];
		this->tf_long[1][1] = this->FormulaArgumentList[1][3];
		this->tf_long[1][2] = this->FormulaArgumentList[1][4];
		this->tf_short[0][0] = this->FormulaArgumentList[0][5];
		this->tf_short[0][1] = this->FormulaArgumentList[0][6];
		this->tf_short[0][2] = this->FormulaArgumentList[0][7];
		this->tf_short[1][0] = this->FormulaArgumentList[1][5];
		this->tf_short[1][1] = this->FormulaArgumentList[1][6];
		this->tf_short[1][2] = this->FormulaArgumentList[1][7];
	}
	else if(s == 21 && this->formulaid == 9){
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		for(int i = 0;i < 8;i++){
			this->FormulaArgumentList[0].push_back(scorematrix[5 + i]); 	// If is trump suit
			this->FormulaArgumentList[1].push_back(scorematrix[13 + i]);	// If not trump suit
		}
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->tf_long[0][0] = this->FormulaArgumentList[0][2];
		this->tf_long[0][1] = this->FormulaArgumentList[0][3];
		this->tf_long[0][2] = this->FormulaArgumentList[0][4];
		this->tf_long[1][0] = this->FormulaArgumentList[1][2];
		this->tf_long[1][1] = this->FormulaArgumentList[1][3];
		this->tf_long[1][2] = this->FormulaArgumentList[1][4];
		this->tf_short[0][0] = this->FormulaArgumentList[0][5];
		this->tf_short[0][1] = this->FormulaArgumentList[0][6];
		this->tf_short[0][2] = this->FormulaArgumentList[0][7];
		this->tf_short[1][0] = this->FormulaArgumentList[1][5];
		this->tf_short[1][1] = this->FormulaArgumentList[1][6];
		this->tf_short[1][2] = this->FormulaArgumentList[1][7];
	}
	else if(s == 24 && this->formulaid == 10){
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		for(int i = 0;i < 8;i++){
			this->FormulaArgumentList[0].push_back(scorematrix[5 + i]); 	// If is trump suit
			this->FormulaArgumentList[1].push_back(scorematrix[13 + i]);	// If not trump suit
		}
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->tf_long[0][0] = this->FormulaArgumentList[0][2];
		this->tf_long[0][1] = this->FormulaArgumentList[0][3];
		this->tf_long[0][2] = this->FormulaArgumentList[0][4];
		this->tf_long[1][0] = this->FormulaArgumentList[1][2];
		this->tf_long[1][1] = this->FormulaArgumentList[1][3];
		this->tf_long[1][2] = this->FormulaArgumentList[1][4];
		this->tf_short[0][0] = this->FormulaArgumentList[0][5];
		this->tf_short[0][1] = this->FormulaArgumentList[0][6];
		this->tf_short[0][2] = this->FormulaArgumentList[0][7];
		this->tf_short[1][0] = this->FormulaArgumentList[1][5];
		this->tf_short[1][1] = this->FormulaArgumentList[1][6];
		this->tf_short[1][2] = this->FormulaArgumentList[1][7];
		this->f_distributedistance[0] = scorematrix[21];
		this->f_distributedistance[1] = scorematrix[22];
		this->f_distributedistance[2] = scorematrix[23];
	}
	else if(s == 23 && this->formulaid == 11){
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->FormulaArgumentList.clear();
		this->FormulaArgumentList.resize(2);
		for(int i = 0;i < 8;i++){
			this->FormulaArgumentList[0].push_back(scorematrix[5 + i]); 	// If is trump suit
			this->FormulaArgumentList[1].push_back(scorematrix[13 + i]);	// If not trump suit
		}
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->tf_long[0][0] = this->FormulaArgumentList[0][2];
		this->tf_long[0][1] = this->FormulaArgumentList[0][3];
		this->tf_long[0][2] = this->FormulaArgumentList[0][4];
		this->tf_long[1][0] = this->FormulaArgumentList[1][2];
		this->tf_long[1][1] = this->FormulaArgumentList[1][3];
		this->tf_long[1][2] = this->FormulaArgumentList[1][4];
		this->tf_short[0][0] = this->FormulaArgumentList[0][5];
		this->tf_short[0][1] = this->FormulaArgumentList[0][6];
		this->tf_short[0][2] = this->FormulaArgumentList[0][7];
		this->tf_short[1][0] = this->FormulaArgumentList[1][5];
		this->tf_short[1][1] = this->FormulaArgumentList[1][6];
		this->tf_short[1][2] = this->FormulaArgumentList[1][7];
		this->f_distributedistance[0] = scorematrix[21];
		this->f_distributedistance[1] = scorematrix[22];
	}
	else if(s == 10 && this->formulaid == 12){
		/*	The HCP only have the discrete card strength
		 *	We get bonus strength from trump suit in long formula
		 *	HCP[1][1]	=	4, it is real number
		 *	HCP[1][2-8]	=	0
		 *	HCP[1][9-T]	=	1
		 *	HCP[1][J]	=	2
		 *	HCP[1][Q]	=	3
		 *	HCP[1][K]	=	4
		 *	f_long		=	fixed long
		 *				=	5, 6
		 *	tf_short	=	training fixed short
		 *				=	7, 8, 9
		 **/
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->f_long[0][0] = scorematrix[5];
		this->f_long[0][1] = scorematrix[6];
		this->tf_short[0][0] = scorematrix[7];
		this->tf_short[0][1] = scorematrix[8];
		this->tf_short[0][2] = scorematrix[9];
	}
	else if(s == 32 && this->formulaid == 13){
		/*	Set the fixed argument of formula 12 first
		 *	called 	:= fine-tuning HCP
		 *			00	:= for RHO of East, and called suit is not trump
		 *			01	:= for LHO of East, and called suit is not trump
		 *			10	:= for RHO of East, and called suit is trump
		 *			11	:= for LHO of East, and called suit is trump
		 *	called_len := fine-tuning length strength
		 *			0	:= for RHO of East
		 *			1	:= for LHO of East
		 *	scorematrix:
		 *		called[0][0] = 0-5
		 *		called[0][1] = 6-11
		 *		called[1][0] = 12-17
		 *		called[1][1] = 18-23
		 *		called_len[0] = 24-27
		 *		called_len[1] = 28-31
		 * */
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = 0.5;
		this->HCPlist[1][10] = 0.5;
		this->HCPlist[1][11] = 0.75;
		this->HCPlist[1][12] = 1.5;
		this->HCPlist[1][13] = 2.5;
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = 0.25;
		this->f_long[0][0] = 1.4;
		this->f_long[0][1] = 0;
		this->tf_short[0][0] = 3;
		this->tf_short[0][1] = 1.5;
		this->tf_short[0][2] = 0.5;
		for(int i = 0;i < 2;i++){
			for(int j = 0;j < 2;j++){
				for(int k = 0;k < 6;k++){
					this->called[i][j][k] = scorematrix[i * 12 + j * 6 + k];
				}
			}
		}
		for(int i = 0;i < 2;i++){
			for(int j = 0;j < 4;j++){
				this->called_len[i][j] = scorematrix[i * 4 + j + 24];
			}
		}
	}
	else if(s == 12 && this->formulaid == 15){
		/*	The HCP only have the discrete card strength
		 *	We get bonus strength from trump suit in long formula
		 *	HCP[1][1]	=	4, it is real number
		 *	HCP[1][2-8]	=	0
		 *	HCP[1][9-T]	=	1
		 *	HCP[1][J]	=	2
		 *	HCP[1][Q]	=	3
		 *	HCP[1][K]	=	4
		 *	f_long		=	fixed long
		 *				=	5, 6(trump), 7, 8(non-trump)
		 *	tf_short	=	training fixed short
		 *				=	9, 10, 11
		 **/
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->f_long[0][0] = scorematrix[5];
		this->f_long[0][1] = scorematrix[6];
		this->f_long[1][0] = scorematrix[7];
		this->f_long[1][1] = scorematrix[8];
		this->tf_short[0][0] = scorematrix[9];
		this->tf_short[0][1] = scorematrix[10];
		this->tf_short[0][2] = scorematrix[11];
	}
	else if(s == 12 && this->formulaid == 16){
		/*	The HCP only have the discrete card strength
		 *	We get bonus strength from trump suit in long formula
		 *	HCP[1][1]	=	4, it is real number
		 *	HCP[1][2-8]	=	0
		 *	HCP[1][9-T]	=	1
		 *	HCP[1][J]	=	2
		 *	HCP[1][Q]	=	3
		 *	HCP[1][K]	=	4
		 *	f_long		=	fixed long
		 *				=	5, 6(trump), 7, 8(non-trump)
		 *	tf_short	=	training fixed short
		 *				=	9, 10, 11
		 **/
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->f_long[0][0] = scorematrix[5];
		this->f_long[0][1] = scorematrix[6];
		this->f_long[1][0] = scorematrix[7];
		this->f_long[1][1] = scorematrix[8];
		this->tf_short[0][0] = scorematrix[9];
		this->tf_short[0][1] = scorematrix[10];
		this->tf_short[0][2] = scorematrix[11];
	}
	else if(s == 12 && this->formulaid == 17){
		/*	The HCP only have the discrete card strength
		 *	We get bonus strength from trump suit in long formula
		 *	HCP[1][1]	=	4, it is real number
		 *	HCP[1][2-8]	=	0
		 *	HCP[1][9-T]	=	1
		 *	HCP[1][J]	=	2
		 *	HCP[1][Q]	=	3
		 *	HCP[1][K]	=	4
		 *	f_long		=	fixed long
		 *				=	a, b
		 *	tf_short	=	training fixed short
		 *		Loser	=	c, d, e
		 *		Winner	=	f, g
		 **/
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->f_long[0][0] = scorematrix[5];
		this->f_long[0][1] = scorematrix[6];
		this->tf_short[0][0] = scorematrix[7];
		this->tf_short[0][1] = scorematrix[8];
		this->tf_short[0][2] = scorematrix[9];
		this->tf_short[1][1] = scorematrix[10];
		this->tf_short[1][2] = scorematrix[11];
	}
	else if(s == 16 && this->formulaid == 18){
		/*	The HCP only have the discrete card strength
		 *	We get bonus strength from trump suit in long formula
		 *	HCP[1][1]	=	4, it is real number
		 *	HCP[1][2-8]	=	0
		 *	HCP[1][9-T]	=	1
		 *	HCP[1][J]	=	2
		 *	HCP[1][Q]	=	3
		 *	HCP[1][K]	=	4
		 *	f_long		=	fixed long
		 *				=	a, b
		 *	tf_short	=	training fixed short
		 *		Loser	=	c, d, e
		 *		With A	=	f, g		f1list[0][0], f1list[1][0]
		 *		With K	=	h, i		f1list[0][1], f1list[1][1]
		 *		With Q	=	j, k		f1list[0][2], f1list[1][2]
		 **/
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->f_long[0][0] = scorematrix[5];
		this->f_long[0][1] = scorematrix[6];
		this->tf_short[0][0] = scorematrix[7];
		this->tf_short[0][1] = scorematrix[8];
		this->tf_short[0][2] = scorematrix[9];
		for(int i = 0;i < 3;i++){
			this->f1list[0][i] = scorematrix[9 + i * 2+ 1];
			this->f1list[1][i] = scorematrix[9 + i * 2+ 2];
		}
	}
	else if(s == 13 && this->formulaid == 19){
		/*	The HCP only have the discrete card strength
		 *	We get bonus strength from trump suit in long formula
		 *	We decrease the short score if we have honor
		 *	HCP[1][1]	=	4, it is real number
		 *	HCP[1][2-8]	=	0
		 *	HCP[1][9-T]	=	1
		 *	HCP[1][J]	=	2
		 *	HCP[1][Q]	=	3
		 *	HCP[1][K]	=	4
		 *	f_long		=	fixed long
		 *				=	a, b
		 *	tf_short	=	training fixed short
		 *		Loser	=	c, d, e
		 *		With A	=	f
		 *		With K	=	g
		 *		With Q	=	h
		 **/
		this->HCPlist[1][1] = 4;
		this->HCPlist[1][9] = scorematrix[1];
		this->HCPlist[1][10] = scorematrix[1];
		this->HCPlist[1][11] = scorematrix[2];
		this->HCPlist[1][12] = scorematrix[3];
		this->HCPlist[1][13] = scorematrix[4];
		for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
		this->f_long[0][0] = scorematrix[5];
		this->f_long[0][1] = scorematrix[6];
		for(int j = 0;j < 2;j++){
			for(int i = 0;i < 3;i++){
				this->tf_short[j][i] = scorematrix[7 + i + j * 3];
			}
		}
	}

	else{
		cerr << "--Wrong size of scorematrix--" << endl;
		return s;
	}
	return 0;
}

int Experiment::Set_FixFormulaArgumentList(vector<double> FixArgument){
	/*	Set the argument.
	 *	Check the argumnet number first if there are more than one formula
	 * */
	const int size = FixArgument.size();
	if(this->FixFormulaArgumentSize[this->Fixformulaid] != size)return size;
	this->FixFormulaArgumentList = FixArgument;
	if(this->Fixformulaid == 3){
		this->early_hand[1] = 4;
		this->late_hand[1] = 4;
		for(auto i = 2;i < 9;i++){
			this->early_hand[i] = FixArgument[0];
			this->late_hand[i] = FixArgument[5];
		}
		this->early_hand[9] = FixArgument[1];
		this->late_hand[9] = FixArgument[6];
		this->early_hand[10] = FixArgument[1];
		this->late_hand[10] = FixArgument[6];
		this->early_hand[11] = FixArgument[2];
		this->late_hand[11] = FixArgument[7];
		this->early_hand[12] = FixArgument[3];
		this->late_hand[12] = FixArgument[8];
		this->early_hand[13] = FixArgument[4];
		this->late_hand[13] = FixArgument[9];
	}
	return 0;
}

void Experiment::scorer(){
	/* Fill up the score list by new formula parameter
	 * formulaid = 
	 * 	1 : formula1
	 * 	2 : formula2
	 * 	else : traditional discrete method
	 * */
	this->score.clear();
	switch(this->formulaid){
	case 1:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula1(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 2:
		for(int i = 0;i < (int)this->teams.size();i++){
//			cout << "teams[" << i << "] score set correctly\n";
//			this->score.push_back(this->formula2(this->teams[i]));
			double result;
			result = this->formula2(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 3:
		for(int i = 0;i < (int)this->teams.size();i++){
//			this->score.push_back(this->formula3(this->teams[i]));
			double result;
			result = this->formula3(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 4:
		for(int i = 0;i < (int)this->teams.size();i++){
//			this->score.push_back(this->formula3(this->teams[i]));
			double result;
			result = this->formula4(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 5:
		for(int i = 0;i < (int)this->teams.size();i++){
//			this->score.push_back(this->formula3(this->teams[i]));
			double result;
			result = this->formula5(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 6:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula6(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 7:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula7(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 8:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula8(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 9:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula9(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 10:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula10(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 11:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula11(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 12:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula12(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 13:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula13(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 15:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula15(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 16:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula16(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;
	case 17:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula17(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;


	case 18:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula18(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;


	case 19:
		for(int i = 0;i < (int)this->teams.size();i++){
			double result;
			result = this->formula19(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
		break;

	default:
		cerr << "The formula number haven't complete. Check your argument again!\n";
		break;
	}
}

void Experiment::GameScorer(){
	/*	This is the scorer for games.
	 *	It will calculate the score of each player in each contract.
	 *	But we only have a good formula for suit contract.
	 *	So just use the same formula and argument for no trump too.
	 *
	 *	The order of players is North, East, South and West.
	 *	So do the matrix of ScoreForPlayers.
	 * */
	switch(this->formulaid){
	case 1:
		for(auto &game:this->games){
			for(int i = 0;i < 4;i++){
				for(int j = 0;j < 5;j++){
					game.ScoreForPlayers[i][j] = pformula1(game.Players[i], j);
				}
			}
		}
		break;
	case 2:
		for(auto &game:this->games){
			for(int i = 0;i < 4;i++){
				for(int j = 0;j < 5;j++){
					game.ScoreForPlayers[i][j] = pformula2(game.Players[i], j);
				}
			}
		}
		break;
	}
}
void Experiment::PartialGamePreScorer(){
	/*	This is the pre scorer for partial games(which already know the declarer, contract suit and DDS result).
	 *	So there is no No Trump contract.
	 *	And use the argument that had trained to calculate the individual score.
	 * */
	switch(this->formulaid){
		case 2:
			for(PartialGame &game:this->Partialgames){
				for(int i = 0;i < 4;i++){
					game.player[i].score = pformula2(game.player[i], game.suit);
//					cout << game.player[i].score << endl;
				}
			}
			break;
		case -1:
			for(PartialGame &game:this->Partialgames){
				for(int i = 0;i < 4;i++){
					game.player[i].score = pHCP(game.player[i], 5);
				}
			}
			break;
		case -2:
			for(PartialGame &game:this->Partialgames){
				for(int i = 0;i < 4;i++){
					game.player[i].score = suitHCP(game.player[i], game.suit);
				}
			}
			break;
		case -3:
			for(PartialGame &game:this->Partialgames){
				for(int i = 0;i < 4;i++){
					game.player[i].score = longformula(game.player[i], game.suit);
				}
			}
			break;
		case -4:
			for(PartialGame &game:this->Partialgames){
				for(int i = 0;i < 4;i++){
					game.player[i].score = shortformula(game.player[i], game.suit);
				}
			}
			break;
		case -5:
			for(PartialGame &game:this->Partialgames){
				for(int i = 0;i < 4;i++){
					game.player[i].score = pHCP(game.player[i], 5) + longformula(game.player[i], game.suit) + shortformula(game.player[i], game.suit);
				}
			}
			break;
		default:
			cerr << "Input formulaID = " << this->formulaid << endl;
			cerr << "Wrong formulaID! If you wanna use formula, you have to implement it!\n";
			break;
	}
}
void Experiment::PartialGameTrainScorer(){
	/*	This score is use to calculate the final score that after fixed.
	 *	And append to the list Experiment::score.
	 *	The list will calculate the final correlation coefficient.
	 * */
	this->score.clear();
	double pscore = 0;
	if(this->Fixformulaid == 2){
		for(auto &game:Partialgames){
			pscore = 0;
			if(game.maker)
				pscore = game.player[1].score + game.player[3].score;
			else 
				pscore = game.player[0].score + game.player[2].score;
			pscore += this->FixFormula2(game);
			this->score.push_back(pscore);
			game.score = pscore;
		}
	}
	else if(this->Fixformulaid == 3){
		for(auto &game:Partialgames){
			pscore = FixFormula3(game);
			this->score.push_back(pscore);
			game.score = pscore;
		}
	}
}

int Experiment::ExposeSuit(Player player){
	/*	If player's hand HCP is large or exist a length of suit is long
	 *	then the player may make a bid to let another players know what
	 *	suit is longest suit in his hand.
	 *	
	 *	This function is check if the HCP >= 13 or (HCP >= 11 and exist a length
	 *	of suit is >= 5).
	 *	If so, return the longest suit, other wise return 4(means no any information expose).
	 * */
	int ret = 4, longestLen = 0;
	vector<int> dist = player.hand.distributed;
	if(player.HCP >= 13){
		for(int i = 0;i < 4;i++){
			if(dist[i] > longestLen){
				longestLen = dist[i];
				ret = i;
			}
		}
	}
	else if(player.HCP >= 11){
		longestLen = 4;
		for(int i = 0;i < 4;i++){
			if(dist[i] > longestLen){
				longestLen = dist[i];
				ret = i;
			}
		}
	}
	return ret;
}
double Experiment::formula1(Team t){
	double ret = 0;
	ret += pformula1(t.player[0], t.suit);
	ret += pformula1(t.player[1], t.suit);
	return ret;
}

double Experiment::pformula1(Player p, int suit){
	/*	score = HCP + a * (card_value(1~13) - b) + c * (card_value(1~13) - d) * pow(e, f)
	 * */
	double ret = 0;
	vector<vector<int>> h = p.hand.getcard();
	for(int i = 0;i < 4;i++){
		int id = 1;
		if(i == suit)id = 0;
		for(auto x:h[i])ret += this->HCPlist[0][x] + (x + this->f1list[id][0]) * this->f1list[id][1] + (x + this->f1list[id][2]) * pow(this->f1list[id][3], fabs(this->f1list[id][4])) * this->f1list[id][5];
	}
	return ret;
}

double Experiment::formula2(Team t){
	double ret = 0;
	ret += pformula2(t.player[0], t.suit);
	ret += pformula2(t.player[1], t.suit);
	return ret;
}

double Experiment::pformula2(Player p, int suit){
	/*	score = HCP + a * pow(suitHCP, b) + c * pow(Long, d) + e * pow(Short, f)
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->suitHCP(p, suit);
	ret += this->longformula(p, suit);
	ret += this->shortformula(p, suit);
	return ret;
}

double Experiment::formula3(Team t){
	double ret = 0;
	ret += pformula3(t.player[0], t.suit);
	ret += pformula3(t.player[1], t.suit);
	return ret;
}

double Experiment::pformula3(Player p, int suit){
	/* score = HCP + a * pow(suitHCP, b)
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->suitHCP(p, suit);
	return ret;
}

double Experiment::formula4(Team t){
	double ret = 0;
	ret += pformula4(t.player[0], t.suit);
	ret += pformula4(t.player[1], t.suit);
	return ret;
}

double Experiment::pformula4(Player p, int suit){
	/* score = HCP + distribute formula
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->distributeformula(p, suit);
	return ret;
}

double Experiment::formula5(Team t){
	double ret = 0;
	ret += pformula5(t.player[0], t.suit);
	ret += pformula5(t.player[1], t.suit);
	return ret;
}

double Experiment::pformula5(Player p, int suit){
	/* score = HCP + suitHCP + distribute formula
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->suitHCP(p, suit);
	ret += this->distributeformula(p, suit);
	return ret;
}

double Experiment::formula6(Team t){
	double ret = 0;
	ret += pformula6(t.player[0], t.suit);
	ret += pformula6(t.player[1], t.suit);
	return ret;
}

double Experiment::pformula6(Player p, int suit){
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->FASTsuitHCP(p, suit);
	ret += this->longformula(p, suit);
	ret += this->shortformula(p, suit);
	return ret;
}

double Experiment::formula7(Team &t){
	double ret = 0;
	ret += pformula7(t.player[0], t.suit);
	ret += pformula7(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula7(Player &p, int suit){
	/*	After calculate the HCP, we have the HCP each suit
	 *	So we can use the result of that to calculate the suitHCP
	 *	score = HCP + suitHCP + editinglongformula(have fixed score when player have four card)
	 *	+ short
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->FASTsuitHCP(p, suit);
	ret += this->Editinglongformula(p, suit);
	ret += this->shortformula(p, suit);
	p.score = ret;
	return ret;
}

double Experiment::formula8(Team &t){
	double ret = 0;
	ret += pformula8(t.player[0], t.suit);
	ret += pformula8(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula8(Player &p, int suit){
	/*	Training the length of long formula and short formula
	 *	score = HCP + suitHCP + TrainLong + TrainShort
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->FASTsuitHCP(p, suit);
	ret += this->TrainLong(p, suit);
	ret += this->TrainShort(p, suit);
	p.score = ret;
	return ret;
}
double Experiment::formula9(Team &t){
	double ret = 0;
	ret += pformula9(t.player[0], t.suit);
	ret += pformula9(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula9(Player &p, int suit){
	/*	Training the discrete score matrix for short card
	 *	score = HCP + suitHCP + TrainLong + Discrete short
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->FASTsuitHCP(p, suit);
	ret += this->TrainLong(p, suit);
	ret += this->discreteshort(p, suit);
	p.score = ret;
	return ret;
}
double Experiment::formula10(Team &t){
	/*	Add the formula that scoring the trump distance between two player
	 * */
	double ret = 0;
	ret += pformula10(t.player[0], t.suit);
	ret += pformula10(t.player[1], t.suit);
	ret += this->distributedistance(t);
	return ret;
}
double Experiment::pformula10(Player &p, int suit){
	/*	Training the discrete score matrix for short card
	 *	score = HCP + suitHCP + TrainLong + Discrete short
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->FASTsuitHCP(p, suit);
	ret += this->TrainLong(p, suit);
	ret += this->discreteshort(p, suit);
	p.score = ret;
	return ret;
}
double Experiment::formula11(Team &t){
	/*	Change the way to calculate the score
	 * */
	double ret = 0;
	ret += pformula10(t.player[0], t.suit);
	ret += pformula10(t.player[1], t.suit);
	ret -= this->distributedistance_v2(t);
	return ret;
}
double Experiment::formula12(Team &t){
	double ret = 0;
	ret += pformula12(t.player[0], t.suit);
	ret += pformula12(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula12(Player &p, int suit){
	/*	ret = HCP + long + short
	 *	the feature long and short are not like the previous one, they don't have the exponential
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	for(int i = 0;i < 4;i++){
		if(i == suit){
			if(p.hand.distributed[i] > this->f_long[0][1]){
				ret += this->f_long[0][0] * (p.hand.distributed[i] - this->f_long[0][1]);
			}
		}
		else{
			if(p.hand.distributed[i] < 3){
				ret += this->tf_short[0][p.hand.distributed[i]];
			}
		}
	}
	return ret;
}
double Experiment::formula13(Team &t){
	/*	ret = formula12 + fine-tuning of the called card
	 * */
	double ret = 0;
	ret += pformula12(t.player[0], t.suit);
	ret += pformula12(t.player[1], t.suit);
	ret += pformula13(t.player[0], t.suit, 0, t.E_suit);
	ret += pformula13(t.player[1], t.suit, 1, t.E_suit);
	return ret;
}
double Experiment::pformula13(Player &p, int suit, int pos, int E_suit){
	/*	ret = fine-tuning
	 *	if you are north, and the east side player have called spade
	 *	means your spade K without spade A may get nothing.
	 *	So we have to fine-tuning the score matrix
	 *	In another words, if you are South side player, and east called spade
	 *	means you can dominate his K by your A.
	 *	The things mentioned above is the experiment of contract bridge expert
	 *	We may find this from the experimental.
	 * */
	double ret = 0;
	if(E_suit == 4)return ret;
	int same = suit == E_suit;
	int i = 0;
	vector<vector<int>> hand = p.hand.getcard();
	for(auto card:hand[E_suit]){
		if(card > 1 && card < 9)
			i = 0;
		else if(card == 1)
			i = 5;
		else if(card == 9 || card == 10)
			i = 1;
		else if(card == 11)
			i = 2;
		else if(card == 12)
			i = 3;
		else i = 4;
		ret += called[same][pos][i];
	}
	if(same){
		ret += called_len[pos][0] * p.hand.distributed[suit];
	}
	else{
		ret += (p.hand.distributed[E_suit] > 2 ? 0:called_len[pos][p.hand.distributed[E_suit] + 1]);
	}
	return ret;
}
double Experiment::formula14(Team &t){
	/*	ret = formula12 + fine-tuning of the called card
	 * */
	double ret = 0;
	ret += pformula12(t.player[0], t.suit);
	ret += pformula12(t.player[1], t.suit);
	ret += pformula14(t.player[0], t.suit, 0, t.E_suit);
	ret += pformula14(t.player[1], t.suit, 1, t.E_suit);
	return ret;
}
double Experiment::pformula14(Player &p, int suit, int pos, int E_suit){
	/*	ret = fine-tuning
	 *	if you are north, and the east side player have called spade
	 *	means your spade K without spade A may get nothing.
	 *	So we have to fine-tuning the score matrix
	 *	In another words, if you are South side player, and east called spade
	 *	means you can dominate his K by your A.
	 *	The things mentioned above is the experiment of contract bridge expert
	 *	We may find this from the experimental.
	 * */
	double ret = 0;
	int same = suit == E_suit;
	int i = 0;
	for(auto suit:p.hand.getcard()){
		for(auto card:suit){
			i = card == 1 ? 5:(card < 9 ? 0:(card < 11 ? 1:(card - 9)));
			ret += called[pos][same][i];
		}
	}
	if(same){
		ret += called_len[pos][0] * p.hand.distributed[suit];
	}
	else{
		ret += (p.hand.distributed[E_suit] > 2 ? 0:called_len[pos][p.hand.distributed[E_suit]]);
	}
	return ret;
}
double Experiment::formula15(Team &t){
	/*	This formula is like formula12, but the long non-trump have extra point
	 * */
	double ret = 0;
	ret += pformula15(t.player[0], t.suit);
	ret += pformula15(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula15(Player &p, int suit){
	/*	ret = HCP + long + short
	 *	the feature long and short are not like the previous one, they don't have the exponential
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	for(int i = 0;i < 4;i++){
		if(i == suit){
			if(p.hand.distributed[i] > this->f_long[0][1]){
				ret += this->f_long[0][0] * (p.hand.distributed[i] - this->f_long[0][1]);
			}
		}
		else{
			if(p.hand.distributed[i] < 3){
				ret += this->tf_short[0][p.hand.distributed[i]];
			}
			if(p.hand.distributed[i] > this->f_long[1][1]){
				ret += this->f_long[1][0] * (p.hand.distributed[i] - this->f_long[1][1]);
			}
		}
	}
	return ret;
}
double Experiment::formula16(Team &t){
	/*	This formula is like formula12, but the long non-trump that with honor have extra point
	 * */
	double ret = 0;
	ret += pformula16(t.player[0], t.suit);
	ret += pformula16(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula16(Player &p, int suit){
	/*	ret = HCP + long + short
	 *	the feature long and short are not like the previous one, they don't have the exponential
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	for(int i = 0;i < 4;i++){
		if(i == suit){
			if(p.hand.distributed[i] > this->f_long[0][1]){
				ret += this->f_long[0][0] * (p.hand.distributed[i] - this->f_long[0][1]);
			}
		}
		else{
			if(p.hand.distributed[i] < 3){
				ret += this->tf_short[0][p.hand.distributed[i]];
			}
			if(p.hand.distributed[i] > this->f_long[1][1] && this->have_honor(p, i)){
				ret += this->f_long[1][0] * (p.hand.distributed[i] - this->f_long[1][1]);
			}
		}
	}
	return ret;
}
double Experiment::formula17(Team &t){
	double ret = 0;
	ret += pformula17(t.player[0], t.suit);
	ret += pformula17(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula17(Player &p, int suit){
	/*	ret = HCP + long + short
	 *	The short with honor and without honor have different scorematrix
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	for(int i = 0;i < 4;i++){
		if(i == suit){
			if(p.hand.distributed[i] > this->f_long[0][1]){
				ret += this->f_long[0][0] * (p.hand.distributed[i] - this->f_long[0][1]);
			}
		}
		else{
			if(p.hand.distributed[i] == 0)
				ret += this->tf_short[0][0];
			else if(p.hand.distributed[i] < 3){
				unsigned int card = cardtobit(p.hand.getcard()[i]);
				if(SetBits(card & Winner))
					ret += this->tf_short[1][p.hand.distributed[i]];
				else
					ret += this->tf_short[0][p.hand.distributed[i]];
			}
		}
	}
	return ret;
}
double Experiment::formula18(Team &t){
	double ret = 0;
	ret += pformula18(t.player[0], t.suit);
	ret += pformula18(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula18(Player &p, int suit){
	/*	ret = HCP + long + short
	 *	The short with honor and without honor have different scorematrix
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	for(int i = 0;i < 4;i++){
		if(i == suit){
			if(p.hand.distributed[i] > this->f_long[0][1]){
				ret += this->f_long[0][0] * (p.hand.distributed[i] - this->f_long[0][1]);
			}
		}
		else{
			if(p.hand.distributed[i] == 0)
				ret += this->tf_short[0][0];
			else if(p.hand.distributed[i] < 3){
				unsigned int card = cardtobit(p.hand.getcard()[i]);
				if(card & 0x2)
					ret += this->f1list[p.hand.distributed[i] - 1][0];
				else if(card & 0x2000)
					ret += this->f1list[p.hand.distributed[i] - 1][1];
				else if(card & 0x1000)
					ret += this->f1list[p.hand.distributed[i] - 1][2];
				else ret += this->tf_short[0][p.hand.distributed[i]];
			}
		}
	}
	return ret;
}
double Experiment::formula19(Team &t){
	double ret = 0;
	ret += pformula19(t.player[0], t.suit);
	ret += pformula19(t.player[1], t.suit);
	return ret;
}
double Experiment::pformula19(Player &p, int suit){
	/*	ret = HCP + long + short
	 *	the feature long and short are not like the previous one, they don't have the exponential
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	for(int i = 0;i < 4;i++){
		if(i == suit){
			if(p.hand.distributed[i] > this->f_long[0][1]){
				ret += this->f_long[0][0] * (p.hand.distributed[i] - this->f_long[0][1]);
			}
		}
		else{
			if(p.hand.distributed[i] < 3){
				ret += this->tf_short[0][p.hand.distributed[i]];
				unsigned int card = cardtobit(p.hand.getcard()[i]);
				if(card & 0x2)
					ret -= this->tf_short[1][0];
				if(card & 0x2000)
					ret -= this->tf_short[1][1];
				if(card & 0x1000)
					ret -= this->tf_short[1][2];
			}
		}
	}
	return ret;

}
int Experiment::loser(Team &t){
	int ret = 24;
	for(int i = 0;i < 4;i++){
		ret -= ploser(t.player[0], i);
		ret -= ploser(t.player[1], i);
	}
	return ret;
}
int Experiment::ploser(Player &p, int suit){
	unsigned int card = cardtobit(p.hand.getcard()[suit]);
	int ret = SetBits(card);
	ret = ret > 3 ? 3:ret;
	ret -= SetBits(card & Winner);
	return ret;
}
unsigned int Experiment::cardtobit(vector<int> card){
	unsigned int ret = 0;
	for(auto i:card)
		ret = ret | (1 << i);
	return ret;
}
double Experiment::Editinglongformula(Player p, int suit){
	/*	If the length is less than 4, ret += 0
	 *	else if the length is equal to 4, ret += a fixed value
	 *	else ret += a * pow(length - 4, b)
	 *	3.6
	 * */
	double ret = 0;
	vector<int> distributed = p.hand.distributed;
	string s[4] = {"spade", "heart", "diamond", "club"};
	for(int i = 0;i < 4;i++){
		int id = (i != suit);
		double t = 0;
		if(distributed[i] < 4)continue;
		else if(distributed[i] == 4)ret += this->long4card[id];
		else{
			t = this->f_long[id][0] * pow(distributed[i] - 4, this->f_long[id][1]);
			ret += t;
		}
	}
	return ret;
}
double Experiment::FASTsuitHCP(Player p, int suit){
	double ret = 0;
	int id;
	for(int i = 0;i < 4;i++){
		id = i != suit;
		ret += this->f_suitHCP[id][0] * pow(p.HCP_suit[i], this->f_suitHCP[id][1]);
	}
	return ret;
}

double Experiment::distributeformula(Player p, int suit){
	/* ret = sum of a * pow(abs(length - base), b)
	 * a, base and b are the trained argument
	 * 3.3
	 * */
	double ret = 0;
	vector<int> h = p.hand.distributed;
	for(int i = 0;i < 4;i++){
		int id = i == suit ? 0 : 1;
		double t = 0;
		t = this->f_dist[id][0] * pow(fabs(h[i] - this->f_dist[id][1]), this->f_dist[id][2]);
		ret += t;
	}
	return ret;
}

double Experiment::suitHCP(Player p, int suit){
	/* Return the sum of the score that each HCP in a suit can get
	 * score = a * pow(HCP, b)
	 * a and b are the argument that be trained
	 * */
	double ret = 0;
	vector<vector<int>> h = p.hand.getcard();
	string s[4] = {"spade", "heart", "diamond", "club"};
	for(int i = 0;i < 4;i++){
		int id = (i != suit);
		double t = 0;
		double currentsuitHCP = 0;
		for(auto x:h[i])currentsuitHCP += this->HCPlist[1][x];
		t = this->f_suitHCP[id][0] * pow(currentsuitHCP, this->f_suitHCP[id][1]);
		ret += t;
	}
	return ret;
}

double Experiment::longformula(Player p, int suit){
	/* Return the sum of the score that each length in a suit can get
	 * score = a * pow(suit length - 4, b)
	 * 4 also can be an argument but we will fix it now
	 * a and b are the argument that be trained
	 * 3.4
	 * */
	double ret = 0;
	vector<int> distributed = p.hand.distributed;
	string s[4] = {"spade", "heart", "diamond", "club"};
	for(int i = 0;i < 4;i++){
		double t = 0;
		if(distributed[i] < 5)continue;
		int id = (i != suit);
		t = this->f_long[id][0] * pow(distributed[i] - 4, this->f_long[id][1]);
		ret += t;
	}
	return ret;
}

double Experiment::shortformula(Player p, int suit){
	/* Return the sum of the score that each length in a suit can get
	 * score = a * pow(3 - suit length, b)
	 * 3 also can be an argument but we will fix it now
	 * a and b are the argument that be trained
	 * 3.7
	 * */
	double ret = 0;
	vector<int> distributed = p.hand.distributed;
	string s[4] = {"spade", "heart", "diamond", "club"};
	for(int i = 0;i < 4;i++){
		double t = 0;
		if(distributed[i] > 2)continue;
		int id = (i != suit);
		t = this->f_short[id][0] * pow(3 - distributed[i], this->f_short[id][1]);
		ret += t;
	}
	return ret;
}

double Experiment::discreteshort(Player p, int suit){
	/*	Return the sum of the score that each length in a suit can get
	 *	the score is discrete value
	 *	haven't put into thesis
	 * */
	double ret = 0;
	int id;
	for(int i = 0;i < 4;i++){
		id = (i != suit);
		if(p.hand.distributed[i] > 2)continue;
		else ret += tf_short[id][p.hand.distributed[i]];
	}
	return ret;
}


double Experiment::TrainLong(Player p, int suit){
	/* Return the sum of the score that each length in a suit can get
	 * score = a * pow(suit length - b, c)
	 * 3.5
	 * */
	double ret = 0;
	vector<int> distributed = p.hand.distributed;
	string s[4] = {"spade", "heart", "diamond", "club"};
	for(int i = 0;i < 4;i++){
		double t = 0;
		int id = (i != suit);
		if(distributed[i] < tf_long[id][2])continue;
		t = this->tf_long[id][0] * pow(double(distributed[i])- tf_long[id][2], this->tf_long[id][1]);
		ret += t;
	}
	return ret;
}

double Experiment::TrainShort(Player p, int suit){
	/* Return the sum of the score that each length in a suit can get
	 * score = a * pow(b - suit length, c)
	 * 3.8
	 * */
	double ret = 0;
	vector<int> distributed = p.hand.distributed;
	string s[4] = {"spade", "heart", "diamond", "club"};
	for(int i = 0;i < 4;i++){
		double t = 0;
		int id = (i != suit);
		if(distributed[i] > tf_short[id][2])continue;
		t = this->tf_short[id][0] * pow(tf_short[id][2] - distributed[i], this->tf_short[id][1]);
		ret += t;
	}
	return ret;
}


double Experiment::TrumpLong(Team t){
	/*	3.10
	 * */
	double ret = 0;
	double p0l = t.player[0].hand.distributed[t.suit], p1l = t.player[1].hand.distributed[t.suit];
	if(p0l > f_long[0][1])
		ret += f_long[0][0] * (p0l - f_long[0][1]);
	if(p1l > f_long[0][1])
		ret += f_long[0][0] * (p1l - f_long[0][1]);
	return ret;
}

double Experiment::Nontrumpshort(Team t){
	/*	3.11
	 * */
	int s = t.suit;
	double ret = 0;
	for(int i = 0;i < 4;i++){
		if(s == i)continue;
		if(t.player[0].hand.distributed[i] < 3)
			ret += tf_short[0][t.player[0].hand.distributed[i]];
		if(t.player[1].hand.distributed[i] < 3)
			ret += tf_short[0][t.player[1].hand.distributed[i]];
	}
	return ret;
}

double Experiment::HCP(Team t){
	/*	3.2
	 * */
	double ret = 0;
	ret += pHCP(t.player[0], t.suit);
	ret += pHCP(t.player[1], t.suit);
	return ret;
}

double Experiment::HCP_notrump(Team t){
	/*	Haven't put it into thesis
	 * */
	double ret = 0;
	ret += pHCP(t.player[0], 4);
	ret += pHCP(t.player[1], 4);
	return ret;
}

double Experiment::pHCP(Player &p, int suit){
	double ret = 0, partial_score;
	vector<vector<int>> h = p.hand.getcard();
	for(int i = 0;i < 4;i++){
		int id = (i != suit);
		partial_score = 0;
		for(auto x:h[i])partial_score += this->HCPlist[id][x];
		p.HCP_suit[i] = partial_score;
		ret += partial_score;
	}
	return ret;
}

double Experiment::LongShort(Team t){
	/*	Haven't put into thesis
	 * */
	double ret = 0;
	ret += pLongShort(t.player[0], t.suit);
	ret += pLongShort(t.player[1], t.suit);
	return ret;
}

double Experiment::pLongShort(Player p, int suit){
	double ret = 0;
	for(int i = 0;i < 4;i++){
		int id = 1;
		if(suit == i)id = 0;
		ret += this->lenlist[id][p.hand.distributed[i]];
	}
	return ret;
}
double Experiment::FixFormula1(PartialGame game){
	//	This formula is my first idea that can fix the score by opponent's hand.
	//	fixscore = a * pow((N - S) * (E - W), b)
	//	If the maker is WE, then you have to return -fixscore.
	//	Idea is good but can't get better.
	
	double dis[2];
	double ret = 1;
	for(int i = 0;i < 2;i++){
		dis[i] = game.player[i].score - game.player[i + 2].score;
	}
	//	This is calculate in NS site
	if((dis[0] > 0 && dis[1] < 0) || (dis[0] < 0 && dis[1] > 0))
		ret = -1;
	else ret = 1;
	ret = (pow(fabs(dis[0]) * fabs(dis[1]), this->FixFormulaArgumentList[1]) * (this->FixFormulaArgumentList[0])) * ret;
	//	So it should change to WE site if it need
	int maker = game.maker;
	if(maker)ret *= -1;
	return ret;
}
double Experiment::FixFormula2(PartialGame game){
	/*	The fix formula2 is fix the score that get from suitHCP and short formula
	 *	set OsuitHCP = original suitHCP with specific suit, Oshort = original short score
	 *				   with specific suit too.
	 *	Then the return value is 
	 *		-a*pow(OsuitHCP, b) + c*pow(Oshort, d)
	 *	Because the suitHCP have to decrease when the right player have long(or strong)
	 *	suit at specific suit.
	 *	And in short formula situation, If we don't have that suit means the opponent can't
	 *	get any tricks from this suit(we can win the tricks by other suit).
	 * */
	double ret = 0;
	int maker = game.maker;
	//	suit1 is the information of North or the information of East
	//	suit2 is the information of South or the information of West
	int suit1, suit2;
	if(!maker){
		suit1 = ExposeSuit(game.player[3]);
		suit2 = ExposeSuit(game.player[1]);
	}
	else{
		suit1 = ExposeSuit(game.player[0]);
		suit2 = ExposeSuit(game.player[2]);
	}
	double NE_HCP, SW_HCP, NE_short, SW_short;
	NE_HCP = singlesuitHCP(game.player[game.maker], suit1);
	SW_HCP = singlesuitHCP(game.player[game.maker + 2], suit2);
	NE_short = singleshortformula(game.player[game.maker], suit1);
	SW_short = singleshortformula(game.player[game.maker + 2], suit2);
	double NE_FIX = FixFormulaArgumentList[2] * pow(NE_short, FixFormulaArgumentList[3])- FixFormulaArgumentList[0] * pow(NE_HCP, FixFormulaArgumentList[1]);
	double SW_FIX = FixFormulaArgumentList[2] * pow(SW_short, FixFormulaArgumentList[3])- FixFormulaArgumentList[0] * pow(SW_HCP, FixFormulaArgumentList[1]);
	ret = NE_FIX + SW_FIX;
	return ret;
}
double Experiment::singlesuitHCP(Player p, int suit){
	/* Return the score that each HCP in a specific suit can get
	 * score = a * pow(HCP, b)
	 * a and b are the argument that be trained
	 * */
	double ret = 0;
	vector<vector<int>> h = p.hand.getcard();
	for(int i = 0;i < 4;i++){
		if(i != suit)continue;
		double currentsuitHCP = 0;
		for(auto x:h[i])currentsuitHCP += this->HCPlist[1][x];
		ret = this->f_suitHCP[1][0] * pow(currentsuitHCP, this->f_suitHCP[1][1]);
	}
	return ret;
}


double Experiment::singleshortformula(Player p, int suit){
	/* Return the score of a length in a specific suit can get
	 * score = a * pow(3 - suit length, b)
	 * 3 also can be an argument but we will fix it now
	 * a and b are the argument that be trained
	 * */
	double ret = 0;
	vector<int> distributed = p.hand.distributed;
	for(int i = 0;i < 4;i++){
		if(i != suit)continue;
		double t = 0;
		if(distributed[i] > 2)continue;
		t = this->f_short[1][0] * pow(3 - distributed[i], this->f_short[1][1]);
		ret += t;
	}
	return ret;
}

double Experiment::FixFormula3(PartialGame game){
	/*	The fix formula3 is a formula that just change the HCP to a new one
	 *	If we change the HCP, suitHCP will change too.
	 *	So we have to calculate the new score between makers.
	 * */
	double ret = 0;
	int maker = game.maker;
	vector<int> expSuit(4, 4);
	for(int i = 0;i < 4;i++){
		expSuit[i] = ExposeSuit(game.player[i]);
	}
	if(maker){
		ret += p_FixFormula3(game.player[1], game.suit, expSuit[0], expSuit[2]);
		ret += p_FixFormula3(game.player[3], game.suit, expSuit[2], expSuit[0]);
	}
	else{
		ret += p_FixFormula3(game.player[0], game.suit, expSuit[3], expSuit[1]);
		ret += p_FixFormula3(game.player[2], game.suit, expSuit[1], expSuit[3]);
	}
	return ret;
}

double Experiment::p_FixFormula3(Player player, int suit, int early_suit, int late_suit){
	double ret = 0;
	double hcp = 0;
	auto hand = player.hand.getcard();
	// calculate the HCP
	for(int i = 0;i < 4;i++){
		if(i == late_suit){
			for(auto card:hand[i]){
				hcp += this->late_hand[card];
			}
		}
		else if(i == early_suit){
			for(auto card:hand[i]){
				hcp += this->early_hand[card];
			}
		}
		else{
			for(auto card:hand[i]){
				hcp += this->HCPlist[1][card];
			}
		}
	}
	ret += hcp;
	ret += FixsuitHCP(player, suit, early_suit, late_suit);
	ret += longformula(player, suit);
	ret += shortformula(player, suit);
	return ret;
}

double Experiment::Fix_early_HCP(Player player, int suit){
	double ret = 0;
	auto card = player.hand.getcard();
	for(auto x:card[suit])
		ret += this->early_hand[x];
	return ret;
}
double Experiment::Fix_late_HCP(Player player, int suit){
	double ret = 0;
	auto card = player.hand.getcard();
	for(auto x:card[suit])
		ret += this->late_hand[x];
	return ret;
}
double Experiment::FixsuitHCP(Player player, int suit, int early_suit, int late_suit){
	int ret = 0, temp = 0, id;
	auto hand = player.hand.getcard();
	for(int i = 0;i < 4;i++){
		temp = 0;
		id = i != suit;
		if(i == late_suit){
			temp = Fix_late_HCP(player, late_suit);
		}
		else if(i == early_suit){
			temp = Fix_early_HCP(player, early_suit);
		}
		else{
			for(auto card:hand[i])temp += HCPlist[1][card];
		}
		ret += this->f_suitHCP[id][0] * pow(temp, this->f_suitHCP[id][1]);
	}
	return ret;
}
double Experiment::distributedistance(Team &t){
	int dis = abs(t.player[0].hand.distributed[t.suit] - t.player[1].hand.distributed[t.suit]);
	int sign = 1;
	if(dis > f_distributedistance[1])sign = -1;
	return sign * f_distributedistance[0] * pow(fabs(f_distributedistance[1] - dis), f_distributedistance[2]);
}

double Experiment::distributedistance_v2(Team &t){
	int dis = abs(t.player[0].hand.distributed[t.suit] - t.player[1].hand.distributed[t.suit]);
	return f_distributedistance[0] * pow(dis, f_distributedistance[1]);
}
double Experiment::HonorTrick(Player p, int suit){
	/*	Maybe use the Ely Culbertson's version
	 * */
	double ret = 0;
	return ret;
}
double Experiment::PlayingTrick(Player p, int suit){
	double ret = 0;
	return ret;
}
double Experiment::LosingTrickCount(Player p, int suit){
	double ret = 0;
	return ret;
}
double Experiment::AssestSystem(Player p, int suit){
	double ret = 0;
	for(auto suit:p.hand.getcard()){
		ret += this->AssestScore[suit.size()];
	}
	return ret;
}
double Experiment::StaymanPointCount(Player p, int suit){
	double ret = 0;
	return ret;
}
double Experiment::RuleofThreeandFour(Player p, int suit){
	double ret = 0;
	return ret;
}
double Experiment::MoinsValue(Player p, int suit){
	double ret = 0;
	return ret;
}
double Experiment::PlusValue(Player p, int suit){
	double ret = 0;
	int TenNine, TwoThreehonors;
	for(auto suit:p.hand.getcard()){
		TenNine = 0;
		TwoThreehonors = 0;
		for(auto card:suit){
			switch(card){
				case 1:
					ret += 0.25;
					TwoThreehonors++;
					break;
				case 9:
				case 10:
					TenNine++;
					break;
				case 12:
				case 13:
					TwoThreehonors++;
					break;
			}
			if(TenNine == 2)ret += 0.5;
			if(TwoThreehonors >= 2)ret += 0.5;
		}
	}
	return ret;
}
void Team::ShowHand(){
	cout << "N: ";
	for(int i = 0;i < 2;i++){
		vector<vector<int>> hand = this->player[i].hand.getcard();
		for(int j = 0;j < 4;j++){
			for(auto c:hand[j]){
				switch(c){
					case 1:
						cout << "A";
						break;
					case 10:
						cout << "T";
						break;
					case 11:
						cout << "J";
						break;
					case 12:
						cout << "Q";
						break;
					case 13:
						cout << "K";
						break;
					default:
						cout << c;
						break;
				}
			}
			if(j < 3)cout << ".";
			else if(i == 1)cout << endl;
			else cout << " ";
		}
	}
}
bool Experiment::have_honor(Player P, int suit){
	bool ret = false;
	auto hand = P.hand.getcard();
	for(auto card:hand[suit]){
		if(card == 1 || card == 12 || card == 13)
			ret = true;
	}
	return ret;
}
int SetBits(uint32_t i){
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	i = (i + (i >> 4)) & 0x0F0F0F0F;
	return (i * 0x01010101) >> 24;
}

void Experiment::nScorer(){
	int id = this->formulaid;
	this->score.clear();
	for(int i = 0;i < (int)this->teams.size();i++){
		double _score = 0;
		switch(id % 10){
			case 0:
				break;
			case 1:
				_score += HCP(teams[i]);
				break;
			case 2:
				_score += HCP_notrump(teams[i]);
				break;
			default:
				break;
		}
		switch((id / 10) % 10){
			case 0:
				break;
			case 1:
				_score += suitHCP(teams[i].player[0], teams[i].suit);
				_score += suitHCP(teams[i].player[1], teams[i].suit);
				break;
			default:
				break;
		}
		switch((id / 100) % 10){
			case 0:
				break;
			case 1:
				_score += LongShort(teams[i]);
				break;
			case 2:
				_score += distributeformula(teams[i].player[0], teams[i].suit);
				_score += distributeformula(teams[i].player[1], teams[i].suit);
				break;
			default:
				break;
		}
		switch((id / 1000) % 10){
			case 0:
				break;
			case 1:
				_score += longformula(teams[i].player[0], teams[i].suit);
				_score += longformula(teams[i].player[1], teams[i].suit);
				break;
			case 2:
				_score += Editinglongformula(teams[i].player[0], teams[i].suit);
				_score += Editinglongformula(teams[i].player[1], teams[i].suit);
				break;
			case 3:
				_score += TrainLong(teams[i].player[0], teams[i].suit);
				_score += TrainLong(teams[i].player[1], teams[i].suit);
				break;
			case 4:
				_score += TrumpLong(teams[i]);
				break;
			default:
				break;
		}
		switch((id / 10000) % 10){
			case 0:
				break;
			case 1:
				_score += shortformula(teams[i].player[0], teams[i].suit);
				_score += shortformula(teams[i].player[1], teams[i].suit);
				break;
			case 2:
				_score += discreteshort(teams[i].player[0], teams[i].suit);
				_score += discreteshort(teams[i].player[1], teams[i].suit);
				break;
			case 3:
				_score += TrainShort(teams[i].player[0], teams[i].suit);
				_score += TrainShort(teams[i].player[1], teams[i].suit);
				break;
			case 4:
				_score += Nontrumpshort(teams[i]);
				break;
			default:
				break;
		}
		if(!(id / 100000) || teams[i].E_suit == 4){
			teams[i].score = _score;
			this->score.push_back(_score);
			continue;
		}
		switch((id / 100000) % 10){
			case 0:
				break;
			case 1:
				_score += E_called_HCP(teams[i].player[0], teams[i].suit, 0, teams[i].E_suit);
				_score += E_called_HCP(teams[i].player[1], teams[i].suit, 1, teams[i].E_suit);
				break;
			default:
				break;
		}
		switch((id / 1000000) % 10){
			case 0:
				break;
			case 1:
				_score += E_called_short(teams[i].player[0], teams[i].suit, 0, teams[i].E_suit);
				_score += E_called_short(teams[i].player[1], teams[i].suit, 1, teams[i].E_suit);
				break;
			default:
				break;
		}
		switch((id / 10000000) % 10){
			case 0:
				break;
			case 1:
				_score += E_called_dis(teams[i].player[0], teams[i].suit, 0, teams[i].E_suit);
				_score += E_called_dis(teams[i].player[1], teams[i].suit, 1, teams[i].E_suit);
				break;
			default:
				break;
		}
		switch((id / 100000000) % 10){
			case 0:
				break;
			case 1:
				_score += E_called_long(teams[i].player[0], teams[i].suit, 0, teams[i].E_suit);
				_score += E_called_long(teams[i].player[1], teams[i].suit, 1, teams[i].E_suit);
				break;
			default:
				break;
		}
		teams[i].score = _score;
		this->score.push_back(_score);
	}
}

int Experiment::nSet_scorematrix(vector<double> scorematrix){
	if(scorematrix.size() != this->needed_para){
		cerr << "You give me wrong size of score matrix!" << endl;
		cerr << "You give me " << scorematrix.size() << ", but I need " << this->needed_para << endl;
		return scorematrix.size();
	}
	int id = this->formulaid;
	int para_size = 0;
	switch(id % 10){
		case 0:
			break;
		case 1:
			para_size += 11;
			this->HCPlist[0][1] = 4;
			for(int i = 2;i < 9;i++)this->HCPlist[0][i] = scorematrix[0];
			this->HCPlist[0][9] = scorematrix[1];
			this->HCPlist[0][10] = scorematrix[1];
			this->HCPlist[0][11] = scorematrix[2];
			this->HCPlist[0][12] = scorematrix[3];
			this->HCPlist[0][13] = scorematrix[4];
			for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[5];
			this->HCPlist[1][9] = scorematrix[6];
			this->HCPlist[1][10] = scorematrix[6];
			this->HCPlist[1][11] = scorematrix[7];
			this->HCPlist[1][12] = scorematrix[8];
			this->HCPlist[1][13] = scorematrix[9];
			this->HCPlist[1][1] = scorematrix[10];
			break;
		case 2:
			para_size += 5;
			this->HCPlist[0][1] = 4;
			this->HCPlist[0][9] = scorematrix[1];
			this->HCPlist[0][10] = scorematrix[1];
			this->HCPlist[0][11] = scorematrix[2];
			this->HCPlist[0][12] = scorematrix[3];
			this->HCPlist[0][13] = scorematrix[4];
			for(int i = 2;i < 9;i++)this->HCPlist[0][i] = scorematrix[0];
			this->HCPlist[1][1] = 4;
			this->HCPlist[1][9] = scorematrix[1];
			this->HCPlist[1][10] = scorematrix[1];
			this->HCPlist[1][11] = scorematrix[2];
			this->HCPlist[1][12] = scorematrix[3];
			this->HCPlist[1][13] = scorematrix[4];
			for(int i = 2;i < 9;i++)this->HCPlist[1][i] = scorematrix[0];
			break;
		default:
			break;
	}
	switch((id / 10) % 10){
		case 0:
			break;
		case 1:
			this->f_suitHCP[0][0] = scorematrix[para_size++];
			this->f_suitHCP[0][1] = scorematrix[para_size++];
			this->f_suitHCP[1][0] = scorematrix[para_size++];
			this->f_suitHCP[1][1] = scorematrix[para_size++];
			break;
		default:
			break;
	}
	switch((id / 100) % 10){
		case 0:
			break;
		case 1:
			for(int i = 0;i < 14;i++){
				this->lenlist[0][i] = scorematrix[para_size + i];
				this->lenlist[1][i] = scorematrix[para_size + 14 + i];
			}
			para_size += 28;
			break;
		case 2:
			for(int i = 0;i < 3;i++){
				this->f_dist[0][i] = scorematrix[para_size + i];
				this->f_dist[1][i] = scorematrix[para_size + i + 3];
			}
			para_size += 6;
			break;
		default:
			break;
	}
	switch((id / 1000) % 10){
		case 0:
			break;
		case 1:
			for(int i = 0;i < 2;i++){
				this->f_long[0][i] = scorematrix[para_size + i];
				this->f_long[1][i] = scorematrix[para_size + i + 2];
			}
			para_size += 4;
			break;
		case 2:
			for(int i = 0;i < 2;i++){
				this->f_long[0][i] = scorematrix[para_size + i];
				this->f_long[1][i] = scorematrix[para_size + i + 2];
			}
			para_size += 4;
			this->long4card[0] = scorematrix[para_size++];
			this->long4card[1] = scorematrix[para_size++];
			break;
		case 3:
			for(int i = 0;i < 3;i++){
				this->tf_long[0][i] = scorematrix[para_size + i];
				this->tf_long[1][i] = scorematrix[para_size + i + 3];
			}
			para_size += 6;
			break;
		case 4:
			this->f_long[0][0] = scorematrix[para_size++];
			this->f_long[0][1] = scorematrix[para_size++];
			break;
		default:
			break;
	}
	switch((id / 10000) % 10){
		case 0:
			break;
		case 1:
			for(int i = 0;i < 2;i++){
				this->f_short[0][i] = scorematrix[para_size + i];
				this->f_short[1][i] = scorematrix[para_size + i + 2];
			}
			para_size += 4;
			break;
		case 2:
		case 3:
			for(int i = 0;i < 3;i++){
				this->tf_short[0][i] = scorematrix[para_size + i];
				this->tf_short[1][i] = scorematrix[para_size + i + 3];
			}
			para_size += 6;
			break;
		case 4:
			for(int i = 0;i < 3;i++)
				this->tf_short[0][i] = scorematrix[para_size++];
			break;
		default:
			break;
	}
	switch((id / 100000) % 10){
		case 0:
			break;
		case 1:
			for(int i = 0;i < 2;i++){
				for(int j = 0;j < 2;j++){
					for(int k = 0;k < 6;k++)
						this->called[i][j][k] = scorematrix[para_size++];
				}
			}
			for(int i = 0;i < 2;i++){
				for(int j = 0;j < 2;j++){
					for(int k = 2;k < 9;k++){
						called_HCP[i][j][k] = called[i][j][0];
					}
					called_HCP[i][j][9] = called[i][j][1];
					called_HCP[i][j][10] = called[i][j][1];
					called_HCP[i][j][11] = called[i][j][2];
					called_HCP[i][j][12] = called[i][j][3];
					called_HCP[i][j][13] = called[i][j][4];
					called_HCP[i][j][1] = called[i][j][5];
				}
			}
			break;
		default:
			break;
	}
	switch((id / 1000000) % 10){
		case 0:
			break;
		case 1:
			for(int i = 0;i < 2;i++){
				for(int j = 0;j < 2;j++){
					for(int k = 0;k < 3;k++){
						called_short[i][j][k] = scorematrix[para_size++];
					}
				}
			}
			break;
		default:
			break;
	}
	switch((id / 10000000) % 10){
		case 0:
			break;
		case 1:
			for(int i = 0;i < 2;i++){
				for(int j = 0;j < 2;j++){
					for(int k = 0;k < 3;k++){
						called_dis[i][j][k] = scorematrix[para_size++];
					}
				}
			}
			break;
		default:
			break;
	}
	switch((id / 100000000) % 10){
		case 0:
			break;
		case 1:
			for(int i = 0;i < 2;i++){
				for(int j = 0;j < 2;j++){
					for(int k = 0;k < 2;k++){
						called_long[i][j][k] = scorematrix[para_size++];
					}
				}
			}
			break;
		default:
			break;
	}
	if(para_size != (int)this->needed_para){
		cerr << "You give me " << this->needed_para << " parameters, but I only use the first " << para_size << " parameters." << endl;
		cerr << "There is bug in when you set the scorematrix!" << endl;
		cerr << "FIX IT!!!!" << endl;
		return para_size;
	}
	return 0;
}
double Experiment::E_called_HCP(Player P, int suit, int position, int E_suit){
	double ret = 0;
	int same_suit = (suit == E_suit);
	auto hand = P.hand.getcard();
	for(auto suit:hand){
		for(auto card:suit){
			ret += called_HCP[same_suit][position][card];
		}
	}
	return ret;
}
double Experiment::E_called_short(Player P, int suit, int position, int E_suit){

	double ret = 0;
	int same_suit = (suit == E_suit);
	auto hand = P.hand;
	for(auto len:hand.distributed){
		if(len < 3){
			ret += called_short[same_suit][position][len];
		}
	}
	return ret;
}
double Experiment::E_called_dis(Player P, int suit, int position, int E_suit){

	double ret = 0;
	int same_suit = (suit == E_suit);
	auto hand = P.hand;
	for(auto len:hand.distributed){
		ret += called_dis[same_suit][position][0] * pow(fabs(len - called_dis[same_suit][position][1]), called_dis[same_suit][position][2]);
	}
	return ret;
}
double Experiment::E_called_long(Player P, int suit, int position, int E_suit){

	double ret = 0;
	auto hand = P.hand;
	int same_suit = (suit == E_suit);
	for(auto len:hand.distributed){
		if(len > called_long[same_suit][position][1]){
			ret += called_long[same_suit][position][0] * (len - called_long[same_suit][position][1]);
		}
	}
	return ret;
}
