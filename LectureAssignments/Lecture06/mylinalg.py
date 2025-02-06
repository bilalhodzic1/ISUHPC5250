"""
Linear algebra module for doing some linear algebra
"""

import matplotlib.pyplot as plt
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
            x[j] = np.round(x[j] - row_needed, 17)
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
    # print(output_string)
    return variables


def LeastSquares(x, f, k):
    """Function for finding coeffecients to a polynomial approx using LeastSquares"""
    # declare A as the coeffecient matrix
    A = []
    for i in enumerate(x):
        row_vals = []
        for j in range(k):
            row_vals.append(i[1] ** j)
        A.append(row_vals)
    A = np.array(A)
    # Create the f vector from the reuslts
    f_vector = []
    for i in enumerate(f):
        f_vector.append([i[1]])
    f_vector = np.array(f_vector)
    # Transpose A
    A_T = np.transpose(A)
    # compute left side and right side of least squares equation and make sure they are floats
    left_result = np.dot(A_T, A)
    right_result = np.dot(A_T, f_vector)
    left_result = left_result * 1.0
    right_result = right_result * 1.0
    # conduct GaussianElimination to get the final results
    coeffecients_vector = GaussianElimination(left_result, right_result)
    print(np.array(coeffecients_vector))
    return np.round(coeffecients_vector, 10)


if __name__ == "__main__":
    # Create X and Y coords for cosine within range
    nodex = np.linspace(-np.pi, np.pi, 51)
    result = np.array(list(map(np.cos, nodex)))
    # nodex = np.array([0, 1, 2, 3])
    # result = np.array([3, 0, 1, 3])
    # Conduct least squares to find best fit polynomial
    coeffecients = LeastSquares(nodex, result, 5)
    dif_y_vals = []
    # Evaluate values of x at this polynomial
    for x_val in range(len(nodex)):
        sum = 0.0
        for cof_val in range(5):
            sum += (nodex[x_val] ** cof_val) * coeffecients[cof_val]
        dif_y_vals.append(sum)
    # Plot the original values as points and the polynomial as the fit line
    plt.plot(nodex, result, "ro")
    plt.plot(nodex, dif_y_vals)
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.show()
