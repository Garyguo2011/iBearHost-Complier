def make_adder(x::int):
	def adder(y::int):
		return x + y
	return adder
a = make_adder(5)
print a(10)
