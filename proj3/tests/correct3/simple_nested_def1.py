def f():
	def g():
		return 1
	return g()

print f()


