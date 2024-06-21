# Create two NumPy arrays of shape (3, 3) and perform element-wise addition.
import numpy as np

arr1 = np.array([[1,2,3],
                 [4,5,6],
                 [7,8,9]])
arr2 = np.array([[1,2,3],
                 [4,5,6],
                 [7,8,9]])
print(arr1+arr2)

arr1 = np.array([[1,2],
                 [3,4]])
arr2 = np.array([[5],
                 [5]])

print(arr1.dot(arr2))
