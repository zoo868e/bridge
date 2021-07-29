import unittest
import Gameinfo.Game as Game
import Gameinfo.parser as parser
import Gameinfo.calculate as Gamefunc
import sys

class TestCalculatorMethod(unittest.TestCase):
    def setUp(self):
        sys.path.append("~/bridge/data")
        self.scorematrix = parser.parse_score_matrix_file("data/score_matrix.txt")
        f = open("data/test")
        rowdata = f.read()
        f.close()
        self.board = Game.loadDDSresult(rowdata)
        self.calculator = Gamefunc.Calculator()
    def test_HCP(self):
        f = open("data/HCPanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[0])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
    def test_Long(self):
        f = open("data/Longanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[0])
        for i in range(len(self.board)):
            self.calculator.Long(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
 
    def test_Short(self):
        f = open("data/Shortanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[0])
        for i in range(len(self.board)):
            self.calculator.Short(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
 
    def test_Pavilcek(self):
        f = open("data/Pavlicekanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[0])
        for i in range(len(self.board)):
            self.calculator.Pavlicek(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
  
    def test_Loser(self):
        f = open("data/Loseranswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[0])
        for i in range(len(self.board)):
            self.calculator.Loser(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
 
    def test_Bamber(self):
        f = open("data/Bambergeranswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[4])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
  
    def test_Collet(self):
        f = open("data/Colletanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[5])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
 
 
    def test_Fourace(self):
        f = open("data/Fouraceanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[6])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
  
    def test_Polish(self):
        f = open("data/Polishanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(6)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[7])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
  
    def test_Reith(self):
        f = open("data/Reithanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(7)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[8])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
  
    def test_Robertson(self):
        f = open("data/Robertsonanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(7)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[9])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(self.calculator.south[0], answer[i][0])
            self.assertEqual(self.calculator.north[0], answer[i][1])
            self.assertEqual(self.calculator.west[0], answer[i][2])
            self.assertEqual(self.calculator.east[0], answer[i][3])
  
    def test_Vernes(self):
        f = open("data/Vernesanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(7)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[10])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(round(self.calculator.south[0], 2), answer[i][0])
            self.assertEqual(round(self.calculator.north[0], 2), answer[i][1])
            self.assertEqual(round(self.calculator.west[0], 2), answer[i][2])
            self.assertEqual(round(self.calculator.east[0], 2), answer[i][3])
  
    def test_AKQ(self):
        f = open("data/AKQanswer")
        rowdata = f.read()
        f.close()
        data = rowdata.splitlines()
        answer = [[] for x in range(7)]
        for i in range(len(data)):
            for j in data[i].split(";"):
                answer[i].append(float(j))
        self.calculator.setHCPlist(self.scorematrix[11])
        for i in range(len(self.board)):
            self.calculator.HCP(self.board[i])
#            print(self.calculator.south[0])
#            print(answer[i][0])
            self.assertEqual(round(self.calculator.south[0], 2), answer[i][0])
            self.assertEqual(round(self.calculator.north[0], 2), answer[i][1])
            self.assertEqual(round(self.calculator.west[0], 2), answer[i][2])
            self.assertEqual(round(self.calculator.east[0], 2), answer[i][3])
 



    def test_isupper(self):
        self.assertTrue('FOO'.isupper())
        self.assertFalse('Foo'.isupper())


if __name__ == "__main__":
    unittest.main()
