import numpy as np
from subprocess import Popen, PIPE
import time
from datetime import date
from os.path import exists
from random import sample
import random

def calculateCost(fitness, P, popSize, lb, ub, process, CORNOT):
    """
    It calculates the fitness value of each individual in the population

    Parameters
    ----------
    fitness     :   function
                    The objective function selected
    P           :   list
                    The list of individuals
    popSize     :   int
                    Number of chrmosomes in a population
    lb          :   list
                    lower bound limit list
    ub          :   list
                    upper bound limit list
    process     :   Popen
                    The subprocess taht calculate the cost
    CORNOT      :   bool
                    Use the C++ subprocess or not

    Returns
    -------
    list
        scores  :   fitness values of all individuals in teh population
    """
    scores = np.full(popSize, 0.0)
    for i in range(0, popSize):
        P[i] = np.clip(P[i], lb, ub)
        if CORNOT == True:
            scores[i] = fitness(process, P[i, :])
            if scores[i] == 3:
                print(P[i, :])
                print(stdoutreadint(process))
                print(stdoutreadint(process))
                print(stdoutreadint(process))
                exit()
        else:
            scores[i] = fitness(P[i, :])
    return scores

def PSO(fitness, bound, dim, popSize, iters, CORNOT, best, formulaID, record = False, dataset_size = 0, SHOWBEST = False):
    """
    This is the main method which implements PSO

    Parameters
    ----------
    fitness     :   function
                    The function/subprocess that return the fitness
    bound       :   list of list
                    The bound limit lists of each dimensions
    dim         :   int
                    The dimension of the individuals
    popSize     :   int
                    Number of chrmosomes in a population
    iters       :   int
                    Number of iterations / generations of PSO
    CORNOT      :   bool
                    True for use C++ subprocess
    best        :   float
                    The best score during the whole experiment
    formulaID   :   int
                    The formula ID will be trained
    record      :   bool
                    True for record every population and the fitness to ./result/yyyy/mmdd_formulaXX_dataset_size_XX_version
    dataset_size:   int
                    The dataset size for record
    """


    start_time = time.time()

    c1_max = 2.5
    c2_max = 2.5
    c1_min = 2.5
    c2_min = 2.5
    wMax = 0.9
    wMin = 0.4
    Vmax = 4
    process = Popen(['./test', str(formulaID)], stdin=PIPE, stdout=PIPE)
    print("c1 = ", c1_min, "~", c1_max, "\nc2 = ", c2_min, "~", c2_max, "\nw = ", wMin, "~", wMax, "\nVmax = ", Vmax)

    ub = [max(x) for x in bound]
    lb = [min(x) for x in bound]

    print("upper bound:", ub)
    print("lower bound:", lb)

    gBest_corr = 0
    gBest_sm = [0 for x in range(dim)]
    pBest_corr = [0 for x in range(popSize)]
    pBest_sm = [[0 for x in range(dim)] for y in range(popSize)]
    vel = [[0 for x in range(dim)] for y in range(popSize)]

#    P = np.array([[np.random.choice(x) for x in bound] for i in range(popSize)])
    P = np.zeros((popSize, dim))
    for i in range(dim):
        P[:, i] = np.random.uniform(0, 1, popSize) * (ub[i] - lb[i]) + lb[i]
    pfitness = calculateCost(fitness, P, popSize, lb, ub, process, CORNOT)
    print("PSO is optimizing    \"" + fitness.__name__ + "\"")
    if record == True:
        year, month, day = date.today().isoformat.split("-")
        i = 1
        record_filename = "result/" + year + "/" + month + day + "_formula" + str(formulaID) + "_size_" + str(dataset_size) + "_" + str(i)
        while exists(record_filename):
            record_filename = "result/" + year + "/" + month + day + "_formula" + str(formulaID) + "_size_" + str(dataset_size) + "_" + str(i)
            i = i + 1
        f = open(record_filename, "w")
        print("Record to " + record_filename)


    for i in range(iters):
        #   record the global best and local best of each individuals
        for popu in range(popSize):
            if pfitness[popu] > pBest_corr[popu]:
                pBest_corr[popu] = pfitness[popu]
                pBest_sm[popu] = P[popu]
            if pfitness[popu] > gBest_corr:
                gBest_corr = pfitness[popu]
                gBest_sm = P[popu]
        #   update the W, c1, c2 of PSO
        w = wMax - (wMax - wMin) * i / iters
        c1 = c1_max + ((c1_min - c1_max) / iters) * i
        c2 = c2_min + ((c2_max - c2_min) / iters) * i
        #   update the velocity and the direction of each individuals
        for popu in range(popSize):
            #   load curren popu
            current_fitness = pfitness[popu]
            current_sm = P[popu]

            r1 = random.random()
            r2 = random.random()

            #   update popu vel and position
            temp_new_sm = [0 for x in range(dim)]

            for d in range(dim):
                vel[popu][d] = round(w * vel[popu][d] + c1 * r1 * (pBest_sm[popu][d] -
                                                                   current_sm[d]) + c2 * r2 * (gBest_sm[d] - current_sm[d]))

                if vel[popu][d] > Vmax:
                    vel[popu][d] = Vmax

                if vel[popu][d] < -Vmax:
                    vel[popu][d] = -Vmax

                current_sm[d] = current_sm[d] + vel[popu][d]
        #   calculate fitness of each individuals
        pfitness = calculateCost(fitness, P, popSize, lb, ub, process, CORNOT)
        #   if record is setting, record the individuals and their fitness
        if record == True:
            for p in range(len(P)):
                for pop in P[p]:
                    f.write(str(pop) + ' ')
                f.write(str(pfitness[i]) + '\n')
        #   if SHOWBEST is setting, print the best fitness
        bestScore = max(pfitness)
        bestID = np.argmax(pfitness)
        best_sm = P[bestID]
        if bestScore < gBest_corr:
            bestScore = gBest_corr
            best_sm = gBest_sm
        if SHOWBEST == True:
            print(['At iteration ' + str(i + 1) + ' the best fitness is ' + str(bestScore)])

    #   print the best fitness of whole iterations
    print("bestScore = ", bestScore)
    for i in best_sm:
        print("{:.5g}".format(i), end = " ")
    print("")
    #   print the time that iters used
    print("Cost", time.time() - start_time, "seconds")
    print("-------------------------------------")
    #   if record is setting, close the file operation
    if record == True:
        f.close()
    #   return the [best fitness, best individual]
    return [bestScore, best_sm]





def printbestIndividual(ans):
    l = []
    for i in ans:
        l.append(round(i, 4))
    print('HCP[1]:%.4g'%4)
    print('HCP[2-8]:%.4g'%l[0])
    print('HCP[9-10]:%.4g'%l[1])
    print('HCP[11]:%.4g'%l[2])
    print('HCP[12]:%.4g'%l[3])
    print('HCP[13]:%.4g'%l[4])
    for i in range(5, len(l), 2):
        print("{:.4g} {:.4g}".format(l[i], l[i + 1]))


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

def ObjfCorr(P, l):
    s = listtostdin(l)
    P.stdin.write(s.encode())
    P.stdin.flush()
    return stdoutreadint(P)



