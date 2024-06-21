import numpy as np

# Create a 2D array (matrix) of shape (3, 3) and extract the element in the second row and third column.

arr = np.array([[1,2,3],
                [4,5,6],
                [7,8,9]])

print(arr[1:2, 0:3])

# Create a 2D array (matrix) of shape (4, 4) and slice out the submatrix of shape (2, 2) from the top-right corner.
arr = np.array([[1,2,3,4],
                [4,5,6,7],
                [7,8,9,10],
                [10,11,12,13]])

print(arr[0:2, 2:4])

# Create a 1D array of integers from 1 to 10 and extract all even numbers from it.

arr = np.arange(1, 10, 1)
print(arr[arr%2==0])