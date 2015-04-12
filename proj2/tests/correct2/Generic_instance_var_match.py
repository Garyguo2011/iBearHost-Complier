class C of [$T]:
    def __init__(self):
        pass

    j::$T = None

anC = C of [str]()

anC.j = "Jinge Zhang"

otherC = C of [int]()

otherC.j = 6
