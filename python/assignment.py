# import array

# arr=array('i')
# with open("data.bin", "wb") as f: # Array → File  (write to file)
#     arr.tofile(f)               # Write array to binary file

# a4 = array('i')    # File → Array (read from file)
# with open("data.bin", "rb") as f:
#     a4.fromfile(f, len(a))    # Read same number of items as original

# # 9. Array of Unicode chars → List of chars (typecode 'u')
# a5 = array('u', 'hello')      # Unicode array
# lst_chars = a5.tolist()       # Convert to list of characters
# print(lst_chars)

from array import array

arr2D = [
    array('i', [1, 2, 3]),
    array('i', [4, 5, 6]),
    array('i', [7, 8, 9])
]

print(arr2D[1][2])  # 6
print(arr2D[1])  # array('i', [4, 5, 6])

import numpy as np

arr = np.array([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
])

print(arr[1][2])  # 6
print(arr[1])  # [4 5 6]
print(dir(arr))