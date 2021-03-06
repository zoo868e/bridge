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
        """
        import random
        tooshort = 0
        self.DDS.clear()
        self.board.clear()
        self.score.clear()
        self.pos.clear()
        random.shuffle(self.data)
        for i in self.data:
            if len(self.board) == board_size:
                break
            elif len(self.board) > board_size:
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
            else:
                self.board.append(i)
                self.suit.append(ns_suit)
                self.DDS.append(ns_ddswin)
                self.pos.append("NS")
            if we_len < 7 and i.West.hand.distributed[we_suit] < 6 and i.East.hand.distributed[we_suit] < 6 or we_ddswin < 7:
                tooshort += 1
            else:
                self.board.append(i)
                self.suit.append(we_suit)
                self.DDS.append(we_ddswin)
                self.pos.append("WE")
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
    def makedataofgameforC(self, filename):
        f = open("./data/" + filename, "w")
        for i in range(len(self.board)):
            s = ""
            s += handtostring(self.board[i].North) + " " + handtostring(self.board[i].East) + " " + handtostring(self.board[i].South) + " " + handtostring(self.board[i].West) + " " + str(self.DDS[i]) + " " + str(self.suit[i]) + " "  + self.pos[i] + "\n"
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
    if i[2] != "-":
        stdoutreadline(P)

def main():
    import Gameinfo.GA_v_Fourguys as GA
    import Gameinfo.parser as ps
    import numpy
    import time
    import os
    from subprocess import Popen, PIPE
    C = corrobj()
    filename = "testPartialGame";
    C.loader("data/DDSresult.txt")
    best = 0
    process = Popen(['./check_whole_corr_Fixed', '2'], stdin=PIPE, stdout=PIPE)
    folder = str(time.time())
    os.mkdir('data/' + folder)
    for i in range(1, 6):
        for j in range(1, 20):
            start_time = str(time.time())
            filename = folder + '/.' + start_time
            C.filter(i * 1000)
            C.makedataofgameforC(filename)
            print("Turn:", j, "\nHave", i * 1000, "datas")
            tmp = GA.GA(GA.ObjfCorr, 0, 4, 10, 50, 100, True, best, 2, filename)
            check_in = tmp[1]
            process.stdin.write(listtostdin(check_in).encode())
            process.stdin.flush()
            print("The coefficient correlation of whole data: ", end = "")
            print(stdoutreadint(process))

if __name__ == "__main__":
    main()
