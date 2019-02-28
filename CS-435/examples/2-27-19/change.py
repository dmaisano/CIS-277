def makeChange(n):
    coins = []

    while n >= 25:
        coins.append(25)
        n -= 25

    while n >= 10:
        coins.append(10)
        n -= 10

    while n >= 5:
        coins.append(5)
        n -= 5

    while n >= 1:
        coins.append(1)
        n -= 1

    return coins


print(makeChange(61))
