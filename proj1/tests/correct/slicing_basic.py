x = [0,1,2,3,4,5]
print x[2:3]
print x[2:]
print x[:5]
x[0:2] = 11,12
x[2:5] = 15, 16, 17
print x[0:]
print x[:5]
x[:2] = 101, 102
x[4:] = 99, 100
print x[:2]
print x[4:]