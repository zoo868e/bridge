#ifndef STDC
#define STDC
#include "bits/stdc++.h"

using namespace std;

class Hand{
	public:
		vector<int> spade;
		vector<int> heart;
		vector<int> diamond;
		vector<int> club;
		vector<int> distributed;
		Hand(vector<int> spade, vector<int> heart, vector<int> diamond, vector<int> club){
			this->spade = spade;
			this->heart = heart;
			this->diamond = diamond;
			this->club = club;
			this->distributed.resize(4);
			this->distributed[0] = this->spade.size();
			this->distributed[1] = this->heart.size();
			this->distributed[2] = this->diamond.size();
			this->distributed[3] = this->club.size();
		}
		Hand(){
			vector<int> a;
			this->spade = a;
			this->heart = a;
			this->diamond = a;
			this->club = a;
			this->distributed.resize(4);
			this->distributed[0] = 0;
			this->distributed[1] = 0;
			this->distributed[2] = 0;
			this->distributed[3] = 0;
		}
		vector<vector<int>> getcard();
};
class Player{
	public:
		string position;
		Hand hand;
		double score;
		Player(Hand hand, string position = "Dontcare"){
			this->hand = hand;
			this->position = position;
			this->score = 0;
		}
		Player(){
			this->hand = Hand();
			this->position = "None";
			this->score = 0;
		}
		pair<Hand, string> getPlayer();
};
class Game{
	public:
		Player South;
		Player West;
		Player North;
		Player East;
		vector<int> SouthDDS;
		vector<int> WestDDS;
		vector<int> NorthDDS;
		vector<int> EastDDS;
		vector<Player> Players;
		vector<vector<double>> ScoreForPlayers = vector<vector<double>>(4, vector<double>(5));
		pair<vector<float>, vector<float>> longest;
		Game(Player south, Player west, Player north, Player east, vector<vector<int>> DDSresult){
			this->South = south;
			this->West = west;
			this->North = north;
			this->East = east;
			this->SouthDDS = DDSresult[0];
			this->WestDDS = DDSresult[1];
			this->NorthDDS = DDSresult[2];
			this->EastDDS = DDSresult[3];
			this->Players = {north, east, south, west};
		}
		vector<Player> getPlayer();
		pair<vector<Player>, vector<vector<int>>> getGame();
		void Set_long();
};
class Team{
	public:
		Player player[2];
		int suit;
		double DDSwin;
		int maker;
		double score;
		Team(Player declarer, Player dummy, double DDS = 0, int suit = 0, int maker = 0){
			this->player[0] = declarer;
			this->player[1] = dummy;
			this->suit = suit;
			this->DDSwin = DDS;
			this->maker = maker;
		}
		Team(){
			this->player[0] = Player();
			this->player[1] = Player();
			this->suit = 0;
			this->DDSwin = 0;
			this->maker = 0;
		}
};
class PartialGame{
	public:
		Player player[4];
		int suit;
		double DDSwin;
		int maker;
		double score;
		PartialGame(Player *player, double DDS = 0, int suit = 0, int maker = 0){
			for(int i = 0;i < 4;i++)
				this->player[i] = player[i];
			this->suit = suit;
			this->DDSwin = DDS;
			// maker = {NS, WE}
			this->maker = maker;
		}
};
class Experiment{
	public:
		vector<Team> teams;
		vector<Game> games;
		vector<PartialGame> Partialgames;
		vector<double> score;
		vector<double> DDS;
		vector<double> FixFormulaArgumentList;
		int formulaid;
		vector<vector<double>> FormulaArgumentList;
		double HCPlist[2][14];
		double lenlist[2][14];
		double Hlenlist[2][14];
		double Dlenlist[2][14];
		double f1list[2][6];
		double f2list[2][6];
		double f_suitHCP[2][2];
		double f_long[2][2];
		double f_short[2][2];
		double f_dist[2][3];
		Experiment(vector<Team> teams, int formulaid = 0){
			this->teams = teams;
			this->formulaid = formulaid;
			double basicHCP[14] = {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3};
			double basiclen[14] = {3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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
		}
		Experiment(vector<PartialGame> partialgames, int formulaid = 0){
			this->Partialgames = partialgames;
			this->formulaid = formulaid;
			for(int i = 0;i < (int)partialgames.size();i++)
				DDS.push_back(partialgames[i].DDSwin);
		}
		Experiment(vector<Game> games, int formulaid = 0){
			this->games = games;
			this->formulaid = formulaid;
		}
		int Set_scorematrix(vector<double> scorematrix);
		int Set_FixFormulaArgumentList(vector<double> FixArgument);
		void scorer();
		void GameScorer();
		void PartialGamePreScorer();
		void PartialGameTrainScorer();
		void setformulaid(int formulaid){
			this->formulaid = formulaid;
		}
	private:
		double HCP(Team t);
		double pHCP(Player p, int suit);
		double LongShort(Team t);
		double pLongShort(Player p, int suit);
		double Highlen(Team t);
		double pHighlen(Player p, int suit);
		double Difflen(Team t);
		double formula1(Team t);
		double pformula1(Player p, int suit);
		double formula2(Team t);
		double pformula2(Player p, int suit);
		double formula3(Team t);
		double pformula3(Player p, int suit);
		double formula4(Team t);
		double pformula4(Player p, int suit);
		double formula5(Team t);
		double pformula5(Player p, int suit);
		double suitHCP(Player p, int suit);
		double longformula(Player p, int suit);
		double shortformula(Player p, int suit);
		double distributeformula(Player p, int suit);
		double FixFormula1(PartialGame game);
};
#endif
