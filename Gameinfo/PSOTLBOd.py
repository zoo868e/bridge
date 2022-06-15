import csv
from random import sample
import random
import operator
import numpy as np
import subprocess
from subprocess import Popen, PIPE
import math
import Gameinfo.problem_lib as problem_lib
from time import time
from datetime import date
from os.path import exists


def PSOTLBO(objf, b, dim, population, era, CORNOT, best, formulaID, record = False, dataset_size = 0, SHOWBEST = False):

    start_time = time()
    PSO_time = 0
    TLBO_time = 0
    mutation_time = 0

    gBest_coverage = 0
    gBest_sm = [0 for x in range(dim)]
    pBest_coverage = [0 for x in range(population)]
    pBest_sm = [[0 for x in range(dim)] for y in range(population)]
    vel = [[0 for x in range(dim)] for y in range(population)]

    process = Popen(['./test', str(formulaID)], stdin=PIPE, stdout=PIPE)

    c1_max = 2.5
    c2_max = 2.5
    c1_min = 1
    c2_min = 1

    wMax = 0.9
    wMin = 0.4
    Vmax = 4

    lb = [min(x) for x in b]
    ub = [max(x) for x in b]
    print("upper bound :", ub)
    print("lower bound :", lb)

    print("PTd is optimizing formula" + str(formulaID))

    P = np.zeros((population, dim))
    tmp_P = np.zeros((population, dim))
    if record == True:
        year, month, day = date.today().isoformat().split("-")
        i = 1
        record_filename = "result/" + year + "/" + month + day + "_formula" + str(formulaID) + "_size_" + str(dataset_size) + "_" + str(i)
        while exists(record_filename):
            record_filename = "result/" + year + "/" + month + day + "_formula" + str(formulaID) + "_size_" + str(dataset_size) + "_" + str(i)
            i = i + 1
        f = open(record_filename, "w")
        print("Record to " + record_filename)
    for i in range(dim):
        P[:, i] = np.random.uniform(
            0, 1, population) * (ub[i] - lb[i]) + lb[i]
#    print("init: ", time() - start_time)
    start_time = time()
    # calculate the fitness
    pfitness = problem_lib.fitness_cal(objf, P, population, lb, ub, process, CORNOT)
    for generation in range(1, era):
        s_time = time()
        # PSO
        # record
        for popu in range(population):

            fitness = pfitness[popu]

            # record pbest
            if fitness > pBest_coverage[popu]:
                pBest_coverage[popu] = fitness
                pBest_sm[popu] = P[popu].copy()

                # record gbest
                if fitness > gBest_coverage:
                    gBest_coverage = fitness
                    gBest_sm = P[popu].copy()

        # update the W, c1, c2 of PSO
        w = wMax - (wMax - wMin) * generation / era
        c1 = c1_max + ((c1_min - c1_max) / era) * generation
        c2 = c2_min + ((c2_max - c2_min) / era) * generation

        for popu in range(population):

            # load current popu
            current_fitness = pfitness[popu]
            current_population = P[popu].copy()

            r1 = random.random()
            r2 = random.random()

            # update popu
            temp_new_population = [0 for x in range(dim)]

            for d in range(dim):

                vel[popu][d] = w * vel[popu][d] + c1 * r1 * (pBest_sm[popu][d] - current_population[d]) + c2 * r2 * (gBest_sm[d] - current_population[d])

                if vel[popu][d] > Vmax:
                    vel[popu][d] = Vmax

                if vel[popu][d] < -Vmax:
                    vel[popu][d] = -Vmax

                temp_new_population[d] = current_population[d] + \
                    vel[popu][d]

            P[i] = temp_new_population.copy()
        # fitness calaulate
        pfitness = problem_lib.fitness_cal(objf, P, population, lb, ub, process, CORNOT)

        PSO_time += time() - s_time
        s_time = time()
        # start TLBO
        teacher_coverage = 0
        teacher_sm = [0 for x in range(dim)]
        mean_sm = [0 for x in range(dim)]

        # update teacher
        teacher_coverage = max(pfitness)
        teacher_sm = P[np.argmax(pfitness)].copy()

        # calculate mean

        mean_sm = np.mean(P, axis = 0).tolist()
        for popu in range(population):

            # teacher phase
            # load current popu
            current_population = P[popu]
            current_fitness = pfitness[popu]
            # update TF
            TF = round(1+random.random())
            # update popu
            temp_new_population = [0 for x in range(dim)]
            for d in range(dim):
                temp_new_population[d] = current_population[d] + random.random()*(teacher_sm[d]-TF*mean_sm[d])
            tmp_P[popu] = temp_new_population.copy()
        # fitness calaulate
        tmp_pfitness = problem_lib.fitness_cal(objf, tmp_P, population, lb, ub, process, CORNOT)

        for popu in range(population):
            if(pfitness[popu] < tmp_pfitness[popu]):
                # fitness
                pfitness[popu] = tmp_pfitness[popu].copy()
                P[popu] = tmp_P[popu].copy()

        for popu in range(population):

            # learning phase
            current_fitness = pfitness[popu]
            current_population = P[popu].copy()
            # load random popu
            randomlist = [x for x in range(population)]
            randomlist.remove(popu)
            randindex = np.random.choice(randomlist)
            random_fitness = pfitness[randindex]
            random_population = P[randindex].copy()
            # update population
            temp_new_population = [0 for x in range(dim)]

            if(current_fitness > random_fitness):
                for d in range(dim):
                    temp_new_population[d] = current_population[d] + random.random()*(current_population[d]-random_population[d])

            else:
                for d in range(dim):
                    temp_new_population[d] = current_population[d] + random.random()*(random_population[d]-current_population[d])

            # record population
            tmp_P[popu] = temp_new_population.copy()

        # fitness calaulate
        tmp_pfitness = problem_lib.fitness_cal(objf, tmp_P, population, lb, ub, process, CORNOT)

        for popu in range(population):
            if(pfitness[popu] < tmp_pfitness[popu]):
                P[popu] = tmp_P[popu].copy()
                pfitness[popu] = tmp_pfitness[popu]

        mean_sm2 = [0 for x in range(dim)]
        # calculate mean and record pbest
        mean_sm2 = np.mean(P, axis = 0).tolist()

        TLBO_time += time() - s_time
        s_time = time()
        # diversity-guided
        div = problem_lib.diversity_guided(P, dim, b)


        # start mutation

        if div <= 0.045:
            # mutation rate
            mp = 1 - (generation / era)
            mutation_rate = problem_lib.mutationP(pfitness, mp).copy()
            for popu in range(population):
                # load popu
                current_population = P[popu].copy()
                current_fitness = pfitness[popu]

                mutation_number = round(mutation_rate[popu] * dim)
                appear_arr = list(range(0, dim))
                random_item = random.sample(appear_arr, int(mutation_number))
                major_rate = random.random()
                mutate_chrmosome = list(range(0, population))
                mutate_chrmosome.remove(popu)
                random_chrmosome = random.sample(mutate_chrmosome, int(mutation_number))
                if major_rate < mutation_rate[popu]:
                    for i in range(len(random_item)):
                        minor_rate = random.random()
                        current_population[random_item[i]] = random.uniform(lb[random_item[i]], ub[random_item[i]])
                        if minor_rate <= 0.5:
                            current_population[random_item[i]] = current_population[random_item[i]] + 1
                        else:
                            current_population[random_item[i]] = current_population[random_item[i]] - 1
                    P[popu] = current_population.copy()
            # fitness calaulate
            pfitness = problem_lib.fitness_cal(objf, P, population, lb, ub, process, CORNOT)
        # record the individuals
        if record == True:
            f.write("------------------In " + str(generation) + "th generation----------------------\n")
            for i in range(len(P)):
                for pop in P[i]:
                    f.write(str(pop) + ' ')
                f.write(str(pfitness[i]) + '\n')
        # show best
        if SHOWBEST == True:
            print(['At iteration ' + str(generation + 1) + ' the best fitness is ' + str(gBest_coverage)])

        mutation_time += time() - s_time
    # close record file if exist
    if record == True:
        f.close()

    print("bestScore =", gBest_coverage)
    for i in gBest_sm:
        print("{:.4g}".format(i), end = " ")
    print("")
    print("Cost", time() - start_time, "seconds")
    print("----------------------------------------------")
    process.terminate()
    if record == True:
        f.close()
#    print("all time : ", time() - start_time)
#    print("PSO time :", PSO_time)
#    print("TLBO time :", TLBO_time)
#    print("mutation time :", mutation_time)
    return [gBest_coverage, gBest_sm]
