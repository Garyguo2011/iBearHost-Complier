def print_func(func::(int,int)->int):
	print func(1,1)
def addition(x::int, y::int)::int:
	return x+y
print_func(addition)
def identity(func::(int,int)->int):
	return func
def composition(x::int, y::int, func::((int,int)->int)->int):
	return func(addition)(x,y)
print composition(1,1,identity)
