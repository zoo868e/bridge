import csv
import math
import operator
import random
import numpy as np
import subprocess
from subprocess import PIPE, Popen


def fitness_cal(objf, population, popSize, lb, ub, process, CORNOT):
    """
    It calculates the fitness value of each individual in the population

    Parameters
    ----------
    objf : function
        The objective function selected
    population : list
        The list of individuals
    popSize: int
        Number of chrmosomes in a population
    lb: list
        lower bound limit list
    ub: list
        Upper bound limit list
    process: Popen
        The subprocess that calculate the cost
    CORNOT: bool
        Use the C++ subprocess or not

    Returns
    -------
    list
        scores: fitness values of all individuals in the population
    """
    scores = np.full(popSize, np.NINF)

    # Loop through individuals in population
    for i in range(0, popSize):
        # Return back the search agents that go beyond the boundaries of the search space
        population[i] = np.clip(population[i], lb, ub)

        # Calculate objective function for each search agent
        if CORNOT == True:
            scores[i] = objf(process, population[i, :])
            if scores[i] == 3:
                print(population[i, :])
                print(stdoutreadint(process))
                print(stdoutreadint(process))
                print(stdoutreadint(process))
                exit()
        else:
            scores[i] = objf(population[i, :])

    return scores


def load_matrices(dim, position):

    # load matrices
    temp1 = Array("ARNDCQEGHILKMFPSTWYVBZX*", dims=2)
    temp_new_population = [0 for x in range(dim)]
    k_1 = 0
    temp1 = substitution_matrices.load(
        "/home/cbyang/leeth/userdefine/our23/scoring_matrix/" + position)
    # 2-D to 1-D
    for i in range(0, 24):
        for j in range(i, 24):
            temp_new_population[k_1] = temp1[i][j]
            k_1 += 1

    return temp_new_population


def oneDto2D(one_d):

    index = 0
    two_d = Array("ARNDCQEGHILKMFPSTWYVBZX*", dims=2)
    for i in range(0, 24):
        for j in range(i, 24):
            two_d[i][j] = one_d[index]
            two_d[j][i] = one_d[index]
            index += 1

    return two_d


def tournament_selection(mastring, score_table):
    competitor = random.sample(score_table, 2)
    if mastring[competitor[0]] > mastring[competitor[1]]:
        return competitor[0]
    else:
        return competitor[1]


def dynamic_muta(gen, era):
    if gen <= era:
        PAR = 1 - (gen / era)
        mutation_number = round(300 * PAR-(30-(0.6*gen)))
        return mutation_number


def dynamic_num(gen, era):
    if gen <= era:
        p = int(era/5)
        q = era % 5
        if(gen < p+q+1):
            lb = -5
            ub = 5
        elif(p+q < gen < 2*p+q+1):
            lb = -4
            ub = 4
        elif(2*p+q < gen < 3*p+q+1):
            lb = -3
            ub = 3
        elif(3*p+q < gen < 4*p+q+1):
            lb = -2
            ub = 2
        elif(4*p+q < gen < 5*p+q+1):
            lb = -1
            ub = 1
        num = random.randint(lb, ub)
        return num


def record_population(score_table, gap, num, generation, popu, a, b, new_population, popu_name):

    score_table.append(str(num) + str(generation) +
                       popu_name + "_" + str(popu))
    gap.update({str(num) + str(generation) +
                popu_name + "_" + str(popu): [a, b]})
    text1 = format(new_population)
    f = open("/home/cbyang/leeth/userdefine/our23/scoring_matrix/" +
             str(num) + str(generation) + popu_name + "_" + str(popu), "w+")
    f.write(text1)
    f.close()

def diversity_guided(population, dim, b):
#   P = population size
#   L = the length of the diagonal in the search space
#   length of the diagonal = sqrt(a1*a1 + a2*a2 + a3*a3 + ... an * an)
    mean_p = np.mean(population, axis = 0)
    P = len(population)
    L = pow(sum(len(x) * len(x) for x in b), 0.5)
    D = 1 / (P * L)
    dis_all_pop = 0
    for pop in population:
        dis_all_pop = dis_all_pop + pow(sum(pow(pop[x] - mean_p[x], 2) for x in range(len(pop))), 0.5)
    D = D * dis_all_pop
    return D

def mutationP(score, mp):
    avg = np.mean(score)
    maxscore = max(score)
    temp = maxscore - avg
    ret = [mp for x in range(len(score))]
    if temp == 0:
        return ret
    for i in range(len(score)):
        if score[i] >= avg:
            ret[i] = ret[i] * (maxscore - score[i]) / temp
    return ret

def adaptive_crossover(k1, k2, population, mastring, score_table, fitness, minfitness):

    avgfitness = 0

    for popu in range(population):

        avgfitness = avgfitness + mastring[score_table[popu]]

    avgfitness = avgfitness/population

    if fitness < avgfitness:
        Rc = k1*((fitness-minfitness)/(avgfitness-minfitness))
    else:
        Rc = k2

    return Rc


def adaptive_mutation(k3, k4, population, mastring, score_table, fitness, maxfitness):

    avgfitness = 0

    for popu in range(population):

        avgfitness = avgfitness + mastring[score_table[popu]]

    avgfitness = avgfitness/population

    if fitness >= avgfitness:
        Rm = k3*((maxfitness-fitness)/(maxfitness-avgfitness))
    else:
        Rm = k4

    return Rm


def init(pop, score_table, gap):
    frequency = Array("ARNDCQEGHILKMFPSTWYVBZX*", dims=2)
    # D維度 23x23
    for i in range(24):
        for j in range(24):
            frequency[i][j] = np.random.randint(0, 999 + 1)
    # print(frequency)

    probabilities = frequency / np.sum(frequency)
    probabilities = (probabilities + probabilities.transpose()) / 2.0
    # print(format(probabilities, "%.3f"))
    background = np.sum(probabilities, 0)
    sum_ba = np.sum(background)
    # print(format(background, "%.3f"))
    print(sum_ba)

    expected = np.dot(background[:, None], background[None, :])
    # print(format(expected, "%.3f"))

    oddsratios = probabilities / expected
    scoring_matrix = np.around(
        np.log2(oddsratios, out=np.zeros_like(oddsratios), where=(oddsratios != 0)))
    print(scoring_matrix)
    open_o = random.randint(-20, -10)
    extend = random.randint(-3, -1)
    text = format(scoring_matrix)
    f = open("/home/cbyang/leeth/userdefine/our23/scoring_matrix/new" + "_" + str(pop),
             "w+")
    f.write(text)
    f.close()
    score_table.append("new" + "_" + str(pop))
    gap.update({"new" + "_" + str(pop): [open_o, extend]})
    # 10個初始值scoring matrix 產生

def stdoutreadint(process):
    ret = process.stdout.readline()
    try:
        return float(str(ret)[2:-3])
    except:
        print(str(ret))
        return str(ret)
    return float(str(ret)[2:-3])

def listtostdin(l):
    s = str(l[0])
    for i in l[1:]:
        s += " " + str(i)
    s += "\n"
#    print(s)
    return s

def ObjfCorr(P, l):
    s = listtostdin(l)
    P.stdin.write(s.encode())
    P.stdin.flush()
    return stdoutreadint(P)
