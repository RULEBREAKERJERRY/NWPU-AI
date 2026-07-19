'''
# 10 个城市
python3 ga.py --cities 10 --population 50 --generations 100 --log-every 50 --seed 42 

# 30 个城市
python3 ga.py --cities 30 --population 100 --generations 500 --crossover-method pmx --mutation-method reverse --log-every 250 --seed 7
'''


import argparse
import math
import random
import time


# Oliver TSP 问题前 10 个城市坐标
CITY_10 = [
    (1, 87, 7),
    (2, 91, 38),
    (3, 83, 46),
    (4, 71, 44),
    (5, 64, 60),
    (6, 68, 58),
    (7, 83, 69),
    (8, 87, 76),
    (9, 74, 78),
    (10, 71, 71),
]


# Oliver TSP 问题 30 个城市坐标
CITY_30 = [
    (1, 87, 7),
    (2, 91, 38),
    (3, 83, 46),
    (4, 71, 44),
    (5, 64, 60),
    (6, 68, 58),
    (7, 83, 69),
    (8, 87, 76),
    (9, 74, 78),
    (10, 71, 71),
    (11, 58, 69),
    (12, 54, 62),
    (13, 51, 67),
    (14, 37, 84),
    (15, 41, 94),
    (16, 2, 99),
    (17, 7, 64),
    (18, 22, 60),
    (19, 25, 62),
    (20, 18, 54),
    (21, 4, 50),
    (22, 13, 40),
    (23, 18, 40),
    (24, 24, 42),
    (25, 25, 38),
    (26, 41, 26),
    (27, 45, 21),
    (28, 44, 35),
    (29, 58, 35),
    (30, 62, 32),
]


KNOWN_BEST = {
    10: 166.541336,
    30: 424.869292,
}


# 计算两个城市之间的欧氏距离
def distance(city1, city2):
    return math.sqrt((city1[1] - city2[1]) ** 2 + (city1[2] - city2[2]) ** 2)


# 计算一条路径的总长度，最后一个城市要回到第一个城市
def route_length(route, cities):
    city_dict = {city[0]: city for city in cities}
    total = 0

    for i in range(len(route) - 1):
        total += distance(city_dict[route[i]], city_dict[route[i + 1]])

    total += distance(city_dict[route[-1]], city_dict[route[0]])
    return total


# 适应度函数：路径越短，适应度越高
# 使用三次方是为了拉开长路径和短路径的差距，使轮盘赌选择更明显地偏向较优路径
def fitness(route, cities):
    return 1 / (route_length(route, cities) ** 3)


# 随机生成一条合法路径，也就是一个染色体
def create_route(cities):
    route = [city[0] for city in cities]
    random.shuffle(route)
    return route


# 初始化种群：随机生成 population_size 条路径
def init_population(cities, population_size):
    population = []

    for _ in range(population_size):
        population.append(create_route(cities))

    return population


# 找出当前种群中路径最短的个体
def find_best(population, cities):
    best_route = population[0]
    best_length = route_length(best_route, cities)

    for route in population[1:]:
        length = route_length(route, cities)
        if length < best_length:
            best_route = route
            best_length = length

    return best_route[:], best_length


# 轮盘赌选择：适应度越高，被选中的概率越大
def roulette_select(population, fitness_list):
    fitness_sum = sum(fitness_list)
    rand = random.random() * fitness_sum
    current = 0

    for i in range(len(population)):
        current += fitness_list[i]
        if current >= rand:
            return population[i][:]

    return population[-1][:]


# PMX 部分匹配交叉
def pmx_crossover(parent1, parent2):
    size = len(parent1)
    start, end = sorted(random.sample(range(size), 2))

    child = [None] * size
    child[start:end + 1] = parent1[start:end + 1]

    for i in range(start, end + 1):
        city = parent2[i]

        if city not in child:
            pos = i

            while True:
                mapped_city = parent1[pos]
                pos = parent2.index(mapped_city)

                if child[pos] is None:
                    child[pos] = city
                    break

    for i in range(size):
        if child[i] is None:
            child[i] = parent2[i]

    return child


# OX 顺序交叉
def ox_crossover(parent1, parent2):
    size = len(parent1)
    start, end = sorted(random.sample(range(size), 2))

    child = [None] * size
    child[start:end + 1] = parent1[start:end + 1]

    index = (end + 1) % size
    for city in parent2:
        if city not in child:
            child[index] = city
            index = (index + 1) % size

    return child


# 根据参数选择交叉算子
def crossover(parent1, parent2, crossover_name):
    if crossover_name == "ox":
        return ox_crossover(parent1, parent2)
    if crossover_name == "pmx":
        return pmx_crossover(parent1, parent2)

    raise ValueError("未知交叉算子")


# 逆转变异：随机选择一段路径并反转
def reverse_mutation(route, mutation_rate):
    new_route = route[:]

    if random.random() < mutation_rate:
        start, end = sorted(random.sample(range(len(new_route)), 2))
        new_route[start:end + 1] = reversed(new_route[start:end + 1])

    return new_route


# 对换变异：随机选择两个城市并交换位置
def swap_mutation(route, mutation_rate):
    new_route = route[:]

    if random.random() < mutation_rate:
        i, j = random.sample(range(len(new_route)), 2)
        new_route[i], new_route[j] = new_route[j], new_route[i]

    return new_route


# 根据参数选择变异算子
def mutate(route, mutation_rate, mutation_name):
    if mutation_name == "reverse":
        return reverse_mutation(route, mutation_rate)
    if mutation_name == "swap":
        return swap_mutation(route, mutation_rate)

    raise ValueError("未知变异算子")


# 使用遗传算法求解 TSP
def genetic_algorithm(
    cities,
    population_size,
    generations,
    crossover_rate,
    mutation_rate,
    crossover_name,
    mutation_name,
    log_every,
):
    start_time = time.perf_counter()

    population = init_population(cities, population_size)
    best_route, best_length = find_best(population, cities)

    for generation in range(1, generations + 1):
        # 每一代先保存当前最优个体，防止优秀路径在交叉、变异中丢失
        now_best_route, now_best_length = find_best(population, cities)
        if now_best_length < best_length:
            best_route = now_best_route
            best_length = now_best_length

        if generation == 1 or generation % log_every == 0:
            print(f"第 {generation:4d} 代，本代最优: {now_best_length:.6f}，当前全局最优: {best_length:.6f}")

        new_population = [best_route[:]]
        fitness_list = [fitness(route, cities) for route in population]

        while len(new_population) < population_size:
            parent1 = roulette_select(population, fitness_list)
            parent2 = roulette_select(population, fitness_list)

            if random.random() < crossover_rate:
                child1 = crossover(parent1, parent2, crossover_name)
                child2 = crossover(parent2, parent1, crossover_name)
            else:
                child1 = parent1[:]
                child2 = parent2[:]

            new_population.append(mutate(child1, mutation_rate, mutation_name))

            if len(new_population) < population_size:
                new_population.append(mutate(child2, mutation_rate, mutation_name))

        population = new_population

    elapsed_time = time.perf_counter() - start_time
    return best_route, best_length, elapsed_time


def build_parser():
    parser = argparse.ArgumentParser(
        description="使用遗传算法求解 TSP 旅行商问题",
    )

    parser.add_argument(
        "--cities",
        type=int,
        choices=[10, 30],
        default=10,
        help="选择城市数量：10 或 30",
    )

    parser.add_argument(
        "--population",
        type=int,
        default=100,
        help="种群规模",
    )

    parser.add_argument(
        "--generations",
        type=int,
        default=500,
        help="进化代数",
    )

    parser.add_argument(
        "--crossover",
        type=float,
        default=0.8,
        help="交叉概率",
    )

    parser.add_argument(
        "--mutation",
        type=float,
        default=0.05,
        help="变异概率",
    )

    parser.add_argument(
        "--crossover-method",
        choices=["pmx", "ox"],
        default="pmx",
        help="交叉算子：pmx 表示部分匹配交叉，ox 表示顺序交叉",
    )

    parser.add_argument(
        "--mutation-method",
        choices=["reverse", "swap"],
        default="reverse",
        help="变异算子：reverse 表示逆转变异，swap 表示对换变异",
    )

    parser.add_argument(
        "--seed",
        type=int,
        default=None,
        help="随机种子，设置后便于复现实验结果",
    )

    parser.add_argument(
        "--log-every",
        type=int,
        default=50,
        help="每隔多少代打印一次当前结果",
    )

    return parser


def main():
    args = build_parser().parse_args()

    if args.seed is not None:
        random.seed(args.seed)

    cities = CITY_10 if args.cities == 10 else CITY_30

    print("TSP 遗传算法实验")
    print("城市数量:", args.cities)
    print("种群规模:", args.population)
    print("进化代数:", args.generations)
    print("交叉概率:", args.crossover)
    print("变异概率:", args.mutation)
    print("交叉算子:", args.crossover_method)
    print("变异算子:", args.mutation_method)
    print()

    best_route, best_length, elapsed_time = genetic_algorithm(
        cities,
        args.population,
        args.generations,
        args.crossover,
        args.mutation,
        args.crossover_method,
        args.mutation_method,
        args.log_every,
    )

    print()
    print("搜索结束")
    print("最优路径:")
    print(" -> ".join(str(city) for city in best_route + [best_route[0]]))
    print(f"最优路径长度: {best_length:.6f}")
    print(f"参考最优长度: {KNOWN_BEST[args.cities]:.6f}")
    print(f"与参考最优差距: {best_length - KNOWN_BEST[args.cities]:.6f}")
    print(f"运行时间: {elapsed_time:.6f} 秒")


if __name__ == "__main__":
    main()