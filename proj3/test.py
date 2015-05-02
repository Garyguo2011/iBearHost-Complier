def f():
	def k():
		x = 1
		return x
	return k()

def g():
	def h():
		return x
	return h()
