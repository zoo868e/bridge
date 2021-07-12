import Gameinfo.Game as Game
import Gameinfo.calculate as Gamefunc

#f = open("Gameinfo/DDSresult.txt")
#rowdata = f.read()
#f.close()
#
#board = Game.loadDDSresult(rowdata)
#for i in range(len(board[:2])):
#    for j in board[i].getgame():
#        print(j)

f = open("Gameinfo/DDSresult.txt")
rowdata = f.read()
f.close()
i = 2
NT_neural = [[0, 3.975, 0.342, 0.340, 0.347, 0.341, 0.356, 0.380, 0.358, 0.496, 0.660, 1.047, 1.676, 2.643],[0, 3.971, 0.327, 0.334, 0.314, 0.332, 0.349, 0.331, 0.361, 0.469, 0.663, 1.032, 1.688, 2.643, 3.971], [0, 3.966, 0.329, 0.328, 0.351, 0.341, 0.339, 0.354, 0.375, 0.461, 0.671, 1.056, 1.675, 2.677], [0, 3.989, 0.342, 0.353, 0.345, 0.344, 0.329, 0.356, 0.400, 0.473, 0.684, 1.030, 1.656, 2.655]]
Suit_neural = [[0, 3.982, 1.660, 1.664, 1.669, 1.660, 1.684, 1.680, 1.709, 1.782, 1.921, 2.174, 2.569, 3.207], [0, 3.984, 1.670, 1.667, 1.655, 1.673, 1.685, 1.684, 1.719, 1.791, 1.916, 2.167, 2.569, 3.210, 3.984], [0, 3.973, 1.668, 1.663, 1.669, 1.676, 1.680, 1.687, 1.718, 1.780, 1.918, 2.177, 2.572, 3.220], [0, 3.995, 1.667, 1.660, 1.685, 1.663, 1.688, 1.697, 1.723, 1.783, 1.938, 2.172, 2.565, 3.216]]
Neural = [NT_neural, NT_neural]
board = Game.loadDDSresult(rowdata)
calculator = Gamefunc.Calculator(HCPlist=Neural)
DDS = []
score = []
func = [calculator.HCP, calculator.Long, calculator.Short, calculator.Pavlicek, calculator.Loser]
fname = ["HCP", "Long", "Short", "Pavlicek", "Loser"]
#func = [calculator.Loser]
#fname = ["Loser"]
for f in range(len(func)):
    DDS.clear()
    score.clear()
    print(fname[f])
    tooshort = 0
    for i in board:
        ns_suit = i.longgest[0][0]
        ns_len = i.longgest[0][1]
        ns_ddswin = i.longgest[0][2]
        we_suit = i.longgest[1][0]
        we_len = i.longgest[1][1]
        we_ddswin = i.longgest[1][2]
        func[f](i)
        ns = calculator.ns
        we = calculator.we
        if ns_len < 7 and i.South.hand.distributed[ns_suit] < 6 and i.North.hand.distributed[nw_suit] < 6:
            tooshort += 1
        else:
            score.append(ns[ns_suit])
            DDS.append(ns_ddswin)
        if we_len < 7 and i.West.hand.distributed[we_suit] < 6 and i.East.hand.distributed[we_suit] < 6:
            tooshort += 1
        else:
            score.append(we[we_suit])
            DDS.append(we_ddswin)
#    print(score)
#    print(DDS)
    print('{:^.4f}'.format(Gamefunc.getcurr(DDS, score)))



### check the longgest list record is correct or not
#    for j in i.getgame():
#        print(j)
#    print(i.South.hand.distributed)
#    print(i.North.hand.distributed)
#    print(i.West.hand.distributed)
#    print(i.East.hand.distributed)
#    print(i.longgest[0])
#    print("To check: SouthDDS = ", i.SouthDDS[i.longgest[0][0]], "NorthDDS = ", i.NorthDDS[i.longgest[0][0]])
#    print(i.longgest[1])
#    print("To check: WestDDS = ", i.WestDDS[i.longgest[1][0]], "EastDDS = ", i.EastDDS[i.longgest[1][0]])

### check the calculator correct or not
#calculator.Short(board[i])
#history = []
#history.append(calculator.getscore())
#calculator.Pavlicek(board[i])
#history.append(calculator.getscore())
#for i in board[i].getgame():
#    print(i)
#print("--------------")
#for i in range(len(history)):
#    for j in range(len(history[i])):
#        print(history[i][j])
#    print("---------")
