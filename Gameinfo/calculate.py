import numpy as np
import math
#[HCP name, SuitHCP[spade, heart, diamond, club], NTHCP[spade, heart, diamond, club]]
basicHCP = ["basic",
        [[0,4,0,0,0,0,0,0,0,0,0,1,2,3],
            [0,4,0,0,0,0,0,0,0,0,0,1,2,3],
            [0,4,0,0,0,0,0,0,0,0,0,1,2,3],
            [0,4,0,0,0,0,0,0,0,0,0,1,2,3]],
        [[0,4,0,0,0,0,0,0,0,0,0,1,2,3],
            [0,4,0,0,0,0,0,0,0,0,0,1,2,3],
            [0,4,0,0,0,0,0,0,0,0,0,1,2,3],
            [0,4,0,0,0,0,0,0,0,0,0,1,2,3]]]
#[spade, heart, diamond, club]
basicLONG = [[[0,0,0,0,0,1,2,3,4,5,6,7,8,9], [0,0,0,0,0,1,2,3,4,5,6,7,8,9], [0,0,0,0,0,1,2,3,4,5,6,7,8,9], [0,0,0,0,0,1,2,3,4,5,6,7,8,9]],\
        [[0,0,0,0,0,1,2,3,4,5,6,7,8,9], [0,0,0,0,0,1,2,3,4,5,6,7,8,9], [0,0,0,0,0,1,2,3,4,5,6,7,8,9], [0,0,0,0,0,1,2,3,4,5,6,7,8,9]]]
#[spade, heart, diamond, club]
basicSHORT = [[[3,2,1,0,0,0,0,0,0,0,0,0,0,0], [3,2,1,0,0,0,0,0,0,0,0,0,0,0], [3,2,1,0,0,0,0,0,0,0,0,0,0,0], [3,2,1,0,0,0,0,0,0,0,0,0,0,0]], \
        [[3,2,1,0,0,0,0,0,0,0,0,0,0,0], [3,2,1,0,0,0,0,0,0,0,0,0,0,0], [3,2,1,0,0,0,0,0,0,0,0,0,0,0], [3,2,1,0,0,0,0,0,0,0,0,0,0,0]]]

def listadd(list1, list2):
    return [sum(x) for x in zip(list1, list2)]

def getcurr(DDS, score):
    x = np.array(DDS)
    y = np.array(score)
    ret = np.corrcoef(x, y)
    return ret[1][0]


# the structure of result in Calculator is [Spade, Heart, Diamond, Club, NT]
class Calculator():
    def __init__(self, HCPlist = basicHCP, Longlist = basicLONG, Shortlist = basicSHORT):
        self.HCPname = HCPlist[0]
        self.HCPlist = HCPlist[1:]
        self.Longlist = Longlist
        self.Shortlist = Shortlist
        self.south = []
        self.north = []
        self.west = []
        self.east = []
        self.ns = []
        self.we = []

    def getscore(self):
        S = self.south.copy()
        S.insert(0, "South score:")
        N = self.north.copy()
        N.insert(0, "North score:")
        W = self.west.copy()
        W.insert(0, "West score:")
        E = self.east.copy()
        E.insert(0, "East score:")
        NS = self.ns.copy()
        NS.insert(0, "NS score:")
        WE = self.we.copy()
        WE.insert(0, "WE score:")
        return [S, N, W, E, NS, WE]
    def setHCPlist(self, HCPlist):
        self.HCPname = HCPlist[0]
        self.HCPlist = HCPlist[1:]

    def setLonglist(self, Longlist):
        self.Longlist = Longlist

    def setShortlist(self, Shortlist):
        self.Shortlist = Shortlist

    def HCP(self, Game):
        self.south = self.p_HCP(Game.South)
        self.west = self.p_HCP(Game.West)
        self.north = self.p_HCP(Game.North)
        self.east = self.p_HCP(Game.East)
        self.ns = listadd(self.south, self.north)
        self.we = listadd(self.west, self.east)

    # return the HCP in every contracts
    def p_HCP(self, player):
        ret = []
        data = player.hand.getcard()
        for suit in range(5):
            r = 0
            for i in range(len(data)):
                for j in data[i]:
                    if i == suit:
                        r += self.HCPlist[0][i][j]
                    else:
                        r += self.HCPlist[1][i][j]
            ret.append(r)
        return ret.copy()
    def Long(self, Game):
        self.south = self.p_Long(Game.South)
        self.west = self.p_Long(Game.West)
        self.north = self.p_Long(Game.North)
        self.east = self.p_Long(Game.East)
        self.ns = listadd(self.south, self.north)
        self.we = listadd(self.west, self.east)
    def p_Long(self, player):
        ret = self.p_HCP(player)
        data = player.hand.getcard()
        for suit in range(5):
            r = 0
            for i in range(len(data)):
                if i == suit:
                    r += self.Longlist[0][i][len(data[i])]
                else:
                    r += self.Longlist[1][i][len(data[i])]
            ret[suit] += r
        return ret
    def Short(self, Game):
        self.south = self.p_Short(Game.South)
        self.west = self.p_Short(Game.West)
        self.north = self.p_Short(Game.North)
        self.east = self.p_Short(Game.East)
        self.ns = listadd(self.south, self.north)
        self.we = listadd(self.west, self.east)
    def p_Short(self, player):
        ret = self.p_HCP(player)
        data = player.hand.getcard()
        for suit in range(5):
            r = 0
            for i in range(len(data)):
                if i == suit:
                    r += self.Shortlist[0][i][len(data[i])]
                else:
                    r += self.Shortlist[1][i][len(data[i])]
            ret[suit] += r
        return ret
    def Loser(self, Game):
        self.south = self.p_Loser(Game.South)
        self.west = self.p_Loser(Game.West)
        self.north = self.p_Loser(Game.North)
        self.east = self.p_Loser(Game.East)
        self.ns = listadd(self.south, self.north)
        self.we = listadd(self.west, self.east)
    def p_Loser(self, player):
        ret = []
        data = player.hand.getcard()
#        print(player.position)
        for suit in range(5):
            r = 0
            for i in range(len(data)):
                re = 0
                l = len(data[i])
                if l == 1:
                    re = 1
                    if 1 in data[i]:
                        re = 0
                elif l == 2:
                    re = 2
                    if 13 in data[i]:
                        re -= 1
                    if 1 in data[i]:
                        re -= 1
                elif l != 0:
                    re = 3
                    biggest = []
                    if 1 in data[i]:
                        biggest.append(1)
                    if 13 in data[i]:
                        biggest.append(13)
                    if 12 in data[i]:
                        biggest.append(12)
                    lenb = len(biggest)
                    if lenb == 1 and biggest[0] == 12 and 11 in data[i]:
                        biggest.append(11)
                        lenb += 1
                    if lenb == 1:
                        if biggest[0] == 12:
                            re = 2.5
                        else:
                            re = 2
                    elif lenb == 2:
                        if biggest[0] != 12:
                            re = 1
                        else:
                            re = 2
                    elif lenb == 3:
                        re = 0
#                print("re = ", re)
                r += re
            ret.append(12 - r)
#            print("End suit")
        return ret
    def Pavlicek(self, Game):
        self.south = self.p_Pavlicek(Game.South)
        self.west = self.p_Pavlicek(Game.West)
        self.north = self.p_Pavlicek(Game.North)
        self.east = self.p_Pavlicek(Game.East)
        self.ns = listadd(self.south, self.north)
        self.we = listadd(self.west, self.east)
    def p_Pavlicek(self, player):
        ret = []
        data = player.hand.getcard()
        for suit in range(5):
            r = 0
            AT = 0
            for i in range(len(data)):
                H = 0
                S = 0
                if 1 in data[i]:
                    AT += 1
                if 10 in data[i]:
                    AT += 1
                if i == suit:
                    S = self.Shortlist[0][i][len(data[i])]
                    H = 0
                    for j in data[i]:
                        H += self.HCPlist[0][i][j]
                else:
                    S = self.Shortlist[1][i][len(data[i])]
                    H = 0
                    for j in data[i]:
                        H += self.HCPlist[1][i][j]
                if H > S:
                    r += H
                else:
                    r += S
            if AT >= 4:
                r += 1
            ret.append(r)
        return ret


if __name__ == "__main__":
    import parser as ps
    import Game as Game
    import sys
    # Add the data folder to path
    sys.path.append("~/bridge/data")
    # import the score matrix
    scorematrix = ps.parse_score_matrix_file("data/score_matrix.txt")
    # Load the data
    f = open("data/test")
    rowdata = f.read()
    f.close()
    board = Game.loadDDSresult(rowdata)
    cal = Calculator(HCPlist = scorematrix[2])
    print(cal.HCPname)
    cal.HCP(board[0])
    print(cal.getscore())
    cal.setHCPlist(scorematrix[0])
    print(cal.HCPname)
    cal.HCP(board[0])
    print(cal.getscore())
