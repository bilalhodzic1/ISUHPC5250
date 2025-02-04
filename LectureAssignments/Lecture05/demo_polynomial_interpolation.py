"""
Lecture 5 assignment. Gaussian method
"""

import numpy as np


def GaussianElimination(A, b):
    """
    Function solves a system using the gaussian Gaussian Elimination method
    """
    x = np.append(A, b, axis=1)
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
    num_vars = A.shape[1]
    variables = [None] * num_vars
    for i in range(num_vars):
        cur_var_index = x.shape[0] - (i + 1)
        variable_row = x[cur_var_index]
        is_set = False
        cur_addition = 0
        for j in range(num_vars - 1, 0, -1):
            print(j)
            if variable_row[j] == 0:
                continue
            if variables[j] is not None:
                cur_addition += variable_row[j] * variables[j]
            else:
                variables[j] = (
                    variable_row[num_cols - 1] - cur_addition
                ) / variable_row[j]
                is_set = True
        if not is_set:
            variables[0] = (variable_row[num_cols - 1] - cur_addition) / variable_row[0]
    print(variables)


test_arr = np.array([[1.0, -2.0, 1.0], [2.0, 1.0, -3.0], [4, -7.0, 1.0]])
test_vector = np.array([[0], [5.0], [-1.0]])

GaussianElimination(test_arr, test_vector)
