
import numpy as np
import matplotlib.pyplot as plot


def get_dna_list_from_filename(filename):
    with open(filename) as rna_file:
        return [line.strip() for  line in rna_file.readlines()]


def get_dna_gc(dna):
    gc_counter = 0
    for i in range(len(dna)):
        if dna[i] == "G" or dna[i] == "C":
            gc_counter += 1
    return gc_counter / len(dna)


def get_gc_data(dna_list):
    res = []
    for i in range(len(dna_list)):
        gc = get_dna_gc(dna_list[i])
        res.append(
            (len(dna_list[i]), gc)
        )
    return res

if __name__ == '__main__':
    gc_data = get_gc_data(get_dna_list_from_filename("genes.in"))
    for i in range(len(gc_data)):
        print("{0:4d}: {1:.4f}".format(gc_data[i][0], gc_data[i][1]))
