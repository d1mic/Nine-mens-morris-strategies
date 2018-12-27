import numpy
import random
import logging
import numpy as np
import math
import os
import time


def generateRandomUnit():
    logging.debug('Generating random unit')
    return ([random.randint(9, 25),
             random.randint(5, 25),
             random.randint(1, 5),
             random.randint(5, 35),
             random.randint(5, 30),
             random.randint(5, 25),
             random.randint(1, 6),
             random.randint(15, 40),
             random.randint(10, 30),
             random.randint(7, 20),
             random.randint(10, 35),
             random.randint(5, 30),
             random.randint(20, 55),
             random.randint(1, 3),
             random.randint(5000, 10000),
             random.randint(5, 25),
             random.randint(5, 30),
             random.randint(15, 45),
             random.randint(5000, 10000)], -100)


def fitness(unit):
    return sum(unit)


def check_range(index, value):

    if index == 0:
        return (9 <= value <= 25)
    elif index == 1:
        return (5 <= value <= 25)
    elif index == 2:
        return (1 <= value <= 5)
    elif index == 3:
        return (5 <= value <= 35)
    elif index == 4:
        return (5 <= value <= 30)
    elif index == 5:
        return (5 <= value <= 25)
    elif index == 6:
        return (1 <= value <= 6)
    elif index == 7:
        return (15 <= value <= 40)
    elif index == 8:
        return (10 <= value <= 30)
    elif index == 9:
        return (7 <= value <= 20)
    elif index == 10:
        return (10 <= value <= 35)
    elif index == 11:
        return (5 <= value <= 30)
    elif index == 12:
        return (20 <= value <= 55)
    elif index == 13:
        return (1 <= value <= 3)
    elif index == 14:
        return (5000 <= value <= 10000)
    elif index == 15:
        return (5 <= value <= 25)
    elif index == 16:
        return (5 <= value <= 30)
    elif index == 17:
        return (15 <= value <= 45)
    elif index == 18:
        return (5000 <= value <= 10000)


def normalize_population(population):
    new_pop = []

    for i in range(len(population)):
        new_pop.append((population[i][0], population[i]
                        [1] + abs(population[-1][1])+1))

    normalized_array = []
    previous = 0
    for i in range(len(new_pop)):
        normalized_array.append(previous+new_pop[i][1])
        previous = normalized_array[i]

    norm = float(normalized_array[-1])
    for i in range(len(normalized_array)):
        normalized_array[i] /= norm

    return normalized_array


def wheelOneSelect(normalized_population):
    previous = 0
    roulette_pick = random.random()
    for i in range(len(normalized_population)):
        if roulette_pick > previous and roulette_pick < normalized_population[i]:
            break
        previous = normalized_population[i]
    return i


def wheelSelection(population, selection_num=40):
    selected = []
    normalized = normalize_population(population)
    for i in range(selection_num):
        k = wheelOneSelect(normalized)
        normalized.pop(k)
        selectedUnit = population.pop(k)
        selected.append(selectedUnit)
    return selected


def eliteSelection(population, elite_num):
    return population[:elite_num]


def initialPopulation(population_size=100):
    logging.info('Generating random population with size: %d', population_size)
    return [generateRandomUnit() for i in range(population_size)]


def unit_to_str(unit):
    unit_data = unit[0]
    unit_string = str(unit_data[0])
    for i in range(1, len(unit_data)):
        unit_string += " " + str(unit_data[i])
    return unit_string


def calculateFitnessForPopulation(population, enemies):
    try:
        f = open("unos.txt", "w")
        f.write(str(len(population)) + " " + str(len(enemies)) + "\n")
        for unit in population:
            f.write(unit_to_str(unit) + "\n")
        for enemy in enemies:
            f.write(unit_to_str(enemy) + "\n")
        f.flush()
        os.system("./a.out")
        time.sleep(0.1)

        f = open("rezultat.txt", "r")
        lines = f.readlines()
        results = []
        for line in lines:
            if line.__contains__("fitness"):
                results.append(int(line[-3:]))

        if len(results) != len(population):
            print("Bad results")
            exit()

    except Exception:
        print("IO error")

    pop_with_fitness = []
    for i in range(len(population)):
        pop_with_fitness.append((population[i][0], results[i]))
    return sortPopulation(pop_with_fitness)


def sortPopulation(population):
    return sorted(population, key=lambda tup: float(tup[1]), reverse=True)


def selection(population, elite=10, wheel=40):
    return eliteSelection(population, elite) + wheelSelection(population[elite + 1:], wheel)


def fourPointCrossover(first_parent, second_parent):
    points = sorted(random.sample(range(0, len(first_parent[0])), 4))
    first_parent = first_parent[0]
    second_parent = second_parent[0]
    first_child = first_parent[:points[0]] + second_parent[points[0]:points[1]] + \
        first_parent[points[1]:points[2]] + \
        second_parent[points[2]:points[3]] + first_parent[points[3]:]
    second_child = second_parent[:points[0]] + first_parent[points[0]:points[1]] + \
        second_parent[points[1]:points[2]] + \
        first_parent[points[2]:points[3]] + second_parent[points[3]:]

    return [(first_child, -100), (second_child, -100)]


def mutation(unit):
    unit_data = unit[0]
    for i in range(len(unit_data)):
        mutation_param = random.random()
        if mutation_param <= 0.08:
            addition_param = random.random()
            if addition_param < 0.5:
                if(check_range(i, unit_data[i]+1)):
                    unit_data[i] += 1
                else:
                    unit_data[i] -= 1
            else:
                if(check_range(i, unit_data[i]-1)):
                    unit_data[i] -= 1
                else:
                    unit_data[i] += 1

    return (unit_data, -100)


def remove_duplicates(pop):
    result = []
    for (unit, fitness) in pop:
        if unit in result:
            pop.remove((unit, fitness))
        else:
            result.append(unit)
    return pop


def main():
    enemies = [([19, 16, 3, 27, 7, 8, 4, 23, 27, 19, 17, 24, 29, 2, 9208, 18, 15, 36, 9975], -100),
        ([19, 16, 4, 24, 7, 9, 6, 21, 27, 12, 34, 8, 54, 1, 7215, 21, 6, 33, 8788], -100),
        ([23, 15, 4, 28, 13, 10, 1, 18, 26, 8, 10, 27, 21, 1, 6662, 16, 5, 40, 5876], -100),
        ([15, 17, 2, 9, 27, 18, 6, 33, 11, 20, 25, 14, 48, 2, 5484, 10, 24, 20, 9864], -100)]
    logging.basicConfig(filename='information.log',
                        format='%(levelname)s: %(asctime)s -- %(message)s',
                        level=logging.INFO, datefmt='%d/%m %I:%M %p')

    population = initialPopulation()
    pop = calculateFitnessForPopulation(population, enemies)
    iteration = 0
    for el in sortPopulation(pop):
        logging.info(str(el[1]) + " "+ str(el[0]))

    while iteration < 4:
        selected = selection(pop)
        for i in range(len(selected)/2):
            unit1 = random.choice(selected)
            selected.remove(unit1)
            unit2 = random.choice(selected)
            selected.remove(unit2)

            child1, child2 = fourPointCrossover(unit1, unit2)
            child1 = mutation(child1)
            child2 = mutation(child2)

            pop.append(child1)
            pop.append(child2)

        pop = remove_duplicates(pop)
        missing_values = 150 - len(pop)
        for i in range(missing_values):
            pop.append(generateRandomUnit())

        new_generation = []
        old_generation = []
        for el in pop:
            if el[1] == -100:
                new_generation.append(el)
            else:
                old_generation.append(el)

        new_generation = calculateFitnessForPopulation(new_generation, enemies)
        pop = new_generation + old_generation
        pop = eliteSelection(sortPopulation(pop), 100)
        iteration += 1

        logging.info("------------------------------------------------")
        for el in sortPopulation(pop):
            logging.info(str(el[1]) + " "+ str(el[0]))

    return 0


if __name__ == "__main__":
    main()
