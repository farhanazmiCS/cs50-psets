from cs50 import get_float


def main():
    coins = 0
    while True:
        oweMoney = get_float("Change owed in dollars: ")
        if oweMoney > 0:
            break
    oweMoneyCents = oweMoney * 100
    while oweMoneyCents >= 25:
        coins += 1
        oweMoneyCents -= 25
        if oweMoneyCents < 25:
            break
    while oweMoneyCents >= 10:
        coins += 1
        oweMoneyCents -= 10
        if oweMoneyCents < 10:
            break
    while oweMoneyCents >= 5:
        coins += 1
        oweMoneyCents -= 5
        if oweMoneyCents < 5:
            break
    while oweMoneyCents >= 1:
        coins += 1
        oweMoneyCents -= 1
        if oweMoneyCents < 1:
            break
    print(coins)


main()