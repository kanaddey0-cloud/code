from ctypes import *

# load your DLL
lib = CDLL("./libgdsl.dll")

# ---------------------------
# Define function signatures
# ---------------------------

# void* bt_create(unsigned short order)
lib.bt_create.argtypes = [c_ushort]
lib.bt_create.restype = c_void_p

# void bt_destroy(void*)
lib.bt_destroy.argtypes = [c_void_p]
lib.bt_destroy.restype = None

# int bt_insert(void*, int)
lib.bt_insert.argtypes = [c_void_p, c_int]
lib.bt_insert.restype = c_int

# int bt_search(void*, int)
lib.bt_search.argtypes = [c_void_p, c_int]
lib.bt_search.restype = c_int

# ---------------------------
# TEST
# ---------------------------

tree = lib.bt_create(3)

print("Insert 10:", lib.bt_insert(tree, 10))
print("Insert 20:", lib.bt_insert(tree, 20))
print("Insert 5 :", lib.bt_insert(tree, 5))

print("Search 20:", lib.bt_search(tree, 20))
print("Search 99:", lib.bt_search(tree, 99))

lib.bt_destroy(tree)