class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def insert(root, key):
    if root is None:
        return Node(key)

    if key < root.data:
        root.left = insert(root.left, key)
    elif key > root.data:
        root.right = insert(root.right, key)

    return root


def preorder(root):       # (Root → Left → Right)
    if root:
        print(root.data, end=" ")
        preorder(root.left)
        preorder(root.right)

def inorder(root):          # (Left → Root → Right)
    if root:
        inorder(root.left)
        print(root.data, end=" ")
        inorder(root.right)

def postorder(root):     	# (Left → Right → Root)
    if root:
        postorder(root.left)
        postorder(root.right)
        print(root.data, end=" ")


def minValueNode(node):
    current = node

    while current.left is not None:
        current = current.left

    return current


def delete(root, key):
    if root is None:
        return root

    if key < root.data:
        root.left = delete(root.left, key)

    elif key > root.data:
        root.right = delete(root.right, key)

    else:
        # Case 1: No child
        if root.left is None and root.right is None:
            return None

        # Case 2: One child
        elif root.left is None:
            return root.right

        elif root.right is None:
            return root.left

        # Case 3: Two children
        temp = minValueNode(root.right)

        root.data = temp.data

        root.right = delete(root.right, temp.data)

    return root


root = None

for x in [50, 30, 70, 20, 40, 60, 80]:
    root = insert(root, x)

print("Before Deletion:")
print("Preorder : ",end="");  preorder(root)
print("\nInorder : ",end="");   inorder(root)
print("\nPostorder : ",end=""); postorder(root)
       
root = delete(root, 50)

print("\n\nAfter Deletion:")
print("Preorder : ",end="");  preorder(root)
print("\nInorder : ",end="");   inorder(root)
print("\nPostorder : ",end=""); postorder(root)


from collections import deque

def bfs(root):
    if root is None:
        return

    q = deque([root])
    while q:
        node = q.popleft()
        print(node.data, end=" ")

        if node.left:
            q.append(node.left)
        if node.right:
            q.append(node.right)


def dfs(root):
    if root is None:
        return

    print(root.data, end=" ")
    dfs(root.left)
    dfs(root.right)

print("\n\nDepth First Search")
print("BFS : ",end="");  bfs(root)

print("\n\nBreadth First Search")
print("DFS : ",end="");  dfs(root)