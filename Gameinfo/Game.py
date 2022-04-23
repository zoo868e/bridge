class Hand():
    def __init__(self, card):
        card[0].sort()
        card[1].sort()
        card[2].sort()
        card[3].sort()
        self.spade = card[0]
        self.heart = card[1]
        self.diamond = card[2]
        self.club = card[3]
        self.distributed = [len(self.spade), len(self.heart), len(self.diamond), len(self.club)]
    def getcard(self):
        return [self.spade, self.heart, self.diamond, self.club]
class Player():
    def __init__(self, Hand, position):
        self.position = position
        self.hand = Hand
    def getplayer(self):
        return [self.position, self.hand.getcard()]
class Game():
    def __init__(self, South, West, North, East, DDSresult):
        self.South = South
        self.West = West
        self.North = North
        self.East = East
        self.DDSresult = DDSresult
        self.SouthDDS = DDSresult[0]
        self.NorthDDS = DDSresult[1]
        self.WestDDS = DDSresult[2]
        self.EastDDS = DDSresult[3]
        # longgest = [[NS longgest suit, NS longgest suit length, NS longgest suit win tricks], [WE longgest suit, WE longgest suit length, WE longgest suit win tricks]]
        self.longgest = self.long()
    def getgame(self):
        return [self.South.getplayer(), self.North.getplayer(), self.West.getplayer(), self.East.getplayer(), self.DDSresult]
    def getplayer(self):
        return [self.South, self.North, self.West, self.East]
    def long(self):
        suit = [[], []]
        l = [-1, -1]
        ddswin = [[], []]
        s = self.South.hand.distributed
        w = self.West.hand.distributed
        n = self.North.hand.distributed
        e = self.East.hand.distributed
        for i in range(4):
            sn = s[i] + n[i]
            we = w[i] + e[i]
            if sn > l[0]:
                l[0] = sn
                suit[0].clear()
                suit[0].append(i)
                ddswin[0].clear()
                ddswin[0].append(max(self.SouthDDS[i], self.NorthDDS[i]))
            elif sn == l[0]:
                ddswin[0].append(max(self.SouthDDS[i], self.NorthDDS[i]))
                suit[0].append(i)
            if we > l[1]:
                l[1] = we
                suit[1].clear()
                suit[1].append(i)
                ddswin[1].clear()
                ddswin[1].append(max(self.WestDDS[i], self.EastDDS[i]))
            elif we == l[1]:
                ddswin[1].append(max(self.WestDDS[i], self.EastDDS[i]))
                suit[1].append(i)
        return [[suit[0], l[0], ddswin[0]], [suit[1], l[1], ddswin[1]]]



def loadDDSresult(rowdata):
    data = rowdata.split("\n")
    board = []
    for i in data:
        if i == '':
            continue
#        try:
#            card, DDSresult = i.split("|")
#            s, n, w, e = reusecard(card.split(":")[1])
#            DDS = loadres(DDSresult)
#            South = Player(Hand(s.copy()), "South")
#            North = Player(Hand(n.copy()), "North")
#            West = Player(Hand(w.copy()), "West")
#            East = Player(Hand(e.copy()), "East")
#            board.append(Game(South, West, North, East, DDS.copy()))
#        except:
#            print(i)
        card, DDSresult = i.split("|")
        s, n, w, e = reusecard(card.split(":")[1])
        DDS = loadres(DDSresult)
        South = Player(Hand(s.copy()), "South")
        North = Player(Hand(n.copy()), "North")
        West = Player(Hand(w.copy()), "West")
        East = Player(Hand(e.copy()), "East")
        board.append(Game(South, West, North, East, DDS.copy()))
    return board

def reusecard(rowdata):
    data = rowdata.split(" ")
    #return data order = South, North, West, East
    return [Transcard(data[2]), Transcard(data[0]), Transcard(data[3]), Transcard(data[1])]

def Transcard(card):
    ret = [[] for x in range(4)]
    suitcard = card.split(".")
    for i in range(4):
        for c in suitcard[i]:
            ret[i].append(suitformat(c))
    return ret.copy()

def suitformat(card):
    if card == 'A':
        return 1
    if card == 'T':
        return 10
    if card == 'J':
        return 11
    if card == 'Q':
        return 12
    if card == 'K':
        return 13
    return int(card)

# return DDS win record in s, w, e, n order
# and every suit = [Spade, Heart, Diamond, Club, NT]
def loadres(DDSresult):
    import ast
    South = []
    North = []
    West = []
    East = []
    ret = [[] for x in range(5)]
    res = DDSresult.split("@")
    for i in range(len(res)):
        data = res[i].split(",")
        South.append(ast.literal_eval(data[2]))
        North.append(ast.literal_eval(data[0]))
        East.append(ast.literal_eval(data[1]))
        West.append(ast.literal_eval(data[3]))
    return [South, North, West, East]

if __name__ == '__main__':
    import sys
    sys.path.append("~/bridge/data")
    file = open("data/test")
    rowdata = file.read()
    file.close()
    board = loadDDSresult(rowdata)
    print("end load")
    for j in range(len(board)):
        for i in board[j].getgame():
            print(i)
        print(board[j].longgest)
