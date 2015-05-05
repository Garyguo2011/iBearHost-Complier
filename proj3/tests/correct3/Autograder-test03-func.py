def f(x, y::int):
	def g(f):
		return f(x)
	
	def h(z::int):
		return z + y
	return g(h)

print f(5,7)
