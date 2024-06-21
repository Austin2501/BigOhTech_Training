import numpy as np

# Create a NumPy array of zeros of shape (3, 4).
arr = np.zeros((3,4))
print(arr)

# Create a NumPy array of ones of shape (2, 3, 4).
arr = np.ones((3,4))
print(arr)

# Create a NumPy array with values ranging from 10 to 30.
arr = np.arange(10, 30, 1)
print(arr)

# Reshape the array created in the previous step to shape (5, 4).
new_arr = arr.reshape(5, 4)
print(new_arr)

