def g(y :: int):
	def h(y :: int):
		return "1"
	def h(y :: str):
		return 5
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
		return 3
	def h(y :: str, z :: int, a :: int):
		return z * a
	def h(y :: str, z :: int, a :: str):
		return True
	def h(y :: str, z :: str, a :: int):
		return 0
	def h(y :: str, z :: str, a :: str):
		return "y->str, z->str, a->str"
	return h

def g(y :: str):
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
		return "False"
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
		return 2
	return h

def g(y :: bool):
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
		return 4
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

def g(y :: int, z :: int):
	def h(y :: int):
		return 1
	def h(y :: str):
		return "1"
	def h(y :: bool):
		return 3
	def h(y :: int, z :: int):
		return y + z
	def h(y :: int, z :: str):
		return "y->int, z->str"
	def h(y :: str, z :: int):
		return False
	def h(y :: int, z :: int, a :: int):
		return True
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

def g(y :: int, z :: str):
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

def g(y :: str, z :: int):
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

def g(y :: int, z :: int, a :: int):
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

def g(y :: int, z :: int, a :: str):
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

def g(y :: int, z :: str, a :: int):
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

def g(y :: int, z :: str, a :: str):
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

def g(y :: str, z :: int, a :: int):
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

def g(y :: str, z :: int, a :: str):
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

def g(y :: str, z :: str, a :: int):
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

def g(y :: str, z :: str, a :: str):
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

f0 = g(1, 2)
f1 = g("f", 3, "o")
f2 = g(False)

print "sucess!"

a = f0(3, 4)
b = f1(1)
c = f2("a", 4)

print "sucess!"

a = f1("a", "a", 9)
b = f1("a", "a", "a")
c = ("3", 4)

print "sucess!"
