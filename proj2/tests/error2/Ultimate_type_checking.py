def g(a, b):
    return a, b

p = g(3, "hello")
t = g(g(1, 2), "hello")
c::str, s::int = p
