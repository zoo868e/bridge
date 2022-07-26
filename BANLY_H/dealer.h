#ifndef DEALER_H
#define DEALER_H

#include<QList>
#include<QChar>
#include<QString>
#include<QRandomGenerator>
#include<QTextStream>
#include<QRegularExpression>
#include<QBitArray>
#include<QTextBrowser>
#include<QDir>
#include<QListWidget>
#include<QLineEdit>
#include<QDateTime>
#include<QProgressBar>
#include<QElapsedTimer>
#include<QScrollBar>
#include<QCoreApplication>

#include<cstdarg>
#include<random>
#include<algorithm>
#include<time.h>
#include"config.h"

class card{
    // C2 = 0, C3 = 1, ... , CA = 12, D2= 13, D3 = 14, ...
public:
    card();
    void setcard(int init);
    void setrsvn(bool r);
    int getnum();
    bool getrsvn();
    QChar getsuit();
    QChar getrank();
    float getpoint();
    bool operator>(card& B) const { return num > B.getnum();}
    bool operator<(card& B) const { return num < B.getnum();}

private:
    int num;
    bool rsvn;
    QChar suit;
    QChar rank;
    float point;
};
bool card_sort(card& A, card& B);

class player{
public:
    player(){ clear();}
    void set_player(QString rawhand){
        clear();
        QStringList dist_hand;
        hand = rawhand;
        dist_hand = rawhand.split(".");
        for(int i = 0; i < 4; ++i)
            ord_dist[i] = dist_hand.at(i).length();
        sort_out_dist();
        int len = rawhand.length();
        for(int i = 0; i < len; ++i){
            //qDebug() << rawhand[i];
            if(rawhand[i] == '.') continue;
            switch(rawhand[i].toLatin1()){
                case 'A':
                        hcp_calc(config::hcp[12]);
                    break;
                case 'K':
                        hcp_calc(config::hcp[11]);
                    break;
                case 'Q':
                        hcp_calc(config::hcp[10]);
                    break;
                case 'J':
                        hcp_calc(config::hcp[9]);
                    break;
                case 'T':
                        hcp_calc(config::hcp[8]);
                    break;
                default:
                    hcp_calc(config::hcp[rawhand[i].toLatin1()-'2']);
            }
        }
    }
    QString unformat_dist(int key, ...);
    void clear();
    QString gethand();
    void gethand(QString suit, QStringList &list){
        QStringList handsp = hand.split(".");
        int suitleng = suit.length(), card_int = 0;

        list.clear();
        suit = suit.toLower();
        for(int i = 0; i < suitleng; ++i){
            if(suit[i] == "s") list.push_back(handsp[0]);
            else if(suit[i] == "h") list.push_back(handsp[1]);
            else if(suit[i] == "d") list.push_back(handsp[2]);
            else if(suit[i] == "c") list.push_back(handsp[3]);
            else{
                card_int = suit[i].digitValue();
                if(card_int == -1) continue;
                else{
                    for(int j = 0; j < 4; ++j)
                        if(ord_dist[j] == card_int) list.push_back(handsp[j]);
                }
            }
        }
        //qDebug() << list.size();
    }
    float gethcp();
    void append_hand(QChar rank);
    void hcp_calc(float point);
    void sort_out_dist();
    void set_dist(int suit, int cs);
    QString get_dist(int type);
    void get_int_dist(int* suit);
private:
    QString hand;
    int dist[4];
    int ord_dist[4];
    float hcp;
};

class bithand{
public:
    bithand(){}
    bithand(QString hand);
    QString gethand();
    player getphand(){
        player more;
        more.set_player(gethand());
        return more;
    }
private:
    QBitArray bitset;
};
class filter{
public:
    filter();
    filter(QString raw);
    int getpos();
    bool hand_filter(player hand, player pa);
    QStringList getfilter(){
        QStringList setting;
        setting.append(QString(config::positiondic[pos]));
        setting.append(QString("hcp " + QString::number(hcp_lo) + " ~ " + QString::number(hcp_diff)));
        setting.append(QString("s " + QString::number(cs_lo[0]) + " ~ " + QString::number(cs_lo[0])));
        setting.append(QString("h " + QString::number(cs_lo[1]) + " ~ " + QString::number(cs_lo[1])));
        setting.append(QString("d " + QString::number(cs_lo[2]) + " ~ " + QString::number(cs_lo[2])));
        setting.append(QString("c " + QString::number(cs_lo[3]) + " ~ " + QString::number(cs_lo[3])));
        setting.append(QString("M " + QString::number(cs_lo[4]) + " ~ " + QString::number(cs_lo[4])));
        setting.append(QString("m " + QString::number(cs_lo[5]) + " ~ " + QString::number(cs_lo[5])));
        setting.append(dist);
        setting.append(adv);
        return setting;
    }
private:
    int pos;
    //  spade = 0, hearts = 1, diamonds = 2, clubs = 3, M = 4, m = 5;
    float hcp_lo;
    float hcp_diff;
    int cs_lo[6];
    int cs_hi[6];
    QString dist;
    QStringList adv;
};
class table{
public:
    table();
    void default_shuffle();
    int setting_shuffle(QTextBrowser *msg,QTextBrowser *sug_msg, QListWidget *settings, QLineEdit *n, QLineEdit *e, QLineEdit *s, QLineEdit *w, QProgressBar *bar = nullptr, int type = 0){
        QList<filter> mesh;
        table dealer;
        QScrollBar *sb = msg->verticalScrollBar();
        int bds_size = config::bds.size(), setting_size;
        QString pos = "NESW";

        config::cfg = QDir::currentPath();
        if(!QDir("files").exists())
                QDir().mkdir("files");
//        do{ config::cfg = config::cfg + "/files/banlz_" + QDateTime::currentDateTime().toString("yymmddzzz");
//        }while(QFile::exists(config::cfg + ".boards"));
		config::cfg = config::cfg + "/files/banlz_";
		qDebug() << config::cfg;
        QFile file(config::cfg + ".Hboards");
        if(file.open(QIODevice::WriteOnly)){
            QTextStream fs(&file);
			fs << config::deal << "\n";
            QElapsedTimer timer;
            qint64 time_took = 0;
            int done_deal = 0;
            //QList<float> occur_per;
            // all set
            bar->setMinimum(0);
            bar->setMaximum(100);
            msg->setTextColor(QColor(70, 140, 200));
            msg->insertPlainText("New file: " + config::cfg + ".boards is created." + "\n");
            msg->setTextColor(QColor(0, 0, 0));
            dealer.set_board_clear();
            if(type == 0){
                mesh.clear();
                if(!n->text().isEmpty())
                    dealer.set_player_hand(0, n->text());
                if(!e->text().isEmpty())
                    dealer.set_player_hand(1, e->text());
                if(!s->text().isEmpty())
                    dealer.set_player_hand(2, s->text());
                if(!w->text().isEmpty())
                    dealer.set_player_hand(3, w->text());
                for(int i = 1; i < settings->count(); ++i){
                    if(settings->item(i)->text().compare("New") != 0){
                        QString str = (settings->item(i)->text());
                                    // N/0-13/0-13/0-13/0-13/0-13/0-13/15-17/(4333)+(4432)+(5332)+(5422)/
                        mesh.push_back(filter(str));
                    }
                }
            }else if(type == 1){
                mesh.clear();
                if(bds_size < 1) return -1;
                for(int i = 0; i < bds_size; ++i){
                    QStringList raw_setting = config::bds[i].getexp().split("|", QString::SkipEmptyParts);
                    setting_size = raw_setting.size();
                    for(int j = 0; j < setting_size; ++j){
                        mesh.append(filter(pos[i%4]+"/"+raw_setting[j]));
                        msg->insertPlainText(pos[i%4]+"/"+raw_setting[j]+"\n");
                    }
                }
            }
            // Start to deal.
            msg->insertPlainText("Start to deal. \n");
            timer.start();
            int filter_num = mesh.size();
            int d_deal = 0;
            if(type == 0){
                for(int i = 0; i < config::limit_deal; ++i){
                    bool nesw[4] = {true, true, true, true};
                    bool done[4] = {false, false, false, false};
                    dealer.default_shuffle();
                    dealer.sort_out_hand();                    
                    for(int j = 0; j < filter_num; ++j){
                        int pos = mesh[j].getpos();
                        if(done[pos] == true) continue;
                        else{
                            nesw[pos] = mesh[j].hand_filter(dealer.gethand(pos), dealer.gethand((pos+2)%4));
                            if(nesw[pos]) done[pos] = nesw[pos];
                        }
                    }
                    if(nesw[0] && nesw[1] && nesw[2] && nesw[3]){
                        msg->insertPlainText(dealer.get_all_hand());
//                        qDebug() << "Success " << dealer.get_all_hand();
                        QCoreApplication::processEvents();
                        fs << "N:" << dealer.get_all_hand();
						done_deal++;
//                        fs << ++done_deal << ". " << dealer.get_all_hand();
                        sb->setValue(sb->maximum());
                    }//else qDebug() << "Failed " << dealer.get_all_hand();
                    ++d_deal;
                    if(done_deal >= config::deal) break;
                }
            }else if(type == 1){
                for(int i = 0; i < config::limit_deal; ++i){
                    int stable = -1;
                    bool nesw[4] = {true, true, true, true};
                    bool done[4] = {false, false, false, false};
                    dealer.default_shuffle();
                    dealer.sort_out_hand();
                    for(int j = 0; j < filter_num; ++j){
                        int pos = mesh[j].getpos();
                        if(stable != -1 && stable != pos && !nesw[stable]) break;
                        if(stable > pos){
                            done[0] = false;
                            done[1] = false;
                            done[2] = false;
                            done[3] = false;
                        }
                        if(done[pos] == true) continue;
                        else{
                            nesw[pos] = mesh[j].hand_filter(dealer.gethand(pos), dealer.gethand((pos+2)%4));
                            done[pos] = nesw[pos];
                            //if(nesw[pos]) msg->insertPlainText(dealer.gethand(pos).gethand() + " ->Success :" +QString::number(j) + "\n");
                        }
                        stable = pos;
                    }
                    if(nesw[0] && nesw[1] && nesw[2] && nesw[3]){
                        sug_msg->insertPlainText(QString::number(++done_deal) + ": " + dealer.get_all_hand());
                        msg->insertPlainText(dealer.get_all_hand());
                        QCoreApplication::processEvents();
                        fs << done_deal << ". " << dealer.get_all_hand();
                        sb->setValue(sb->maximum());
                    }
                    ++d_deal;
                    if(done_deal >= config::deal) break;
                }
            }else{ return -1;}
            time_took = timer.elapsed();
            msg->insertPlainText("In " + QString::number(d_deal) + " deals, " + QString::number(done_deal) + " are fitted.\n");
            msg->insertPlainText("Time: " + QString::number(time_took/1000) + "s "+ QString::number(time_took%1000) +"ms \n");            
        }else{
            msg->setTextColor(QColor(255, 0, 0));
            msg->insertPlainText("Something is wrong, cann't open the file.\n");
            msg->setTextColor(QColor(0, 0, 0));
            return -1;
        }        
        return 0;
    }
    void set_board_clear();
    int set_player_hand(int pos, QString hand);
    void sort_out_hand();
    player gethand(int pos);
    QString get_all_hand();
private:
    // C++
    //std::random_device rd;
    // QT
    card board[52];
    player seat[4];

};
#endif // DEALER_H
