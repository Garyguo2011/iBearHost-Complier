def f(n):
	i::int = 0
	t::int = 3
	while i < n:
		if 1 < i % 7 <= 2:
			print i,
		i = i + 1
	else:
		s = i + 2; t = t + s ** 2
		print "s =", s, "t =", t
		i = i + 1
		return i

print f(5)
# print f(3) + f(2)
