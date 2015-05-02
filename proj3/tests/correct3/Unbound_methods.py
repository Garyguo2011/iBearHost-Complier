class C:
    def __init__(self):
        pass

    def g (self):
        return 6

vg::(C)->int = C.g

anC::C = C()

print vg(anC)

List = [C.g]

vg = List[0]

print vg(anC)
