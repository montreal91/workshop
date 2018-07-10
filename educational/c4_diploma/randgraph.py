
from random import random


def loaded_toss(p):
    x = random()
    return x < p


def generate_random_graph(vertexes, edge_probability):
    graph = []
    for i in range(vertexes):
        for j in range(i + 1, vertexes):
            if (loaded_toss(edge_probability)):
                graph.append((i, j))

    print(vertexes)
    print_graph(graph)


def print_graph(graph):
    [print(edge[0], edge[1]) for edge in graph]
    print(-1, -1) # Terminator


def process_input():
    import sys

    if len(sys.argv) < 3:
        print("Not enough arguments.", file=sys.stderr)
        return

    try:
        vertexes = int(sys.argv[1])
        eprob = float(sys.argv[2])

        if not 0 <= eprob <= 1:
            print(
                "Probability should be a real number between 0 and 1",
                file=sys.stderr
            )
            return

        return vertexes, eprob
    except ValueError as e:
        print(e, file=sys.stderr)


if __name__ == '__main__':
    params = process_input()
    if params is not None:
        generate_random_graph(*params)
