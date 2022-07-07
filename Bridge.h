#ifndef STDC
#define STDC
#include "bits/stdc++.h"

using namespace std;

static const double basicHCP[14] = {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3};
static const double basiclen[14] = {3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const unsigned int Winner = 0x3002;
int SetBits(uint32_t i);
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
		double HCP;
		double HCP_suit[4];
		Player(Hand hand, string position = "Dontcare"){
			this->hand = hand;
			this->position = position;
			this->score = 0;
			this->HCP = 0;
			memset(HCP_suit, 0, sizeof(HCP_suit));
			int tempHCP;
			auto handcard = hand.getcard();
			for(int i = 0;i < 4;i++){
				tempHCP = 0;
				for(auto card:handcard[i]){
					this->HCP += basicHCP[card];
					tempHCP += basicHCP[card];
				}
				this->HCP_suit[i] = tempHCP;
			}
		}
		Player(){
			this->hand = Hand();
			this->position = "None";
			this->score = 0;
			this->HCP = 0;
			for(auto suit:hand.getcard()){
				for(auto card:suit){
					this->HCP += basicHCP[card];
				}
			}
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
		int E_suit;
		Team(Player North, Player South, double DDS = 0, int suit = 4, int maker = 0, int E_suit = 4){
			this->player[0] = North;
			this->player[1] = South;
			this->suit = suit;
			this->DDSwin = DDS;
			this->maker = maker;
			this->E_suit = E_suit;
		}
		Team(){
			this->player[0] = Player();
			this->player[1] = Player();
			this->suit = 4;
			this->DDSwin = 0;
			this->maker = 0;
			this->E_suit = 4;
		}
		void ShowHand();
};
class PartialGame{
	public:
		Player player[4];	//{North, East, South, West}
		int suit;			//{Spade, Heart, Diamond, Club}
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
		unsigned int needed_para;
		int Fixformulaid;
		const vector<int> FixFormulaArgumentSize = {0, 2, 4, 10};
		const vector<int> FormulaArgumentSize = {0, 26, 17, 9, 11, 15, 12, 19, 21, 21, 24, 23, 10, 32, 32, 12, 12, 12, 16, 13};
		//	HCP, HCP_notrump, 
		//	suitHCP, LongShort, 
		//	longformula, Editinglongformula, TrainLong,
		//	shortformula, discreteshort, TrainShort,
		//	TrumpLong, Nontrumpshort, distributeformula
		const vector<int> FeatureSize = {11, 5, 4, 28, 4, 6, 6, 4, 6, 6, 2, 3, 6};
		//	HCP, HCP_notrump, 
		const vector<int> HCPSize = {0, 11, 5};
		//	suitHCP
		const vector<int> suitHCPSize = {0, 4};
		//	LongShort, distributeformula
		const vector<int> distriSize = {0, 28, 6};
		//	longformula, Editinglongformula, TrainLong, TrumpLong
		const vector<int> longSize = {0, 4, 6, 6, 2};
		//	shortformula, discreteshort, TrainShort, Nontrumpshort
		const vector<int> shortSize = {0, 4, 6, 6, 3};
		//	Called_HCP
		const vector<int> CHCPSize = {0, 24};
		//	Called_short
		const vector<int> CShortSize = {0, 12};
		//	Called_dis
		const vector<int> CDisSize = {0, 12};
		//	Called_long
		const vector<int> CLongSize = {0, 8};
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
		double tf_long[2][3];
		double tf_short[2][3];
		double f_dist[2][3];
		double f_fixsuitHCP[2];
		double early_hand[14];
		double late_hand[14];
		double f_distributedistance[3];
		double called[2][2][6];
		double called_HCP[2][2][14];
		double called_short[2][2][3];
		double called_long[2][2][2];
		double called_dis[2][2][3];
		double called_len[2][4];
		double AssestScore[14];
		vector<double> long4card;
		double distributedistance(Team &t);
		void nScorer();
		int nSet_scorematrix(vector<double> scorematrix);
		Experiment(vector<Team> teams, int _formulaid = 0);
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
		
		void setformulaid(int _formulaid);
		void setFixformulaid(int Fixformulaid){
			this->Fixformulaid = Fixformulaid;
		}
		int ExposeSuit(Player);
		void foo();
		void bar();
		double HonorTrick(Player p, int suit);
		double PlayingTrick(Player p, int suit);
		double LosingTrickCount(Player p, int suit);
		double AssestSystem(Player p, int suit);
		double StaymanPointCount(Player p, int suit);
		double RuleofThreeandFour(Player p, int suit);
		double MoinsValue(Player p, int suit);
		double PlusValue(Player p, int suit);
	private:
		double HCP(Team t);
		double HCP_notrump(Team t);
		double pHCP(Player &p, int suit);
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
		double formula6(Team t);
		double pformula6(Player p, int suit);
		double formula7(Team &t);
		double pformula7(Player &p, int suit);
		double formula8(Team &t);
		double pformula8(Player &p, int suit);
		double formula9(Team &t);
		double pformula9(Player &p, int suit);
		double formula10(Team &t);
		double pformula10(Player &p, int suit);
		double formula11(Team &t);
		double formula12(Team &t);
		double pformula12(Player &p, int suit);
		double formula13(Team &t);
		double pformula13(Player &p, int suit, int pos, int E_suit);
		double formula14(Team &t);
		double pformula14(Player &p, int suit, int pos, int E_suit);
		double formula15(Team &t);
		double pformula15(Player &p, int suit);
		double formula16(Team &t);
		double pformula16(Player &p, int suit);
		double formula17(Team &t);
		double pformula17(Player &p, int suit);
		double formula18(Team &t);
		double pformula18(Player &p, int suit);
		double formula19(Team &t);
		double pformula19(Player &p, int suit);
		int loser(Team &t);
		int ploser(Player &p, int suit);
		unsigned int cardtobit(vector<int> card);
//		double distributedistance(Team &t);
		double distributedistance_v2(Team &t);
		double suitHCP(Player p, int suit);
		double FASTsuitHCP(Player p, int suit);
		double singlesuitHCP(Player p, int suit);
		double longformula(Player p, int suit);
		double Editinglongformula(Player p, int suit);
		double shortformula(Player p, int suit);
		double discreteshort(Player p, int suit);
		double TrainLong(Player p, int suit);
		double TrainShort(Player p, int suit);
		double TrumpLong(Team t);
		double Nontrumpshort(Team t);
		double singleshortformula(Player p, int suit);
		double distributeformula(Player p, int suit);
		double FixFormula1(PartialGame game);
		double FixFormula2(PartialGame game);
		double FixFormula3(PartialGame game);
		double p_FixFormula3(Player, int, int, int);
		double FixsuitHCP(Player, int, int, int);
		double Fix_early_HCP(Player, int);
		double Fix_late_HCP(Player, int);
		bool have_honor(Player P, int suit);
		double E_called_HCP(Player P, int suit, int position, int E_suit);
		double E_called_short(Player P, int suit, int position, int E_suit);
		double E_called_dis(Player P, int suit, int position, int E_suit);
		double E_called_long(Player P, int suit, int position, int E_suit);
};
#endif
