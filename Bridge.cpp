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
//		cout << "Set correctly\n";
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
		this->f_suitHCP[0][0] = this->FormulaArgumentList[0][0];
		this->f_suitHCP[0][1] = this->FormulaArgumentList[0][1];
		this->f_suitHCP[1][0] = this->FormulaArgumentList[1][0];
		this->f_suitHCP[1][1] = this->FormulaArgumentList[1][1];
		this->FormulaArgumentList[0].push_back(scorematrix[9]);
		this->FormulaArgumentList[0].push_back(scorematrix[10]);
		this->FormulaArgumentList[0].push_back(scorematrix[11]);
		this->FormulaArgumentList[1].push_back(scorematrix[12]);
		this->FormulaArgumentList[1].push_back(scorematrix[13]);
		this->FormulaArgumentList[1].push_back(scorematrix[14]);
		this->f_dist[0][0] = this->FormulaArgumentList[0][2];
		this->f_dist[0][1] = this->FormulaArgumentList[0][3];
		this->f_dist[0][2] = this->FormulaArgumentList[0][4];
		this->f_dist[1][0] = this->FormulaArgumentList[1][2];
		this->f_dist[1][1] = this->FormulaArgumentList[1][3];
		this->f_dist[1][2] = this->FormulaArgumentList[1][4];
	}
	else{
		cerr << "--Wrong size of scorematrix--" << endl;
		return s;
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
	case 4:
		for(int i = 0;i < (int)this->teams.size();i++){
//			this->score.push_back(this->formula3(this->teams[i]));
			double result;
			result = this->formula4(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
	case 5:
		for(int i = 0;i < (int)this->teams.size();i++){
//			this->score.push_back(this->formula3(this->teams[i]));
			double result;
			result = this->formula5(this->teams[i]);
			this->score.push_back(result);
			this->teams[i].score = result;
		}
	default:
		for(int i = 0;i < (int)this->teams.size();i++){
			double ret = 0;
			ret += this->HCP(teams[i]);
			ret += this->LongShort(teams[i]);
			this->score.push_back(ret);
		}
		break;
	}
}

double Experiment::formula1(Team t){
	double ret = 0;
	ret += pformula1(t.player[0], t.suit);
	ret += pformula1(t.player[1], t.suit);
	return ret;
}

double Experiment::pformula1(Player p, int suit){
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
/*
	vector<vector<int>> hand = p.hand.getcard();
	for(auto x:hand){
		for(auto y:x)cout << y << " ";
		cout << " | ";
	}
	cout << ", score " << endl;
	cout << this->pHCP(p, 4) << endl;
	cout << this->suitHCP(p, suit) << endl;
	cout << this->longformula(p, suit) << endl;
	cout << this->shortformula(p, suit) << endl;
	cout << "---------------\n";
	*/
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
	/* score = HCP + distribute formula
	 * */
	double ret = 0;
	ret += this->pHCP(p, 4);
	ret += this->suitHCP(p, suit);
	ret += this->distributeformula(p, suit);
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
		t = this->f_dist[id][0] * pow(fabs(h[i] - f_dist[id][1]), f_dist[id][2]);
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
		int id = i == suit ? 0:1;
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
		int id = i == suit ? 0:1;
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
		int id = i == suit ? 0:1;
		t = this->f_short[id][0] * pow(3 - distributed[i], this->f_short[id][1]);
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

double Experiment::pHCP(Player p, int suit){
	double ret = 0;
	vector<vector<int>> h = p.hand.getcard();
	for(int i = 0;i < 4;i++){
		int id = 1;
		if(i == suit)id = 0;
		for(auto x:h[i])ret += this->HCPlist[id][x];
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
