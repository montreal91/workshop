
def split(x1, x2, alpha):
    return (x1 + alpha * x2) / (1 + alpha)

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 4:
        print("You should specify:\n \tCoordinate of the first vertex;")
        print("\tCoordinate of the second vertex;")
        print
    x1 = float(sys.argv[1])
    x2 = float(sys.argv[2])
    alpha = float(sys.argv[3])
    print(round(split(x1=x1, x2=x2, alpha=alpha), 3))
