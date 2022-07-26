#ifndef TRASHCAN_H
#define TRASHCAN_H
/*
QString texthtml = "\
                    <p align=\"center\">\
                    <table style=\"border:3px #cccccc solid;width: 450px;\">\
                    <tr>\
                    <td style=\"width: 130px; text-align: center;\">&nbsp;</td>\
                    <td style=\"width: 80px; text-align: center;\">&nbsp;North</td>\
                    <td style=\"width: 80px; text-align: center;\">&nbsp;East</td>\
                    <td style=\"width: 80px; text-align: center;\">&nbsp;South</td>\
                    <td style=\"width: 80px; text-align: center;\">&nbsp;West</td>\
                    </tr>\
                    <tr>\
                    <td style=\"width: 130px; text-align: center;\"><span style=\"color: #ff0000;\">High Card Point</td>\
                    <td style=\"width: 80px; text-align: center;\">" + QString::number(mean[0]).left(5) + "±" + QString::number(sd[0]).left(4) + "</td>\
                    <td style=\"width: 80px; text-align: center;\">" + QString::number(mean[1]).left(5) + "±" + QString::number(sd[1]).left(4) + "</td>\
                    <td style=\"width: 80px; text-align: center;\">" + QString::number(mean[2]).left(5) + "±" + QString::number(sd[2]).left(4) + "</td>\
                    <td style=\"width: 80px; text-align: center;\">" + QString::number(mean[3]).left(5) + "±" + QString::number(sd[3]).left(4) + "</td>\
                    </tr>\
                    </table>";
*/
#endif // TRASHCAN_H

/*
class bidder{
    // first, check last bidding if it is art.
    //      if yes, check resp.
    //      if not, nat.
public:
    bidder();
    QString getbdseq(){ return bdseq;}
    void sethand(QString hands){ allhand = hands;}
private:
    QString allhand;
    QString bdseq;
};
class Distribution{
public:
    Distribution(){
        dist.clear();
        fre = 0;
    }
    Distribution(QString d, float h, float type){
        dist = d;
        fre = 1;
        host = h;
        if(type >= 0 && type <= 2)
            clt = 0;
        else if(type >= 3 && type <= 5)
            clt = 3;
        else if(type >= 6 && type <= 8)
            clt = 6;
        else
            clt = 9;
    }
    bool compare(Distribution another){
        if(dist != another.dist)
            return false;
        if(host-another.host < 0 || host-another.host > 0)
            return false;
        if(another.clt-clt <0 && another.clt-clt >= 3)
            return false;
        return true;
    }
    QString dist;
    float host, clt;
    int fre;

};

*/
