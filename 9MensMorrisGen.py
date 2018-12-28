import random
import logging
import os
import sys
import re
import time


def generate_random_unit():
    """
    Generates one unit
    """
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


def check_range(index, value):
    """
    Checks if the selected gene of the unit are is in the right range
    :param index: Index of the gene (int) in one unit
    :param value: Value of the gene (int) in one unit

    :return: true/false - if the selected gene is in the right range
    """

    if index == 0:
        return 9 <= value <= 25
    elif index == 1:
        return 5 <= value <= 25
    elif index == 2:
        return 1 <= value <= 5
    elif index == 3:
        return 5 <= value <= 35
    elif index == 4:
        return 5 <= value <= 30
    elif index == 5:
        return 5 <= value <= 25
    elif index == 6:
        return 1 <= value <= 6
    elif index == 7:
        return 15 <= value <= 40
    elif index == 8:
        return 10 <= value <= 30
    elif index == 9:
        return 7 <= value <= 20
    elif index == 10:
        return 10 <= value <= 35
    elif index == 11:
        return 5 <= value <= 30
    elif index == 12:
        return 20 <= value <= 55
    elif index == 13:
        return 1 <= value <= 3
    elif index == 14:
        return 5000 <= value <= 10000
    elif index == 15:
        return 5 <= value <= 25
    elif index == 16:
        return 5 <= value <= 30
    elif index == 17:
        return 15 <= value <= 45
    elif index == 18:
        return 5000 <= value <= 10000


def normalize_population(population):
    """
    Normalizes population
    :param population: Population to be normalized

    :return: normalized population 

    """
    new_pop = []

    for i in range(len(population)):
        new_pop.append((population[i][0], population[i][1] + abs(population[-1][1]) + 1))

    normalized_array = []
    previous = 0
    for i in range(len(new_pop)):
        normalized_array.append(previous + new_pop[i][1])
        previous = normalized_array[i]

    norm = float(normalized_array[-1])
    for i in range(len(normalized_array)):
        normalized_array[i] /= norm

    return normalized_array


def wheel_one_select(normalized_population):
    """
    Takes the normalized population and uses wheel selection to select one unit

    :param normalized_population: already normalized population
    :return: index of the unit of population to be selected
    """
    previous = 0
    roulette_pick = random.random()
    for i in range(len(normalized_population)):
        if previous < roulette_pick < normalized_population[i]:
            break
        previous = normalized_population[i]
    return i


def wheel_selection(population, selection_num=40):
    """
    Uses wheel selection to pick selection_num units from population

    :param population: population to be picked from
    :param selection_num: number of units to be selected
    :return: array of selected units
    """
    selected = []
    normalized = normalize_population(population)
    for i in range(selection_num):
        k = wheel_one_select(normalized)
        normalized.pop(k)
        selected_unit = population.pop(k)
        selected.append(selected_unit)
    return selected


def elite_selection(population, elite_num):
    """
    Uses elite selection to pick elite_num units from population

    :param population: population to be picked from
    :param elite_num: number of units to be selected
    :return: array of selected units
    """
    return population[:elite_num]


def initial_population(population_size=100):
    """
    Generates unit population of population_size units

    :param population_size: number of units
    :return: population of random units
    """
    logging.info('Generating random population with size: %d', population_size)
    return [generate_random_unit() for i in range(population_size)]


def initial_population_from_backup(filename="backup.txt"):
    """
    Takes initial population from backup file

    :param filename: backup file
    :return: population from backup file
    """
    try:
        f = open(filename, "r")
        lines = f.readlines()
        num_units = int(re.search(r'\d+', lines[0]).group())
        population = []
        for i in range(1, num_units + 1):
            array = [int(number) for number in lines[i].split(' ')]
            population.append((array, -100))
        logging.info('Using population from backup')
        return population

    except IOError:
        print("IO error - backup error ")


def unit_to_str(unit):
    """
    Converts unit into string that is in format to be passed to fitness function

    :param unit: unit
    :return: string representation of unit
    """
    unit_data = unit[0]
    unit_string = str(unit_data[0])
    for i in range(1, len(unit_data)):
        unit_string += " " + str(unit_data[i])
    return unit_string


def tournament_setup(population, enemies, filename="unos.txt"):
    """
    Writing into file - adding population and enemies that will play the tournament

    :param population: population of players
    :param enemies: enemies that the players will play against
    :param filename: input file path for tournament
    """
    try:
        f = open(filename, "w")
        f.write(str(len(population)) + " " + str(len(enemies)) + "\n")
        for unit in population:
            f.write(unit_to_str(unit) + "\n")
        for enemy in enemies:
            f.write(unit_to_str(enemy) + "\n")
        f.flush()

    except IOError:
        print("IO error while writing into file unos.txt")


def tournament_results(filename="rezultat.txt"):
    """
    Read tournament results (fitness) from file

    :param filename: path for tournament results
    :return: array with fitness for each unit of population
    """
    try:
        f = open(filename, "r")
        lines = f.readlines()
        results = []
        for line in lines:
            if line.__contains__("fitness"):
                results.append(int(line[-3:]))
        return results

    except IOError:
        print("IO error while reading results of matches from rezultat.txt")


def tournament_run(program="./a.out"):
    """
    Run tournament
    :param program: path to tournament executable
    """
    os.system(program)
    time.sleep(0.1)


def calculate_population_fitness(population, enemies):
    """
    Calculates the fitness of all units in the population and adds that fitness to the units

    :param population: population without fitness values (-100 - default value)
    :param enemies: enemies for units to play 9 men morris with
    :return: population with units that have fitness values
    """
    tournament_setup(population, enemies)
    tournament_run()
    results = tournament_results()

    if len(results) != len(population):
        logging.warning("Number of results different then number of units in population")
        print("Number of results different then number of units in population")
        exit()

    pop_with_fitness = []
    for i in range(len(population)):
        pop_with_fitness.append((population[i][0], results[i]))
    return sort_population(pop_with_fitness)


def sort_population(population):
    """
    Sorts the population based on fitness values

    :param population: population to be sorted
    :return: sorted population
    """
    return sorted(population, key=lambda tup: float(tup[1]), reverse=True)


def selection(population, elite=10, wheel=40):
    """
    Selects units from initial population
    :param population: initial population
    :param elite: number of elements to be selected using elite selection
    :param wheel: number of elements to be selected using wheel selection
    :return: array of selected elements
    """
    return elite_selection(population, elite) + wheel_selection(population[elite + 1:], wheel)


def four_point_crossover(first_parent, second_parent):
    """
    Makes 2 child units using 4 point crossover method
    :param first_parent: parent to be crossed over
    :param second_parent: parent to be crossed over
    :return: 2 child units
    """
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
    """
    Uses mutation to change some of the genes. Each gene has 8% chance to be mutated.
    :param unit: unit to be mutated
    :return: unit
    """
    unit_data = unit[0]
    for i in range(len(unit_data)):
        mutation_param = random.random()
        if mutation_param <= 0.08:
            addition_param = random.random()
            if addition_param < 0.5:
                if check_range(i, unit_data[i] + 1):
                    unit_data[i] += 1
                else:
                    unit_data[i] -= 1
            else:
                if check_range(i, unit_data[i] - 1):
                    unit_data[i] -= 1
                else:
                    unit_data[i] += 1

    return (unit_data, -100)


def remove_duplicates(population):
    """
    If the population has duplicate units removes them
    :param population: population
    :return: population without duplicate units
    """
    result = []
    for (unit, fitness) in population:
        if unit in result:
            population.remove((unit, fitness))
        else:
            result.append(unit)
    return population


def init_enemies():
    """
    Initialize enemies for fitness function
    :return:
    """
    return [([19, 16, 3, 27, 7, 8, 4, 23, 27, 19, 17, 24, 29, 2, 9208, 18, 15, 36, 9975], -100)]
    # ([19, 16, 4, 24, 7, 9, 6, 21, 27, 12, 34, 8, 54, 1, 7215, 21, 6, 33, 8788], -100),
    # ([23, 15, 4, 28, 13, 10, 1, 18, 26, 8, 10, 27, 21, 1, 6662, 16, 5, 40, 5876], -100),
    # ([15, 17, 2, 9, 27, 18, 6, 33, 11, 20, 25, 14, 48, 2, 5484, 10, 24, 20, 9864], -100)]


def log_population(population, iteration):
    """
    Log population using logger
    :param population: population to be logged
    :param iteration: int
    """
    logging.info("-" * 77)
    logging.info("Iteration no. " + str(iteration))
    logging.info("-" * 77)
    for el in sort_population(population):
        logging.info(str(el[1]) + " " + str(el[0]))

    logging.info("-" * 77)
    logging.info("Best unit: " + unit_to_str(population[0]))
    logging.info("Fitness: " + str(population[0][1]))
    logging.info("Worst unit: " + unit_to_str(population[-1]))
    logging.info("Fitness: " + str(population[-1][1]))


def log_crossover_and_mutation(parents, children):
    """
    Log parents -> children transition after crossover and mutation
    :param parents: parent units
    :param children: children units
    """
    logging.info("-" * 50)
    logging.info(str(parents[0][0]) + " +")
    logging.info(str(parents[1][0]))
    logging.info("-" * 50)
    logging.info(str(children[0][0]))
    logging.info(str(children[1][0]))


def main():
    logging.basicConfig(filename='information.log',
                        format='%(levelname)s: %(asctime)s -- %(message)s',
                        level=logging.INFO, datefmt='%d/%m %I:%M %p')

    num_of_iterations = 2
    enemies = init_enemies()

    if len(sys.argv) > 1 and sys.argv[1] == "-n":
        population = initial_population()
    else:
        population = initial_population_from_backup()

    pop = calculate_population_fitness(population, enemies)
    iteration = 0
    log_population(pop, iteration)

    while iteration < num_of_iterations:
        selected = selection(pop)
        for i in range(int(len(selected) / 2)):
            unit1 = random.choice(selected)
            selected.remove(unit1)
            unit2 = random.choice(selected)
            selected.remove(unit2)

            child1, child2 = four_point_crossover(unit1, unit2)
            child1 = mutation(child1)
            child2 = mutation(child2)

            log_crossover_and_mutation([unit1, unit2], [child1, child2])
            pop.append(child1)
            pop.append(child2)

        pop = remove_duplicates(pop)
        missing_values = 150 - len(pop)
        for i in range(missing_values):
            pop.append(generate_random_unit())

        new_generation = []
        old_generation = []
        for el in pop:
            if el[1] == -100:
                new_generation.append(el)
            else:
                old_generation.append(el)

        new_generation = calculate_population_fitness(new_generation, enemies)
        pop = new_generation + old_generation
        pop = elite_selection(sort_population(pop), 100)
        tournament_setup(pop, enemies, "backup.txt")
        iteration += 1
        log_population(pop, iteration)

    logging.info("THE END")

    return 0


if __name__ == "__main__":
    main()
