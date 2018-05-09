
import sys

def find_byte_string(b_string, filename):
    res = []
    with open(filename, 'r') as ifile:
        res = [i for i in range(len(ifile) - len(b_string) + 1)
        if int(ifile[i:i+8], 2) & int(b_string,2)]
    return res

def main():
    if len(sys.argv) > 2:
        print(find_byte_string(sys.argv[1], sys.argv[2]))
    else:
        print("Nah")

if __name__ == '__main__':
    main()