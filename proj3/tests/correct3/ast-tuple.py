x = 1, 2, 3
print x

for i in [1, 2, 3]:
	print i

def f():
	return 1, 3, 4

y = f()
print y

def g(x):
	return x

z = g(1), g(2), g(3)
print z
