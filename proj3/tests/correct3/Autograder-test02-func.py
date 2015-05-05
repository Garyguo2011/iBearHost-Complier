def g(f, x, y):
	f(x, y)

def f(x, y):
	print x
	print y

g(f, (1,2), (3,4))
g(f, 1, 2)
