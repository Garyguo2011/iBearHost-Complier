def h(x::int):
    def g(y):
        def f(z):
            print x, y, z
        f(11)
    g(10)
h(9)
