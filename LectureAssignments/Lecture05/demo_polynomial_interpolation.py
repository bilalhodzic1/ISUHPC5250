"""
Lecture 5 assignment. Gaussian method
"""

import numpy as np


def GaussianElimination(A, b):
    """
    Function solves a system using the gaussian Gaussian Elimination method
    """
    x = np.append(A, b, axis=1)
    print(x)
    num_rows = x.shape[0]
    num_cols = x.shape[1]
    for i in range(num_cols - 2):
        for j in range(i + 1, num_rows):
            numerator = x[j][i]
            if numerator == 0:
                continue
            denom = x[i][i]
            scalarval = numerator / denom
            row_needed = np.copy(x[i])
            row_needed = row_needed * scalarval
            x[j] = x[j] - row_needed
            print("-------------------")
            print(x)
    print(x)


test_arr = np.array([[2.0, -2.0, 0], [1.0, -1.0, 1], [0, 3.0, -2.0]])
test_vector = np.array([[-6.0], [1.0], [-5.0]])

GaussianElimination(test_arr, test_vector)
