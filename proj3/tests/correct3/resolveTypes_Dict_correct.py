a::int = 4
x::dict of [int, str] = {a : 'a'}
y::dict of [int, str] = x

print y

b::dict of [int, list of [int]] = {1: [1,2,3,4]}

print b

c::dict of [str, tuple3 of [int, str, bool]] = {'1': (1, 'a', False)}

print c

d::dict of [bool, tuple3 of [int, str, bool]] = {True: (1, 'a', False)}

print d
