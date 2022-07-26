#include "mainwindow.h"
#include <QApplication>
#include <iostream>

using namespace std;
vector<string> split(const string &str, const string & delim){
	vector<string> res;
	if("" == str)return res;
	string strs = str + delim;
	size_t pos;
	size_t size = strs.size();
	for(size_t i = 0;i < size;i++){
		pos = strs.find(delim, i);
		if(pos < size){
			string s = strs.substr(i, pos - i);
			res.push_back(s);
			i = pos + delim.size() - 1;
		}
	}
	return res;
}



int main(int argc, char *argv[])
{
	if(argc > 1){
		string size = argv[1];
		config::limit_deal = 10000;
		config::deal = stoi(size);
	}
    QApplication a(argc, argv);
    MainWindow w;
	w.on_btn_deal_click_clicked(argv[2], "", argv[3], "");
	/*

    //w.show();
	string input;
	vector<string> NS;
	while(getline(cin, input)){
		if(input == "" || input[0] == '0')break;
		NS = split(input, " ");
		cout << NS[0] << endl << NS[1] << endl;
		w.on_btn_deal_click_clicked(NS[0], "", NS[1], "");
		cout << "done\n";
	}
	// haven't complete, complete it at this weak;
	while(getline(cin, input)){
		switch(input[0]){
			case 'A':		//advanced
				break;
			case 'E':		//edit a position's hand
				break;
			case 'S':		//
			default:
				cerr << "Only accept 'A(advanced)' and 'E(edit a position's hand)'" << endl;
				continue;
		}
	}
	string s = "S";
	w.on_pb_sub_clicked(s);


	w.on_btn_deal_click_clicked("48.A8J.A236.89JQ", "", "A35.6K.59TQ.A27K");
	string s;
	while(getline(cin, s)){
		if(s[0] == '0')break;
		else{
			w.on_edit_deal_max_textChanged(QString(s));
			w.on_edit_deal_tar_textChanged(QString(s));
			w.on_btn_deal_click_clicked();
		}
	}
	*/

	return 0;
//	return a.exec();
}
