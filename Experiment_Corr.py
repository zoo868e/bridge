"""
This program is to calculate the correlation coefficient between the calculated score and the result of DDS
"""
def runExperiment(board, ExperimentFuncion, scorematrix, EvaluationFunction, calculator):
    print(ExperimentFuncion.__name__)
    print("{:^20}".format(" "), end = " ")
    for i in EvaluationFunction:
        print("{:^10}".format(i.__name__), end = " ")
    print("")
    for i in scorematrix:
        calculator.setHCPlist(i)
        ExperimentFuncion(board, calculator, EvaluationFunction)
if __name__ == "__main__":
    import Gameinfo.Game as Game
    import Gameinfo.calculate as Gamefunc
    import Gameinfo.CurrExperiment as Currgetter
    import Gameinfo.parser as ps
    import Gameinfo.Objfunc as Objf
    import math
    import sys
#    C = Objf.corrobj()
#    C.loader("./data/DDSresult.txt")
#    C.filter(2 * len(C.data))
#    print(len(C.data))
#    print(len(C.board))
#    print(len(C.DDS))
    # Add the data folder to path
    sys.path.append("~/bridge/data")
    # import the score matrix
    scorematrix = ps.parse_score_matrix_file("data/score_matrix.txt")
    # Load the rowdata
    f = open("data/wholeStaticForOLDMethod")
    rowdata = f.read()
    f.close()
    # Load the data and initialize
    board = Game.loadDDSresult(rowdata)
    calculator = Gamefunc.Calculator()
    DDS = []
    score = []
    func = [calculator.HCP, calculator.Long, calculator.Short, calculator.Pavlicek, calculator.Loser]
    fname = ["HCP", "Long", "Short", "Pavlicek", "Loser"]
    # Run the experiment
    runExperiment(board, Currgetter.LongestSuit20220324, scorematrix, func, calculator)
