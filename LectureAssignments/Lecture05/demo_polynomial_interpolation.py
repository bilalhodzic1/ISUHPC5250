"""
Lecture 5 assignment. Gaussian method
"""

import numpy as np

np.set_printoptions(linewidth=1000)


def GaussianElimination(A, b):
    """
    Function solves a system using the gaussian Gaussian Elimination method
    """
    # Append b to A
    x = np.append(A, b, axis=1)
    # Get rows and cols for looping
    num_rows = x.shape[0]
    num_cols = x.shape[1]
    # Loop through conduction Gaussian Elmination to get a triangle of 0s
    for i in range(num_cols - 2):
        for j in range(i + 1, num_rows):
            numerator = x[j][i]
            if numerator == 0:
                continue
            denom = x[i][i]
            scalarval = numerator / denom
            row_needed = np.copy(x[i])
            row_needed = row_needed * scalarval
            # subtraction resulted in extremely small decimals sometimes instead of 0
            # added round of result to 10 decimal places to avoid this
            # occurs due to
            x[j] = np.round(x[j] - row_needed, 10)
    # determine number of variables needed to complete the problem and set an array of all none
    num_vars = A.shape[1]
    variables = [None] * num_vars
    for i in range(num_vars):
        # determine the row of interest from the array
        cur_var_index = x.shape[0] - (i + 1)
        variable_row = x[cur_var_index]
        is_set = False
        cur_addition = 0
        # loop in reverse the values in the row. Substitute variables where needed
        # NOTE this loop assumes trangle to work
        for j in range(num_vars - 1, 0, -1):
            # Dont do anything on 0s
            if variable_row[j] == 0:
                continue
            # Sunstitute variable and multiple if possible
            if variables[j] is not None:
                cur_addition += variable_row[j] * variables[j]
            # Set variable where it doesnt exist
            else:
                variables[j] = (
                    variable_row[num_cols - 1] - cur_addition
                ) / variable_row[j]
                is_set = True
        # Set varaible if it wasnt. This occurs on last variable we set
        if not is_set:
            variables[0] = (variable_row[num_cols - 1] - cur_addition) / variable_row[0]
    output_string = ""
    current_exp = num_vars - 1
    for i in range(num_vars):
        if current_exp == 0:
            output_string += f"{variables[i]}"
        else:
            output_string += f"{variables[i]}x^{current_exp} + "
        current_exp -= 1
    print(output_string)
    return output_string


x_0 = -0.1
x_1 = -0.02
x_2 = 0.02
x_3 = 0.1

test_arr = np.array(
    [
        [1.0, x_0, x_0**2, x_0**3],
        [1.0, x_1, x_1**2, x_1**3],
        [1.0, x_2, x_2**2, x_2**3],
        [1.0, x_3, x_3**2, x_3**3],
    ]
)
# test_arr = np.array(
#    [[1.0, 2.0, -1.0, 1.0], [-1, 1, 2, -1], [2, -1, 2, 2], [1, 1, -1, 2]]
# )
test_vector = np.array([[np.cos(x_0)], [np.cos(x_1)], [np.cos(x_2)], [np.cos(x_3)]])
# test_vector = np.array([[6.0], [3.0], [14.0], [8.0]])

GaussianElimination(test_arr, test_vector)
