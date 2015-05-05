def g(x::int, y):
    def h(y::int):
        if y == 0:
            return 1
        else:
            t::int = h(y-1)
            return t * x
    return h(y)

print g(3,4)
