import Gameinfo.calculate as Gamefunc
import Gameinfo.Game as Game
def validateTheOldMethod20220311(board, calculator, func):
    """
    This function is doing the experiment that only count the longest suit and
    the result of DDS is more than 6.
    If there are two same length only calcutae the suit which have the most
    win tricks.
    If the tricks they win still same, then only calculate the biggest suit.
    """
    DDS = []
    score = []
    print("{:^20}".format(calculator.HCPname), end = " ")
 
    for f in range(len(func)):
        DDS.clear()
        score.clear()
        tooshort = 0
        l = 0
        correct = 0
        one = 0
        two = 0
        for i in board:
            func[f](i)
            score.append(calculator.ns[0])
            DDS.append(i.SouthDDS[0])
        print('{:^10.4f}'.format(Gamefunc.getcurr(DDS, score)), end = " ")
    print("")


# calculate the correlation coefficient during Suit contract
def LongestSuit20220324(board, calculator, func):
    """
    This function is doing the experiment that only count the longest suit and
    the result of DDS is more than 6.
    If there are two same length only calcutae the suit which have the most
    win tricks.
    If the tricks they win still same, then only calculate the biggest suit.
    """
    DDS = []
    score = []
    print("{:^20}".format(calculator.HCPname), end = " ")
 
    for f in range(len(func)):
        DDS.clear()
        score.clear()
        tooshort = 0
        l = 0
        correct = 0
        one = 0
        two = 0
        for i in board:
            func[f](i)
            ns_maxlong = [i.longgest[0][0][0], i.longgest[0][2][0]]
            for s in range(len(i.longgest[0][0])):
                if i.longgest[0][2][s] > ns_maxlong[1]:
                    ns_maxlong[0] = i.longgest[0][0][s]
                    ns_maxlong[1] = i.longgest[0][2][s]
            ns_suit = ns_maxlong[0]
            ns_len = i.longgest[0][1]
            ns_ddswin = ns_maxlong[1]
            ns = calculator.ns
            if ns_len < 7 and i.South.hand.distributed[ns_suit] < 6 and i.North.hand.distributed[nw_suit] < 6:
                tooshort += 1
            else:
                score.append(ns[ns_suit])
                DDS.append(ns_ddswin)
        print('{:^10.4f}'.format(Gamefunc.getcurr(DDS, score)), end = " ")
    print("")



# calculate the correlation coefficient during Suit contract
def LongestSuit20210715(board, calculator, func):
    """
    This function is doing the experiment that only count the longest suit and
    the result of DDS is more than 6.
    If there are two same length only calcutae the suit which have the most
    win tricks.
    If the tricks they win still same, then only calculate the biggest suit.
    """
    DDS = []
    score = []
    print("{:^20}".format(calculator.HCPname), end = " ")
 
    for f in range(len(func)):
        DDS.clear()
        score.clear()
        tooshort = 0
        l = 0
        correct = 0
        one = 0
        two = 0
        for i in board:
            func[f](i)
            ns_maxlong = [i.longgest[0][0][0], i.longgest[0][2][0]]
            we_maxlong = [i.longgest[1][0][0], i.longgest[1][2][0]]
            for s in range(len(i.longgest[0][0])):
                if i.longgest[0][2][s] > ns_maxlong[1]:
                    ns_maxlong[0] = i.longgest[0][0][s]
                    ns_maxlong[1] = i.longgest[0][2][s]
            for s in range(len(i.longgest[1][0])):
                if i.longgest[1][2][s] > we_maxlong[1]:
                    we_maxlong[0] = i.longgest[1][0][s]
                    we_maxlong[1] = i.longgest[1][2][s]
            ns_suit = ns_maxlong[0]
            ns_len = i.longgest[0][1]
            ns_ddswin = ns_maxlong[1]
            we_suit = we_maxlong[0]
            we_len = i.longgest[1][1]
            we_ddswin = we_maxlong[1]
            ns = calculator.ns
            we = calculator.we
            if ns_len < 7 and i.South.hand.distributed[ns_suit] < 6 and i.North.hand.distributed[nw_suit] < 6 or ns_ddswin < 7:
                tooshort += 1
            else:
                score.append(ns[ns_suit])
                DDS.append(ns_ddswin)
            if we_len < 7 and i.West.hand.distributed[we_suit] < 6 and i.East.hand.distributed[we_suit] < 6 or we_ddswin < 7:
                tooshort += 1
            else:
                score.append(we[we_suit])
                DDS.append(we_ddswin)
        print('{:^10.4f}'.format(Gamefunc.getcurr(DDS, score)), end = " ")
    print("")


def LongestSuit20210729(board, calculator, func):
    """
    This function is doing the experiment that only count the longest suit and
    the result of DDS is more than 6.
    If there are two same length calcutae all of them.
    """
    DDS = []
    score = []
    print("{:^20}".format(calculator.HCPname), end = " ")
 
    for f in range(len(func)):
        DDS.clear()
        score.clear()
        tooshort = 0
        l = 0
        correct = 0
        one = 0
        two = 0
        for i in board:
            func[f](i)
            ns_maxlong = [i.longgest[0][0][0], i.longgest[0][2][0]]
            we_maxlong = [i.longgest[1][0][0], i.longgest[1][2][0]]
            for s in range(len(i.longgest[0][0])):
                if i.longgest[0][2][s] > ns_maxlong[1]:
                    ns_maxlong[0] = i.longgest[0][0][s]
                    ns_maxlong[1] = i.longgest[0][2][s]
            for s in range(len(i.longgest[1][0])):
                if i.longgest[1][2][s] > we_maxlong[1]:
                    we_maxlong[0] = i.longgest[1][0][s]
                    we_maxlong[1] = i.longgest[1][2][s]
            ns_suit = i.longgest[0][0]
            ns_len = i.longgest[0][1]
            ns_ddswin = i.longgest[0][2]
            we_suit = i.longgest[1][0]
            we_len = i.longgest[1][1]
            we_ddswin = i.longgest[1][2]
            ns = calculator.ns
            we = calculator.we
            for s in range(len(ns_suit)):
                if ns_len < 7 and i.South.hand.distributed[ns_suit[s]] < 6 and i.North.hand.distributed[nw_suit[s]] < 6 or ns_ddswin[s] < 7:
                    tooshort += 1
                else:
                    score.append(ns[ns_suit[s]])
                    DDS.append(ns_ddswin[s])
            for s in range(len(we_suit)):
                if we_len < 7 and i.West.hand.distributed[we_suit[s]] < 6 and i.East.hand.distributed[we_suit[s]] < 6 or we_ddswin[s] < 7:
                    tooshort += 1
                else:
                    score.append(we[we_suit[s]])
                    DDS.append(we_ddswin[s])
        print('{:^10.4f}'.format(Gamefunc.getcurr(DDS, score)), end = " ")
    print("")



# calculate the correlation coefficient during NT contract
def NT20210715(board, calculator, func):
    DDS = []
    score = []
    print("{:^10}".format("NT20210715"), end = " ")
    print("")
    print("{:^10}".format(calculator.HCPname), end = " ")
    for f in range(len(func)):
        DDS.clear()
        score.clear()
        toosmall = 0
        for i in board:
            func[f](i)
            ns_suit = 4
            ns_ddswin = (i.DDSresult[0][4] + i.DDSresult[1][4]) / 2
            we_suit = 4
            we_ddswin =  (i.DDSresult[2][4] + i.DDSresult[3][4]) / 2
            ns = calculator.ns
            we = calculator.we
            if ns_ddswin < 7:
                toosmall += 1
            else:
                score.append(ns[ns_suit])
                DDS.append(ns_ddswin)
            if we_ddswin < 7:
                toosmall += 1
            else:
                score.append(we[we_suit])
                DDS.append(we_ddswin)
        print('{:^10.4f}'.format(Gamefunc.getcurr(DDS, score)), end = " ")
    print("")

if __name__=="__main__":
    import sys
    sys.path.append("~/bridge/data")
    f = open("data/test")
    rowdata = f.read()
    f.close()
    board = Game.loadDDSresult(rowdata)
    calculator = Gamefunc.Calculator()
#    func = [calculator.HCP, calculator.Long, calculator.Short, calculator.Pavlicek, calculator.Loser]
    func = [calculator.HCP]
    LongestSuit20210715(board, calculator, func)
    LongestSuit20210729(board, calculator, func)
