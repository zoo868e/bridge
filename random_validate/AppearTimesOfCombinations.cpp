#include"Bridge.h"
#include"DataSetReader.h"

using namespace std;

/*	This program aimed to know that how many times of distributed of specific card(s)
 *	./main [data set] [length of permutation]
 *	The maximum length of permutation is 9
 * */

const unsigned int MASK = (1 << 13) - 1;

// return the card rank from 1 to 13 (rank in 2 ~ A)
int CardToIndex(const char C){
	switch(C){
		case 'A':
			return 13;
		case 'K':
			return 12;
		case 'Q':
			return 11;
		case 'J':
			return 10;
		case 'T':
			return 9;
		default:
			return C - '1';
	}
}


// Put in the card number and return the next start index
int SuitToIndex(vector<int> &index, const string suit, const int base, int start_id){
	int id;
	for(auto card:suit){
		id = base * 13 + CardToIndex(card);
		index[start_id] = id;
		start_id++;
	}
	return start_id;
}

// Translate the hand and store that
void HandToIndex(vector<int> &index, const string hand){
	vector<string> temp_hand = split(hand, ".");
	fill(index.begin(), index.end(), 0);
	int temp_start_id = 0, base = 0;
	for(auto suit:temp_hand){
		temp_start_id = SuitToIndex(index, suit, base++, temp_start_id);
	}
	sort(index.begin(), index.end());
}

// Return the target string
string TargetString(vector<int> &index, unsigned int target){
	int i = 0;
	string ret = "";
	while(target){
		if(target & 1){
			if(index[i] < 10)
				ret += "0";
			ret += to_string(index[i]);
		}
		i++;
		target = target >> 1;
	}
	return ret;
}


int main(int argc, char* argv[]){
	if(argc == 1){
		cerr << "Usages:\n";
		cerr << setw(10) << "./main [data set] [length of permutation]\n";
		return 1;
	}
	string filename = argv[1];
	fstream f;
	f.open(filename, ios::in);
	string s;
	getline(f, s);
	int size = stoi(s);
	vector<vector<string>> vs(size, vector<string>(2, ""));
	vector<string> temp_input(2, "");
	for(int i = 0;i < size;i++){
		getline(f, s);
		temp_input = split(s, " ");
		vs[i][0] = temp_input[1];
		vs[i][1] = temp_input[3];
	}
	f.close();
	cout << vs[0][0] << " " << vs[0][1] << endl;
	map<string, int> times;
	vector<vector<vector<int>>> record(size, vector<vector<int>>(2, vector<int>(13, 0)));
	int temp_id = 0;
	for(auto x:vs){
		HandToIndex(record[temp_id][0], x[0]);
		HandToIndex(record[temp_id][1], x[1]);
		temp_id++;
	}
	unsigned int mask;
	for(auto x:record){
		mask = MASK;
		while(mask){
			times[TargetString(x[0], mask)]++;
			times[TargetString(x[1], mask)]++;
			mask--;
		}
	}
	vector<int> remained_card;
	remained_card.insert(remained_card.end(), record[0][0].begin(), record[0][0].end());
	remained_card.insert(remained_card.end(), record[0][1].begin(), record[0][1].end());
	sort(remained_card.begin(), remained_card.end());
	mask = (1 << 26) - 1;
	string temp_string;
	while(mask){
		temp_string = TargetString(remained_card, mask--);
		if(temp_string.size() > 26)
			continue;
		cout << setw(27) << temp_string << setw(0) << ": " << times[temp_string] << endl;
	}
	/*
	vs = vector<vector<string>>();
	vector<int> E(52, 0), W(52, 0);
	for(int i = 0;i < size;i++){
		for(auto ele:record[i][0])
			cout << ele << " ";
		cout << ";";
		for(auto ele:record[i][1])
			cout << ele << " ";
		cout << endl;
	}
	for(int i = 0;i < size;i++){
		for(auto ele:record[i][0])
			E[ele]++;
		for(auto ele:record[i][1])
			W[ele]++;
	}
	cout << "The total times" << endl;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 13;j++)
			cout << setw(10) << W[i * 13 + j] + E[i * 13 + j] << " ";
		cout << endl;
	}
	cout << "The west's total times" << endl;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 13;j++)
			cout << setw(10) << W[i * 13 + j] << " ";
		cout << endl;
	}
	cout << "The east's total times" << endl;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 13;j++)
			cout << setw(10) << E[i * 13 + j] << " ";
		cout << endl;
	}
	cout << "The distance of total times" << endl;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 13;j++)
			cout << setw(10) << (W[i * 13 + j] - E[i * 13 + j]) / 2 << " ";
		cout << endl;
	}
	*/
	return 0;
}
