def g(x::int, y::int):
    if y == 0:
        return 1
    else:
        t::int = g (x, y-1)
        return t * x

print g(3,4)

