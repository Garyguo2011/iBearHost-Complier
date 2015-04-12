def g(y, z, a):

	def h(y, z, a):
		return "y->int, z->int, a->int"

	def h(y, z, a):
		return z + a

	def h(y, z, a):
		return 0

	return h


a :: int = 9
b :: str = "4"
c :: bool = True

f = g(b, b, b)

b = f(4, "4", "4") #Ambigurious


