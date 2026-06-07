# class Node:
#     def __init__(self, data):
#         self.data = data
#         self.next = None


# class LinkedList:
#     def __init__(self):
#         self.head = None

#     def insert_end(self, data):
#         new_node = Node(data)

#         if self.head is None:
#             self.head = new_node
#             return
        
#         temp = self.head
#         while temp.next != None:
#             temp = temp.next

#         temp.next = new_node

#     def display(self):
#         temp = self.head

#         while temp != None:
#             print(temp.data, end=" -> ")
#             temp = temp.next

#         print("None")


# ll = LinkedList()

# ll.insert_end(10)
# ll.insert_end(20)
# ll.insert_end(30)

# ll.display()


# # if(rear+1)%size == front:
# #     queue OverflowError

# # rear=(rear+1)%size
# # queue[rear]=data

# # -------------------------------------

# # if front==-1:
# #     quueue underflowerror

# # data=queue[front]

# # if rear==front:
# #     rear=front=-1

# # front=(front+1)%size

# # -------------------------------------


# class Stack:
#     def __init__(self):
#         self.items = []

#     def push(self, item):
#         self.items.append(item)

#     def pop(self):
#         if not self.is_empty():
#             return self.items.pop()

#     def peek(self):
#         if not self.is_empty():
#             return self.items[-1]

#     def is_empty(self):
#         return len(self.items) == 0


# def precedence(op):
#     if op == '+' or op == '-':
#         return 1
#     elif op == '*' or op == '/':
#         return 2
#     elif op == '^':
#         return 3
#     return 0


# def infix_to_postfix(expression):
#     stack = Stack()
#     postfix = ""

#     for ch in expression:

#         if ch.isalnum():  postfix += ch

#         elif ch == '(':  stack.push(ch)

#         elif ch == ')':
#             while not stack.is_empty() and stack.peek() != '(':
#                 postfix += stack.pop()
#             stack.pop()

#         else:
#             while (not stack.is_empty() and
#                    precedence(ch) <= precedence(stack.peek())):
#                 postfix += stack.pop()
#             stack.push(ch)

#     while not stack.is_empty():
#         postfix += stack.pop()

#     return postfix


# expr = "A+B*(C-D)"
# print("Infix Expression :", expr)

# result = infix_to_postfix(expr)
# print("Postfix Expression :", result)

