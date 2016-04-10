
import test_functions
import utility_functions

from min_seeker import MinSeeker
from vector     import Vector

def IsConditionDone( vec, epsilon, target_derivative_cb, iteration, max_iterations ):
    gradient = target_derivative_cb( vec )
    main_stop_condition = gradient.length < epsilon
    max_iterations = max_iterations <= iteration
    return main_stop_condition or max_iterations

def FindMinimum( vec, target_cb, target_drv_cb, epsilon=0.01, max_iterations=1000, restarts=50 ):
    utility_functions.PrintTableHeader()
    iteration   = 0
    curr_vec    = vec
    prev_vec    = vec
    lin_acc     = epsilon ** 3
    restarts    = [i * restarts for i in range(int(max_iterations/restarts))]
    while not IsConditionDone( curr_vec, epsilon, target_drv_cb, iteration, max_iterations ):
        if iteration in restarts:
            iteration = 0

        if iteration == 0:
            direction   = target_drv_cb( curr_vec ) * ( -1 ) # Antigradient
            phi_func    = utility_functions.FunctionPhi( curr_vec, direction, target_cb )
            ms          = MinSeeker( phi_func, accuracy=lin_acc )
            alpha       = ms.GetMinimum()

            if alpha is not None:
                curr_vec = curr_vec + direction * alpha
            else:
                raise Exception( "There is no minimum in phi function" )

            utility_functions.PrintTableLine(
                iteration=iteration,
                direction=direction,
                alpha=alpha,
                curr_vec=curr_vec,
                prev_vec=prev_vec,
                func_val=target_cb( curr_vec )
            )
        else:
            beta        = utility_functions.GetBeta( curr_vec, prev_vec, target_drv_cb )
            direction   = ( target_drv_cb( curr_vec ) + target_drv_cb( prev_vec ) * beta ) * ( -1 )
            phi_func    = utility_functions.FunctionPhi( curr_vec, direction, target_cb )
            ms          = MinSeeker( phi_func, accuracy=lin_acc )
            alpha       = ms.GetMinimum()
            new_vec     = curr_vec + direction * alpha
            prev_vec    = curr_vec
            curr_vec    = new_vec
            utility_functions.PrintTableLine(
                iteration=iteration,
                direction=direction,
                alpha=alpha,
                beta=beta,
                curr_vec=curr_vec,
                prev_vec=prev_vec,
                func_val=target_cb( curr_vec )
            )
        iteration += 1
    utility_functions.PrintTableFooter()
    return curr_vec

if __name__ == '__main__':
    print( "TEST SUITE ONE")
    FindMinimum( Vector( 1, 1 ), test_functions.TargetFunc1, test_functions.TargetFuncDerivative1 )

    print( "<br>TEST SUITE TWO")
    FindMinimum( Vector( 1, 1 ), test_functions.TargetFunc2, test_functions.TargetFuncDerivative2 )

    print( "<br>TEST SUITE THREE")
    FindMinimum( Vector( 1, 0 ), test_functions.TargetFunc2, test_functions.TargetFuncDerivative2 )

    print( "<br>TEST SUITE FOUR")
    FindMinimum( Vector( -1, 2 ), test_functions.TargetFunc3, test_functions.TargetFuncDerivative3 )
