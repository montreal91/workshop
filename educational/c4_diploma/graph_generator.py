
import sys

from random import shuffle


def generate_clique(list_of_indexes):
	res = []
	for i in range(len(list_of_indexes)-1):
		for j in range(i+1, len(list_of_indexes)):
			res.append((list_of_indexes[i], list_of_indexes[j]))

	return res


def generate_graph(n, c1, c2):
	verts = [i for i in range(n)]
	shuffle(verts)

	c1_edges = generate_clique(verts[:c1])
	c2_edges = generate_clique(verts[-c2:])

	return c1_edges, c2_edges


if __name__ == '__main__':
	n = int(sys.argv[1])
	c1 = int(sys.argv[2])
	c2 = int(sys.argv[3])
	e1, e2 = generate_graph(n, c1, c2)

	print(2)
	print(n)
	[print(e[0], e[1]) for e in e1]
	print()
	[print(e[0], e[1]) for e in e2]
	print("\n", -1, -1)
