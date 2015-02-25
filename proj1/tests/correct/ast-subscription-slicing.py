x = (1, 2, 3, 4, 5)

for i in range(0, 5):
	print x[i]

print x[0:4]
print x[1:]


def f(x):
	return x[1], x[2]

y = [1, 2, 3]
y[0], y[1] = f(x)

print y[0]
print y[1]
