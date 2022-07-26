#ifndef CONFIG_H
#define CONFIG_H

#include<QFile>
#include<QTextStream>
#include<QDebug>

class continfo{
public:
    continfo(){}
    continfo(int le, int su, QString meaning);
    continfo(QString limit);
    QString getcont(){ return cont;}
    QString getexp(){ return exp;}
    void cont_doubled(int doubled);
    int getlevel(){ return level;}
    int getsuit(){ return suit;}
    void setexp(QString newexp){ exp = newexp;}
private:
    QString cont;
    int level;
    int suit;
    QString exp;
};
class config{
public:
    static float hcp[13]; // 2 = 0, 3 = 1, 4 = 2, ..., J = 9, K = 11, A = 12
    static float card[14];
    static QList<continfo> bds;
    static QString check_pos;
    static QString cfg;
    static int deal;
    static int limit_deal;
    static int pos_deal;
    static bool ns_vul;
    static bool ew_vul;
    static QString positiondic;
    static QStringList suitdic;
    static int make_rate_lb;
    static int level_test;
};
#endif // CONFIG_H
