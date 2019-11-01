
import random

NUCLEOTIDES = "AGUC"

START_CODONS = (
    ("A", "U", "G"),
)

STOP_CODONS = (
    ("U", "A", "G"),
    ("U", "A", "A"),
    ("U", "G", "A"),
)

def generate_rna_sequence(n):
    # Гененируем длиннющий кортеж, потому что считаем, что РНК не меняется
    return tuple(random.choice(NUCLEOTIDES) for _ in range(n))


def get_codon(sequence, pos):
    seq_len = len(sequence)
    if pos >= seq_len or pos + 1 >= seq_len or pos + 2 >= seq_len:
        # С данной позиции кодон считать нельзя, поэтому возвращаем None
        return None

    return sequence[pos], sequence[pos + 1], sequence[pos + 2]


def can_translate(start_pos, stop_pos):
    # Анализируем, можно ли транслировать последовательность

    if start_pos is None:
        return False

    return start_pos < stop_pos


def analyze_sequence(sequence, pos):
    # производим анализ последовательности по одной рамке считывания

    codon = get_codon(sequence, pos)
    counter = {}
    start_pos = None
    stop_pos = -1

    while codon is not None:
        counter.setdefault(codon, 0)
        counter[codon] += 1

        if codon in START_CODONS and start_pos is None:
            start_pos = pos
        if codon in STOP_CODONS:
            stop_pos = pos

        pos += 3
        codon = get_codon(sequence, pos)

    return (
        can_translate(start_pos, stop_pos),
        max(counter.items(), key=lambda item: item[1])
    )


# print(analyze_sequence(
#     tuple("A" for _ in range(10)), 0
# ))
# print(analyze_sequence(
#     tuple(n for n in "AUGUUUGGGGGGUGA"), 0
# ))
# print(analyze_sequence(
#     tuple(n for n in "AUGUUUGGGGGGUGA"), 1
# ))

def convert_codon_to_string(codon):
    return "".join(codon)

def main():
    rna = generate_rna_sequence(100)
    res_0 = analyze_sequence(rna, 0)
    res_1 = analyze_sequence(rna, 1)
    res_2 = analyze_sequence(rna, 2)
    can_translate = any(r[0] for r in (res_0, res_1, res_2))
    print(convert_codon_to_string(res_0[1][0]), res_0[1][1])
    print(convert_codon_to_string(res_1[1][0]), res_1[1][1])
    print(convert_codon_to_string(res_2[1][0]), res_2[1][1])
    if can_translate:
        print("Эту последовательность можно транслировать")
    else:
        print("Эту последовательность нельзя транслировать")


if __name__ == '__main__':
    main()
