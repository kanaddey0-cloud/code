# A = {"x": 1, "y": 2}
# B = {"y": 3, "z": 4}
# C = {"y": 2}

# # Items operations: (key, value pairs)
# print(A.items() & B.items())   # Intersection
# print(A.items() & C.items())   
# print(A.items() | B.items())   # Union
# print(A.items() - B.items())   # Difference
# print("________________________________________")

# # Manual set conversion for values (works in all versions)
# print( set(A.values()) & set(B.values()) )
# print( set(A.values()) | set(B.values()) )
# print( set(A.values()) - set(B.values()) )
# print("________________________________________")
# a=input()
# lst = [10, 20, 30, 40]
# print(lst[0])   # 10 
# print(lst[3])
# print(lst[-1])  # 40 (last element)
# print(lst[-2])
# def sumUP(n):
#     rem= tmp= 0
#     while n!=0 :
#         rem= n%10
#         tmp+= rem
#         n//= 10
#     return tmp

# num = int(input("Enter a number: "))
# while num>9 :
#     num= sumUP(num)
# print(num)

# from pprint import pprint

# nested = {
#     "users": [
#         {"id": 1, "info": {"name": "Alice", "age": 25}},
#         {"id": 2, "info": {"name": "Bob", "age": 30}}
#     ]
# }
# pprint(nested)
# pprint(nested, depth=1)
# pprint(nested, width=40)

# from pprint import PrettyPrinter

# pp = PrettyPrinter(width=40, depth=2, compact=True)
# pp.pprint(nested)

# from pprint import pprint

# data = {"a": [1,2,3], "b": {"x":10, "y":20}}
# pprint(data)
# pprint(data, sort_dicts=True)
# pprint(data, sort_dicts=False)

# data = {"z": 1, "a": 2}
# pprint(data)
# pprint(data, sort_dicts=True)
# pprint(data, sort_dicts=False)

# 1. List
# lst = [10, 20, 30, 40]
# print("List examples:")
# print(lst[0])    # 10
# print(lst[3])    # 40
# print(lst[-1])   # 40 (last element)
# print(lst[-2])   # 30


# # 2. Tuple (immutable list)
# t = (1, 2, 3)
# print("Tuple examples:")
# print(t[0])    # 1
# print(t[2])    # 3
# print(t[-1])   # 3
# print(t[-2])   # 2


# # 3. Set (unordered, no indexing)
# s = {10, 20, 30}
# print("Set examples:")
# # print(s[0])  # ❌ Error (not allowed)
# lst_from_set = list(s)
# print(lst_from_set[0])   # Works after converting to list


# # 4. Dictionary (key-based access only)
# d = {'a': 10, 'b': 20}
# print("Dictionary examples:")
# print(d['a'])      # 10
# # print(d[0])      # ❌ Error
# keys = list(d.keys())
# print(d[keys[0]])  # Access first key's value

# Example 1: Using *args (variable length positional arguments)
# def show_numbers(*args):
#     print("Type of args:", type(args))   # tuple
#     print("Numbers (as tuple):", args)

#     # You can loop over args
#     for num in args:
#         print("->", num)

# show_numbers(1, 2, 3, 4)
# print("-" * 40)


# # Example 2: Using **kwargs (variable length keyword arguments)
# def show_info(**kwargs):
#     print("Type of kwargs:", type(kwargs))   # dict
#     print("Info (as dict):", kwargs)

#     # You can loop over dictionary
#     for key, value in kwargs.items():
#         print(f"{key} = {value}")

# show_info(name="Alice", age=25, city="Paris")
# print("-" * 40)


# # Example 3: Mixing normal, *args, and **kwargs
# def mixed_function(title, *args, **kwargs):
#     print("Title:", title)
#     print("Args:", args)          # tuple
#     print("Kwargs:", kwargs)      # dict

# mixed_function("Student Data", 1, 2, 3, name="Bob", grade="A")
# print("-" * 40)


# # Example 4: Default + *args + **kwargs together
# def order(item, qty=1, *extras, **details):
#     print(f"Item: {item}, Qty: {qty}")
#     print("Extras:", extras)        # tuple of extra positional args
#     print("Details:", details)      # dict of keyword args

# order("Laptop", 2, "Charger", "Bag", color="Silver", warranty="2 years")





# Example: Using  *args, **kwargs (variable length keyword arguments)
# def  info(*args , **kwargs):
#     print("Type of args:", type(args))   # tuple
#     print("Numbers (as tuple):", args)

#     for num in args:    # You can loop over args
#         print("->", num)
#     print("-" * 40)
#     print("Type of kwargs:", type(kwargs))   # dict
#     print("Info (as dict):", kwargs)

#     for key, value in kwargs.items():    # You can loop over dictionary / kwargs
#         print(f"{key} = {value}")

# info(1, 2, 3, 4, name="Alice", age=25, city="Paris")

# n = 2
# res = "Odd" if n % 2 else [i*i for i in range(5)]
# print(res)    # [0, 1, 4, 9, 16]
# res = ["Odd" if i % 2 else "Even" for i in range(5)]
# print(res)    # ['Even', 'Odd', 'Even', 'Odd', 'Even']

# gen = (x for x in range(5))
# print(next(gen))  # 0
# print(next(gen))  # 1
# print(list(gen))  # [4, 9, 16]

# evens = (x for x in range(10) if x % 2 == 0)
# print(list(evens))  # [0, 2, 4, 6, 8]
# print(list(evens))  # [0, 2, 4, 6, 8]

# num = next((i for i in range(5) if i == 3), None)
# print(num)  # 3
# num = list((i for i in range(5) if i == 3), None)
# print(num)


# first_odd = next((x for x in range(10) if x % 2 ), None)
# print(first_odd)  # 1

# n = 2;  res = "Odd" if n % 2 else [i*i for i in range(5)]
# print(res)    # [0, 1, 4, 9, 16]      Else  For

# res = ["Odd" if i % 2 else "Even" for i in range(5)]
# print(res)    # ['Even', 'Odd', 'Even', 'Odd', 'Even']      For  Else

# from functools import reduce

# nums = [1, 2, 3, 4]
# result = reduce(lambda a, b: a + b, nums)
# print(result)    # (((1+2)+3)+4) = 10

# from functools import reduce

# nums = [3, 7, 2, 9, 5]
# result = reduce(lambda a, b: a if a > b else b, nums)
# print(result)  

# from functools import reduce

# nums = [1, 2, 3, 4]
# result = reduce(lambda a, b: a * b, nums)
# print(result)    # (((1*2)*3)*4) = 24

# from functools import reduce

# nums = [1, 2, 3]
# result = reduce(lambda a, b: a + b, nums, 10)
# print(result)    # (((10+1)+2)+3) = 16

# x = 100  # global

# def outer():
#     y = 50  # enclosing

#     def inner():
#         global x     # modifies global
#         nonlocal y   # modifies enclosing
#         x += 1
#         y += 1
#         print("Inside inner -> x:", x, "y:", y)

#     inner()
#     print("After inner in outer -> x:", x, "y:", y)

# outer()
# print("Outside all -> global x:", x)
# # print("Outside all -> nonlocal x:", y)  ERROR



# 🔹 Global variable
# x = 100   # global scope
 
# print("Start: Global x =", x)

# def demo_scope():
#     y = 10;  print("\nInside demo_scope -> Local y:", y)         # Local
#     print("Inside demo_scope -> Can READ global x:", x)        # global

# def make_counter():
#     count = 0          # Closure to show variable lifetime
#     def inc():
#         nonlocal count
#         count += 1
#         return count
#     return inc   # return inner function (closure keeps `count` alive)

# demo_scope();  print("\nAfter demo_scope -> Global x still:", x)

# counter = make_counter()           # Closure example
# print("\nClosure counter calls:")
# print(counter())  
# print(counter())
# print(counter())

# x = 100      # global

# def outer():
#     y = 50      # enclosing

#     def inner():
#         global x     # modifies global
#         nonlocal y     # modifies enclosing
#         x += 1
#         y += 1
#         print("Inside inner -> x:", x, "y:", y)

#     inner()
#     print("After inner in outer -> x:", x, "y:", y)

# outer()
# print("Outside all -> global x:", x)
# # print("Outside all -> nonlocal x:", y)  ERROR

# num = next((i for i in range(5) if i >= 3), None) 
# print(num)    # 3 


# names = ["Alice", "Bob", "Charlie"]
# scores = [85, 90, 95]
# # Pairs elements from multiple iterables into tuples.
# for name, score in zip(names, scores):
#     print(name, score)

# # You can also turn them into dicts:
# student_scores = dict(zip(names, scores))
# print("\n",student_scores)

# def greet(name: str) -> str:
#     """This function returns a greeting message."""
#     return f"Hello, {name}!"

# import inspect

# # Define a sample function
# def add(a: int, b: int = 10) -> int:
#     """Add two numbers with default value for b."""
#     return a + b
# # 1. Basic Introspection
# print("=== Basic Introspection ===")
# help(add)   # shows docstring and signature
# print("Function name:", add.__name__)
# print("Docstring:", add.__doc__)
# print("Annotations:", add.__annotations__)   
# print("Is callable?", callable(add))
# print("Attributes of function:", dir(add))
# # 2. Using inspect module
# print("\n=== Using inspect ===")
# sig = inspect.signature(add)
# print("Signature:", sig)
# for name, param in sig.parameters.items():
#     print(f"Parameter: {name}, Default: {param.default}, Annotation: {param.annotation}")
# print("Return type:", sig.return_annotation)
# # Older but detailed args info
# argspec = inspect.getfullargspec(add)
# print("\nFull Arg Spec:", argspec)
# # 3. Advanced Introspection
# print("\n=== Advanced Introspection ===")
# print("Source code:\n", inspect.getsource(add))
# print("Defined in module:", inspect.getmodule(add))
# print("Is function?", inspect.isfunction(add))
# print("Is method?", inspect.ismethod(add))

# def gen_numbers(n):
#     for i in range(n):
#         yield i     # yield that pauses and resumes later.

# g = gen_numbers(8)
# print(next(g));  print(next(g))   
# print(list(g))   # continues where left off

# def sub():
#     yield 1; yield 2

# def main():
#     yield 0
#     yield from sub()   # yield all values from sub()
#     yield 3

# print(list(main()))  

# import asyncio

# async def task(name):
#     print(f"Start {name}")
#     await asyncio.sleep(1)   # non-blocking wait
#     print(f"End {name}")

# async def main():
#     await asyncio.gather(task("A"), task("B"))

# asyncio.run(main())

# def coro():
#     total = 0
#     while True:
#         x = (yield total)   # receive value via send()
#         if x is None: break
#         total += x

# c = coro()
# print(next(c))       # start → 0
# print(c.send(5))     # send 5 → total = 5
# print(c.send(10))    # send 10 → total = 15
# c.close()

# from functools import partial

# def power(base, exp):
#     return base ** exp

# square = partial(power, exp=2)   # fix exp=2
# cube   = partial(power, exp=3)   # fix exp=3

# print(square(5))   # 25
# print(cube(2))     # 8
# print("-------------------------")

# def multiply(a):
#     def inner(b):
#         return a * b
#     return inner

# double = multiply(2)
# print(double(5))   # 10
# print(multiply(3)(4))  # 12
# print("-------------------------")

# def add(x): return x + 1
# def square(x): return x * x

# def compose(f, g):
#     return lambda x: f(g(x))

# new_func = compose(square, add)   # square(add(x))
# print(new_func(3))   # square(4) → 16
# print("-------------------------")

# def greet(name):
#     print(f"Hello, {name}")

# def process_user(name, callback):
#     callback(name)   # call the function passed in

# process_user("Alice", greet)

# def add(x, y): return x + y
# def sub(x, y): return x - y
# def mul(x, y): return x * y

# ops = {"add": add, "sub": sub, "mul": mul }
# print(ops["add"](2, 3))   
# print(ops["sub"](8, 4))   
# print(ops["mul"](4, 5))   

# def my_decorator(func):
#     def wrapper():
#         print('After Function')
#         func()
#         print('Before Function')
#     return wrapper
# @my_decorator
# def fun():
#     print('Execute Function')
# fun()

# from functools import wraps

# def logging_decorator(func):    # functools.wraps → Preserve metadata
#     @wraps(func)    # preserves func.__name__, __doc__
#     def wrapper(*args, **kwargs):
#         print(f"Calling {func.__name__}, {func.__doc__}") 
#         print(f"with args={args}, kwargs={kwargs}")
#         return func(*args, **kwargs)
#     return wrapper

# @logging_decorator
# def add(a, b):
#     """Adds two numbers"""
#     return a + b

# print(add(3, 4))         # Logs call, then prints 7

# def repeat(times):     # Decorators with Arguments
#     def decorator(func):
#         @wraps(func)
#         def wrapper(*args, **kwargs):
#             for _ in range(times):
#                 func(*args, **kwargs)
#         return wrapper
#     return decorator

# @repeat(3)
# def hello():
#     print("Hello!")

# hello()

# from functools import lru_cache

# @lru_cache(maxsize=None)   # cache all results, no limit
# def fib(n):
#     if n < 2:
#         return n
#     return fib(n-1) + fib(n-2)

# print([fib(i) for i in range(10)])

# class Adder:
#     def __init__(self, n):
#         self.n = n          # store the number
#     def __call__(self, x):
#         return self.n + x   # make the object "callable"

# add5 = Adder(5)   # creates an object with n = 5
# print(add5(10))   # actually calls add5.__call__(10)

# def add(a: int, b: int = 10) -> int:
#     """Add two numbers together."""
#     c = 5  # local constant to show co_consts
#     return a + b + c

# # --- remaining Function Introspection ---
# print("Defaults:", add.__defaults__)            # Default values for positional args
# print("Keyword-only defaults:", add.__kwdefaults__)  # None here
# print("Module:", add.__module__)                # Module where defined
# print("Qualified name:", add.__qualname__)      # Useful for nested functions
# print("Custom dict:", add.__dict__)             # Custom attributes (empty now)

# # --- Code object ---
# code = add.__code__
# print("Argument names:", code.co_varnames)      # ('a', 'b', 'c')
# print("Number of arguments:", code.co_argcount) # 2 (a, b)
# print("Constants:", code.co_consts)             # (None, 5)
# print("Bytecode names used:", code.co_names)    # Empty because no globals used

# # --- Globals used ---
# print("Globals of function:\n", list(add.__globals__.keys())[:5], "...")  # Shows some globals

# # --- Call the function using __call__ ---
# result = add.__call__(2)
# print("Calling with __call__(2):", result)  # 2 + 10 + 5 = 17

# def outer(x):    # --- Closure example ---
#     y = 5
#     def inner(z):
#         return x + y + z
#     return inner
# f = outer(10)
# print("Closure contents:", f.__closure__[0].cell_contents)  # x=10
# print("Closure call f(3):", f(3))                            # 10 + 5 + 3 = 18

# def foo(): pass
# class Adder:
#     def __call__(self, x): return x+1

# print(callable(foo))        # True, function
# print(callable(Adder))      # True, class
# add5 = Adder()
# print(callable(add5))       # True, callable object
# print(callable(42))         # False, integer is not callable

# x = 10
# expr = "x + 5"
# result = eval(expr)
# print(result)  # 15

# def add(a, b): return a + b     # You can even call functions dynamically:
# func_name = "add"
# print(eval(f"{func_name}(3, 4)"))  

# code = """
# def greet(name):
#     print("Hello", name)
# greet("Kanad")
# """
# exec(code)
# Output: Hello Kanad


# ✅ Input & Print
# my_list = list(map(int, input("Enter numbers: ").split()))  
# print("List:", my_list)  

# # ✅ Insert (append, insert)
# my_list.append(100)    # Adds at the end
# my_list.insert(1, 50)    # Inserts 50 at index 1

# # ✅ Delete (remove, pop, del)
# my_list.remove(50)    # Removes first occurrence of 50
# popped = my_list.pop()    # Removes last element
# del my_list[0]    # Deletes first element

# if 20 in my_list:    # ✅ Check if an element exists
#     print("20 is in the list")

# my_list = [10, 20, 30, 40]    # ✅Print all element using loop
# for item in my_list:     # Looping through list elements
#     print(item)

# lst = [10, 20, 30, 40, 50, 60]
# print(lst[2:5])    # slicing
# print(lst[::-1])

# # ✅ Input & Print
# my_tuple = tuple(map(int, input("Enter numbers: ").split()))  
# print("Tuple:", my_tuple)  

# # ❌ Insert & Delete (Not possible, tuples are immutable)

# # ✅ Check if an element exists
# if 10 in my_tuple:
#     print("10 is in the tuple")

# # ✅Print all element using loop
# my_tuple = (100, 200, 300)
# for item in my_tuple:    # Looping through tuple elements
#     print(item)

# tup = (10, 20, 30, 40, 50, 60)
# print(tup[2:5])    # slicing
# print(tup[::-1])     # Reverse tuple

# sorted_t = sorted(tup)
# print(sorted_t, tuple(sorted_t))
# print(tuple(sorted_t))

# from functools import wraps
# def repeat(times):     
#     def decorator(func):
#         @wraps(func)  # This Line Not neccessary
#         def wrappe(*args, **kwargs):
#             for _ in range(times):
#                 func(*args, **kwargs)
#         return wrappe
#     return decorator
# @repeat(3)
# def hello():
#     print("Hello!")

# hello()

# from functools import lru_cache

# @lru_cache(maxsize=3)
# def test(x):
#     print("--Inside: ",x);  
#     return x

# values = [10, 20, 10, 30, 20]
# for v in values:
#     print("Return: ", test(v))




# from functools import lru_cache

# count = 1   # global counter

# @lru_cache(maxsize=5)
# def odd_even(x):
#     return "Even" if x % 2 == 0 else "Odd"

# values = [1, 2, 3, 4, 2, 5, 6, 4, 4]
# for v in values:
#     print(f"Result: {odd_even(v)}")
#     if count == 5:    # Every 4th call after → show cache info
#         print("---- Cache after 4 calls ----")
#         print(odd_even.cache_info());  count = 0
#         print("-----------------------------");  
#     count += 1
# print("-------------------------\nFinal ",odd_even.cache_info())
# print(odd_even.cache_parameters())
# for i in [1,2,1.0,'a','S',"K"]:
#     print(i)



# def log_all(module):
#     print(f"Decorating module: {module.__name__}")

#     # Patch every function inside module
#     for name, obj in module.__dict__.items():
#         if callable(obj):
#             print(f"Found function: {name}")
#     return module

# @log_all
# module:
#     def hello():
#         print("Hello")

#     def add(a, b):
#         return a + b

# hello()
# print(add(2, 3))

# from functools import wraps

# def star(func):
#     @wraps(func)
#     def wrapper(*args, **kwargs):
#         print("***** before star *****")
#         result = func(*args, **kwargs)
#         print("***** after star *****")
#         return result
#     return wrapper

# def plus(func):
#     @wraps(func)
#     def wrapper(*args, **kwargs):
#         print("+++++ before plus +++++")
#         result = func(*args, **kwargs)
#         print("+++++ after plus +++++")
#         return result
#     return wrapper

# @star   # applied last (outer wrapper)
# @plus   # applied first (inner wrapper)
# def greet():
#     print("Hello!")

# greet()


# f = open(r"C:\Users\kanad\OneDrive\Desktop\Android Development\Code\python\Demo.txt", "w")  # Open a file for writing

# f.write("Hello, this is the first line.\n")  # Write some data
# f.write("Python file I/O is very simple!\n")
# f.write("Hello\n")  # Writes a single string
# f.writelines(["One\n", "Two\n", "Three\n"])  # Writes line by line
# f.close()
# print("Writing File \n"+"-"*16)
# f = open(r"C:\Users\kanad\OneDrive\Desktop\Android Development\Code\python\Demo.txt", "r")
# data = f.read()          # Reads the entire file
# print(data)
# print(f.read(5))       # Read first 5 chars
# print(f.readline())    # Read one line
# print(f.readlines())   # Read remaining lines as list
# f.close()
# print("-"*16)
# f = open(r"C:\Users\kanad\OneDrive\Desktop\Android Development\Code\python\Demo.txt", "r")
# print(f.tell())     # → 0 (beginning)
# f.read(5)
# print(f.tell())     # → 5
# f.seek(0)           # Go back to start
# print(f.read())     # Read again
# f.close()

# with open(r"C:\Users\kanad\OneDrive\Desktop\Android Development\Code\python\Demo.txt", "r") as f:
#     data = f.read()

# letters = digits = spaces = others = 0

# for ch in data:
#     if ch.isalpha():
#         letters += 1
#     elif ch.isdigit():
#         digits += 1
#     elif ch.isspace():
#         spaces += 1
#     else:
#         others += 1

# print("Letters:", letters)
# print("Digits:", digits)
# print("Spaces:", spaces)
# print("Others:", others)


# with open(r"C:\Users\kanad\OneDrive\Desktop\Android Development\Code\python\Demo.txt", "r") as f:
#     data = f.read()

# data_upper = ""
# for ch in data:
#     if ch.isalpha():
#         data_upper += ch.upper()
#     else:
#         data_upper += ch

# with open(r"C:\Users\kanad\OneDrive\Desktop\Android Development\Code\python\Demo.txt", "w") as f:
#     f.write(data_upper)
# print("-"*16)

# with open(r"C:\Users\kanad\OneDrive\Desktop\Android Development\Code\python\Demo.txt", "r") as f:
#     words = f.read().split()
# print("Shortest word:",min(words, key=len))

# print("Longest word:", max(words, key=len))
# print("Average word length:", sum(len(w) for w in words) / len(words))

# x = 10
# print(type(x))          # <class 'int'>

# y = 3.14
# print(type(y))          # <class 'float'>

# z = "Hello"
# print(type(z))          # <class 'str'>

# a = [1, 2, 3]
# print(type(a))          # <class 'list'>

# MyClass = type('MyClass', (), {"x": 10})
# obj = MyClass()
# print(obj.x)            # 10
# print(type(obj)) 

# x = 10; y = 2.5
# print(isinstance(x, int))         # True
# print(isinstance(x, float))       # False
# print(isinstance(y, float))       # False

# x = 10.5
# print(isinstance(x, (int, float)))  # True

# x = 5
# print(id(x))
# y = x
# print(id(y),"\nnew ",id(x))   # same id → same object
# x=x+1
# print(id(x))

# x = [1, 2, 3]
# print(dir(x))  # shows all methods in applicable in here
# print("-"*32)
# class Student:
#     def __init__(self, name, age):
#         self.name = name
#         self.age = age
# s = Student("Kanad", 20)
# print(vars(s))    # {'name': 'Kanad', 'age': 20}
# print("-"*32)
# # help(str)
# # help(print)
# # print("-"*32)
# x = "Hello"
# print(str(x))    # Hello
# print(repr(x))   # 'Hello'

# print("""Helloworld""")
# # print(""Helloworld"")
# print("Helloworld")
# print('''Helloworld''')
# # print(''Helloworld'')
# print('Helloworld')
# print('------------------')
# print(" ' ")   # prints single quote
# print(' " ')   # prints double quote
# print('------------------')
# print(r"C:\new\folder")    # Output: C:\new\folder
# print("C:\new\folder")
# print("C:\\new")        # Prints a single backslash (\) → Output: C:\new
# print('------------------')
# print('It\'s ok')       # Escapes single quote → Output: It's ok
# print('------------------')

# print("He said \"Hi\"") # Escapes double quotes → Output: He said "Hi"
# print('------------------')

# print("Hello\nWorld")   # \n inserts a newline → Output:
#                         # Hello
#                         # World
# print('------------------')

# print("Name\tAge")      # \t inserts a tab space → Output: Name    Age
# print('------------------')

# print("Hello\rHi")      # \r moves cursor to line start, overwrites → Output: Hi
# print('------------------')

# print("Helloo\b")       # \b backspace deletes previous character → Output: Hello
# print('------------------')

# print("Hello\fWorld")   # \f form feed (new page / vertical space) → Output:
#                         # Hello
#                         #       World  (may look like a newline)
# print('------------------')

# print("\a")             # \a bell sound (alert) – makes a beep (if terminal supports)
# print('------------------')

# print("A\vB")           # \v vertical tab → Output:
#                         # A
#                         #   B
# print('------------------')

# print("Hello\0World")   # \0 null character (invisible) → Output: HelloWorld

# """
# This is also a comment
# using triple double-quotes.
# Python will ignore it.
# """
# print("Hello")

# '''You can also use triple single quotes
# for the same purpose.'''


# class ClassName:
#     class_var = 100        # class variable

#     # 1️⃣ Constructor (has self)
#     def __init__(self, x):
#         print(self)        # ✔ self
#         print(ClassName)   # ✔ cls (through class name)

#     # 2️⃣ Instance Method (has self)
#     def inst_method(self, a):
#         print(self)        # ✔ self
#         print(ClassName)   # ✔ cls (through class name)

#     # 3️⃣ Class Method (has cls)
#     @classmethod
#     def cls_method(cls, b):
#         print(cls)         # ✔ cls
#         # print(self)      # ❌ ERROR (no self)

#     # 4️⃣ Static Method (no self, no cls)
#     @staticmethod
#     def static_method(c):
#         # print(self)      # ❌ no self
#         # print(cls)       # ❌ no cls
#         print(c)

#     # 5️⃣ Destructor (has self)
#     def __del__(self):
#         print("called")        # ✔ self
#         print(ClassName)   # ✔ cls (through class name)

# obj = ClassName(10)
# obj2 = ClassName.cls_method(20)
# # obj.inst_method(5)
# # ClassName.static_method(4)
# del obj
# del obj2

# print(_)   # prints 15

# class Demo:
#     # 1. __new__
#     def __new__(cls, *args, **kwargs):
#         print("__new__ called")
#         return super().__new__(cls)

#     # 2. __init__
#     def __init__(self, value):
#         print("__init__ called")
#         self.value = value

#     # 3. __del__
#     def __del__(self):
#         print("__del__ called (destructor)")

#     # 4. __str__
#     def __str__(self):
#         return f"Demo(value={self.value})"

#     # 5. __repr__
#     def __repr__(self):
#         return f"Demo({self.value})"

#     # 6. __call__
#     def __call__(self, x):
#         print("__call__ executed")
#         return self.value + x

#     # 7. __add__
#     def __add__(self, other):
#         print("__add__ called")
#         return self.value + other.value

#     # 8. __len__
#     def __len__(self):
#         return self.value

#     # 9. __getitem__
#     def __getitem__(self, index):
#         print("__getitem__ called")
#         return f"Index = {index}"

#     # 10. __setitem__
#     def __setitem__(self, index, val):
#         print("__setitem__ called")
#         print(f"Setting index {index} = {val}")

#     # 11. __contains__
#     def __contains__(self, item):
#         print("__contains__ called")
#         return item == self.value


# # ---------------------------------------
# # Using the class
# # ---------------------------------------

# obj = Demo(10)

# print(obj)              # __str__
# print(repr(obj))        # __repr__

# obj(5)                   # __call__

# obj2 = Demo(20)
# print(obj + obj2)       # __add__

# print(len(obj))         # __len__

# print(obj[0])           # __getitem__

# obj[1] = 100            # __setitem__

# print(10 in obj)        # __contains__

# del obj                 # __del__
# del obj2

# import copy

# a = [1, [2, 3]]
# b = copy.deepcopy(a); c = copy.copy(a)
# print(a); b[1][0] = 999
# print(a); c[1][0] = 777
# print(a); print(b); print(c)


# ls=[[1,2,3],[4,5,6]]
# tp=((1,2,3),(4,5,6))
# tup = ([1,2], [3,4], [1,2], [5,6], [3,4], [3,4])
# tup = ([[1, 2], [3, 4]],
#        [[1, 2], [3, 4]],
#        [[5, 6]],
#        [[1, 2], [3, 4], [5, 6]],
#        [[5, 6]])
# tmp=[]
# c=0
# for i in tup:
#     if i not in tmp:
#         tmp.append(i)
#         for j in tmp:
#             if i == j: c+=1
#         print(i," : ",c)


# tup = ([1, 1], [2, 2], [1, 1], [3, 3], [2, 2], [4, 4])
# ls=[]
# for i in tup:
#     if i not in ls:
#         ls.append(i)
# ls=tuple(ls)
# print(type(ls),"\n",ls)


# tup = ([1,2], [3,4], [1,2], [5,6], [3,4], [3,4])
# tmp=[[],[]]; 
# for i in tup:
#     if i not in tmp: 
#         tmp.append(i)
#         for j in tup:
#             if i == j: 
#                 tmp[0].append(j)
#         tmp[1].append(list(tmp[0])); 
#         del tmp[0][:]
# print(tmp[1])
            

# from collections import Counter

# tup = (1,2,3,4,1,2,5,6,3,4,3,4)
# print(Counter(tup))  # return Dict


# tup = ([1],
#        [2,3],
#        [4,5,6],
#        [7],
#        [8,9],
#        [10,11,12])
# tmp=[[],[]]; 
# for i in tup:
#     if len(i) not in tmp: 
#         tmp.append(len(i))
#         for j in tup:
#             if len(i) == len(j): 
#                 tmp[0].append(j)
#         tmp[1].append(list(tmp[0])); 
#         del tmp[0][:]
# for i in tmp[1]:
#     print(i)


# tup = ([1],
#        [2,3],
#        [4,5,6],
#        [7],
#        [8,9],
#        [10,11,12])
# a = [1, [2, [3]]]
# def printContainer(container):
#     for i in container:
#         if type(i)==tuple or type(i)==set or type(i)==list or type(i)==dict:
#             printContainer(i)
#         else:
#             print(i)
# printContainer(tup)


# d1 = {'a':1, 'b':2}
# d2 = {'b':20, 'c':3}

# d3 = {**d1, **d2}
# d4 = {*d1, *d2}
# print(d3,d4)    # {'a':1, 'b':20, 'c':3}

# LIST + LIST
# print([1, 2] + [3, 4])

# # LIST * INT
# print([10, 20] * 3)

# # TUPLE + TUPLE
# print((1, 2) + (3, 4))

# # TUPLE * INT
# print((5, 6) * 4)

# results = []   # store all outputs here

# # LIST + LIST
# a = [1, 2] + [3, 4]
# results.append(a)

# # LIST * INT
# b = [10, 20] * 3
# results.append(b)

# # TUPLE + TUPLE
# c = (1, 2) + (3, 4)
# results.append(c)

# # TUPLE * INT
# d = (5, 6) * 4
# results.append(d)

# # PRINT ALL RESULTS WITH TYPE
# for item in results:
#     print(item, " --> ", type(item))

# n = int(input("Enter number: "))
# s = 0

# while n > 0:
#     s += n % 10
#     n //= 10

# print("Sum of digits:", s)

# tup = ((1, 2), (3, 4), (5, 6))

# x = int(input("Enter element to search: "))
# found = False

# for inner in tup:
#     if x in inner:
#         found = True
#         break

# if found:
#     print(x, "is present")
# else:
#     print(x, "is NOT present")

# tup = ([1,2], [3,4], [1,2], [5,6], [3,4], [3,4])

# count = {}

# for lst in tup:
#     key = tuple(lst)
#     if key in count:
#         count[key] += 1
#     else:
#         count[key] = 1

# for k in count:
#     print(list(k), ":", count[k])

# lst = [(1,2), (3,4), (1,2), (5,6), (3,4)]

# unique = []

# for t in lst:
#     found = False
    
#     # check if t already exists in unique
#     for u in unique:
#         if len(t) == len(u):              
#             same = True
#             for i in range(len(t)):      
#                 if t[i] != u[i]:
#                     same = False
#                     break
#             if same:
#                 found = True
#                 break
    
#     if not found:
#         unique.append(t)

# print("After removing duplicates:", unique)

# tup = ([3,4], [1,2], [5,6], [2,3])

# lst = []
# for x in tup:
#     lst.append(x)

# n = len(lst)
# for i in range(n):
#     for j in range(0, n-i-1):
        
#         a = lst[j]
#         b = lst[j+1]

#         k = 0
#         smaller = False
#         greater = False
        
#         while k < len(a) and k < len(b):
#             if a[k] < b[k]:
#                 smaller = True
#                 break
#             elif a[k] > b[k]:
#                 greater = True
#                 break
#             k += 1
        
#         if k == len(a) or k == len(b):
#             if len(a) > len(b):
#                 greater = True

#         # swap if greater
#         if greater:
#             lst[j], lst[j+1] = lst[j+1], lst[j]

# tup_sorted = tuple(lst)
# print("Sorted tuple of lists:", tup_sorted)


# tup = ([8,4], [2], [3,4,5,1,2], [6,5], [4,3,6], [3,0], [6], [6,2,3])
# def _1(arr):
#     ln=len(arr)
#     for i in range(0,ln):
#         for j in range(i+1,ln):
#             if arr[j]<arr[i]: arr[i],arr[j] = arr[j],arr[i]
#     return arr
# def _2(arr):
#     ln=len(arr)
#     for i in range(0,ln):
#         for j in range(i+1,ln):
#             if len(arr[j])<len(arr[i]): arr[i],arr[j] = arr[j],arr[i]
#     return arr
# def _3(arr):
#     ln=len(arr)
#     for i in range(0,ln):
#         for j in range(i+1,ln):
#             if len(arr[i])==len(arr[j]) and arr[j][0]<arr[i][len(arr[i])-1]: 
#                 arr[i],arr[j] = arr[j],arr[i]
#     return arr
# for x in tup: x=_1(x)
# print(tup)
# print('---------------------------------------')
# tup=tuple(_2(list(tup)))
# print(tup)
# print('---------------------------------------')
# tup=tuple(_3(list(tup)))
# print(tup)

# A = {1, 2, 3, 4}
# B = {3, 4, 5, 6}

# print("Union:", A | B)    # print(A.union(B))
# print("Intersection:", A & B)    # print(A.intersection(B))
# print("Difference (A - B):", A - B)      # print(B.diAerence(A))
# print("Symmetric Difference (A ∪ B) – (A ∩ B):", A ^ B) 
# # print(A.symmetric_diAerence(B))


# class Singleton:
#     _instance = None

#     def __new__(cls, *args, **kwargs):
#         if cls._instance is None:
#             cls._instance = super().__new__(cls)
#         return cls._instance

#     def __init__(self, value):
#         self.value = value

# a = Singleton(10)
# b = Singleton(20)

# print(a.value)
# print(b.value)
# print(a is b)   # True


# from functools import singledispatch

# @singledispatch
# def display(value):
#     print("Default:", value)

# @display.register(int)
# def _(value):
#     print("Integer:", value)

# @display.register(str)
# def _(value):
#     print("String:", value)

# display(10)
# display("Hello")


# class GrandParent:
#     def __init__(self):
#         self.a = 10        # Public
#         self._b = 20       # Protected
#         self.__c = 30      # Private

#     def show_gp(self):
#         print("GrandParent:", self.a, self._b, self.__c)

# class Parent(GrandParent):
#     def __init__(self):
#         super().__init__()

#     def show_p(self):
#         print("Parent accessing:")
#         print(self.a)      # ✅ Public
#         print(self._b)     # ✅ Protected
#         # print(self.__c)  # ❌ Private (ERROR)

# class Child(Parent):
#     def __init__(self):
#         super().__init__()

#     def show_c(self):
#         print("Child accessing:")
#         print(self.a)      # ✅ Public
#         print(self._b)     # ✅ Protected
#         # print(self.__c)  # ❌ Private (ERROR)

# obj = Child()
# obj.show_gp()
# obj.show_p()
# obj.show_c()


# Base classes
# class A:
#     pass

# class B:
#     pass

# # Level 1
# class C(A):
#     pass

# class D(B):
#     pass

# class E(A):
#     pass

# class F(B):
#     pass

# class G(A):
#     pass

# # Level 2
# class H(C, E, D):
#     pass

# class J(F, E, G):
#     pass

# class K(F, C):
#     pass

# # Top level
# class S(H, J, K):
#     pass



# class A:
#     def show(self):
#         print("A")

# class B(A):
#     pass

# class C(B, A): 
#     def show(self):
#         print("C")

# obj = C() 
# obj.show()


# class A:
#     x = 10
#     y = 100
#     def show(self):
#         print("A")

# class B(A):
#     x = 20
#     def show(self):
#         print("B")

# class C(B):
#     x = 30

# obj = C()
# print(obj.x, "\n", obj.y)
# obj.show()


# class A:
#     x = 10

# class B(A):
#     pass

# class C(B):
#     pass

# obj = C()
# obj.x = 50   # creates instance variable
# print(obj.x)

# class A:
#     def __show(self):    
#         print("A")

# class B(A):
#     pass

# obj = B()
# # obj.__show() ❌
# obj._A__show() 


# class GrandParent:
#     def __init__(self):
#         self.a = 10        # Public
#         self._b = 20       # Protected
#         self.__c = 30      # Private

#     def show_gp(self):
#         print("GrandParent:", self.a, self._b, self.__c)

# class Parent(GrandParent):
#     def __init__(self):
#         super().__init__()

#     def show_p(self):
#         print("Parent accessing:")
#         print(self.a)      # ✅ Public
#         print(self._b)     # ✅ Protected
#         # print(self.__c)  # ❌ Private (ERROR)

# class Child(Parent):
#     def __init__(self):
#         super().__init__()

#     def show_c(self):
#         print("Child accessing:")
#         print(self.a)      # ✅ Public
#         print(self._b)     # ✅ Protected
#         # print(self.__c)  # ❌ Private (ERROR)

# obj = Child()
# obj.show_gp()
# obj.show_p()
# obj.show_c()
# # print(obj._Parent__c)  # AttributeError: 'Child' object has no attribute '_Parent__c'

# class A:
#     __class_var = 100        # private class variable

#     def __init__(self):
#         self.__inst_var = 200   # private instance variable

#     def __show(self):        # private method
#         print("Private method of A")

#     def access_inside(self):
#         print(self.__class_var)
#         print(self.__inst_var)
#         self.__show()

# class B(A): pass

# class C(B):
#     def access_child(self):
#         # Access using name-mangling ✅
#         print(self._A__class_var)
#         print(self._A__inst_var)
#         self._A__show()

# obj = C()

# print("Access from A method:")
# obj.access_inside()

# print("\nAccess from C method:")
# obj.access_child()

# # print(obj._B__class_var)
# # print(obj._B__inst_var)    
# # obj._B__show()
# print()
# print(obj._A__class_var)   # 
# print(obj._A__inst_var)    # 200
# obj._A__show()             # Private method of A

# In Python, private members (__name) are not truly private, but they are name-mangled.
# __something  →  _ClassName__something


# def add(a, b): return a+b
# def add(a, b, c): return a+b+c
# print(add(5,5,5))

# class A:
#     def a(self):
#         print("Class A")

# class B:
#     def b(self):
#         print("Class B")

# class C(A, B):
#     pass

# obj = C()
# obj.a()
# obj.b()


# class A:
#     x = 10;   y = 100
#     def show(self):
#         print("A")

# class B(A):
#     x = 20
#     def show(self):
#         print("B",self.x)

# class C(B):
#     x = 30

# obj = C()
# print(obj.x, "\n", obj.y)
# obj.show()

# x = -5
# assert x > 0, "x must be positive"

# x = 10
# assert x < 0
# print("OK")


# # 1️⃣What is a String?
# s1 = "hello"          # string using double quotes
# s2 = 'world'          # string using single quotes
# s3 = """multi
# line"""               # multi-line string using triple quotes
# # Strings are immutable (cannot be changed after creation)

# # 2️⃣String creation
# s = "Python"          # direct string creation
# s_num = str(123)      # integer to string -> "123"
# s_float = str(12.5)    # float to string -> "12.5"

# # 3️⃣Immutability (VERY IMPORTANT)
# s = "hello"
# s = s + " world"   # creates a NEW string object
#                                    # old string "hello" is NOT modified

# # 4️⃣String operators
# concat = "a" + "b"        # concatenation -> 'ab'
# repeat = "a" * 3          # repetition -> 'aaa'
# check1 = "a" in "cat"     # membership test -> True
# check2 = "a" not in "cat" # membership test -> False

# # 5️⃣String comparison (ASCII / Unicode value based)
# compare1 = "a" == "A"     # False (case-sensitive)
# compare2 = "a" < "b"      # True ('a' comes before 'b')

# # Printing results
# print(s1, s2)
# print(s3)
# print(s_num, s_float)
# print(s)
# print(concat, repeat)
# print(check1, check2)
# print(compare1, compare2)


# s = "Education" # Common interview questions, Also Palindrome
# count = sum(1 for c in s if c in "aeiouAEIOU")  
# print("Number of Vowels",count)
# print("--------------------------------------")
# # 9️⃣ STRING FORMATTING (IMPORTANT)

# # Old style formatting (% operator)
# print("%s is %d" % ("Age", 20))
# # format() method
# print("{} is {}".format("Age", 20))
# age = 20  # f-string (BEST & modern)
# print(f"Age is {age}")
# # A raw string treats backslashes (\) as normal characters and does NOT process escape sequences.
# print(r"C:\new\test")
# print("--------------------------------------")

# # 🔟 ESCAPE CHARACTERS
# print("Hello\nWorld")   # \n -> new line
# print("Hello\tWorld")   # \t -> tab space
# print("Backslash: \\")  # \\ -> backslash
# print("Single quote: \'Python\'")  # \' -> single quote
# print("--------------------------------------")

# # 1️⃣2️⃣ STRING ITERATION
# for ch in "abc":
#     print(ch)           # prints each character
# print("--------------------------------------")

# # 1️⃣4️⃣ STRING LENGTH
# print(len("Python"))    # 6
# print("--------------------------------------")

# # 1️⃣6️⃣ UNICODE & ord / chr
# print(ord('A'))         # 65 -> Unicode value of character
# print(chr(65))          # 'A' -> character from Unicode value
# print("--------------------------------------")

# # String memory & interning (ADVANCED)
# a = "hello"
# b = "hello"
# print(id(a), id(b))
# print(a == b)   # True  (values are same)
# print(a is b)   # True  (same memory due to interning)

# s = "Python Programming"
# print(s.lower())       
# print(s.upper())       
# print(s.title())       
# print(s.strip())       
# print(s.replace("Python", "Java"))
# print(s.find("gram"))  # index or -1
# print(s.count("m"))    # count occurrences
# print(s.startswith("  Py"))
# print(s.endswith("  "))

# s = "Python Programming"; print(s) 

# print(s.lower())       
# # converts all characters to lowercase
# print(s.upper())       
# # converts all characters to uppercase
# print(s.title())       
# # capitalizes first letter of each word
# print(s.strip())       
# # removes leading and trailing spaces (no spaces here, so unchanged)

# print(s.replace("Python", "Java"))
# # replaces "Python" with "Java"

# print(s.find("gram"))  
# # returns starting index of "gram", or -1 if not found
# print(s.count("m"))    
# # counts how many times 'm' appears in the string

# print(s.startswith("  Py"))
# # checks if string starts with given substring (returns True/False)
# print(s.endswith("  "))
# # checks if string ends with given substring (returns True/False)


# # String example
# s = "Hello World";  print(s)
# print("--------------------------------------")

# # Basic string methods
# print(s.capitalize())       # 'Hello world' → first character uppercase, rest lowercase
# print(s.casefold())         # 'hello world' → converts all characters to lowercase (better than lower() for caseless comparisons)
# print(s.count("o"))         # 2 → counts how many times 'o' appears
# print(s.find("World"))      # 6 → returns starting index of substring, -1 if not found
# print(s.index("Hello"))     # 0 → returns index of substring, raises ValueError if not found
# print(s.isalnum())          # False → contains non-alphanumeric characters (space)
# print(s.isalpha())          # False → contains non-alphabet characters (space)
# print(s.isascii())          # True → all characters are ASCII
# print(s.isdecimal())        # False → not all characters are decimal numbers
# print(s.isdigit())          # False → not all characters are digits
# print(s.isidentifier())     # False → not a valid identifier in Python
# print("hello world".islower())  # True → all letters are lowercase
# print(s.isnumeric())        # False → not all characters are numeric
# print(s.isprintable())      # True → all characters are printable

# print("--------------------------------------")

# # Find vs Index
# s = "python"
# print(s.find("z"))          # -1 → returns -1 because 'z' is NOT found
# # print(s.index("z"))       # ValueError → raises error if 'z' is NOT found

# print("--------------------------------------")

# # Checking types of characters
# print("123".isdigit())        # True → contains only digits
# print("abc".isalpha())        # True → contains only alphabets
# print("abc123".isalnum())     # True → contains alphabets + digits (no spaces)

# print("--------------------------------------")

# # Encoding and Decoding
# s = "hello"
# b = s.encode();  print(b)     # b'hello' → converts string to bytes
# s2 = b.decode();  print(s2)   # 'hello' → converts bytes back to string

# print("--------------------------------------")

# # Changing case and removing spaces
# s = "Python Programming";  print(s)
# print(s.lower())    # 'python programming' → all lowercase
# print(s.upper())    # 'PYTHON PROGRAMMING' → all uppercase
# print(s.title())    # 'Python Programming' → capitalize first letter of each word
# print(s.strip())    # 'Python Programming' → removes leading/trailing spaces (none here)

# print("--------------------------------------")

# # Replace and find/count
# print(s.replace("Python", "Java"))  # 'Java Programming' → replace substring
# print(s.find("gram"))                # 10 → starting index of 'gram', -1 if not found
# print(s.count("m"))                  # 2 → count of character 'm'

# print("--------------------------------------")

# # Checking start and end of string
# print(s.startswith("Py"))    # True → checks if string starts with given substring
# print(s.endswith("  "))      # False → checks if string ends with given substring


# table = str.maketrans("aeiou", "12345");  print(table)  
# # creates mapping: a→1, e→2, i→3, o→4, u→5
# print("apple".translate(table))   
# # replaces vowels using mapping → '1ppl2'


s = " Python Programming ";  print(s)
print(s.find("z"))          # -1 → returns -1 because 'z' is NOT found
# print(s.index("z"))       # ValueError → raises error if 'z' is NOT found
print("--------------------------------------")
print(s.replace("Python", "Java"))  # 'Java Programming' → replace substring
print(s.find("gram"))                # 10 → starting index of 'gram', -1 if not found
print(s.count("m"))                  # 2 → count of character 'm'
print("--------------------------------------")
s = "hello"
b = s.encode();  print(b)     # b'hello' → converts string to bytes
s2 = b.decode();  print(s2)   # 'hello' → converts bytes back to string
print("--------------------------------------")
s = "python"
# Checking start and end of string
print(s.startswith("Py"))    # True → checks if string starts with given substring
print(s.endswith("  "))      # False → checks if string ends with given substring
print("--------------------------------------")
table = str.maketrans("aeiou", "12345");  print(table)  
# creates mapping: {'a'→'1',   'e'→'2',     'i'→'3',      'o'→'4',     'u'→'5'}
                                      # {97: 49, 101: 50, 105: 51, 111: 52, 117: 53}
# When you print table, Python shows it as Unicode numbers:
print("apple".translate(table))    # replaces vowels using mapping 1ppl2
# If character exists in the table → replace it    If not → keep it unchanged
# | Character  |            Action          |
# | -------------- | --------------------- |
# |         `a`        | replaced by `1` |
# |         `p`        | unchanged           |
# |         `p`        | unchanged           |
# |         `l`         | unchanged           |
# |         `e`        | replaced by `2` |

