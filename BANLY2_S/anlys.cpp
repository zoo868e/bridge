#include "anlys.h"

cont::cont(){
    contract = "";
    level = 0;
    suit = 5;
    score = -10000;
}
cont::cont(QString type){ contract = type; score = -10000;}
cont::cont(int boardpos,int boardlevel,int boardsuit, int boardtrick, int doubled, int boardscore){
    suit = boardsuit;
    level = boardlevel;
    trick = boardtrick;
    pos = boardpos;
    contract += QString::number(boardlevel);
    switch(boardsuit){
        case 0:
            contract += "S";
        break;
        case 1:
            contract += "H";
        break;
        case 2:
            contract += "D";
        break;
        case 3:
            contract += "C";
        break;
        default:
            contract += "N";
    }
    if(doubled == 2)
        contract += "X";
    else if(doubled == 4)
        contract += "XX";
    contract += "/";
    switch(boardpos){
        case 0:
            contract += "N";
        break;
        case 1:
            contract += "E";
        break;
        case 2:
            contract += "S";
        break;
        case 3:
            contract += "W";
        break;
        case 4:
            contract += "NS";
        break;
        case 5:
            contract += "EW";
        break;
    }
    contract = contract + " " + QString::number(boardtrick-6>=boardlevel?(boardtrick-6):-(boardlevel+6-boardtrick));
    score = boardscore;
}
int cont::getscore(int level, int suit, int trick, int doubled = 1, int value = 1){ //double 2-X 4-XX, value 1-non 2-vul
    int score = 0;
    if(trick >= 6+level){
        int trick_value, over_value;
        switch(suit){
            case 0: //S
            case 1: //H
                trick_value = 30;
                over_value = 30;
                break;
            case 2: //D
            case 3: //C
                trick_value = 20;
                over_value = 20;
                break;
            default: //NT
                trick_value = 30;
                over_value = 30;
                score += 10*doubled;
        }
        if(doubled >= 2){
            trick_value = trick_value*doubled;
            over_value = 50*value*doubled;
        }
        score += level*trick_value;
        if(score >= 100) score += 300+200*(value-1);
        else score += 50;
        if(level >= 6) score += (500+(value-1)*250)*(level-5);
        score += (doubled/2)*50;
        score += (trick-level-6)*over_value;
        return score;
    }else{
        switch(value){
            case 1:
                switch(doubled){
                    case 1:
                        return 50*(level+6-trick);
                    default:
                        if((level+6-trick) <= 3) return (200*(level+6-trick-1)+100)*doubled/2;
                        else return (500+(level+6-trick-3)*300)*doubled/2;
                }
            case 2:
                switch(doubled){
                    case 1:
                        return 100*(level+6-trick);
                    default:
                        return (200+(level+6-trick-1)*300)*doubled/2;
                }
            default:
                return -1;
        }
    }
}
bool cont::contsort(const cont& c1, const cont& c2){
    int s1 = c1.score < 0 ? -c1.score : c1.score, s2 = c2.score < 0 ? -c2.score : c2.score;
    int diff = (s1-s2 <= 10 && s1-s2 >= -10) ? 1:0;
    if(diff){
        if(c1.level == c2.level){
            if(c1.suit == 4) return true;
            else if(c2.suit == 4) return false;
            else {
                return c1.suit < c2.suit;
            }
        }
        else
            return c1.level < c2.level;
    }
    return s1 > s2;
}
bool cont::gethigher(const cont& c1, const cont& c2){
    if(c1.level == c2.level){
        if(c1.suit == 4) return true;
        else if(c2.suit == 4) return false;
        else return c1.suit < c2.suit;
    }else
        return c1.level > c2.level;
}

anlys::anlys(){};
int anlys::getdds(QString hand,struct ddTableResults &result){
    int res;
    struct ddTableDealPBN ddshand;
    strcpy(ddshand.cards, hand.toLocal8Bit().constData());
    res = CalcDDtablePBN(ddshand, &result);
    return res;
}
void anlys::comprset(QList<cont> &set, int type = 1){
    if(type == 1){

    }else if(type == 2){
        for(int i = 0; i < set.size(); ++i){
            if(set.at(i).suit == 4 && set.at(i).level > 3 && set.at(i).level < 6){
                set.insert(i, cont(set.at(i).pos, 3, set.at(i).suit, set.at(i).trick, 1, set.at(i).score));
                set.removeAt(i+1);
            }else if(set.at(i).suit >= 0 && set.at(i).suit < 2 && set.at(i).level > 4 && set.at(i).level < 6){
                set.insert(i, cont(set.at(i).pos, 4, set.at(i).suit, set.at(i).trick, 1, set.at(i).score));
                set.removeAt(i+1);
            }else{ //compress partshow and c/d
                if(set.at(i).level > 1 && ((set.at(i).level < 5 && set.at(i).suit >= 2 && set.at(i).suit < 4)||(set.at(i).level < 4 && set.at(i).suit >= 0 && set.at(i).suit < 2)||(set.at(i).level < 3 && set.at(i).suit ==4))){
                    set.insert(i, cont(set.at(i).pos, 1, set.at(i).suit, set.at(i).trick, 1, set.at(i).score));
                    set.removeAt(i+1);
                }
            }
        }
    }
}
void anlys::sort_out_set(QList<cont> &set){
    int initscore = set.at(0).score > 0? set.at(0).score : -set.at(0).score;
    for(int i = 1; i < set.size(); ++i){
        int otherscore = set.at(i).score > 0? set.at(i).score : -set.at(i).score;
        if(!((initscore - otherscore <= 10)&&(initscore - otherscore >= -10)) || set.at(0).pos%2 != set.at(i).pos%2){
            set.insert(i, cont("------\n"));
            break;
        }
    }
}
void anlys::getcontset(struct ddTableResults ddsresult, QList<cont> &contset, int ns_value, int ew_value){
    /* 1. set all dds done
     * 2. sort high level to low level
     * 3. same dire. NS/EW compare the score
     *      or (sacrifice)
     * 4. loop 3. until all done.
    */
    int valuetable[2] = { ns_value, ew_value};
    int score;

    contset.clear();
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 5; ++j){
            int trick = ddsresult.resTable[j][i];
            int trick_opp = ddsresult.resTable[j][i+2];
            if(trick > 6){
                score = cont::getscore(trick-6, j, trick, 1, valuetable[i%2]);
                if(trick_opp > 6){
                    if(trick == trick_opp)
                        contset.append(cont(i+4, trick-6, j, trick, 1, (i%2)==1?-score:score));
                    else{
                        contset.append(cont(i, trick-6, j, trick, 1, (i%2)==1?-score:score));
                        score = cont::getscore(trick_opp-6, j, trick_opp, 1, valuetable[i%2]);
                        contset.append(cont(i+2, trick_opp-6, j, trick_opp, 1, (i%2)==1?-score:score));
                    }
                }else
                    contset.append(cont(i, trick-6, j, trick, 1, (i%2)==1?-score:score));
            }else if(trick_opp > 6){
                score = cont::getscore(trick_opp-6, j, trick_opp, 1, valuetable[i%2]);
                contset.append(cont(i+2, trick_opp-6, j, trick_opp, 1, (i%2)==1?-score:score));
            }
        }
    }
    std::sort(contset.begin(), contset.end(), cont::gethigher);
    //  3.
    bool diff = false;
    int maxleg = contset.size(), maxlev = contset.at(0).level, mainpos = contset.at(0).pos%2, mainsuit = contset.at(0).suit;
    for(int i = 0; i < maxleg; ++i){
        if(mainpos != contset.at(i).pos%2){
            diff = true;
            for(int j = maxlev; j <= maxlev; ++j){
                score = (contset.at(i).pos%2 == 0 ? -cont::getscore(j, contset.at(i).suit, contset.at(i).trick, 2, valuetable[contset.at(i).pos%2]):cont::getscore(j, contset.at(i).suit, contset.at(i).trick, 2, valuetable[contset.at(i).pos%2]));
                if(((contset.at(0).score - score <= 10 && contset.at(0).score - score >= -10)&& mainpos == 1)||((contset.at(0).score - score >= -10 && contset.at(0).score - score >= 10)&& mainpos == 0))
                    contset.append(cont(contset.at(i).pos, j, contset.at(i).suit, contset.at(i).trick, 2, score));
            }
        }
    }
    if(!diff){
        std::sort(contset.begin(), contset.end(), cont::contsort);
        comprset(contset, 2);
        sort_out_set(contset);
    }else{
        std::sort(contset.begin(), contset.end(), cont::gethigher);
        maxleg = contset.size();
        diff = false;
        for(int i = 0; i < maxleg; ++i){
            if(maxlev > contset.at(i).level) break;
            else if(contset.at(i).pos == mainpos){
                for(int j = i+1; j < contset.size();){
                    if(contset.at(j).level+6 > contset.at(j).trick && contset.at(j).suit != 4 && contset.at(j).suit > mainsuit)
                        contset.removeAt(j);
                    else ++j;
                }
                break;
            }
        }
        sort_out_set(contset);
    }
    return ;
}
int anlys::getimp(int score_a, int score_b){
    int score = score_a - score_b, neg = (score < 0 ? -1 : 0);
    score = score < 0 ? -score : score;
    if(score <= 10) return 0;
    else if(score >= 20 && score <= 40)
        return neg*1;
    else if(score >= 50 && score <= 80)
        return neg*2;
    else if(score >= 90 && score <= 120)
        return neg*3;
    else if(score >= 130 && score <= 160)
        return neg*4;
    else if(score >= 170 && score <= 210)
        return neg*5;
    else if(score >= 220 && score <= 260)
        return neg*6;
    else if(score >= 270 && score <= 310)
        return neg*7;
    else if(score >= 320 && score <= 360)
        return neg*8;
    else if(score >= 370 && score <= 420)
        return neg*9;
    else if(score >= 430 && score <= 490)
        return neg*10;
    else if(score >= 500 && score <= 590)
        return neg*11;
    else if(score >= 600 && score <= 740)
        return neg*12;
    else if(score >= 750 && score <= 890)
        return neg*13;
    else if(score >= 900 && score <= 1090)
        return neg*14;
    else if(score >= 1100 && score <= 1290)
        return neg*15;
    else if(score >= 1300 && score <= 1490)
        return neg*16;
    else if(score >= 1500 && score <= 1740)
        return neg*17;
    else if(score >= 1750 && score <= 1990)
        return neg*18;
    else if(score >= 2000 && score <= 2240)
        return neg*19;
    else if(score >= 2250 && score <= 2490)
        return neg*20;
    else if(score >= 2500 && score <= 2990)
        return neg*21;
    else if(score >= 3000 && score <= 3490)
        return neg*22;
    else if(score >= 3500 && score <= 3990)
        return neg*23;
    else return neg*24;
}
void anlys::ddssd(QList<struct ddTableResults> result, float sd[5][4], float avg[5][4]){
        for(int i = 0; i < 5; ++i){
            for(int j = 0; j < 4; ++j){
                float sum = 0.0, mean, stddev = 0.0;
                int rs = result.size();
                for(int k = 0; k < rs; ++k)
                    sum += result[k].resTable[i][j];
                mean = sum/rs;
                avg[i][j] = mean;
                for(int k = 0; k < rs; ++k)
                    stddev += pow(result[k].resTable[i][j] - mean, 2);
                sd[i][j] = sqrt(stddev / rs);
            }
        }
}
void anlys::hcpsd(QTextBrowser *msg){
    QFile file(config::cfg + ".boards");
    QScrollBar *sb = msg->verticalScrollBar();
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }else{
        QTextStream fs(&file);
        QString readline;
        QStringList sephand;
        int boardnum = 0;
        float sd[4], avg[4], sum[4] = {0, 0, 0, 0}, mean[4] = {0, 0, 0, 0}, stddev[4] = {0.0, 0.0, 0.0, 0.0};
        player tarpl;

        msg->insertPlainText("\n");
        while(!fs.atEnd()){
            readline = fs.readLine();
            sephand = readline.split(" ");
            if(sephand.size() != 5) return;
            for(int i = 0; i < 4; ++i){
                tarpl.set_player(sephand[i+1]);
                sum[i] += tarpl.gethcp();
            }
            ++boardnum;
        }
        for(int i = 0; i < 4; ++i) mean[i] = sum[i]/boardnum;
        fs.seek(0);
        while(!fs.atEnd()){
            readline = fs.readLine();
            sephand = readline.split(" ");
            if(sephand.size() != 5) return;
            for(int i = 0; i < 4; ++i){
                tarpl.set_player(sephand[i+1]);
                stddev[i] += pow(tarpl.gethcp() - mean[i], 2);
            }
        }
        for(int i = 0; i < 4; ++i)
            sd[i] = sqrt(stddev[i]/boardnum);
        QTextTableFormat *maintype = new QTextTableFormat();
        QVector<QTextLength> lengset;
        maintype->setAlignment(Qt::AlignCenter);
        lengset.push_back(QTextLength(QTextLength::FixedLength, 100));
        lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
        lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
        lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
        lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
        maintype->setColumnWidthConstraints(lengset);
        maintype->setBorderBrush(Qt::NoBrush);
        maintype->setBorder(0);

        QTextBlockFormat centerAlign;
        centerAlign.setAlignment(Qt::AlignCenter);
        QTextTable *table = msg->textCursor().insertTable(2, 5, *maintype);
        table->cellAt(0, 1).firstCursorPosition().insertText("North");
        table->cellAt(0, 2).firstCursorPosition().insertText("East");
        table->cellAt(0, 3).firstCursorPosition().insertText("South");
        table->cellAt(0, 4).firstCursorPosition().insertText("West");
        table->cellAt(1, 0).firstCursorPosition().insertText("High Card Point");
        table->cellAt(1, 1).firstCursorPosition().insertText(QString::number(mean[0]).left(5) + "±" + QString::number(sd[0]).left(4));
        table->cellAt(1, 2).firstCursorPosition().insertText(QString::number(mean[1]).left(5) + "±" + QString::number(sd[1]).left(4));
        table->cellAt(1, 3).firstCursorPosition().insertText(QString::number(mean[2]).left(5) + "±" + QString::number(sd[2]).left(4));
        table->cellAt(1, 4).firstCursorPosition().insertText(QString::number(mean[3]).left(5) + "±" + QString::number(sd[3]).left(4));
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 5; ++j)
                table->cellAt(i, j).firstCursorPosition().setBlockFormat(centerAlign);
    }
    msg->insertPlainText("\n\n");
    sb->setValue(sb->maximum());
}
bool typeinfo_sort(typeinfo &A, typeinfo &B){
    return A.fre > B.fre;
}
