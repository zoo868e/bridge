from subprocess import Popen, PIPE
import numpy as np
import Gameinfo.GA_v01 as GA

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

def main():
    import Gameinfo.GA_v01 as GA
    import Gameinfo.parser as ps
    import numpy
    from subprocess import Popen, PIPE
    C = corrobj()
    C.loader("data/DDSresult.txt")
    for i in range(10):
        C.filter(5000)
        C.makedatasetforC()
        GA.GA(GA.ObjfCorr, 0, 1, 56, 50, 1000, True)

if __name__ == "__main__":
    main()
#    p = Popen(['./subprocessC'], stdin=PIPE, stdout=PIPE)
#    import Gameinfo.parser as ps
#    import random
#    from decimal import Decimal
#    scorematrix = ps.parse_score_matrix_file("data/GA_init_score_matrix.txt")
#    dim = 56
#    popSize = 5
#    lb = [0] * dim
#    ub = [1] * dim
#
#
#    ga = np.zeros((popSize, dim))
#    z = [0 for x in range(dim - 28)]
#    for i in range(popSize):
#        ga[i] = [*random.choice(scorematrix)[1][0], *random.choice(scorematrix)[2][0], *z]
#    for i in range(28, dim):
#        ga[:, i] = np.random.uniform(
#            0, 1, popSize) * (ub[i] - lb[i]) + lb[i]
#    for i in range(popSize):
#        s = listtostdin(ga[i])
#        print(s)
#        p.stdin.write(s.encode())
#        p.stdin.flush()
#        print(stdoutreadint(p))
#    p.stdin.close()
#    p.wait()
#    print(p.returncode)
