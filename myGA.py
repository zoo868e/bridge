import numpy as np
import sys
import random
from subprocess import Popen, PIPE

def GA(scorer, lower_bound, upper_bound, dim, popSize, generation, crossover_rate, mutation_rate, elitism_keep, train_process):
    """
    scorer: functiion(individual)
        The objective function selected that return value is the fitness of the individual
    lower_bound: list
        Lower bound limit list
    upper_bound: list
        Upper bound limit list
    dim: int
        Number of the dimension in a individual
    popSize: int
        Number of the individuals in a generation
    generation: int
        Number of generations of GA
    crossover_rate: float
        The crossover rate of the GA
    mutation_rate: float
        The mutation rate of the GA
    elitism_keep: int
        Number of the elitism will keep to next generation
    """
    ub = []
    lb = []
    convergence_curve = []

    cp = crossover_rate
    mp = mutation_rate
    keep = elitism_keep

    if not isinstance(upper_bound, list):
        ub = np.array([upper_bound for x in range(dim)])
    else:
        ub = np.array(upper_bound)
    if not isinstance(lower_bound, list):
        lb = np.array([lower_bound for x in range(dim)])
    else:
        lb = np.array(lower_bound)

    width = np.array([ub[i] - lb[i] for i in range(len(ub))])
    individuals = np.array([lb + width * np.random.random(dim) for x in range(popSize)])
    scores = calculateCost(scorer, individuals, popSize, train_process)
    best_ind = individuals[np.argmax(scores)]
    best_score = np.max(scores)


    for l in range(generation):
        # crossover
        individuals = crossoverPopulation(individuals, scores, popSize, cp, keep)
        # mutation
        mutatePopulation(individuals, popSize, dim, mp, keep, lb, ub)
        # remove the duplicated individuals
        individuals = clearDups(individuals, dim, lb, ub)
        # calculate the fitness
        scores = calculateCost(scorer, individuals, popSize, train_process)
        # record the best individual and performance
        convergence_curve.append(np.max(scores))
        best_ind = individuals[np.argmax(scores)]
        best_score = np.max(scores)
#        print("Iter:", l, "the best score is", best_score)

    train_process.terminate()
    return [best_score, best_ind, convergence_curve]

def calculateCost(objf, individuals, popSize, process):
    """
    Calculate the fitness of each individual in the populationn

    Parameters
    ----------
    objf: function
        The objective function selected
    individuals: list
        The list of individuals
    popSize: int
        Number of individuals in a population
    process: Popen
        The subprocess that calculate the cost

    Returns
    -------
    scores: list
        fitness values of all individuals in the generation
    """
    scores = np.full(popSize, np.inf)
    for i in range(popSize):
        individuals[i] = np.clip(individuals[i], lb, ub)
        scores[i] = objf(process, population[i, :])
        if scores[i] == 3:
            print(individuals[i, :])
            print(stdoutreadint(process))
            print(stdoutreadint(process))
            print(stdoutreadint(process))
            exit()
    return scores

def clearDups(individuals, dim, lb, ub):
    """
    Remove the duplicate individuals and generate the individuals randomly

    Parameters
    ----------
    individuals: list
        The list of individuals
    dim: int
        Number of dimensions of an individual
    lb: list
        lower bound limit list
    ub: list
        upper bound limit list

    Returns
    -------
    newIndividuals: list
        the updated list of individuals
    """
    newIndividuals = np.unique(individuals, axis = 0)
    if len(newIndividuals) < len(individuals):
        new = np.array([[random.uniform(lb[i], ub[i]) for i in range(dim)] for i in range(len(individuals) - len(newIndividuals))])
        newIndividuals = np.append(newIndividuals, new.copy(), axis = 0)
    return newIndividuals





def mutatePopulation(individuals, popSize, dim, mp, keep, lb, ub):
    """
    The mutation of all individuals

    Parameters
    ----------
    individuals: list
        The list of individuals
    popSize: int
        Number of the individuals
    dim: int
        Number of the dimension in an individual
    mp: float
        The probability of mutating an individual
    keep: int
        Number of best individuals to keep without mutating for the next generation
    lb: list
        lower bound limit list
    ub: list
        upper bound limit list
    """
    for i in range(keep, popSize):
        # Mutation
        offspringMutationProbability = random.uniform(0, 1)
        if offspringMutationProbability < mp:
            mutation(individuals[i], dim, lb, ub)

def mutation(individual, dim, lb, ub):
    """
    The mutation operation of a single individual

    Parameters
    ----------
    individual: list
        The generated individual after the crossover
    dim: int
        Number of the dimensin in an individual
    lb: list
        lower bound limit list
    ub: list
        upper bound limit list
    """
    mutationIndex = random.randint(0, dim - 1)
    mutationValue = random.uniform(lb[mutationIndex], ub[mutationIndex])
    individual[mutationIndex] = mutationValue

def crossoverPopulation(individuals, scores, popSize, cp, keep):
    """
    The crossover of all individuals

    Parameters
    ----------
    individuals: list
        The individuals used to crossover
    scores: list
        The fitness of each individuals
    popSize: int
        Number of the individuals
    cp: float
        Crossover rate
    keep: int
        Number of the elitism will keep for next generation

    Returns
    -------
    newIndividuals: list
        The updated individuals
    """

    Probability = scores.copy()
    Ind = individuals.copy()
    newIndividuals = np.empty_like(individuals)
    for i in range(keep):
        _id = np.argmax(scores)
        newIndividuals[i] = individuals[_id].copy()
        scores = np.delete(scores, _id)
        individuals = np.delete(individuals, _id, axis = 0)
    for i in range(keep, popSize, 2):
        # Roulette Wheel Selection
        Pro = Probability.copy()
        I = Ind.copy()
        parent1_id = random.choices(range(len(Pro)), weights=Pro)[0]
        parent1 = I[parent1_id].copy()
        Pro = np.delete(Pro, parent1_id)
        I = np.delete(I, parent1_id, axis = 0)
        parent2_id = random.choices(range(len(Pro)), weights=Pro)[0]
        parent2 = I[parent2_id].copy()

        parent_crossover_probability = random.uniform(0, 1)
        if parent_crossover_probability < cp:
            offspring1, offspring2 = crossover(parent1, parent2)
        else:
            offspring1 = parent1.copy()
            offspring2 = parent2.copy()
        newIndividuals[i] = offspring1.copy()
        if i + 1 < popSize:
            newIndividuals[i + 1] = offspring2.copy()
    return newIndividuals

def crossover(parent1, parent2):
    """
    The crossover operator.

    Parameters
    ----------
    parent1: list
        The first parent individual.
    parent2: list
        The second parent individual.

    Returns
    -------
    offspring1: list
        The first updated parent individual of the pair
    offspring2: list
        The second updated parent individual of the pair
    """
    # The point that crossover two parents
    point = random.randint(1, min(len(parent1), len(parent2)) - 1)
    offspring1 = np.concatenate([parent1[:point], parent2[point:]])
    offspring2 = np.concatenate([parent2[:point], parent1[point:]])
    return offspring1, offspring2

