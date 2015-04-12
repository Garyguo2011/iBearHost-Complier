
def g(y, z, a):
	def h(y :: int):
		return 1
	def h(y :: str):
		return "1"
	def h(y :: bool):
		return True
	def h(y :: int, z :: int):
		return y + z
	def h(y :: int, z :: str):
		return "y->int, z->str"
	def h(y :: str, z :: int):
		return False
	def h(y :: int, z :: int, a :: int):
		return "y->int, z->int, a->int"
	def h(y :: int, z :: int, a :: str):
		return z + a
	def h(y :: int, z :: str, a :: int):
		return False
	def h(y :: int, z :: str, a :: str):
		return "y->int, z->str, a->str"
	def h(y :: str, z :: int, a :: int):
		return z * a
	def h(y :: str, z :: int, a :: str):
		return True
	def h(y :: str, z :: str, a :: int):
		return 0
	def h(y :: str, z :: str, a :: str):
		return "y->str, z->str, a->str"
	return h

def g(y, z, a):
	def h(y :: int):
		return 1
	def h(y :: str):
		return "1"
	def h(y :: bool):
		return True
	def h(y :: int, z :: int):
		return y + z
	def h(y :: int, z :: str):
		return "y->int, z->str"
	def h(y :: str, z :: int):
		return False
	def h(y :: int, z :: int, a :: int):
		return "y->int, z->int, a->int"
	def h(y :: int, z :: int, a :: str):
		return z + a
	def h(y :: int, z :: str, a :: int):
		return False
	def h(y :: int, z :: str, a :: str):
		return "y->int, z->str, a->str"
	def h(y :: str, z :: int, a :: int):
		return z * a
	def h(y :: str, z :: int, a :: str):
		return True
	def h(y :: str, z :: str, a :: int):
		return 0
	def h(y :: str, z :: str, a :: str):
		return "y->str, z->str, a->str"
	return h


a :: int = 9
b :: str = "4"
c :: bool = True

f0 = g(1, 2, 3)
f1 = g("f", 3, "o")

b = f0("f", "f", "f") # Has two seperate senarios to call
