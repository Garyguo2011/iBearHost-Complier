def make_adder(x):
	def adder(y):
		return x + y
	return adder
a = make_adder(5)
print a(10)
