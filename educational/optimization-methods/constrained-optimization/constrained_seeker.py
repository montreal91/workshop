
from vector2        import Vector2
from nd_min_seeker  import FindMinimum2

def GetSlice( callback ):
    def Slice(x):
        return max(0, callback(x))
    return Slice

def GetPenaltyFunction(rk, eq_list, ineq_list):
    slices = [GetSlice(fun) for fun in ineq_list]
    def P(vec):
        res = 0
        for fun in eq_list + slices:
            res += fun(vec) ** 2
        return res * (rk / 2)
    return P

def GetDerPenaltyFunction(rk, eq_list, der_eq_list, ineq_list, der_ineq_list):
    slices      = [GetSlice(fun) for fun in ineq_list]
    def DerPen(vec):
        res = Vector2()
        for i in range(len(eq_list)):
            der_call = der_eq_list[i]
            call = eq_list[i]
            res += (der_call(vec) * 2 * call(vec))
        for j in range(len(ineq_list)):
            slice_j = slices[j]
            der_slice_j = der_ineq_list[j]
            res += slice_j(vec) * der_slice_j(vec)
        return res * rk
    return DerPen

def GetAdditionalFunction(target_fun, penalty_fun):
    def Fun(vec):
        return target_fun(vec) + penalty_fun(vec)
    return Fun

def GetConstrainedMinimum(
    start,
    target_cb,
    der_target_cb,
    eq_list=[],
    der_eq_list=[],
    ineq_list=[],
    der_ineq_list=[],
    pen_factor=2.0,
    eps=0.01
):
    have_to_exit    = False
    curr_pen_factor = pen_factor
    aux_min         = start
    iter_counter    = 0
    while not have_to_exit:
        penalty_function    = GetPenaltyFunction(curr_pen_factor, eq_list, ineq_list)
        der_pen_function    = GetDerPenaltyFunction(
            curr_pen_factor,
            eq_list,
            der_eq_list,
            ineq_list,
            der_ineq_list
        )
        aux_function        = GetAdditionalFunction( target_cb, penalty_function )
        der_aux_function    = GetAdditionalFunction( der_target_cb, der_pen_function )
        res                 = FindMinimum2( aux_min, aux_function, der_aux_function, epsilon=0.0001, restarts=200 )
        aux_min             = res.first
        iter_counter += res.second
        if penalty_function(aux_min) < eps:
            have_to_exit = True
        else:
            curr_pen_factor *= 2
            print(curr_pen_factor)
    return aux_min, iter_counter

if __name__ == "__main__":
    def Target(vec):
        return vec.x ** 2 + vec.y ** 2

    def DerTarget(vec):
        return Vector2(2 * vec.x, 2 * vec.y)

    def ineq_constraint(vec):
        return (vec.x + 10) ** 2 + vec.y ** 2 - 1

    def der_ineq_constraint(vec):
        return Vector2( 2 * vec.x + 20, 2 * vec.y )

    def eq_constraint1( vec ):
        return vec.x

    def der_eq_constraint1( vec ):
        return Vector2(1, 0)

    def eq_constraint2(vec):
        return vec.x + vec.y - 2

    def der_eq_constraint2(vec):
        return Vector2(1, 1)

    def IneqMinimum1(vec):
        return -2 * vec.x + vec.y + 2

    def DerIneqMinimum1(vec):
        return Vector2(-2, 1)

    def IneqMinimum2(vec):
        return -vec.x - vec.y - 3

    def DerIneqMinimum2(vec):
        return Vector2( -1, -1)

    def IneqMinimum3(vec):
        return vec.x + vec.y - 3

    def DerIneqMinimum3(vec):
        return Vector2(1, 1)

    res = GetConstrainedMinimum(
        Vector2(-5, 0),
        Target,
        DerTarget,
        eq_list=[],
        der_eq_list=[],
        ineq_list=[IneqMinimum1, IneqMinimum2, IneqMinimum3],
        der_ineq_list=[DerIneqMinimum1, DerIneqMinimum2, DerIneqMinimum3],
        eps=0.0001
    )
    print(res[0], res[1])
