import math

# -------------------------------
# Helper functions
# -------------------------------

def is_operator(c):
    return c in "+-*/^"

def precedence(op):
    if op == '^':
        return 3
    if op in "*/":
        return 2
    if op in "+-":
        return 1
    return 0

def apply_op(a, b, op):
    if op == '+': return a + b
    if op == '-': return a - b
    if op == '*': return a * b
    if op == '/': return a / b
    if op == '^': return a ** b


# -------------------------------
# INFIX -> POSTFIX
# -------------------------------

def infix_to_postfix(expression):
    stack = []
    result = []
    i = 0

    while i < len(expression):
        if expression[i] == ' ':
            i += 1
            continue

        # number (multi-digit)
        if expression[i].isdigit():
            num = ""
            while i < len(expression) and expression[i].isdigit():
                num += expression[i]
                i += 1
            result.append(num)
            continue

        # (
        if expression[i] == '(':
            stack.append('(')

        # )
        elif expression[i] == ')':
            while stack and stack[-1] != '(':
                result.append(stack.pop())
            stack.pop()

        # operator
        elif is_operator(expression[i]):
            while (stack and stack[-1] != '(' and
                   precedence(stack[-1]) >= precedence(expression[i])):
                result.append(stack.pop())
            stack.append(expression[i])

        i += 1

    while stack:
        result.append(stack.pop())

    return " ".join(result)


# -------------------------------
# INFIX -> PREFIX
# -------------------------------

def infix_to_prefix(expression):
    # Step 1: tokenize properly
    tokens = expression.split()

    # Step 2: reverse tokens
    tokens = tokens[::-1]

    # Step 3: swap brackets
    for i in range(len(tokens)):
        if tokens[i] == '(':
            tokens[i] = ')'
        elif tokens[i] == ')':
            tokens[i] = '('

    # Step 4: convert to string again
    reversed_expr = " ".join(tokens)

    # Step 5: postfix of reversed expression
    postfix = infix_to_postfix(reversed_expr)

    # Step 6: correct prefix = reverse postfix tokens
    prefix = postfix.split()[::-1]

    return " ".join(prefix)


# -------------------------------
# POSTFIX EVALUATION
# -------------------------------

def evaluate_postfix(expr):
    stack = []
    tokens = expr.split()

    for token in tokens:
        if token.isdigit():
            stack.append(int(token))
        else:
            b = stack.pop()
            a = stack.pop()
            stack.append(apply_op(a, b, token))

    return stack[0]


# -------------------------------
# PREFIX EVALUATION
# -------------------------------

def evaluate_prefix(expr):
    stack = []
    tokens = expr.split()[::-1]

    for token in tokens:
        if token.isdigit():
            stack.append(int(token))
        else:
            a = stack.pop()
            b = stack.pop()
            stack.append(apply_op(a, b, token))

    return stack[0]


# -------------------------------
# TEST
# -------------------------------

exp = "10 + ( 2 * 3 )"

postfix = infix_to_postfix(exp)
prefix = infix_to_prefix(exp)

print("Infix   :", exp)
print("Postfix :", postfix)
print("Prefix  :", prefix)

print("\nPostfix Eval:", evaluate_postfix(postfix))
print("Prefix Eval :", evaluate_prefix(prefix))