
import utilities

from one_d_min_seeker   import OneDMinSeeker
from utilities          import Struct


def IsConditionDone( vec, epsilon, target_derivative_cb, iteration, max_iterations ):
    gradient = target_derivative_cb( vec )
    main_stop_condition = gradient.length < epsilon
    max_iterations = max_iterations <= iteration
    return main_stop_condition or max_iterations

def FindMinimum2( vec, target_cb, target_drv_cb, epsilon=0.01, max_iterations=1000, restarts=50 ):
    iteration   = 0
    curr_vec    = vec
    prev_vec    = vec
    lin_acc     = epsilon ** 2
    restarts    = [i * restarts for i in range(int(max_iterations/restarts))]
    while not IsConditionDone( curr_vec, epsilon, target_drv_cb, iteration, max_iterations ):
        if iteration in restarts:
            direction   = target_drv_cb( curr_vec ) * ( -1 ) # Antigradient
            phi_func    = utilities.FunctionPhi2( curr_vec, direction, target_cb )
            ms          = OneDMinSeeker( phi_func, accuracy=lin_acc )
            alpha       = ms.GetMinimum()

            if alpha is not None:
                curr_vec += (direction * alpha)
            else:
                raise Exception( "There is no minimum in phi function" )
        else:
            beta        = utilities.GetBeta( curr_vec, prev_vec, target_drv_cb )
            direction   = ( target_drv_cb( curr_vec ) + target_drv_cb( prev_vec ) * beta ) * ( -1 )
            phi_func    = utilities.FunctionPhi2( curr_vec, direction, target_cb )
            ms          = OneDMinSeeker( phi_func, accuracy=lin_acc )
            alpha       = ms.GetMinimum()
            new_vec     = curr_vec + direction * alpha
            prev_vec    = curr_vec
            curr_vec    = new_vec
        iteration += 1
    pair = Struct()
    pair.first = curr_vec
    pair.second = iteration
    return pair
