"""
This program is to calculate the correlation coefficient between the calculated score and the result of DDS
"""
if __name__ == "__main__":
    import Gameinfo.Game as Game
    import Gameinfo.calculate as Gamefunc
    import Gameinfo.CurrExperiment as Currgetter
    import math
    import sys
    # Add the data folder to path
    sys.path.append("~/bridge/data")
    f = open("data/test")
    rowdata = f.read()
    f.close()
    NT_neural = [[0, 3.975, 0.342, 0.340, 0.347, 0.341, 0.356, 0.380, 0.358, 0.496, 0.660, 1.047, 1.676, 2.643],[0, 3.971, 0.327, 0.334, 0.314, 0.332, 0.349, 0.331, 0.361, 0.469, 0.663, 1.032, 1.688, 2.643, 3.971], [0, 3.966, 0.329, 0.328, 0.351, 0.341, 0.339, 0.354, 0.375, 0.461, 0.671, 1.056, 1.675, 2.677], [0, 3.989, 0.342, 0.353, 0.345, 0.344, 0.329, 0.356, 0.400, 0.473, 0.684, 1.030, 1.656, 2.655]]
    Suit_neural = [[0, 3.982, 1.660, 1.664, 1.669, 1.660, 1.684, 1.680, 1.709, 1.782, 1.921, 2.174, 2.569, 3.207], [0, 3.984, 1.670, 1.667, 1.655, 1.673, 1.685, 1.684, 1.719, 1.791, 1.916, 2.167, 2.569, 3.210, 3.984], [0, 3.973, 1.668, 1.663, 1.669, 1.676, 1.680, 1.687, 1.718, 1.780, 1.918, 2.177, 2.572, 3.220], [0, 3.995, 1.667, 1.660, 1.685, 1.663, 1.688, 1.697, 1.723, 1.783, 1.938, 2.172, 2.565, 3.216]]
    Neural = [Suit_neural, NT_neural]
    board = Game.loadDDSresult(rowdata)
    calculator = Gamefunc.Calculator(HCPlist=Neural)
    #calculator = Gamefunc.Calculator()
    DDS = []
    score = []
    func = [calculator.HCP, calculator.Long, calculator.Short, calculator.Pavlicek, calculator.Loser]
    fname = ["HCP", "Long", "Short", "Pavlicek", "Loser"]
    #func = [calculator.HCP]
    #fname = ["HCP"]
    Currgetter.LongestSuit20210715(board, calculator, func, fname)
    Currgetter.NT20210715(board, calculator, func, fname)
