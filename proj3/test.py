def fib(n):
    if n < 2:
        return n
    return fib(n-2) + fib(n-1)

for i in xrange(0, 7):
	print fib(i)
