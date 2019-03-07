
def is_vowel(letter):
    VOWELS = ('a', 'e', 'i', 'o', 'u')

    return letter in VOWELS

def are_same(l1, l2):
    return is_vowel(l1) == is_vowel(l2)


def check_superheroes(hero1, hero2):
    if len(hero1) != len(hero2):
        return False

    for i in range(len(hero1)):
        if not are_same(hero1[i], hero2[i]):
            return False
    return True


if __name__ == '__main__':
    hero1 = input()
    hero2 = input()

    if check_superheroes(hero1, hero2):
        print("Yes")
    else:
        print("No")
