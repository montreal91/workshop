
from utilities  import Struct
from vector2    import Vector2


def Target1( vec ):
    return vec.x ** 2 + vec.y ** 2

def DerTarget1( vec ):
    return Vector2( 2 * vec.x, 2 * vec.y )

def Target2(vec):
    return vec.x ** 2 + vec.y ** 3

def DerTarget2(vec):
    return Vector2(2 * vec.x, 3 * vec.y ** 2)

def Target3(vec):
    return (vec.x **2 + 6 * vec.y) ** 4 + 8 * vec.x * vec.y

def DerTarget3(vec):
    x = ((vec.x ** 2 + 6 * vec.y) ** 3 ) * 8 * vec.x + 8 * vec.y
    y = ((vec.x ** 2 + 6 * vec.y) ** 3 ) * 24 + 8 * vec.y
    return Vector2(x, y)

def e11(vec):
    return vec.x + 1.235

def de11(vec):
    return Vector2(1, 0)

def e12(vec):
    return vec.y - 1

def de12(vec):
    return Vector2(0, 1)

def e13(vec):
    return vec.x - 2 * vec.y ** 2 + 8 * vec.y

def de13(vec):
    return Vector2(1, -4 * vec.y + 8)

def i21(vec):
    return (vec.x + 2) ** 2 + (vec.y + 2) ** 2 - 4

def di21(vec):
    return Vector2(2 * vec.x + 4, 2 * vec.y + 4)

def i22(vec):
    return vec.x ** 2 + vec.y ** 2 - 1

def di22(vec):
    return Vector2(2 * vec.x, 2 * vec.y)

def i31(vec):
    return vec.x - 1

def di31(vec):
    return Vector2(1, 0)

def i32(vec):
    return - 3 * vec.x + vec.y - 6

def di32(vec):
    return Vector2( -3, 1)

def i33(vec):
    return vec.x - vec.y - 4

def di33(vec):
    return Vector2(1, -1)

def i34(vec):
    return -0.5 * vec.x + vec.y + 2

def di34(vec):
    return Vector2(-0.5, 1)

def i35(vec):
    return -vec.x - vec.y - 4

def di35(vec):
    return Vector2(-1, -1)

def TargetBygfoot(vec):
    return - vec.x * vec.y

def DerTargetBygfoot(vec):
    return Vector2(-vec.y, -vec.x)

def i_bfoot1(vec):
    return -vec.x

def di_bfoot1(vec):
    return Vector2(-1, 0)

def i_bfoot2(vec):
    return vec.x - 30000

def di_bfoot2(vec):
    return Vector2(1, 0)

def i_bfoot3(vec):
    return -vec.y

def di_bfoot3(vec):
    return Vector2(0, -1)

def i_bfoot4(vec):
    return vec.y - 30

def di_bfoot4(vec):
    return Vector2(0, 1)

bf_suite1                      = Struct()
bf_suite1.target_cb            = TargetBygfoot
bf_suite1.d_target_cb          = DerTargetBygfoot
bf_suite1.constraints_eq_l     = []
bf_suite1.d_constraints_eq_l   = []
bf_suite1.constraints_ineq_l   = [i_bfoot1, i_bfoot2, i_bfoot3, i_bfoot4]
bf_suite1.d_constraints_ineq_l = [di_bfoot1, di_bfoot2, di_bfoot3, di_bfoot4]
bf_suite1.start_point          = Vector2(50000, 100)


suite1                      = Struct()
suite1.target_cb            = Target1
suite1.d_target_cb          = DerTarget1
suite1.constraints_eq_l     = [e11]
suite1.d_constraints_eq_l   = [de11]
suite1.constraints_ineq_l   = []
suite1.d_constraints_ineq_l = []
suite1.start_point          = Vector2(4, 3)

suite2                      = Struct()
suite2.target_cb            = Target1
suite2.d_target_cb          = DerTarget1
suite2.constraints_eq_l     = [e11, e12]
suite2.d_constraints_eq_l   = [de11, de12]
suite2.constraints_ineq_l   = []
suite2.d_constraints_ineq_l = []
suite2.start_point          = Vector2(-4, 3)

suite3                      = Struct()
suite3.target_cb            = Target1
suite3.d_target_cb          = DerTarget1
suite3.constraints_eq_l     = [e13]
suite3.d_constraints_eq_l   = [de13]
suite3.constraints_ineq_l   = []
suite3.d_constraints_ineq_l = []
suite3.start_point          = Vector2(3, -2)

suite4                      = Struct()
suite4.target_cb            = Target2
suite4.d_target_cb          = DerTarget2
suite4.constraints_eq_l     = []
suite4.d_constraints_eq_l   = []
suite4.constraints_ineq_l   = [i21]
suite4.d_constraints_ineq_l = [di21]
suite4.start_point          = Vector2(4, -4)

suite5                      = Struct()
suite5.target_cb            = Target2
suite5.d_target_cb          = DerTarget2
suite5.constraints_eq_l     = []
suite5.d_constraints_eq_l   = []
suite5.constraints_ineq_l   = [i21, i22]
suite5.d_constraints_ineq_l = [di21, di22]
suite5.start_point          = Vector2(4, 4)

suite6                      = Struct()
suite6.target_cb            = Target3
suite6.d_target_cb          = DerTarget3
suite6.constraints_eq_l     = []
suite6.d_constraints_eq_l   = []
suite6.constraints_ineq_l   = [i31, i32, i33, i34, i35]
suite6.d_constraints_ineq_l = [di31, di32, di33, di34, di35]
suite6.start_point          = Vector2(-4, 4)
