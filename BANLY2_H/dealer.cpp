#include "dealer.h"

//////
/// card::
///     int num;
///     bool rsvn;
///     QChar suit;
///     QChar rank;
///     float point;
//////

card::card(){}
void card::setcard(int init){
    num = init;
    rsvn = false;
    if(init/13 == 0)
        suit = 'C';
    else if(init/13 == 1)
        suit = 'D';
    else if(init/13 == 2)
        suit = 'H';
    else
        suit = 'S';
    if(init%13 <= 7)
        rank = '2'+init%13;
    else{
        if(init%13 == 8)
            rank = 'T';
        else if(init%13 == 9)
            rank = 'J';
        else if(init%13 == 10)
            rank = 'Q';
        else if(init%13 == 11)
            rank = 'K';
        else
            rank = 'A';
    }
    point = config::hcp[init%13];
}
void card::setrsvn(bool r){
    rsvn = r;
}
int card::getnum(){ return num;}
bool card::getrsvn(){
    return rsvn;
}
QChar card::getsuit(){
    return suit;
}
QChar card::getrank(){
    return rank;
}
float card::getpoint(){
    return point;
}
bool card_sort(card& A, card& B){
    return A.getnum() > B.getnum();
}

//////
/// player::
///     QString hand;
///     int dist[4];
///     int ord_dist[4];
///     float hcp;
///
//////

void player::clear(){
    hand.clear();
    hcp = 0;
    for(int i = 0; i < 4; ++i){
        dist[i] = 0;
        ord_dist[i] = 0;
    }
}
QString player::gethand(){
    return hand;
}
float player::gethcp(){
    return hcp;
}
void player::append_hand(QChar rank){
    hand += rank;
}
void player::hcp_calc(float point){
    hcp += point;
    //qDebug() << QString::number(hcp);
}
void player::sort_out_dist(){
    for(int i = 0; i < 4; ++i)
         dist[i] = ord_dist[i];
    std::sort(dist, dist+4);
    std::reverse(dist, dist+4);
}
void player::set_dist(int suit, int cs){
    ord_dist[suit] = cs;
}
void player::get_int_dist(int* suit){
     suit[0] = ord_dist[0];
     suit[1] = ord_dist[1];
     suit[2] = ord_dist[2];
     suit[3] = ord_dist[3];
}
QString player::get_dist(int type){
    switch (type){
        case 0:
            return QString::number(ord_dist[0]) + QString::number(ord_dist[1]) + QString::number(ord_dist[2]) + QString::number(ord_dist[3]);
        case 1:
            return QString::number(dist[0]) + QString::number(dist[1]) + QString::number(dist[2]) + QString::number(dist[3]);
        case 2:
            return "(" + QString::number(dist[0]) + QString::number(dist[1]) + QString::number(dist[2]) + QString::number(dist[3]) + ")";
        default:
            return "Bad ";
    }
}
QString player::unformat_dist(int key, ...){
    QString newdist = "";
    va_list num_list;

    for(int i = 0; i < 4; ++i){
        bool ans = false;
        va_start(num_list, key);
        for(int j = 0; j < key; ++j){
            if(ord_dist[i] == va_arg(num_list, int)){
                ans = true;
                break;
            }
        }
        va_end(num_list);
        if(ans)
            newdist.append(QString::number(ord_dist[i]));
        else
            newdist.append("x");
    }
    return newdist;
}
//////
/// bithand
///
//////
bithand::bithand(QString hand){
    int handlen = hand.length();
    int suit = 3;
    bitset.resize(56);
    bitset.fill(false);
    for(int i = 0; i < handlen; ++i){
        switch(hand[i].toLatin1()){
            case '.':
                --suit;
                break;
            case 'A':
                bitset[suit*13+12] = true;
                break;
            case 'K':
                bitset[suit*13+11] = true;
                break;
            case 'Q':
                bitset[suit*13+10] = true;
                break;
            case 'J':
                bitset[suit*13+9] = true;
                break;
            case 'T':
                bitset[suit*13+8] = true;
                break;
            default:
                int pos = hand[i].toLatin1() - '2';
                bitset[suit*13+pos] = true;
        }
    }
}
QString bithand::gethand(){
    QString unzip;
    for(int i = 51; i >= 0; --i){
        if(i%13 == 12) unzip += ".";
        if(bitset[i] == true){
            switch (i%13) {
                case 12:
                    unzip += "A";
                    break;
                case 11:
                    unzip += "K";
                    break;
                case 10:
                    unzip += "Q";
                    break;
                case 9:
                    unzip += "J";
                    break;
                case 8:
                    unzip += "T";
                    break;
                default:
                    unzip += ('2'+(i%13));
                    break;
            }
        }
    }
    unzip.remove(0, 1);
    return unzip;
}

//////
/// filter::filter
///
//////
filter::filter(){ pos = -1;}
filter::filter(QString raw){
    QStringList cfg = raw.split("/");
    if(cfg[0] == "N") pos = 0;
    else if (cfg[0] == "E") pos = 1;
    else if (cfg[0] == "S") pos = 2;
    else if (cfg[0] == "W") pos = 3;
    for(int i = 0; i < 6; ++i){ //by cs
        QStringList comp = cfg[i+1].split("-");
        cs_lo[i] = comp[0].toInt();
        cs_hi[i] = comp[1].toInt();
    }
    for(int i = 7; i < 8; ++i){
        QStringList comp = cfg[i].split("-");
        hcp_lo = comp[0].toFloat();
        hcp_diff = comp[1].toFloat()-hcp_lo;
    }
    dist = cfg[8];
    if(cfg.size() > 9){
        for(int i = 9; i < cfg.size(); ++i){
            adv.append(cfg[i]);
        }
    }
}
int filter::getpos(){
  return pos;
}
bool filter::hand_filter(player hand, player pa){
    int suit[4], pasuit[4];
    hand.get_int_dist(suit);
    pa.get_int_dist(pasuit);
    for(int i = 0; i < 4; ++i){
        if((suit[i] < cs_lo[i] || suit[i] > cs_hi[i]))
            return false;
    }
    // M
    if((suit[0]+suit[1]-cs_lo[4] < 0 || suit[0]+suit[1] > cs_hi[4]))
        return false;
    // m
    if((suit[2]+suit[3]-cs_lo[5] < 0 || suit[2]+suit[3] > cs_hi[5]))
        return false;
    if(!dist.isEmpty()){
        if(dist.indexOf(hand.get_dist(2)) >= 0){
                if(dist.indexOf(hand.get_dist(2)) > 0 && dist[dist.indexOf(hand.get_dist(2))-1] == '-')
                    return false;
        }else{
            if(dist.indexOf(hand.get_dist(0)) >= 0){
                if(dist.indexOf(hand.get_dist(0)) > 0 && dist[dist.indexOf(hand.get_dist(0))-1] == '-')
                    return false;
            }else if(dist.indexOf("-") == -1)
                return false;
        }
    }
    int adv_size = adv.size();
    for(int i = 0; i < adv_size; ++i){ // sh(d/c) = S+H(D+C) ltc = Losing Trick Count hwp = hcp with partner
        int ltc, lob = 0, hib = 0, losing = 0;
        QStringList hh;
        QStringList  det = adv[i].split(" ");
        int setleg = det[0].length();
        if(setleg == 0) break;
        else if(setleg == 2){
            QStringList hs = hand.gethand().split(".");
            lob = det[1].section('-', 0, 0).toInt();
            hib = det[1].section('-', 1, 1).toInt();
            //qDebug() << hand.get_dist(0);
            if(det[0][0] == "s"){
                if(det[0][1] == "h"){
                    //qDebug() << QString::number(suit[0] + suit[1]);
                    //qDebug() << "lo " << QString::number(lob);
                    //qDebug() << "hi "<< QString::number(hib);
                    if(suit[0] + suit[1] < lob || suit[0] + suit[1] > hib) return false;
                }else if(det[0][1] == "d"){
                    if(suit[0] + suit[2] < lob || suit[0] + suit[2] > hib) return false;
                }else if(det[0][1] == "c"){
                    if(suit[0] + suit[3] < lob || suit[0] + suit[3] > hib) return false;
                }else if(det[0][1] == "m"){
                    if(suit[0] + suit[2] < lob || suit[0] + suit[2] > hib){
                        if(suit[0] + suit[3] < lob || suit[0] + suit[3] > hib) return false;
                    }
                }else return false;
            }else if(det[0][0] == "h"){
                if(det[0][1] == "d"){
                    if(suit[1] + suit[2] < lob || suit[1] + suit[2] > hib) return false;
                }else if(det[0][1] == "c"){
                    if(suit[1] + suit[3] < lob || suit[1] + suit[3] > hib) return false;
                }else if(det[0][1] == "m"){
                    if(suit[1] + suit[2] < lob || suit[1] + suit[2] > hib){
                        if(suit[1] + suit[3] < lob || suit[1] + suit[3] > hib) return false;
                    }
                }else return false;
            }else if(det[0][0] == "M"){
                if(det[0][1] == "d"){
                    if(suit[1] + suit[2] < lob || suit[1] + suit[2] > hib){
                        if(suit[1] + suit[0] < lob || suit[0] + suit[2] > hib) return false;
                    }
                }else if(det[0][1] == "c"){
                    if(suit[1] + suit[3] < lob || suit[1] + suit[3] > hib){
                        if(suit[0] + suit[3] < lob || suit[0] + suit[3] > hib) return false;
                    }
                }else return false;
            }else return false;
        }else if(setleg == 3){
            if(det[0] == "ltc"){
                hh = hand.gethand().split(".");
                ltc = 0;
                for(int i = 0; i < 4; ++i){
                    losing = hh[i].length() < 3 ? hh[i].length() : 3;
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
                QStringList spl = det[1].split("-");
                if(spl.size() > 1){
                    lob = spl[0].toInt();
                    hib = spl[1].toInt();
                    if(ltc < lob || ltc > hib) return false;
                }else{
                    int hib = spl[0].toInt();
                    if(ltc > hib) return false;
                }
            }else if(det[0] == "shc"){ // suit honor count
                QString suit = det[1];
                QStringList rng = det[2].split("-");
                bool ok, ok_2;
                int shc = 0, lob = rng[0].toInt(&ok), hib = rng[1].toInt(&ok_2);
                int suitlen;
                QString phd; // part of hand
                if(det[1] == "s"){
                    phd = hand.gethand().section('.', 0, 0);
                }else if(det[1] == "h"){
                    phd = hand.gethand().section('.', 1, 1);
                }else if(det[1] == "d"){
                    phd = hand.gethand().section('.', 2, 2);
                }else if(det[1] == "c"){
                    phd = hand.gethand().section('.', 3, 3);
                }
                suitlen = phd.length();
                if(ok && ok_2){
                    shc = (phd.indexOf('A') == -1 ? 0:1) + (phd.indexOf('K') == -1 ? 0:1) + (phd.indexOf('Q') == -1 ? 0:1);
                    if(shc < lob || shc > hib) return false;
                }else if(!ok && !ok_2){
                    if(((phd.indexOf("AK") == -1) ? false : true && phd.length() >= 9 )||((phd.indexOf("AKQJ") == -1) ? false : true && phd.length() >= 6 )||((phd.indexOf("AKQ") == -1) ? false : true && suitlen >= 7))
                        shc = 2;
                    else if(((((phd.indexOf("AKJ") == -1) ? false : true)||((phd.indexOf("AQJ") == -1) ? false : true)||((phd.indexOf("KQJ") == -1) ? false : true))&& suitlen >= 6)||(((phd.indexOf("AKQ") == -1) ? false : true)&& suitlen == 6))
                        shc = 1;
                    else shc = 0;
                    if(rng[0] == "p") lob = 0;
                    else if(rng[0] == "s") lob = 1;
                    else if(rng[0] == "S") lob = 2;
                    else return false;
                    if(rng[1] == "p") hib = 0;
                    else if(rng[1] == "s") hib = 1;
                    else if(rng[1] == "S") hib = 2;
                    else return false;
                    if(shc > hib || lob > shc) return false;
                }else return false;
            }else if(det[0] == "law"){
                int level = det[1].toInt();
                hh = hand.gethand().split(".");
                ltc = 0;
                for(int i = 0; i < 4; ++i){
                    losing = hh[i].length() < 3 ? hh[i].length() : 3;
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
                if(pos%2 == 0){
                    if(config::ns_vul){
                        if(level+ltc-7 > 2) return false;
                    }else{
                        if(level+ltc-7 > 3)return false;
                    }
                }else{
                    if(config::ew_vul){
                        if(level+ltc-7 > 2) return false;
                    }else{
                        if(level+ltc-7 > 3) return false;
                    }
                }
            }else if(det[0] == "hwp"){
                QStringList hcp_range = det[1].split("-");
                float lb, ub, epsilon = 0.001f;

                lb = hcp_range[0].toFloat();
                if(hcp_range.size() > 1) ub = hcp_range[1].toFloat();
                else ub = 100;
                //qDebug() << QString::number(hand.gethcp()+pa.gethcp()) << endl;
                if(hcp_range.size() == 1){
                    if(!(fabs((hand.gethcp()+pa.gethcp())-lb) < epsilon)) return false;
                }else if(hcp_range.size() == 2){
                    if(((hand.gethcp()+pa.gethcp()) < lb) || ((hand.gethcp()+pa.gethcp()) > ub))return false;
                }else return false;
            }else if(det[0] == "wph"){
                QMap<QChar, int> map;
                map.insert('s', 0);
                map.insert('h', 1);
                map.insert('d', 2);
                map.insert('c', 3);
                if(det.size() != 3)
                    return false;
                else{
                    QStringList c_range = det[2].split("-");
                    int lb, ub;
                    if(c_range.size() != 2) return false;
                    lb = c_range[0].toInt();
                    ub = c_range[1].toInt();
                    det[1] = det[1].toLower();
                    if(det[1].length() == 2){ // [a][b] a is ur_suit, b is pa_suit, for example ss means ur_spades and pa_spades. note 'os' means without spades+spades, other suits fit the condition
                        if(det[1][0] == "o"){
                            int wo = map.value(det[1][1], -1);
                            for(int i = 0; i < 4; ++i){
                                if(i == wo) continue;
                                else if(suit[i]+pasuit[i] > ub || suit[i]+pasuit[i] < lb) return false;
                            }
                        }else{
                            // [urs][pas]
                            int urs = map.value(det[1][0], -1), pas = map.value(det[1][1], -1);
                            if(urs == -1 || pas == -1) return false;
                            int result = suit[urs] + pasuit[pas];
                            if(result > ub || result < lb) return false;
                            //qDebug() << lb << " " << result << " " << ub;
                        }
                    }else return false;
                }
            }else if(det[0] == "skc"){ //(format: /skc [suit] 0/1/2/... keycard [option])
                if(det.size() == 5){
                    QStringList ts;
                    int bound = det[2].toInt(), temp, tssize, suitlen;
                    int sk, kc; // sk = specific card kc = keycard
                    int opt = det[4].toInt();

                    if(opt == 0){
                        if(det[4] != "0") return false;
                    }
                    if(bound == 0){
                        if(det[2] != "0")
                            return false;
                    }
                    hand.gethand(det[1], ts);
                    tssize = ts.size();
                    kc = det[3].toInt();
                    if(kc == 0){
                        if(det[3] == "A") kc = 13;
                        else if(det[3] == "K") kc = 12;
                        else if(det[3] == "Q") kc = 11;
                        else if(det[3] == "J") kc = 10;
                        else if(det[3] == "T") kc = 9;
                        else return false;
                    }
                    //qDebug() << tssize;
                    for(int i = 0; i < tssize; ++i){
                        temp = bound;
                        suitlen = ts[i].length();
                        for(int j = 0; j < suitlen; ++j){
                            //qDebug() << ts[i];
                            sk = ts[i][j].digitValue()-1; // dig..ue will return -1, when it can't tranfer char to int
                            if(sk == -2){ // if upper condition, -1-1 = -2
                                if(ts[i][j] == 'A') sk = 13;
                                else if(ts[i][j] == 'K') sk = 12;
                                else if(ts[i][j] == 'Q') sk = 11;
                                else if(ts[i][j] == 'J') sk = 10;
                                else if(ts[i][j] == 'T') sk = 9;
                                else return false;
                            }
                            if(opt == 0){
                                if(sk >= kc) --temp;
                                else{
                                    if(temp > 0) return false;
                                }
                            }else if(opt == 1){
                                if(sk == kc) break;
                                else return false;
                            }else return false;
                        }
                        if(temp > 0 && opt == 0) return false;
                    }
                }else return false;
            }else return false;
        }else return false;
        /// other filter
    }
    if(hcp_lo <= hand.gethcp() && hcp_diff >= hand.gethcp()-hcp_lo)
        return true;
    else
        return false;
}

//////
/// table::
///     card board[52];
///     player seat[4];
/////

table::table(){
    for(int i = 0; i < 52; ++i)
        board[i].setcard(i);
    for(int i = 0; i < 4; ++i)
        seat[i].clear();
}
void table::set_board_clear(){
    for(int i = 0; i < 52; ++i)
        board[i].setrsvn(false);
}
void table::default_shuffle(){
    //std::default_random_engine generator(rd());
    int  rannum;
    for(int i = 0; i < 52; ++i){
        while(board[i].getrsvn() == true){
            ++i;
            if(i > 51) return;
        }
        std::uniform_int_distribution<int> dist(i,51);
        do{
            rannum = dist(*QRandomGenerator::global());
         }while(board[rannum].getrsvn() == true);
        std::swap(board[i], board[rannum]);
    }
}
int table::set_player_hand(int pos, QString hand){
    QString player_dic = "NESW";
    QString suit_dic = "SHDC";
    int suit = 0, handleng = 0;
    for(int i = 0; i < hand.length(); ++i){
        while(hand[i] == '.'){
            ++i;
            ++suit;
            if(suit > 3) return 1;
        }
        for(int j = 0; j < 52; ++j){
            if(board[j].getrank() == hand[i] && board[j].getsuit() == suit_dic[suit]){
                std::swap(board[j], board[13*pos+handleng]);
                board[13*pos+handleng].setrsvn(true);
                ++handleng;
                break;
            }
        }
    }
    //qDebug() << hand;
    return 0;
}
void table::sort_out_hand(){
    QString suit_dic = "SHDC";
    std::sort(board, board+13, card_sort);
    std::sort(board+13, board+26, card_sort);
    std::sort(board+26, board+39, card_sort);
    std::sort(board+39, board+52, card_sort);
    for(int i = 0; i < 4; ++i){
        int suit_int = 0, suitleng = 0;
        seat[i].clear();
        for(int j = 0; j <13 ; ++j){
            while(board[13*i+j].getsuit() != suit_dic[suit_int]){
                seat[i].append_hand('.');
                seat[i].set_dist(suit_int, suitleng);
                suitleng = 0;
                ++suit_int;
                if(suit_int > 3) break;
            }
            ++suitleng;
            seat[i].append_hand(board[13*i+j].getrank());
            seat[i].hcp_calc(board[13*i+j].getpoint());
        }
        seat[i].set_dist(suit_int, suitleng);
        for(int k = suit_int; k < 3;){
            seat[i].append_hand('.');
            seat[i].set_dist(++k, 0);
        }
        seat[i].sort_out_dist();
    }
}
player table::gethand(int pos){ return seat[pos];}
QString table::get_all_hand(){
    return seat[0].gethand() +" "+seat[1].gethand()+" "+seat[2].gethand()+" "+seat[3].gethand()+"\n";
}




