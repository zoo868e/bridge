#include<bits/stdc++.h>
#include "DataSetReader.h"

using namespace std;


const unsigned int MAX = (1 << 26) - 1;
unsigned int times[MAX];
int mask[53];


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

// String to integer, just translate sequence to int
int SeqToInt(const string s){
	int ret = 0;
	vector<string> temp_s = split(s, " ");
	string input = temp_s[temp_s.size() - 1];
	int size = input.size();
//	cout << s << endl;
	for(int i = 0;i < size;i+=2){
//		cout << input.substr(i, 2) << endl;
		ret = ret | (1 << mask[stoi(input.substr(i, 2))]);
	}
	return ret;
}

//Count the number of 1's
int count_bit(int x){
	x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
	x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
	x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
	x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
	x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
	return x;
}

//Show the times of the specific length combination 
void show_times(int len = 1){
	int i = 1;
	while(i <= (int)MAX){
		if(count_bit(i) == len){
			cout << bitset<26>(i) << ": " << times[i] << endl;
		}
		i++;
	}
}

int main(int argc, char* argv[]){
	if(argc < 3){
		cerr << setw(10) << "Usages:" << endl;
		cerr << setw(10) << " " << "RandomConclusion [Data Set file: *.ATOC] [the specific length you want (from 1 to 13)]" << endl;
		return 1;
	}
	string filename = argv[1];
	cout << "The file name is: " << filename << endl;
	cout << "The length of card is " << argv[2] << endl;
	fstream f;
	f.open(filename, ios::in);
	if(!f.is_open()){
		cerr << "Can't open file: " << filename << endl;
		return 2;
	}
	string s;
	vector<string> temp_input;
	memset(times, 0, sizeof(times));
	memset(mask, 0, sizeof(mask));
	getline(f, s);
	vector<vector<vector<int>>> record(1, vector<vector<int>>(2, vector<int>(13, 0)));
	temp_input = split(s, " ");
	HandToIndex(record[0][0], temp_input[0]);
	HandToIndex(record[0][1], temp_input[1]);
	vector<int> remained_card;
	remained_card.insert(remained_card.end(), record[0][0].begin(), record[0][0].end());
	remained_card.insert(remained_card.end(), record[0][1].begin(), record[0][1].end());
	sort(remained_card.begin(), remained_card.end());
	int m = 0;
	for(auto x:remained_card){
		mask[x] = m;
		m++;
	}
	while(getline(f, s)){
		temp_input = split(s, ":");
//		cout << bitset<26>(SeqToInt(temp_input[0])) << ": " << stoi(temp_input[1]) << endl;
		times[SeqToInt(temp_input[0])] = stoi(temp_input[1]);
	}
	f.close();
	show_times(stoi(argv[2]));
	return 0;
}
