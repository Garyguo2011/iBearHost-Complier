a :: int = 4
def f(x :: int) :: int:
	def g() :: int:
		return 6
	x = 9
	return x
t :: int = f(a)
print(t)
