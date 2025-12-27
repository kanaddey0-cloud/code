s = "python"
# Checking start and end of string
print(s.startswith("Py"))    # True → checks if string starts with given substring
print(s.endswith("  "))      # False → checks if string ends with given substring
print("--------------------------------------")
table = str.maketrans("aeiou", "12345");  print(table)  
# creates mapping: a→1, e→2, i→3, o→4, u→5
print("apple".translate(table))    # replaces vowels using mapping → '1ppl2'
