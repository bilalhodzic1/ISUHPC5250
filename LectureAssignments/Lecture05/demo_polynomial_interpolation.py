"""
Lecture 5 assignment. Gaussian method
"""

import numpy as np

# def GaussianElimination(A, b):
#    return 0

x = np.array([[1.0, -2.0, 1.0, 0], [2.0, 1.0, -3.0, 5.0], [4.0, -7.0, 1.0, -1.0]])

num_rows = x.shape[0]
num_cols = x.shape[1]

for i in range(num_cols - 2):
    for j in range(i + 1, num_rows):
        numerator = x[j][i]
        denom = x[i][i]
        scalarval = numerator / denom
        row_needed = np.copy(x[i])
        row_needed = row_needed * scalarval
        x[j] = x[j] - row_needed
print(x)
