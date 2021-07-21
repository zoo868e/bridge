import Gameinfo.calculate as Gamefunc
import Gameinfo.Game as Game
# calculate the correlation coefficient during Suit contract
def LongestSuit20210715(board, calculator, func, fname):
    DDS = []
    score = []
    print("LongestSuit20210715")
    for f in range(len(func)):
        DDS.clear()
        score.clear()
        print(fname[f])
        tooshort = 0
        l = 0
        correct = 0
        one = 0
        two = 0
        for i in board:
            func[f](i)
            ns_suit = i.longgest[0][0]
            ns_len = i.longgest[0][1]
            ns_ddswin = i.longgest[0][2]
            we_suit = i.longgest[1][0]
            we_len = i.longgest[1][1]
            we_ddswin = i.longgest[1][2]
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
        print('{:^.4f}'.format(Gamefunc.getcurr(DDS, score)))


# calculate the correlation coefficient during NT contract
def NT20210715(board, calculator, func, fname):
    DDS = []
    score = []
    print("NT")
    for f in range(len(func)):
        DDS.clear()
        score.clear()
        print(fname[f])
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
        print('{:^.4f}'.format(Gamefunc.getcurr(DDS, score)))

if __name__=="__main__":
    f = open("test")
    rowdata = f.read()
    f.close()
    NT_neural = [[0, 3.975, 0.342, 0.340, 0.347, 0.341, 0.356, 0.380, 0.358, 0.496, 0.660, 1.047, 1.676, 2.643],[0, 3.971, 0.327, 0.334, 0.314, 0.332, 0.349, 0.331, 0.361, 0.469, 0.663, 1.032, 1.688, 2.643, 3.971], [0, 3.966, 0.329, 0.328, 0.351, 0.341, 0.339, 0.354, 0.375, 0.461, 0.671, 1.056, 1.675, 2.677], [0, 3.989, 0.342, 0.353, 0.345, 0.344, 0.329, 0.356, 0.400, 0.473, 0.684, 1.030, 1.656, 2.655]]
    Suit_neural = [[0, 3.982, 1.660, 1.664, 1.669, 1.660, 1.684, 1.680, 1.709, 1.782, 1.921, 2.174, 2.569, 3.207], [0, 3.984, 1.670, 1.667, 1.655, 1.673, 1.685, 1.684, 1.719, 1.791, 1.916, 2.167, 2.569, 3.210, 3.984], [0, 3.973, 1.668, 1.663, 1.669, 1.676, 1.680, 1.687, 1.718, 1.780, 1.918, 2.177, 2.572, 3.220], [0, 3.995, 1.667, 1.660, 1.685, 1.663, 1.688, 1.697, 1.723, 1.783, 1.938, 2.172, 2.565, 3.216]]
    Neural = [NT_neural, NT_neural]
    board = Game.loadDDSresult(rowdata)
    calculator = Gamefunc.Calculator(HCPlist=Neural)
    func = [calculator.HCP, calculator.Long, calculator.Short, calculator.Pavlicek, calculator.Loser]
    fname = ["HCP", "Long", "Short", "Pavlicek", "Loser"]
    LongestSuit20210715(board, calculator, func, fname)
    NT20210715(board, calculator, func, fname)
