"""Simple math functions module"""


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
        rel_error = abs(s_n - s_np1) / abs(s_n)
        if rel_error < tolerance:
            guess = s_np1
            return guess
        guess = s_np1
        return guess


def factorial(x):
    """Gets the factorial of input x"""
    # if 0 return 0
    if x == 0:
        return 0
    # if negative factorials cannot be defined at negative so return -1 for invalid
    if x < 0:
        print("Factorial of negative is not possible")
        return -1
    # recursively return factorial. Will go to base case 0 and climb back
    return x * factorial(x - 1)


def exp(x):
    """Find e to the power of given input x"""
    tolerance = 0.00000000000001
    # declare e as constant value
    e = 2.7182818284590451
    # get closest into to x
    x_0 = int(round(x))
    # find z value being number close to 0
    z = x - x_0
    # conduct taylor expansion to approximate e^x
    e_to_z = 0
    for i in range(10):
        val_to_add = (z**i) / (factorial(i))
        # Check if value to add is lower than the tolerance
        if val_to_add < tolerance:
            break
        e_to_z = e_to_z + val_to_add
    return (e**x_0) * (e_to_z)


def ln(x, kmax):
    """Finds natural log of given value x using newtons method"""
    # set tolerance value
    tolerance = 0.00000000000001
    # set intiial guess to x
    guess = x
    for _ in range(kmax):
        # Check relative error is less than tolerance and return
        s_n = guess
        s_np1 = guess - 1 + (x * exp(-guess))
        rel_error = (abs(s_np1 - s_n)) / abs(s_n)
        if rel_error < tolerance:
            guess = s_np1
            return guess
        guess = s_np1
        return guess


sqr = sqrt(19562, 100)
print(f"square root of 19562 = {sqr}")
fac = factorial(10)
print(f"factorial of 10 = {fac}")
expon = exp(5.782)
print(f"e^5.782 = {expon}")
nlog = ln(18, 100)
print(f"ln(18) = {nlog}")
