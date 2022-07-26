#ifndef ANLYS_H
#define ANLYS_H

#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QTableWidget>
#include <QBrush>
#include <QTextTable>
#include <string.h>
#include <algorithm>
#include <math.h>
#include "./include/dll.h"
#include "dealer.h"
#include "config.h"


class cont{
public:
    QString contract;
    int level;
    int suit;
    int score;
    int trick;
    int pos;
    cont();
    cont(QString type);
    cont(int boardpos,int boardlevel,int boardsuit, int boardtrick, int doubled, int boardscore);
    static int getscore(int level, int suit, int trick, int doubled, int value);
    static bool contsort(const cont& c1, const cont& c2);
    static bool gethigher(const cont& c1, const cont& c2);
};

class typeinfo{
public:
    typeinfo(QString t, int f){ type = t; fre = f;}
    static int getltc(QString hand){
        QStringList hh = hand.split(".");
        int ltc = 0;
        for(int i = 0; i < hh.size(); ++i){
            int losing = hh[i].length() < 3 ? hh[i].length() : 3;
            //qDebug() << QString::number(losing);
            if(hh[i].length() >= 3){
                for(int j = 0; j < 3; j++)
                    if(hh[i][j] == "A" || hh[i][j] == "K" || hh[i][j] == "Q") --losing;
            }else if(hh[i].length() == 2){
                for(int j = 0; j < 2; j++)
                    if(hh[i][j] == "A" || hh[i][j] == "K") --losing;
            }else if(hh[i].length() == 1){
                for(int j = 0; j < 1; j++)
                    if(hh[i][j] == "A") --losing;
            }
            ltc += losing;
            //qDebug() << QString::number(ltc);
        }
        return ltc;
    }
    static QStringList handtype(player pl){
        QStringList typeset;
        QString hand = pl.gethand();
        QStringList suits = hand.split(".");
        QString dist = pl.get_dist(1);

        if(dist == "4432"|| dist == "4333"|| dist == "5332") typeset.append("BAL");
        else if(dist == "6322" || dist == "7222") typeset.append("semi_BAL");
        else typeset.append("non_BAL");
        //else if(dist == "4441" || dist == "5431" || dist == "5521" || dist == "6331" || dist == "6421" || dist == "7321" || dist == "8221")
        for(int i = 0; i < 4; ++i){
            int sleng = suits[i].length();
            QString newtype;
            if(sleng == 0) typeset.append("void in " + config::suitdic[i]);
            else if(sleng == 1){
                if(suits[i] == "A") typeset.append("singleton with A in " + config::suitdic[i]);
                else if(suits[i] == "K" || suits[i] == "Q" ||suits[i] == "J") typeset.append("singleton with K/Q/J in " + config::suitdic[i]);
                else typeset.append("singleton w/o honors in " + config::suitdic[i]);
                typeset.append("singleton in " + config::suitdic[i]);
            }else if(sleng == 2){
                if(suits[i] == "AK") typeset.append("doubleton w/ AK in " + config::suitdic[i]);
                else if(suits[i] == "KQ" || suits[i] == "AQ") typeset.append("doubleton with AQ/KQ in " + config::suitdic[i]);
                else if(suits[i] == "AJ" || suits[i] == "KJ") typeset.append("doubleton with AJ/KJ in " + config::suitdic[i]);
                else if(suits[i] == "QJ") typeset.append("doubleton with QJ in " + config::suitdic[i]);
                typeset.append("doubleton in " + config::suitdic[i]);
            }else{
                int ltc = typeinfo::getltc(suits[i]);
                if(ltc != 3) typeset.append("cards with A/K/Q in " + config::suitdic[i]);
                else if(suits[i].indexOf("J") != -1) typeset.append("cards with J in " + config::suitdic[i]);
                else typeset.append("cards with nothing in " + config::suitdic[i]);
            }
        }
        return typeset;
    }
    QString type; //" hcp dist dist_type s h d c "
    int fre;
};

class seatinfo{
public:
    seatinfo(){}
    void addhcp(player pl){
        QString handtype = pl.get_dist(0);
        hcp.push_back(pl.gethcp());
    }
    float hcpsd(){
        int hcpsize = hcp.size();
        float mean, sum = 0, stddev = 0;
        for(int i = 0; i < hcpsize; ++i)
            sum += hcp.at(i);
        mean = sum/hcpsize;
        for(int i = 0; i < hcpsize; ++i)
            stddev += pow(hcp.at(i) - mean, 2);
        return sqrt(stddev/hcpsize);
    }
    float hcp_mean(){
        int hcpsize = hcp.size();
        float sum = 0;
        for(int i = 0; i < hcpsize; ++i)
            sum += hcp.at(i);
        return sum/hcpsize;
    }
private:
    QList<float> hcp;
};
bool typeinfo_sort(typeinfo &A, typeinfo &B);

class typeset{
public:
    typeset(){alltype.clear();}
    void addinfo(player pl){
        QStringList t_set = typeinfo::handtype(pl);
        int t_size = t_set.size();
        for(int i = 0; i < t_size; ++i){
            int all_size = alltype.size();
            bool new_type = true;
            for(int j = 0 ; j < all_size; ++j){
                if(t_set[i] == alltype[j].type){
                    ++alltype[j].fre;
                   new_type = false;
                   break;
                }
            }
            if(new_type){
                typeinfo newtype(t_set[i], 1);
                alltype.append(newtype);
            }
        }
    }
    void sort(){
        std::sort(alltype.begin(), alltype.end(), typeinfo_sort);
    }
    QList<typeinfo> alltype;
};

class anlys{
public:
    anlys();

    static int getdds(QString hand,struct ddTableResults &result);
    static int getimp(int score_a, int score_b);
    static void ddssd(QList<struct ddTableResults> result, float sd[5][4], float avg[5][4]);
    static void hcpsd(QTextBrowser *msg);
    static void getbestcont(QList<cont> &set);
    static void comprset(QList<cont> &set, int type); // undone
    static void sort_out_set(QList<cont> &set);
    static void getcontset(struct ddTableResults ddsresult, QList<cont> &contset, int ns_value, int ew_value);
    void position_anlys(int tarpos, QTextBrowser *msg, QTableWidget *ddsmsg, QList<filter> mesh, QString all_hands, int anly_pos, int main, float sdresult[5][4], float avg[5][4], QTextBrowser *infomsg, QTextBrowser *sugmsg){
        table dealer;
        QList<struct ddTableResults> ddsresult;
        struct ddTableResults result;
        float real_sd[5][4], real_avg[5][4];
        int filter_num = mesh.size();
        QStringList strlist = all_hands.split("|");
        seatinfo pos[4];
        QScrollBar *sb = msg->verticalScrollBar();
        int goal = 0, d_deal = 0;

        if(!strlist[tarpos].isEmpty())
            dealer.set_player_hand(tarpos, strlist[tarpos]);
        if(strlist[anly_pos].isEmpty()) return;

        ///
        continfo lastcont("AP");
        int doubled = 0, declarer = 4, ddssize = ddsresult.size();
        //qDebug() << all_hands;
        msg->insertPlainText("Start to analyze Information.\n");
        getdeclarer(doubled, declarer, lastcont);
        ////
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
                msg->insertPlainText(QString::number(ddsresult.size()+1) + " : " + dealer.get_all_hand());
                if(getdds("N:" + dealer.get_all_hand(), result)){
                    QStringList pyh = dealer.get_all_hand().split(" ");
                    player py;
                    for(int i = 0; i < 4; ++i){
                        py.set_player(pyh[i]);
                        pos[i].addhcp(py);
                    }
                    ddsresult.push_back(result);
                }else{
                    msg->insertPlainText("Analysis of information failed.");
                }
                QCoreApplication::processEvents();
                sb->setValue(sb->maximum());
                ++goal;
            }
            ++d_deal;
            if(goal == config::pos_deal) break;
        }
        ddssd(ddsresult, real_sd, real_avg);
        ddssize = ddsresult.size();
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 5; ++j){
                ddsmsg->setItem(i, (j+1)%5, new QTableWidgetItem(QString::number(real_avg[j][i]).left(5) + "±" + QString::number(real_sd[j][i]).left(4)));
                ddsmsg->item(i, (j+1)%5)->setTextAlignment(Qt::AlignCenter);
            }
        }
        for(int i = 0; i < 4; ++i){
            ddsmsg->setItem(i, 5, new QTableWidgetItem(QString::number(pos[i].hcp_mean()).left(5) + "±" + QString::number(pos[i].hcpsd()).left(4)));
            ddsmsg->item(i, 5)->setTextAlignment(Qt::AlignCenter);
        }
        infomsg->insertPlainText(config::positiondic[tarpos] + " deals " + QString::number(d_deal) + " boards.\n");
        if(main == 1){
            infomsg->insertPlainText(QString(config::positiondic[anly_pos]) + " has " + strlist[anly_pos] + "\n");
            infomsg->insertPlainText("After DDS, \n");
            infomsg->insertPlainText(
                    QString(config::positiondic[anly_pos])+ "(" + QString(config::positiondic[(anly_pos+2)%4]) + ")" +
                    "  play NT is " + QString::number(real_avg[4][anly_pos]) + "±" + QString::number(real_sd[4][anly_pos]).left(4) + "(" + QString::number(real_avg[4][(anly_pos+2)%4]) + "±" + QString::number(real_sd[4][(anly_pos+2)%4]).left(4) + ")" +
                    "\n        play Spade is " + QString::number(real_avg[0][anly_pos]) + "±" + QString::number(real_sd[0][anly_pos]).left(4) + "(" + QString::number(real_avg[0][(anly_pos+2)%4]) + "±" + QString::number(real_sd[0][(anly_pos+2)%4]).left(4) + ")" +
                    "\n        play Heart is " + QString::number(real_avg[1][anly_pos]) + "±" + QString::number(real_sd[1][anly_pos]).left(4) + "(" + QString::number(real_avg[1][(anly_pos+2)%4]) + "±" + QString::number(real_sd[1][(anly_pos+2)%4]).left(4) + ")" +
                    "\n        play Diamond is " + QString::number(real_avg[2][anly_pos]) + "±" + QString::number(real_sd[2][anly_pos]).left(4) + "(" + QString::number(real_avg[2][(anly_pos+2)%4]) + "±" + QString::number(real_sd[2][(anly_pos+2)%4]).left(4) + ")" +
                    "\n        play Club is " + QString::number(real_avg[3][anly_pos]) + "±" + QString::number(real_sd[3][anly_pos]).left(4) + "(" + QString::number(real_avg[3][(anly_pos+2)%4]) + "±" + QString::number(real_sd[3][(anly_pos+2)%4]).left(4) + ")" +"\n"
                );
            if(declarer != 4){
                float made = 0, down = 0;
                for(int i = 0; i < ddssize; ++i){
                    if(ddsresult[i].resTable[lastcont.getsuit()][declarer] < lastcont.getlevel()+6) ++down;
                    else  ++made;
                }
               infomsg->insertPlainText("In " + QString::number(ddssize) + " boards, " + QString(config::positiondic[declarer]) + " played " + lastcont.getcont() + " , " + QString::number(made) + "(" + QString::number(made*100/ddssize).left(4) + "%) are made and " + QString::number(down) + "(" + QString::number(down*100/ddssize).left(4) + "%) are down.\n");
            }

            int suitcircle[5] = {3, 2, 1, 0, 4};
            int suitdic[5] = {3, 2, 1, 0, 4};
            QList<continfo> conttest;
            for(int i = (lastcont.getlevel() == -1 ? 1 : lastcont.getlevel()); i < lastcont.getlevel()+config::level_test;){
                for(int j = (i == lastcont.getlevel() ? suitdic[lastcont.getsuit()]+1:0); j < 5; ++j){
                    continfo newcont(i, suitcircle[j], "");
                    conttest.append(newcont);
                }
                if(i == 7) break;
                else ++i;
            }
            infomsg->insertPlainText("\n");
            for(int i = 0; i < conttest.size(); ++i){
                int made = 0;
                int down = 0;
                int made_p = 0;
                int down_p = 0;
                for(int j = 0; j < ddsresult.size(); ++j){
                    if(ddsresult[j].resTable[conttest[i].getsuit()][anly_pos] >= (conttest[i].getlevel()+6))
                        ++made;
                    else ++down;
                    if(ddsresult[j].resTable[conttest[i].getsuit()][(anly_pos+2)%4] >= (conttest[i].getlevel()+6))
                        ++made_p;
                    else ++down_p;
                }
                int first, declarer, doubled;
                config::bds.append(conttest[i]);
                first = getdeclarer(doubled, declarer, conttest[i]);
                if(((100*made)/(made+down)) >= config::make_rate_lb || ((100*made_p)/(made_p+down_p)) >= config::make_rate_lb){
                    if(first == 1) infomsg->insertPlainText("In " + QString::number(ddssize) + " boards, " + QString(config::positiondic[anly_pos]) + "(" + QString(config::positiondic[(anly_pos+2)%4]) + ")" + " played " + conttest[i].getcont() + ", " + QString::number(made) + "(" + QString::number(made_p) + ") are made and " + QString::number(down) + "(" + QString::number(down_p) + ") are down.\n");
                    else infomsg->insertPlainText("In " + QString::number(ddssize) + " boards, " + QString(config::positiondic[declarer]) + " played " + conttest[i].getcont() + ", " + QString::number(declarer == anly_pos ? made : made_p) + " are made and " + QString::number(declarer == anly_pos ? down : down_p) + " are down.\n");
                }
                config::bds.pop_back();
            }
            for(int i = 0; i < 5; ++i){
                float sd = (real_avg[i][anly_pos] - avg[i][anly_pos])/sdresult[i][anly_pos];
                if(sd > 1 && i < 4) infomsg->insertPlainText(config::suitdic[i] + " is better than partner's expectation.\n");
                else if(sd > 1 && i == 4) infomsg->insertPlainText("NT contract is better than partner's expectation.\n");
            }
        }
    }
    static int getdeclarer(int &doubled, int &declarer, continfo &lastcont){
        int contleg = config::bds.size();
        int lastbidder = 4;
        bool first = true;
        for(int i = contleg-1; i >= 0; --i){
            QString contname = config::bds[i].getcont();
            if(contname != "PASS"){
                if(contname == "X"){
                    if(doubled != 4) doubled = 2;
                    continue;
                }
                if(contname == "XX"){
                    doubled = 4;
                    continue;
                }
                lastcont = config::bds[i];
                lastbidder = i%4;
                declarer = lastbidder;
                for(int j = i - 2; j >= 0; j = j-2){
                    if(config::bds[j].getsuit() == lastcont.getsuit()){
                        declarer = j%4;
                        first = false;
                    }
                }
                lastcont.cont_doubled(doubled);
                if(first) return 1;
                else return 2;
            }
        }
        return 0;
    }
    static int basic_anlys(QTextBrowser *msg, QTextBrowser *anly_msg, QTextBrowser *sug_msg,QList<QTableWidget*> ddsmsg,int nsV, int ewV, QString all_hands, QProgressBar *bar = nullptr){
        // caculate all distriutions and detail information about hands
        //  , than return message or number tell the user that
        //  if the dist. or infor. are useful in this board
        QScrollBar *sb = msg->verticalScrollBar();
        QScrollBar *sug_sb = sug_msg->verticalScrollBar();
        if(config::cfg.isEmpty()) return -1;
        else{
            QFile file(config::cfg + ".boards");
            if(!file.open(QIODevice::ReadOnly)){
                msg->insertPlainText("Fail to open file.\n");
                return -1;
            }else{
                QTextStream fs(&file);
                QList<struct ddTableResults> ddsresult;
                struct ddTableResults result;
                float sdresult[5][4], avg[5][4];
                QString ddhand, readline;
                int res;
                player py[4];
                seatinfo pos[4];
                //int barvalue = 50;
                int anly_pos = config::bds.size()%4;
                continfo lastcont("AP");
                int doubled = 0, declarer = 4, ddssize, first = 0;
                int contleg = config::bds.size();

                msg->insertPlainText("Start to analyze DDS.\n");
                sb->setValue(sb->maximum());

                // get declarer
                first = getdeclarer(doubled, declarer, lastcont);
                //qDebug() << first << " " << declarer ;
                int suitcircle[5] = {3, 2, 1, 0, 4};
                int suitdic[5] = {3, 2, 1, 0, 4};

                float neg_sco = 0, pos_sco = 0;
                int made = 0, down = 0;
                typeset m_set, d_set;
                while(!fs.atEnd()){
                    readline = fs.readLine();
                    if(readline.isEmpty()) break;
                    ddhand = "N:" + readline.section(' ', 1, 4);
                    if((res = getdds(ddhand, result)) == 1){
                        for(int p = 0; p < 4; ++p){
                            py[p].set_player(readline.section(' ', p+1, p+1));
                            pos[p].addhcp(py[p]);
                        }
                        ddsresult.push_back(result);
                        if(declarer != 4){
                            if(result.resTable[lastcont.getsuit()][declarer] < lastcont.getlevel()+6) ++down;
                            else  ++made;                            
                            // 4 type for recording
                            // 1. pass > bid(raise) 2. dbl > bid(raise) 3. bid(raise) > pass(dbl) 4. bid(sacr) > pass
                            int new_doubled = result.resTable[lastcont.getsuit()][declarer]-6 >= lastcont.getlevel() ? 1 : 2;
                            int pass_score = cont::getscore(lastcont.getlevel(), lastcont.getsuit(), result.resTable[lastcont.getsuit()][declarer], doubled >= 2 ? doubled : new_doubled, declarer%2 == 0 ? nsV : ewV);
                                if(result.resTable[lastcont.getsuit()][declarer]-6 >= lastcont.getlevel() && declarer%2 != anly_pos%2) pass_score = -pass_score;
                                else if(result.resTable[lastcont.getsuit()][declarer]-6 < lastcont.getlevel() && declarer%2 == anly_pos%2) pass_score = -pass_score;
                            //qDebug() << pass_score << lastcont.getlevel() << lastcont.getsuit() << result.resTable[lastcont.getsuit()][declarer];
                            if(pass_score > 0) pos_sco += pass_score;
                            else neg_sco += pass_score;
                            if((pass_score > 0 && anly_pos%2 != declarer%2) || (pass_score < 0 && anly_pos%2 == declarer%2)){
                                // down
                                d_set.addinfo(py[anly_pos]);
                            }else{
                                // made
                                m_set.addinfo(py[anly_pos]);
                            }
                        }
                    }else{
                        msg->insertPlainText("Something wrong when dds.\n");
                        return -1;
                    }
                }
                ddssize = ddsresult.size();
                if(ddssize == 0) return -1;
                if(declarer != 4){
                    m_set.sort();
                    d_set.sort();
                    sug_msg->insertPlainText("In " + QString::number(ddssize) + " boards, " + QString(config::positiondic[declarer]) + " played " + lastcont.getcont() + " , " + QString::number(made) + "(" + QString::number(made*100/ddssize).left(4) + "%) are made and " + QString::number(down) + "(" + QString::number(down*100/ddssize).left(4) + "%) are down.\n");
                    int d_set_size = d_set.alltype.size();
                    int m_set_size = m_set.alltype.size();

                    QTextTableFormat *maintype = new QTextTableFormat();
                    QVector<QTextLength> lengset;
                    maintype->setAlignment(Qt::AlignCenter);
                    lengset.push_back(QTextLength(QTextLength::FixedLength, 200));
                    lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
                    maintype->setColumnWidthConstraints(lengset);
                    maintype->setBorderBrush(Qt::NoBrush);
                    maintype->setBorder(0);
                    QTextBlockFormat centerAlign;
                    centerAlign.setAlignment(Qt::AlignCenter);
                    QTextTable *table;
                    sug_msg->insertPlainText("\n\nBoards are made w/ ...\n");
                    table = sug_msg->textCursor().insertTable(m_set_size, 2, *maintype);
                    for(int i = 0; i < m_set_size; ++i){
                        table->cellAt(i, 0).firstCursorPosition().insertText(m_set.alltype[i].type);
                        table->cellAt(i, 1).firstCursorPosition().insertText(QString::number(m_set.alltype[i].fre));
                    }
                    if(declarer%2 != anly_pos%2) sug_msg->insertPlainText("Mean: " + QString::number((neg_sco)/(made)).left(7) +"\n");
                    else sug_msg->insertPlainText("Mean: " + QString::number((pos_sco)/(made)).left(6) + "\n");

                    sug_msg->insertPlainText("\n\nBoards are down w/ ...\n");
                    table = sug_msg->textCursor().insertTable(d_set_size, 2, *maintype);
                    for(int i = 0; i < d_set_size; ++i){
                        table->cellAt(i, 0).firstCursorPosition().insertText(d_set.alltype[i].type);
                        table->cellAt(i, 1).firstCursorPosition().insertText(QString::number(d_set.alltype[i].fre));
                    }
                    if(declarer%2 == anly_pos%2) sug_msg->insertPlainText("Mean: " + QString::number((neg_sco)/(down)).left(7)+"\n");
                    else sug_msg->insertPlainText("Mean: " + QString::number((pos_sco)/(down)).left(6)+"\n");

                    if(all_hands.section('|', anly_pos, anly_pos).length() == 16){
                        sug_msg->insertPlainText("\n\nYour hand w/ ...\n");
                        player urhd;
                        typeset urset;
                        urhd.set_player(all_hands.section('|', anly_pos, anly_pos));
                        urset.addinfo(urhd);
                        urset.sort();
                        table = sug_msg->textCursor().insertTable(urset.alltype.size(), 2, *maintype);
                        for(int i = 0; i < urset.alltype.size(); ++i){
                            QString sig;
                            int m_num = -1, d_num = -1;
                            table->cellAt(i, 0).firstCursorPosition().insertText(urset.alltype[i].type);
                            for(int j = 0; j < m_set_size; ++j){
                                if(m_set.alltype[j].type == urset.alltype[i].type){
                                    m_num = m_set.alltype[j].fre;
                                    break;
                                }
                            }
                            for(int j = 0; j < d_set_size; ++j){
                                if(d_set.alltype[j].type == urset.alltype[i].type){
                                    d_num = d_set.alltype[j].fre;
                                    break;
                                }
                            }
                            if(d_num == m_num){
                                if(d_num == -1) table->cellAt(i, 1).firstCursorPosition().insertText("N");
                                else table->cellAt(i, 1).firstCursorPosition().insertText("=");
                            }else if((d_num > m_num && declarer%2 == anly_pos%2) || (d_num < m_num && declarer%2 != anly_pos%2)) table->cellAt(i, 1).firstCursorPosition().insertText("-");
                            else table->cellAt(i, 1).firstCursorPosition().insertText("+");
                        }
                    }
                }
                ddssd(ddsresult, sdresult, avg);
                for(int i = 0; i < 4; ++i){
                    for(int j = 0; j < 5; ++j){
                        ddsmsg[0]->setItem(i, (j+1)%5, new QTableWidgetItem(QString::number(avg[j][i]).left(5) + "±" + QString::number(sdresult[j][i]).left(5)));
                        ddsmsg[0]->item(i, (j+1)%5)->setTextAlignment(Qt::AlignCenter);
                    }
                    //barvalue += (i+1)*2;
                    //bar->setValue(barvalue);
                }
                for(int i = 0; i < 4; ++i){
                    ddsmsg[0]->setItem(i, 5, new QTableWidgetItem(QString::number(pos[i].hcp_mean()).left(5) + "±" + QString::number(pos[i].hcpsd()).left(5)));
                    ddsmsg[0]->item(i, 5)->setTextAlignment(Qt::AlignCenter);
                }
                //barvalue = 60;
                //bar->setValue(barvalue);

                msg->insertPlainText("Start to analyze Information.\n");
                sb->setValue(sb->maximum());
                // output org. result
                if(declarer != 4)
                    anly_msg->insertPlainText("In " + QString::number(ddssize) + " boards, " + QString(config::positiondic[declarer]) + " played " + lastcont.getcont() + " , " + QString::number(made) + "(" + QString::number(made*100/ddssize).left(4) + "%) are made and " + QString::number(down) + "(" + QString::number(down*100/ddssize).left(4) + "%) are down.\n");
                sb->setValue(sb->maximum());
                // redo, set shuffle
                ddsresult.clear();
                QList<filter> mesh;
                int setting_size;

                mesh.clear();
                for(int i = 0; i < contleg; ++i){
                    QStringList raw_setting = config::bds[i].getexp().split("|", QString::SkipEmptyParts);
                    setting_size = raw_setting.size();
                    for(int j = 0; j < setting_size; ++j)
                        mesh.append(filter(config::positiondic[i%4]+"/"+raw_setting[j]));
                }
                // anlys
                QStringList pyh = all_hands.split("|");
                for(int i = 0; i < 4; ++i){
                    anlys *detail = new anlys();
                    if(pyh[i].isEmpty()) continue;
                    detail->position_anlys( i, msg, ddsmsg[i+1], mesh, all_hands, anly_pos, (anly_pos == i)? 1:0, sdresult, avg, anly_msg, sug_msg);
                    delete detail;
                }
            }
        }
        return 0;
    }

};

#endif // ANLYS_H
