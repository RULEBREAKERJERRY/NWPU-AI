'''
# 不可达状态
python3 astar.py --start '1 2 3 8 0 4 7 5 6' --goal '1 2 3 8 0 4 7 6 5'

# 可达状态
# 错位数
python3 astar.py --heuristic misplaced
python3 astar.py --start '5 6 8 3 1 2 0 4 7' --heuristic misplaced
python3 astar.py --start '5 4 0 2 1 8 3 6 7' --heuristic misplaced

# 曼哈顿距离
python3 astar.py --heuristic manhattan
python3 astar.py --start '5 6 8 3 1 2 0 4 7' --heuristic manhattan
python3 astar.py --start '5 4 0 2 1 8 3 6 7' --heuristic manhattan
'''


import argparse
import heapq
import time


# 默认初始状态和目标状态
DEFAULT_START = (2, 8, 3,
                 1, 6, 4,
                 7, 0, 5)

DEFAULT_GOAL = (1, 2, 3,
                8, 0, 4,
                7, 6, 5)


# 把命令行输入的字符串转换成八数码状态元组
def parse_state(text):
    nums = [int(x) for x in text.replace(",", " ").split()]

    if len(nums) != 9:
        raise argparse.ArgumentTypeError("状态必须包含 9 个数字。")

    if sorted(nums) != list(range(9)):
        raise argparse.ArgumentTypeError("状态必须恰好包含 0 到 8，且不能重复。")

    return tuple(nums)


# 按 3 行 3 列打印棋盘，其中 0 显示为空格
def print_board(state):
    for i in range(0, 9, 3):
        row = state[i:i + 3]
        print(" ".join(" " if x == 0 else str(x) for x in row))
    print()


# 计算状态的逆序数（判断可达性时不把空格 0 算进去）
def inversion_count(state):
    nums = [x for x in state if x != 0]
    count = 0
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] > nums[j]:
                count += 1
    return count


# 判断初始状态是否可以到达目标状态
def can_reach(start, goal):
    return inversion_count(start) % 2 == inversion_count(goal) % 2


# 计算曼哈顿距离
def manhattan(state, goal):
    distance = 0
    for num in range(1, 9):
        now = state.index(num)
        target = goal.index(num)

        now_row, now_col = now // 3, now % 3
        target_row, target_col = target // 3, target % 3

        distance += abs(now_row - target_row) + abs(now_col - target_col)
    return distance


# 计算错位数：统计不在目标位置上的数字个数，不统计空格 0
def misplaced_tiles(state, goal):
    count = 0
    for i in range(9):
        if state[i] != 0 and state[i] != goal[i]:
            count += 1
    return count


# 根据命令行参数选择启发函数
def choose_heuristic(name):
    if name == "manhattan":
        return manhattan, "曼哈顿距离"
    if name == "misplaced":
        return misplaced_tiles, "错位数"

    raise ValueError("未知启发函数")


# 扩展当前状态，生成空格向上、下、左、右移动后的后继状态
def get_next_states(state):
    next_states = []
    zero = state.index(0)
    row, col = zero // 3, zero % 3

    moves = [
        (-1, 0, "上"),
        (1, 0, "下"),
        (0, -1, "左"),
        (0, 1, "右"),
    ]

    for dr, dc, move_name in moves:
        new_row = row + dr
        new_col = col + dc

        if 0 <= new_row < 3 and 0 <= new_col < 3:
            new_zero = new_row * 3 + new_col
            new_state = list(state)
            new_state[zero], new_state[new_zero] = new_state[new_zero], new_state[zero]
            next_states.append((tuple(new_state), move_name))

    return next_states


# 根据 parent 返回指针，从目标状态回溯出完整路径
def build_path(parent, move, end_state):
    path = []
    state = end_state

    while state is not None:
        path.append((state, move.get(state, "开始")))
        state = parent.get(state)

    path.reverse()
    return path


# 使用 A* 算法搜索从 start 到 goal 的最短移动路径
def astar(start, goal, heuristic):
    start_time = time.perf_counter()

    # 先判断是否可达，避免对无解状态进行无意义搜索
    if not can_reach(start, goal):
        print("该初始状态无法到达目标状态。")
        print("初始状态逆序数:", inversion_count(start))
        print("目标状态逆序数:", inversion_count(goal))
        return None

    # OPEN 表：保存待扩展节点，按 f = g + h 从小到大排列
    open_list = []

    # g[state] 表示从初始状态到 state 的实际移动步数，即 g(n)
    g = {start: 0}

    # h 表示当前状态到目标状态的估计距离，即 h(n)
    h = heuristic(start, goal)
    heapq.heappush(open_list, (g[start] + h, h, start))

    # CLOSED 表：保存已经扩展过的状态
    closed = set()

    # parent 用来记录返回指针，move 用来记录每一步移动方向
    parent = {start: None}
    move = {start: "开始"}

    expanded_count = 0
    generated_count = 1

    while open_list:
        # 每次取出 OPEN 表中 f 值最小的状态进行扩展
        f_value, h_value, current = heapq.heappop(open_list)

        # 如果该状态已经扩展过，就跳过
        if current in closed:
            continue

        closed.add(current)
        expanded_count += 1

        if current == goal:
            path = build_path(parent, move, current)
            elapsed_time = time.perf_counter() - start_time
            return path, expanded_count, generated_count, elapsed_time

        # 生成当前状态的所有后继状态
        for next_state, move_name in get_next_states(current):
            if next_state in closed:
                continue

            # 八数码中每移动一步代价为 1
            new_g = g[current] + 1

            # 如果第一次到达该状态，或发现了更短路径，就更新记录
            if next_state not in g or new_g < g[next_state]:
                g[next_state] = new_g
                h = heuristic(next_state, goal)
                f = new_g + h

                # 记录返回指针和移动方向，方便最后还原路径
                parent[next_state] = current
                move[next_state] = move_name

                heapq.heappush(open_list, (f, h, next_state))
                generated_count += 1

    elapsed_time = time.perf_counter() - start_time
    return None, expanded_count, generated_count, elapsed_time


def build_parser():
    parser = argparse.ArgumentParser(
        description="使用 A* 算法求解八数码问题，状态中 0 表示空格",
    )

    parser.add_argument(
        "--start",
        type=parse_state,
        default=DEFAULT_START,
        help="初始状态：9 个数字，用空格或逗号分隔",
    )

    parser.add_argument(
        "--goal",
        type=parse_state,
        default=DEFAULT_GOAL,
        help="目标状态：9 个数字，用空格或逗号分隔",
    )

    parser.add_argument(
        "--heuristic",
        choices=["manhattan", "misplaced"],
        default="manhattan",
        help="启发函数：manhattan 表示曼哈顿距离，misplaced 表示错位数",
    )

    return parser


def main():
    args = build_parser().parse_args()
    start_state = args.start
    goal_state = args.goal
    heuristic, heuristic_name = choose_heuristic(args.heuristic)

    print("初始状态:")
    print_board(start_state)

    print("目标状态:")
    print_board(goal_state)

    print("启发函数:", heuristic_name)
    print()

    result = astar(start_state, goal_state, heuristic)

    if result is None:
        return

    path, expanded_count, generated_count, elapsed_time = result

    if path is None:
        print("OPEN 表为空，搜索失败。")
        print("扩展节点数:", expanded_count)
        print("生成节点数:", generated_count)
        print(f"搜索耗时: {elapsed_time:.6f} 秒")
        return

    print("搜索成功，移动步骤如下:")
    for step, (state, move_name) in enumerate(path):
        g_value = step
        h_value = heuristic(state, goal_state)
        f_value = g_value + h_value

        print(f"Step {step}, 移动: {move_name}, g={g_value}, h={h_value}, f={f_value}")
        print_board(state)

    print("性能统计:")
    print("启发函数:", heuristic_name)
    print("路径步数:", len(path) - 1)
    print("扩展节点数:", expanded_count)
    print("生成节点数:", generated_count)
    print(f"搜索耗时: {elapsed_time:.6f} 秒")


if __name__ == "__main__":
    main()