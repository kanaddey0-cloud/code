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

from functools import wraps

def star(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print("***** before star *****")
        result = func(*args, **kwargs)
        print("***** after star *****")
        return result
    return wrapper

def plus(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print("+++++ before plus +++++")
        result = func(*args, **kwargs)
        print("+++++ after plus +++++")
        return result
    return wrapper

@star   # applied last (outer wrapper)
@plus   # applied first (inner wrapper)
def greet():
    print("Hello!")

greet()

