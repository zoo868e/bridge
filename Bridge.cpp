#include"Bridge.h"

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
	else if(s == 26 && this->formulaid == 1){
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
	default:
		for(int i = 0;i < (int)this->teams.size();i++){
			double ret = 0;
			ret += this->HCP(teams[i]);
			ret += this->LongShort(teams[i]);
			this->score.push_back(ret);
			this->teams[i].score = ret;
		}
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
double Experiment::Editinglongformula(Player p, int suit){
	/*	If the length is less than 4, ret += 0
	 *	else if the length is equal to 4, ret += a fixed value
	 *	else ret += a * pow(length - 4, b)
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

double Experiment::HCP(Team t){
	double ret = 0;
	ret += pHCP(t.player[0], t.suit);
	ret += pHCP(t.player[1], t.suit);
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
