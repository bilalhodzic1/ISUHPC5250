def sqrt(x, kmax):
    guess = x
    for i in range(kmax):
        guess = 0.5 * (guess + (x/guess))
    return guess

z = sqrt(19562, 100)
print(z)
