from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break
    for row in range(0, height):
        for length in range(0, height):
            if row + length < height - 1:
                print(" ", end="")
            else:
                print("#", end="")
        print()


main()