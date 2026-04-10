import random
import time

def main():
    print(
        "\n============================\n"
        "This program generates <n> random words with generator's seed <seed>\n"
        "from <min length> to <max length>, from <min ascii> to <max ascii>\n"
        "and writes it into <filename>;\n"
        "if seed == 0, then seed = current time\n"
        "============================\n"
    )

    n, min_length, max_length, min_ascii, max_ascii, seed = map(
        int,
        input("Input:\n<n> <min length> <max length> <min ascii> <max ascii> <seed>\n").split()
    )

    if max_length < min_length or max_ascii < min_ascii:
        print("Error: max values must be >= min values")
        return

    if (
        max_length < 1 or min_length < 1 or n < 1 or
        min_ascii < 32 or max_ascii < 32 or
        min_ascii > 126 or max_ascii > 126
    ):
        print("Error: invalid input ranges")
        return

    if seed == 0:
        random.seed(time.time())
    else:
        random.seed(seed)

    if n > 5000000:
        print("n too large (>5M)")
        return

    if n >= 1000000:
        res = input(f"n = {n}, press <Y> to continue\n")
        if res != "Y":
            return

    filename = input("Input <filename>:\n")

    with open(filename, 'w') as file:
        for _ in range(n):
            word_len = random.randint(min_length, max_length)
            word = ''.join(
                chr(random.randint(min_ascii, max_ascii))
                for _ in range(word_len)
            )
            file.write(word + '\n')

    print("Done")

if __name__ == "__main__":
    main()
