# Abs functions makes all values positive
def abs(x):
    if x < 0:
        return x * -1
    return x


def sqrt(x, kmax):
    tolerance = 0.00000000000001

    if x < 0:
        print("cannot square root negative")
        return 0
    elif x == 0:
        return 0
    guess = x
    for i in range(kmax):
        guess = 0.5 * (guess + (x / guess))
    return guess


def factorial(x):
    if x == 0:
        return 0
    if x < 0:
        print("Factorial of negative is not possible")
        return -1
    return x * factorial(x - 1)


def exp(x):
    e = 2.7182818284590451
    x_0 = int(round(x))
    z = x - x_0
    e_to_z = 0
    for i in range(10):
        val_to_add = (z**i) / (factorial(i))
        e_to_z = e_to_z + val_to_add
    return (e**x_0) * (e_to_z)


def ln(x, kmax):
    guess = x
    for i in range(kmax):
        guess = guess - 1 + (x * exp(-guess))
    return guess


z = sqrt(19562, 100)
print(f"square root of 19562 = {z}")
fac = factorial(10)
print(f"factorial of 10 = {fac}")
expon = exp(5.782)
print(f"e^5.782 = {expon}")
nlog = ln(18, 100)
print(f"ln(18) = {nlog}")
