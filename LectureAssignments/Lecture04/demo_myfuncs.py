def sqrt(x, kmax):
    """Takes the square root of number with newtons method of approximation"""
    # Declare tolerance value
    tolerance = 0.00000000000001
    # check for negative root and return error
    if x < 0:
        print("cannot square root negative")
        return 0
    # check for 0 and return 0
    if x == 0:
        return 0
    # guess starts at value. Conduct newtons method
    guess = x
    for _ in range(kmax):
        # check relative error is within tolerance. If not return value and stop iteration
        s_n = guess
        s_np1 = 0.5 * (guess + (x / guess))
        rel_error = (s_n - s_np1) / s_n
        if rel_error < tolerance:
            guess = s_np1
            return guess
        guess = s_np1
        return guess


def factorial(x):
    """Gets the factorial of input x"""
    if x == 0:
        return 0
    if x < 0:
        print("Factorial of negative is not possible")
        return -1
    return x * factorial(x - 1)


def exp(x):
    """Find e to the power of given input x"""
    e = 2.7182818284590451
    x_0 = int(round(x))
    z = x - x_0
    e_to_z = 0
    for i in range(10):
        val_to_add = (z**i) / (factorial(i))
        e_to_z = e_to_z + val_to_add
    return (e**x_0) * (e_to_z)


def ln(x, kmax):
    """Finds natural log of given value x using newtons methid"""
    guess = x
    for _ in range(kmax):
        guess = guess - 1 + (x * exp(-guess))
    return guess


sqr = sqrt(19562, 100)
print(f"square root of 19562 = {sqr}")
fac = factorial(10)
print(f"factorial of 10 = {fac}")
expon = exp(5.782)
print(f"e^5.782 = {expon}")
nlog = ln(18, 100)
print(f"ln(18) = {nlog}")
