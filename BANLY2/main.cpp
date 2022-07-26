#include "mainwindow.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
	/*
	string input;
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
	/*
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

//	return 0;
	return a.exec();
}
