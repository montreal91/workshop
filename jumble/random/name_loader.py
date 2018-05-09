
import json

def ReadNames(filename):
    names = []
    with open(filename) as data_file:
        names = json.load(data_file)
    return names

if __name__ == '__main__':
    n = ReadNames("n.json")
    for l in n:
        print(type(l), l)