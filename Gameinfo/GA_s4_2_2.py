import numpy
import random
import sys


times = 0

def crossoverPopulaton(population, scores, popSize, crossoverProbability, keep):
    """
    The crossover of all individuals

    Parameters
    ----------
    population : list
        The list of individuals
    scores : list
        The list of fitness values for each individual
    popSize: int
        Number of chrmosome in a population
    crossoverProbability: float
        The probability of crossing a pair of individuals
    keep: int
        Number of best individuals to keep without mutating for the next generation


    Returns
    -------
    N/A
    """
    # initialize a new population
    newPopulation = numpy.empty_like(population)
    newPopulation[0:keep] = population[0:keep]
    # Create pairs of parents. The number of pairs equals the number of individuals divided by 2
    for i in range(keep, popSize, 2):
        # pair of parents selection
        parent1, parent2 = pairSelection(population, scores, popSize)
        crossoverLength = min(len(parent1), len(parent2))
        parentsCrossoverProbability = random.uniform(0.0, 1.0)
        if parentsCrossoverProbability < crossoverProbability:
            offspring1, offspring2 = crossover(
                crossoverLength, parent1, parent2)
        else:
            offspring1 = parent1.copy()
            offspring2 = parent2.copy()

        # Add offsprings to population
        newPopulation[i] = numpy.copy(offspring1)
        if i + 1 < popSize:
            newPopulation[i + 1] = numpy.copy(offspring2)

    return newPopulation


def mutatePopulaton(population, popSize, mutationProbability, keep, lb, ub):
    """
    The mutation of all individuals

    Parameters
    ----------
    population : list
        The list of individuals
    popSize: int
        Number of chrmosome in a population
    mutationProbability: float
        The probability of mutating an individual
    keep: int
        Number of best individuals to keep without mutating for the next generation
    lb: list
        lower bound limit list
    ub: list
        Upper bound limit list

    Returns
    -------
    N/A
    """
    for i in range(keep, popSize):
        # Mutation
        offspringMutationProbability = random.uniform(0.0, 1.0)
        if offspringMutationProbability < mutationProbability:
            mutation(population[i], len(population[i]), lb, ub)


def elitism(population, scores, bestIndividual, bestScore):
    """
    This melitism operator of the population

    Parameters
    ----------
    population : list
        The list of individuals
    scores : list
        The list of fitness values for each individual
    bestIndividual : list
        An individual of the previous generation having the best fitness value
    bestScore : float
        The best fitness value of the previous generation

    Returns
    -------
    N/A
    """

    # get the worst individual
    worstFitnessId = selectWorstIndividual(scores)

    # replace worst cromosome with best one from previous generation if its fitness is less than the other
    if scores[worstFitnessId] > bestScore:
        population[worstFitnessId] = numpy.copy(bestIndividual)
        scores[worstFitnessId] = numpy.copy(bestScore)


def selectWorstIndividual(scores):
    """
    It is used to get the worst individual in a population based n the fitness value

    Parameters
    ----------
    scores : list
        The list of fitness values for each individual

    Returns
    -------
    int
        maxFitnessId: The individual id of the worst fitness value
    """

    maxFitnessId = numpy.where(scores == numpy.max(scores))
    maxFitnessId = maxFitnessId[0][0]
    return maxFitnessId


def pairSelection(population, scores, popSize):
    """
    This is used to select one pair of parents using roulette Wheel Selection mechanism

    Parameters
    ----------
    population : list
        The list of individuals
    scores : list
        The list of fitness values for each individual
    popSize: int
        Number of chrmosome in a population

    Returns
    -------
    list
        parent1: The first parent individual of the pair
    list
        parent2: The second parent individual of the pair
    """
    parent1Id = rouletteWheelSelectionId(scores, popSize)
    parent1 = population[parent1Id].copy()

    parent2Id = rouletteWheelSelectionId(scores, popSize)
    parent2 = population[parent2Id].copy()

    return parent1, parent2


def rouletteWheelSelectionId(scores, popSize):
    """
    A roulette Wheel Selection mechanism for selecting an individual

    Parameters
    ----------
    scores : list
        The list of fitness values for each individual
    popSize: int
        Number of chrmosome in a population

    Returns
    -------
    id
        individualId: The id of the individual selected
    """

    # reverse score because minimum value should have more chance of selection
    reverse = max(scores) + min(scores)
    reverseScores = reverse - scores.copy()
    sumScores = sum(reverseScores)
    pick = random.uniform(0, sumScores)
    current = 0
    for individualId in range(popSize):
        current += reverseScores[individualId]
        if current > pick:
            return individualId


def crossover(individualLength, parent1, parent2):
    """
    The crossover operator of a two individuals

    Parameters
    ----------
    individualLength: int
        The maximum index of the crossover
    parent1 : list
        The first parent individual of the pair
    parent2 : list
        The second parent individual of the pair

    Returns
    -------
    list
        offspring1: The first updated parent individual of the pair
    list
        offspring2: The second updated parent individual of the pair
    """

    # The point at which crossover takes place between two parents.
    crossover_point = random.randint(0, individualLength - 1)
    # The new offspring will have its first half of its genes taken from the first parent and second half of its genes taken from the second parent.
    offspring1 = numpy.concatenate(
        [parent1[0:crossover_point], parent2[crossover_point:]])
    # The new offspring will have its first half of its genes taken from the second parent and second half of its genes taken from the first parent.
    offspring2 = numpy.concatenate(
        [parent2[0:crossover_point], parent1[crossover_point:]])

    return offspring1, offspring2


def mutation(offspring, individualLength, lb, ub):
    """
    The mutation operator of a single individual

    Parameters
    ----------
    offspring : list
        A generated individual after the crossover
    individualLength: int
        The maximum index of the crossover
    lb: list
        lower bound limit list
    ub: list
        Upper bound limit list

    Returns
    -------
    N/A
    """
    mutationIndex = random.randint(0, individualLength - 1)
    mutationValue = random.uniform(lb[mutationIndex], ub[mutationIndex])
    offspring[mutationIndex] = mutationValue


def clearDups(Population, lb, ub):
    """
    It removes individuals duplicates and replace them with random ones

    Parameters
    ----------
    objf : function
        The objective function selected
    lb: list
        lower bound limit list
    ub: list
        Upper bound limit list

    Returns
    -------
    list
        newPopulation: the updated list of individuals
    """
    newPopulation = numpy.unique(Population, axis=0)
    oldLen = len(Population)
    newLen = len(newPopulation)
    if newLen < oldLen:
        nDuplicates = oldLen - newLen
        newPopulation = numpy.append(newPopulation, numpy.random.uniform(0, 1, (nDuplicates, len(
            Population[0]))) * (numpy.array(ub) - numpy.array(lb)) + numpy.array(lb), axis=0)

    return newPopulation


def calculateCost(objf, population, popSize, lb, ub, process, CORNOT):
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
    scores = numpy.full(popSize, numpy.inf)

    # Loop through individuals in population
    for i in range(0, popSize):
        # Return back the search agents that go beyond the boundaries of the search space
        population[i] = numpy.clip(population[i], lb, ub)

        # Calculate objective function for each search agent
        if CORNOT == True:
            scores[i] = 1 - objf(process, population[i, :])
            if scores[i] == 3:
                print(population[i, :])
                print(stdoutreadint(process))
                print(stdoutreadint(process))
                print(stdoutreadint(process))
                exit()
        else:
            scores[i] = 1 - objf(population[i, :])

    return scores


def sortPopulation(population, scores):
    """
    This is used to sort the population according to the fitness values of the individuals

    Parameters
    ----------
    population : list
        The list of individuals
    scores : list
        The list of fitness values for each individual

    Returns
    -------
    list
        population: The new sorted list of individuals
    list
        scores: The new sorted list of fitness values of the individuals
    """
    sortedIndices = scores.argsort()
    population = population[sortedIndices]
    scores = scores[sortedIndices]

    return population, scores


def GA(objf, lb, ub, dim, popSize, iters, CORNOT, best, formulaID, cp, mp, keep):
    """
    This is the main method which implements GA

    Parameters
    ----------
    objf : function
        The objective function selected
    lb: list
        lower bound limit list
    ub: list
        Upper bound limit list
    dim: int
        The dimension of the indivisual
    popSize: int
        Number of chrmosomes in a population
    iters: int
        Number of iterations / generations of GA
    CORNOT: bool
        True for use C++ subprocess
        False for not use
    best: float
        The best score during the whole experiment
    formulaID: int
        The formula ID will enter in C subprocess
    cp: float
        The crossover Probability
    mp: float
        The mutation Probability
    keep: int
        The elitism parameter: how many of the best individuals to keep from one generation to the next

    """

    import Gameinfo.parser as ps
    from subprocess import Popen, PIPE
    import time
    start_time = time.time()
    scorematrix = ps.parse_score_matrix_file("data/GA_init_score_matrix.txt")
#    print("keep = ", keep, "dim = ", dim, "formulaID = ", formulaID)
    process = Popen(['./subprocesstest', str(formulaID)], stdin=PIPE, stdout=PIPE)

    if not isinstance(lb, list):
        lb = [lb] * dim
    if not isinstance(ub, list):
        ub = [ub] * dim

    bestIndividual = numpy.zeros(dim)
    scores = numpy.random.uniform(0.0, 1.0, popSize)
    bestScore = float("inf")
    pre = bestScore

    ga = numpy.zeros((popSize, dim))
    z = [0 for x in range(dim - 28)]
#    for i in range(popSize):
#        ga[i] = [*random.choice(scorematrix)[1][0], *random.choice(scorematrix)[2][0], *z]
    for i in range(dim):
        ga[:, i] = numpy.random.uniform(
            0, 1, popSize) * (ub[i] - lb[i]) + lb[i]
    convergence_curve = numpy.zeros(iters)


    for l in range(iters):

        # crossover
#        start_time = time.time()
        pre = bestScore
        ga = crossoverPopulaton(ga, scores, popSize, cp, keep)
#        print("Cost", time.time() - start_time, "seconds to crossover")

        # mutation
#       start_time = time.time()
        mutatePopulaton(ga, popSize, mp, keep, lb, ub)
#        print("Cost", time.time() - start_time, "seconds to mutation")

#        start_time = time.time()
        ga = clearDups(ga, lb, ub)
#        print("Cost", time.time() - start_time, "seconds to remove the duplicate")

#        start_time = time.time()
        scores = calculateCost(objf, ga, popSize, lb, ub, process, CORNOT)
#        print("Cost", time.time() - start_time, "seconds to calculate the fitness")

        bestScore = min(scores)

        # Sort from best to worst
#        start_time = time.time()
        ga, scores = sortPopulation(ga, scores)
#        print("Cost", time.time() - start_time, "seconds to sort the population")

        convergence_curve[l] = bestScore

#        if (l % 1 == 0):
#            print(['At iteration ' + str(l+1) +
#                   ' the best fitness is ' + str(bestScore)])

#    print("bestScore =", 1 - bestScore)
#    for i in ga[0]:
#        print("{:.4g}".format(i), end = " ")
#    if 1 - bestScore > best:
#        print("bestIndividual=")
#        for i in ga[0]:
#            print("{:.4g}".format(i), end = " ")
#    else:
#        print("not better, ignore it")
#    print("")
#    printbestIndividual(ga[0])
#    print("bestScore:{:.4g}".format(1 - bestScore))
#    print("Cost", time.time() - start_time, "seconds")
#    print("----------------------------------------------")
    process.terminate()
    return [1 - bestScore, [round(num, 3) for num in ga[0]], l, convergence_curve]
#    return [1 - bestScore, ga[0]]

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
        print(str(ret))
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

def stop_condition(s, pre):
    global times
    if s >= pre:
        times += 1
    else:
        times = 0
    return times

if __name__ == "__main__":
    import parser as ps
    sys.path.append("~/bridge/data")
    scorematrix = ps.parse_score_matrix_file("data/GA_init_score_matrix.txt")
    print(len(scorematrix))
    a = numpy.zeros((10, 42))
    print(a)
    z = [0 for x in range(42 - 28)]
    for i in range(len(a)):
        a[i] = [*random.choice(scorematrix)[1][0], *random.choice(scorematrix)[2][0], *z]
        print(a[i])
    print(a)
