# def modify_list(lst1,lst2):
#     lst1.append(100); print(id(lst1),lst1)
#     lst2=[1,2,3,4]; print(id(lst2),lst2)

# ls1 = [1, 2, 3]; ls2 = [1, 2, 3]
# modify_list(ls1,ls2)
# print(ls1,id(ls1)); print(ls2,id(ls2))

# print('\n')
# def decorator(func):                    # decorator function
#     def wrapper(original_fun_parameter):   # wrapper takes same parameter
#         # code before function
#         print("Before function")
#         result = func(original_fun_parameter)   # call original function
#         # code after function
#         print("After function")
#         return result
#     return wrapper

# @decorator
# def function_name(parameter):   # original_function
#     print("Original function:", parameter)


# function_name(10)


# def repeat(times):                 # 1️⃣ outer function (takes argument)
#     def decorator(func):           # 2️⃣ real decorator (takes function)
#         def wrapper():             # 3️⃣ wrapper (same parameters as original function)
#             for _ in range(times):
#                 func()             # call original function
#         return wrapper
#     return decorator

# @repeat(3)                         # repeat(3) returns decorator
# def hello():                       # original function
#     print("Hello!")


# hello()




# from pprint import pprint
# from collections import Counter
# data = 'input()'
# print(pprint(Counter(data),width=1))
# for i in range(1,len(data)+1):
#     print(data[-i],end='')

# num=[3,5,78,7,54,43,32,4,7]
# for i in range(0,9):
#     x=i
#     for j in range(i+1,9):
#         if num[x]>num[j]:
#             x=j
#     num[x],num[i]=num[i],num[x]
# print(num)


# import re

# text = "Call me at 9876543210 or +91-9876543210 or +91 9876543210"

# text = "abc1234xyz56"

# result = re.subn(r"[0-9]+", "-", text)
# print(" ",text)
# print(result)
# pattern = r'(\+91[- ]?)?[6-9]\d{9}'
# numbers = re.findall(pattern, text)
# print(numbers)

# s = "test@gmail.com test@yahoo.co.in"
# result = re.findall(r'\w+@\w+\.(?:com|co\.in)', s)


# text = "2026-02-19 ERROR Database failed"
# match = re.search(r'(\d{4}-\d{2}-\d{2}) (\w+) (.+)', text)

# print(match.group(0))  # Full match
# print(match.group(1))  # First group (date)
# print(match.group(2))  # Second group (level)
# print(match.group(3))  # Third group (message)
# print(match.groups())  # All groups as a tuple

# print(match.start())    # 0 → start of full match
# print(match.start(1))   # 0 → start of group 1 (date)
# print(match.start(2))   # 11 → start of group 2 (ERROR)

# print(match.end())      # 34 → end of full match
# print(match.end(1))     # 10 → end of group 1 (date)
# print(match.end(2))     # 16 → end of group 2 (ERROR)

# print(match.span())     # (0, 34) → full match
# print(match.span(1))    # (0, 10) → group 1 (date)
# print(match.span(2))    # (11, 16) → group 2 (ERROR)

# matches = re.finditer(r'\d+', "My numbers are 12, 34 and 56")
# for match in matches:
#     print(match.group(), match.start(), match.end(), match.span())

# import pandas as pd
# df = pd.DataFrame( { 
#     "Name": ["Amit", "Rina", "Sohan"],  
#     "Marks": [85, 90, 78] 
# }, index=['a','b','c']) 
# df["New"]=['a', 2, 4]
# df.loc[3]=["kanad", 5, 's']
# df.info()
# # print(df.loc['b',"Name":"New"])

# print()
# s = pd.Series([1,2,3], index=['a', 'b', 'c'], name='mew')
# s["n"]=7
# print(s[s>3])
       


# class A: 
#     a1 = 10
#     @classmethod
#     def aa(cls):
#         print(cls.__name__,cls.a1)
#     def a(self): 
#         print("Class A") 

# class B(A):
#     b2 = 20
#     @classmethod
#     def aa(cls):
#         print(cls.__name__,cls.a1,cls.b2)
#     def b(self): 
#         print("Class B") 

# class C(A):
#     c3 = 30
#     @classmethod
#     def cc(cls):
#         print(cls.__name__,cls.a1,cls.c3,cls.b2)
#     def c(self): 
#         C.cc()
#         print("Class C") 

# class D(B, C): 
#     def f():
#         C.cc()

# obj = D() 
# obj.cc()
# D.cc()

 

# class A:
#     a1 = 10

#     @classmethod
#     def aa(cls):
#         print("a1:", cls.a1)

# class B(A):
#     b2 = 20

#     @classmethod
#     def aa(cls):
#         super().aa()
#         print("b2:", cls.b2)

# A.aa()
# B.aa()

# try:
#     # Code body
#     raise Exception("ERROR Sms") 
#     # Code body
# except Exception as e:
#     print("Bachao bachao",e)
# except ZeroDivisionError as ze:
#     print("Bachao bachao",ze)
# except:
#     print("ki error ami jani na")
# else:
#     print("Jodi kon error na hoy")
# finally:
#     print("All Time")

# x = -5
# assert 0, "x must be positive"

# class A:
#     mew = 4
#     def __init__(s,p1,p2,p3):
#         s.x=p1
#         s.y=p2
#         A.mew = p3
#         print(s)

# a1 = A(10,20,11)
# a2 = A(30,40,22)
# A.mew = 33
# print('a1-> ',a1.x,a1.y,a1.mew)
# print('a2-> ',a2.x,a2.y,a2.mew)

class A: 
    x = 10;   y = 100 
    def show(self): 
        print("A") 
 
class B(A): 
    x = 20 
    def show(self): 
        print("B->",self.x) 

class C(B): 
    x = 30 

 
obj = C() 
print(obj.x, "\n", obj.y) 
obj.show()