#class names generator

from random import shuffle, randint

syllables = [
    "a", "e", "i", "o", "u", "y",
    "ab", "ac", "ad", "az", "ax", "aw", "ay",
    "ef", "ej", "ek", "ev", "eu", "et", "es",
    "il", "im", "in", "ir", "iq", "ip", "io", 
    "un", "um", "ul", "uk", "uo", "up", "uq",
    "yp", "yq", "yr", "ys", "yj", "yi", "yh",
    # "ba", "ca", "da", "za", "xa", "wa",
]

shuffle(syllables)
def GenerateClassNames(s_list):
    name_file = open("names.txt", "w")
    for s1 in s_list:
        for s2 in s_list:
            for s3 in s_list:
                for s4 in s_list:
                    name_file.write(s1+s2+s3+"\n")
    name_file.close()

def GenerateBigNumbers(n):
    num_file = open("numbers", "w")
    for i in range(n):
        num_file.write(str(randint(9000000, 90000000))+"\n")
    num_file.close()

if __name__ == '__main__':
    # GenerateBigNumbers(41**4)
    GenerateClassNames(syllables)
