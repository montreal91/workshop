
def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)


if __name__ == '__main__':
	import sys

	if len(sys.argv) < 3:
		print("Not enough arguments.")

	print(gcd(int(sys.argv[1]), int(sys.argv[2])))
