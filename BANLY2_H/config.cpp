#include "config.h"

float config::hcp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4};
float config::card[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
QList<continfo> config::bds; // bds = bidding set
QString config::check_pos = "N/";
QString config::cfg = "";
int config::deal = 1000;
int config::limit_deal = 1000;
int config::pos_deal = 700;
QString config::positiondic = "NESW";
QStringList config::suitdic = {"Spade", "Heart", "Diamond", "Club"};
bool config::ns_vul = false;
bool config::ew_vul = false;
int config::make_rate_lb = 25;
int config::level_test = 7;

continfo::continfo(int le, int su, QString meaning){ // 0 = s, 1 = h, ..., 4 = nt
    level = le;
    suit = su;
    exp = meaning;
    cont.clear();
    cont += QString::number(level);
    switch (suit) {
        case 0:
            cont += "S";
            break;
        case 1:
            cont += "H";
            break;
        case 2:
            cont += "D";
            break;
        case 3:
            cont += "C";
            break;
        case 4:
            cont += "N";
            break;
    }
}
continfo::continfo(QString limit){
    cont = limit;
    level = -1;
    suit = -1;
}
void continfo::cont_doubled(int doubled){
    if(doubled == 2) cont += "X";
    else if (doubled == 4) cont += "XX";
}
