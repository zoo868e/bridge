import unittest
import sys
import numpy as np
HCPlist = [0,4,0,0,0,0,0,0,0,0,0,1,2,3]
Longlist = [0,0,0,0,0,1,2,3,4,5,6,7,8,9]
Shortlist = [3,2,1,0,0,0,0,0,0,0,0,0,0,0]
basicHCP = HCPlist
basicLong = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
basicShort = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
class corrobj():
    """
    This object is to record the data and define the filter.
    The loader(filename) is to load the data from a specific file
    The filter is a tule that filt the data that may use to calculate the correlation coefficient
    """
    def __init__(self):
        self.board = []
        self.DDS = []
        self.score = []
        self.suit = []
        self.pos = []
        """
        The score matrix is [Trump suit, others suit]
        """
        self.HCPlist = HCPlist * 2
        self.Longlist = basicLong * 2
        self.Shortlist = basicShort * 2
    def set_scorematrix(self, scorematrix):
        """
        Description
        ----
        To set the HCPlist, Longlist, Shortlist
        scorematrix = [14, 14, 14] or [28, 28, 28], the first one is for NT and
        the second one is for suit contract

        Input
        ----
        scorematrix : list

        Output
        ----
        If the input don't the type we mention above, the program will exit.
        """
        if len(scorematrix) == 42:
            self.HCPlist = [y for x in [scorematrix[:15], scorematrix[:15]] for y in x]
            self.Longlist = [y for x in [scorematrix[15:29], scorematrix[15:29]] for y in x]
            self.Shortlist = [y for x in [scorematrix[29:], scorematrix[29:]] for y in x]
        elif len(scorematrix) == 84:
            self.HCPlist = scorematrix[0:29]
            self.Longlist = scorematrix[29:57]
            self.Shortlist = scorematrix[57:]
        else:
            print("Wrong size of score matrix!")
            exit()
    def getcorr(self, scorematrix):
        """
        Description
        ----
        To get the correlation coefficient at that specific score matrix

        Input
        ----
        scorematrix : list

        Output
        ----
        1 - correlation coefficient
        """
        self.set_scorematrix(scorematrix)
        self.scorer()
        x = np.array(self.DDS)
        y = np.array(self.score)
        return 1 - np.corrcoef(x, y)[1][0]
    def scorer(self):
        """
        Description
        ----
        To update the score list by using the specific score matrix
        """
        self.score.clear()
        for i in range(len(self.board)):
            ADD = 0
            if self.pos[i] == "NS":
                ADD += self.HCP(self.board[i].South, self.board[i].North, self.suit[i])
                ADD += self.Long(self.board[i].South, self.board[i].North, self.suit[i])
                ADD += self.Short(self.board[i].South, self.board[i].North, self.suit[i])
            else:
                ADD += self.HCP(self.board[i].West, self.board[i].East, self.suit[i])
                ADD += self.Long(self.board[i].West, self.board[i].East, self.suit[i])
                ADD += self.Short(self.board[i].West, self.board[i].East, self.suit[i])
            self.score.append(ADD)
    def HCP(self, player1, player2, suit):
        """
        Description
        ----
        To get the hand strength in a pair

        Input
        ----
        player1 : player
        player2 : player
        suit : The number to describe the trump suit

        Output
        ----
        The strength that calculated by high card point method
        """
        return self.p_HCP(player1, suit) + self.p_HCP(player2, suit)
    def p_HCP(self, player, suit):
        """
        Description
        ----
        To get the hand strength in a player

        Input
        ----
        player : player
        suit : The number to describe the trump suit

        Output
        ----
        The strength that calculated by HCPlist
        """
        ret = 0
        data = player.hand.getcard()
        for i in range(len(data)):
            for j in data[i]:
                if i == suit:
                    ret += self.HCPlist[j]
                else:
                    ret += self.HCPlist[14 + j]
        return ret
    def Long(self, player1, player2, suit):
        """
        Description
        ----
        To get the hand strength in a pair

        Input
        ----
        player1 : player
        player2 : player
        suit : The number to describe the trump suit

        Output
        ----
        The strength that calculated by long trick method
        """
        return self.p_Long(player1, suit) + self.p_Long(player2, suit)
    def p_Long(self, player, suit):
        """
        Description
        ----
        To get the hand strength in a player

        Input
        ----
        player : player
        suit : The number to describe the trump suit

        Output
        ----
        The strength that calculated by Longlist
        """
        ret = 0
        data = player.hand.distributed
        for i in range(len(data)):
            if i == suit:
                ret += self.Longlist[data[i]]
            else:
                ret += self.Longlist[14 + data[i]]
        return ret
    def Short(self, player1, player2, suit):
        """
        Description
        ----
        To get the hand strength in a pair

        Input
        ----
        player1 : player
        player2 : player
        suit : The number to describe the trump suit

        Output
        ----
        The strength that calculated by short trick method
        """
        return self.p_Short(player1, suit) + self.p_Short(player2, suit)
    def p_Short(self, player, suit):
        """
        Description
        ----
        To get the hand strength in a player

        Input
        ----
        player : player
        suit : The number to describe the trump suit

        Output
        ----
        The strength that calculated by Shortlist
        """
        ret = 0
        data = player.hand.distributed
        for i in range(len(data)):
            if i == suit:
                ret += self.Shortlist[data[i]]
            else:
                ret += self.Shortlist[14 + data[i]]
        return ret


    def loader(self, filename):
        """
        Description
        ----
        To load the data from a file

        Input
        ----
        filename : string
        """
        import Gameinfo.Game
        import sys
        sys.path.append("~/bridge/data")
        file = open(filename)
        rowdata = file.read()
        file.close()
        self.data = Gameinfo.Game.loadDDSresult(rowdata)
    def filter(self, board_size = 1000):
        """
        Description
        ----
        To filt the data that will be use to experiment and the result is store in member board and DDS

        Input
        ----
        board_size : The number to describe how much data the experiment may use
                     It is 1000 by default
                     If board_size is a list instance, the element of the list means
                     the particular number of each tricks.
        """
        import random
        tooshort = 0
        self.DDS.clear()
        self.board.clear()
        self.score.clear()
        self.suit.clear()
        self.pos.clear()
        random.shuffle(self.data)
        board_is_list = isinstance(board_size, list)
        print("board_is_list", board_is_list)
        board_size_ret = [0 for x in range(14)]
        if board_is_list == True:
            size = sum(board_size)
        else:
            size = board_size
        for i in self.data:
            if len(self.board) == size:
                break
            elif len(self.board) > size:
                while len(self.board) > board_size:
                    self.board.pop()
                    self.DDS.pop()
                    self.pos.pop()
                    self.suit.pop()
                break
            ns_maxlong = [i.longgest[0][0][0], i.longgest[0][2][0]]
            we_maxlong = [i.longgest[1][0][0], i.longgest[1][2][0]]
            for s in range(len(i.longgest[0][0])):
                if i.longgest[0][2][s] > ns_maxlong[1]:
                    ns_maxlong = [i.longgest[0][0][s], i.longgest[0][2][s]]
            for s in range(len(i.longgest[1][0])):
                if i.longgest[1][2][s] > we_maxlong[1]:
                    we_maxlong = [i.longgest[1][0][s], i.longgest[1][2][s]]
            ns_suit = ns_maxlong[0]
            ns_len = i.longgest[0][1]
            ns_ddswin = ns_maxlong[1]
            we_suit = we_maxlong[0]
            we_len = i.longgest[1][1]
            we_ddswin = we_maxlong[1]
            if ns_len < 7 and i.South.hand.distributed[ns_suit] < 6 and i.North.hand.distributed[ns_suit] < 6 or ns_ddswin < 7:
                tooshort += 1
            elif board_is_list != True or board_size[ns_ddswin] > board_size_ret[ns_ddswin]:
                self.board.append(i)
                self.suit.append(ns_suit)
                self.DDS.append(ns_ddswin)
                self.pos.append("NS")
                board_size_ret[ns_ddswin] += 1
            if we_len < 7 and i.West.hand.distributed[we_suit] < 6 and i.East.hand.distributed[we_suit] < 6 or we_ddswin < 7:
                tooshort += 1
            elif board_is_list != True or board_size[we_ddswin] > board_size_ret[we_ddswin]:
                self.board.append(i)
                self.suit.append(we_suit)
                self.DDS.append(we_ddswin)
                self.pos.append("WE")
                board_size_ret[we_ddswin] += 1
        print("Distribute of tricks: ", board_size_ret)
        for i in range(7, 14):
            print(i, "tricks have ", board_size_ret[i], "times")
    def makedatasetforC(self, filename):
        """
            Make the data set file that C++ can use
        """
        f = open("./data/" + filename, "w")
        for i in range(len(self.board)):
            s = ""
            if self.pos[i] == "WE":
                s += handtostring(self.board[i].East) + " " + handtostring(self.board[i].West) + " " + str(self.DDS[i]) + " " + str(self.suit[i]) + " 0\n"
            else:
                s += handtostring(self.board[i].South) + " " + handtostring(self.board[i].North) + " " + str(self.DDS[i]) + " " + str(self.suit[i]) + " 0\n"
            f.write(s)
        f.close()

    def makedatasetforC_showdata(self, filename):
        """
            Make the data set file that C++ can use
        """
        f = open("./data/" + filename, "w")
        for i in range(len(self.board)):
            s = ""
            if self.pos[i] == "WE":
                s += handtostring(self.board[i].East) + " " + handtostring(self.board[i].West) + " " + str(self.DDS[i]) + " " + str(self.suit[i]) + " 0\n"
                s += handtostring(self.board[i].South) + " " + handtostring(self.board[i].North) + " " + str(13 - self.DDS[i]) + " " + str(self.suit[i]) + " 0\n"
            else:
                s += handtostring(self.board[i].South) + " " + handtostring(self.board[i].North) + " " + str(self.DDS[i]) + " " + str(self.suit[i]) + " 0\n"
                s += handtostring(self.board[i].East) + " " + handtostring(self.board[i].West) + " " + str(13 - self.DDS[i]) + " " + str(self.suit[i]) + " 0\n"
            f.write(s)
        f.close()


class TestObj(unittest.TestCase):
    def setUp(self):
        sys.path.append("~/bridge/data")
        self.obj = corrobj()
        self.obj.loader("data/test")
        self.obj.filter()
    def test_pos(self):
        self.assertEqual(self.obj.pos[0], "NS")
        self.assertEqual(self.obj.pos[1], "WE")
        self.assertEqual(self.obj.pos[2], "WE")
        self.assertEqual(self.obj.pos[3], "WE")
        self.assertEqual(self.obj.pos[4], "NS")
        self.assertEqual(self.obj.pos[5], "NS")
        self.assertEqual(self.obj.pos[6], "WE")
        self.assertEqual(self.obj.pos[7], "NS")
        self.assertEqual(self.obj.pos[8], "WE")
    def test_board(self):
        self.assertEqual(self.obj.board[0], self.obj.data[0])
        self.assertEqual(self.obj.board[1], self.obj.data[0])
        self.assertEqual(self.obj.board[2], self.obj.data[1])
        self.assertEqual(self.obj.board[3], self.obj.data[2])
        self.assertEqual(self.obj.board[4], self.obj.data[3])
        self.assertEqual(self.obj.board[5], self.obj.data[4])
        self.assertEqual(self.obj.board[6], self.obj.data[4])
        self.assertEqual(self.obj.board[7], self.obj.data[5])
        self.assertEqual(self.obj.board[8], self.obj.data[5])
    def test_suit(self):
        self.assertEqual(self.obj.suit[0], 3)
        self.assertEqual(self.obj.suit[1], 0)
        self.assertEqual(self.obj.suit[2], 2)
        self.assertEqual(self.obj.suit[3], 2)
        self.assertEqual(self.obj.suit[4], 3)
        self.assertEqual(self.obj.suit[5], 1)
        self.assertEqual(self.obj.suit[6], 0)
        self.assertEqual(self.obj.suit[7], 0)
        self.assertEqual(self.obj.suit[8], 3)

    def test_DDS(self):
        self.assertEqual(self.obj.DDS[0], 7.5)
        self.assertEqual(self.obj.DDS[1], 9)
        self.assertEqual(self.obj.DDS[2], 11)
        self.assertEqual(self.obj.DDS[3], 9)
        self.assertEqual(self.obj.DDS[4], 10)
        self.assertEqual(self.obj.DDS[5], 11)
        self.assertEqual(self.obj.DDS[6], 7)
        self.assertEqual(self.obj.DDS[7], 8)
        self.assertEqual(self.obj.DDS[8], 8)
    def test_HCP(self):
        f = open("data/HCPanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        for i in range(len(self.obj.data)):
            self.assertEqual(self.obj.p_HCP(self.obj.data[i].South, 0), answer[i][0])
            self.assertEqual(self.obj.p_HCP(self.obj.data[i].North, 0), answer[i][1])
            self.assertEqual(self.obj.p_HCP(self.obj.data[i].West, 0), answer[i][2])
            self.assertEqual(self.obj.p_HCP(self.obj.data[i].East, 0), answer[i][3])
    def test_Long(self):
        f = open("data/Longanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        rowlong = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                rowlong[i].append(float(j))
        f = open("data/HCPanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        rowHCP = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                rowHCP[i].append(float(j))
        answer = [[] for x in range(6)]
        for i in range(len(rowHCP)):
            for j in range(len(rowHCP[i])):
                answer[i].append(rowlong[i][j] - rowHCP[i][j])
        for i in range(len(self.obj.data)):
            self.assertEqual(self.obj.p_Long(self.obj.data[i].South, 0), answer[i][0])
            self.assertEqual(self.obj.p_Long(self.obj.data[i].North, 0), answer[i][1])
            self.assertEqual(self.obj.p_Long(self.obj.data[i].West, 0), answer[i][2])
            self.assertEqual(self.obj.p_Long(self.obj.data[i].East, 0), answer[i][3])
    def test_Short(self):
        f = open("data/Shortanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        rowshort = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                rowshort[i].append(float(j))
        f = open("data/HCPanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        rowHCP = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                rowHCP[i].append(float(j))
        answer = [[] for x in range(6)]
        for i in range(len(rowHCP)):
            for j in range(len(rowHCP[i])):
                answer[i].append(rowshort[i][j] - rowHCP[i][j])
        for i in range(len(self.obj.data)):
            self.assertEqual(self.obj.p_Short(self.obj.data[i].South, 0), answer[i][0])
            self.assertEqual(self.obj.p_Short(self.obj.data[i].North, 0), answer[i][1])
            self.assertEqual(self.obj.p_Short(self.obj.data[i].West, 0), answer[i][2])
            self.assertEqual(self.obj.p_Short(self.obj.data[i].East, 0), answer[i][3])
    def test_scorer(self):
        answer = []
        for i in range(len(self.obj.board)):
            if self.obj.pos == "NS":
                answer.append(self.obj.HCP(self.obj.board[i].North, self.obj.board[i].South, 0)\
                        + self.obj.Long(self.obj.board[i].North, self.obj.board[i].South, 0)\
                        + self.obj.Short(self.obj.board[i].North, self.obj.board[i].South, 0))
            else:
                answer.append(self.obj.HCP(self.obj.board[i].West, self.obj.board[i].East, 0)\
                        + self.obj.Long(self.obj.board[i].West, self.obj.board[i].East, 0)\
                        + self.obj.Short(self.obj.board[i].West, self.obj.board[i].East, 0))
        self.obj.scorer()
        for i in range(len(self.obj.board)):
            self.assertEqual(self.obj.score[i], answer[i])


def cardtostring(card):
    if card == 1:
        return "A"
    elif card == 13:
        return "K"
    elif card == 12:
        return "Q"
    elif card == 11:
        return "J"
    elif card == 10:
        return "T"
    else:
        return str(card)

def handtostring(player):
    s = ""
    count = 1
    for i in player.hand.getcard():
        for j in i:
            s += cardtostring(j)
        if count < 4:
            s += "."
        count += 1
    return s

def stdoutreadint(process):
    ret = process.stdout.readline()
    try:
        return float(str(ret)[2:-3])
    except:
        return str(ret)
    return float(str(ret)[2:-3])

def listtostdin(l):
    s = str(l[0])
    for i in l[1:]:
        s += " " + str(i)
    s += "\n"
    return s
def shufflelist(l):
    import random
    random.shuffle(l)
def makeDATASET(l, size = 1000):
    shufflelist(l)
    f = open("./data/dataForCofsection42", "w")
    for i in range(min(size, len(l))):
        f.write(l[i] + '\n')
    f.close()
def makeCalledDATASET(l, size = 1000):
    shufflelist(l)
    f = open("./data/dataForCofsection42", "a")
    for i in range(min(size, len(l))):
        f.write(l[i] + '\n')
    f.close()
def read(filename):
    l = []
    file = open(filename)
    for line in file.readlines():
        line = line.strip()
        l.append(line)
    file.close()
    return l

def listtostdin2(l):
    s = str(l[0])
    for i in l[1:]:
        s += " " + str(i)
    s += "\n"
    return s

def objf(P, l):
    s = listtostdin2(l)
    P.stdin.write(s.encode())
    P.stdin.flush()
    return stdoutreadint(P)

def main():
    import Gameinfo.GA_s4_4 as GA
    import Gameinfo.parser as ps
    import numpy
    from subprocess import Popen, PIPE
    import statistics as stat
    HCPSize = [0, 11, 5]
    HCP_name = ['', '$HT$', '$H$']
    HCP_ub = [[], [4 for x in range(11)], [4 for x in range(5)]]
    HCP_lb = [[], [0 for x in range(11)], [0 for x in range(5)]]
    suitHCPSize = [0, 4]
    suitHCP_name = ['', '$sH$']
    suitHCP_ub = [[], [4 for x in range(4)]]
    suitHCP_lb = [[], [0 for x in range(4)]]
    distriSize = [0, 28, 6]
    distri_name = ['', '$LS$', '$D$']
    dis_ub = [[], [4 for x in range(28)], [4 for x in range(6)]]
    dis_lb = [[], [0 for x in range(28)], [0 for x in range(6)]]
    longSize = [0, 4, 6, 6, 2]
    long_name = ['', '$L$', '$L_4$', '$L^*$', '$TL$']
    long_ub = [[], [4 for x in range(4)], [4 for x in range(6)], [4 for x in range(6)], [4 for x in range(2)]]
    long_lb = [[], [0 for x in range(4)], [0 for x in range(6)], [0 for x in range(6)], [0 for x in range(2)]]
    shortSize = [0, 4, 6, 6, 3]
    short_name = ['', '$S$', '$DS$', '$S^*$', '$NT$']
    short_ub = [[], [4 for x in range(4)], [4 for x in range(6)], [4 for x in range(6)], [4 for x in range(3)]]
    short_lb = [[], [0 for x in range(4)], [0 for x in range(6)], [0 for x in range(6)], [0 for x in range(3)]]
    called_HCP = ['', '$cH$']
    called_HCP_size = [0, 24]
    called_short = ['', '$cS$']
    cH_ub = [[], [4 for x in range(24)]]
    cH_lb = [[], [-4 for x in range(24)]]
    called_short_size = [0, 12]
    cS_ub = [[], [4 for x in range(12)]]
    cS_lb = [[], [-4 for x in range(12)]]
    called_dis = ['', '$cD$']
    called_dis_size = [0, 12]
    cD_ub = [[], [4 for x in range(12)]]
    cD_lb = [[], [-4 for x in range(12)]]
    called_long = ['', '$cL$']
    called_long_size = [0, 8]
    cL_ub = [[], [4 for x in range(8)]]
    cL_lb = [[], [-4 for x in range(8)]]
    Original_HCP = [0, 0, 1, 2, 3]
    Original_long = [1, 4]
    Original_short = [3, 2, 1, 3, 2, 1]
    Original_dis = [3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    data = read("./data/wholeStaticForC")
    data_called = read("./data/EastOpened.txt.tmp")
    Train_target = ["44002", "34002", "24002", "14002", "04202", "00202", "44202", "03002", "14012", "40202", "40001", "24012", "34012", "43002", "13002", "44012", "34202", "20202", "30202", "10202", "03202", "23002", "33002", "44001", "04212"]

    Trained_cp = [1, 1, 1, 0.8, 1, 0.8, 1, 1, 1, 1, 0.8, 1, 1, 0.8, 1, 0.8, 1, 0.8, 1, 0.8, 0.8, 0.8, 1, 1, 0.08]
    Trained_mp = [0.03, 0.02, 0.02, 0.05, 0.05, 0.04, 0.05, 0.01, 0.03, 0.05, 0.05, 0.04, 0.05, 0.05, 0.04, 0.01, 0.02, 0.03, 0.05, 0.03, 0.04, 0.03, 0.05, 0.05, 0.03]
    Trained_keep = [3, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 4, 3, 4, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4]
    convergence_curve = [[] for x in range(6)]

    for _formulaid in range(len(Train_target)):
        formulaid = Train_target[_formulaid]
        best_para = []
        best_hyper = [0, 0, 0]
        # best_corr = [Best, Worse, Mean, Median, Stdev]
        best_corr = [0, 0, 0, 0, 0]
        best = 0
        H = int(formulaid) % 10
        sH = int(formulaid) // 10 % 10
        D = int(formulaid) // 100 % 10
        L = int(formulaid) // 1000 % 10
        S = int(formulaid) // 10000 % 10
        para_size = HCPSize[H] + suitHCPSize[sH] + distriSize[D] + longSize[L] + shortSize[S]
        ub = HCP_ub[H] + suitHCP_ub[sH] + dis_ub[D] + long_ub[L] + short_ub[S]
        lb = HCP_lb[H] + suitHCP_lb[sH] + dis_lb[D] + long_lb[L] + short_lb[S]
        para_name = HCP_name[H]
        if sH > 0:
            if len(para_name) > 0:
                para_name += " + "
            para_name += suitHCP_name[1]
        if D > 0:
            if len(para_name) > 0:
                para_name += " + "
            para_name += distri_name[D]
        if L > 0:
            if len(para_name) > 0:
                para_name += " + "
            para_name += long_name[L]
        if S > 0:
            if len(para_name) > 0:
                para_name += " + "
            para_name += short_name[S]
        for _H in range(2):
            for _S in range(2):
                for _D in range(2):
                    for _L in range(2):
                        if _H == 0 and _S == 0 and _D == 0 and _L == 0:
                            continue
                        final_formulaid = str(_L) + str(_D) + str(_S) + str(_H) + formulaid
                        final_para_size = para_size + called_HCP_size[_H] + called_short_size[_S] + called_dis_size[_D] + called_long_size[_L]
                        final_para_name = para_name
                        final_ub = ub.copy()
                        final_lb = lb.copy()
                        trained_corr = []
                        if _H > 0:
                            final_para_name += " + " + called_HCP[_H]
                            final_ub += cH_ub[_H]
                            final_lb += cH_lb[_H]
                        if _S > 0:
                            final_para_name += " + " + called_short[_S]
                            final_ub += cS_ub[_S]
                            final_lb += cS_lb[_S]
                        if _D > 0:
                            final_para_name += " + " + called_dis[_D]
                            final_ub += cD_ub[_D]
                            final_lb += cD_lb[_D]
                        if _L > 0:
                            final_para_name += " + " + called_long[_L]
                            final_ub += cL_ub[_L]
                            final_lb += cL_lb[_L]
                        print("final para name:", final_para_name, file=sys.stderr)
                        print("final formula id:", final_formulaid, file=sys.stderr)
                        print("size of ub:", len(final_ub), file=sys.stderr)
                        print("size of lb:", len(final_lb), file=sys.stderr)
                        print("final para size:", final_para_size, file=sys.stderr)
                        checkerProcess_train = Popen(['./test', final_formulaid, "./data/called_and_ignore_data"], stdin=PIPE, stdout=PIPE)
                        for _i in range(30):
                            makeDATASET(data, 100)
                            makeCalledDATASET(data_called, 100)
                            bestScore, best_para, iters, curve = GA.GA(GA.ObjfCorr, final_lb, final_ub, final_para_size, 50, 1000, True, final_formulaid, Trained_cp[_formulaid], Trained_mp[_formulaid], Trained_keep[_formulaid])
                            tmp_corr = objf(checkerProcess_train, best_para)
                            trained_corr.append(tmp_corr)
                        print(final_para_name, round(max(trained_corr), 3), round(min(trained_corr), 3), round(stat.mean(trained_corr), 3), round(stat.median(trained_corr), 3), round(stat.stdev(trained_corr), 3), sep=" & ", end="\\\\\hline\n")
                        checkerProcess_train.terminate()


#        GA.GA(C.getcorr, 0, 1, 42, 50, 1000, False)
#    for k in range(10):
#        print("Turn: ", k + 1)
#        C.filter(5000)
    ### for calculate the correlation coefficient of result of GA.
#    C.filter(2 * len(C.data))
#    f = open("data/GA84result")
#    rowdata = f.read()
#    f.close()
#    matrix = rowdata.splitlines()
#    scorematrix = []
#    for i in range(len(matrix)):
#        scorematrix.append(float(matrix[i]))
#    print(1 - C.getcorr(scorematrix))
#    thousand = []
#    five = []
#    unittest.main()
#    for i in range(20):
#        print("Expression of 84 argument at ", i, "turn")
#        C.filter(5000)
#        GA.GA(C.getcorr, 0, 1, 84, 50, 1000)
#    for i in range(20):
#        print("Expression of 42 argument at ", i, "turn")
#        C.filter(5000)
#        GA.GA(C.getcorr, 0, 1, 42, 50, 1000)
#    for i in range(1000):
#        print("Calculating the", i, "-th correlation coefficient in 1000 random games.")
#        C.filter(1000)
#        C.scorer()
#        x = numpy.array(C.DDS)
#        y = numpy.array(C.score)
#        thousand.append(np.corrcoef(x, y)[0][1])
#    for i in range(1000):
#        print("Calculating the", i, "-th correlation coefficient in 5000 random games.")
#        C.filter(5000)
#        C.scorer()
#        x = np.array(C.DDS)
#        y = np.array(C.score)0.5723 0.6518 1.214 1.725 2.626 1.42 1.449 0.0234 0.2352 0.5945 2.699 3.409 1.083 0.8197 0.1542 2.555 1.669
#        five.append(np.corrcoef(x, y)[0][1])
#    print("The standard deviation of a thousand correlation coefficients calculated from one thousand data", np.std(thousand, ddof=1))
#    print("The standard deviation of a thousand correlation coefficients calculated from five thousand data", np.std(five, ddof=1))
#    print("The standard deviation of two thousand correlation coefficients calculated from five thousand data and one thousand data respectively", np.std([*five, *thousand], ddof=1))
def listtostdin(l):
    s = str(round(l[0], 4))
    for i in l[1:]:
        s += " " + str(round(i, 4))
    s += "\n"
    return s
def runSubprocess(P, l):
    s = listtostdin(l)
    P.stdin.write(s.encode())
    P.stdin.flush()
    stdoutreadline(P)
def stdoutreadline(P):
    ret = P.stdout.readline()
    i = str(ret)
    print(i[2:-3])
    while i[2] != "-":
        if i == '':
            break;
        ret = P.stdout.readline()
        i = str(ret)
        print(i[2:-3])

if __name__ == "__main__":
    main()
