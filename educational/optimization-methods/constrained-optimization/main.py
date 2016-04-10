
from constrained_seeker import GetConstrainedMinimum
from test_suites        import suite1, suite2, suite3
from test_suites        import suite4, suite5, suite6, bf_suite1

def main():
    print("\nTest suite BygFoot")
    res7 = GetConstrainedMinimum(
        bf_suite1.start_point,
        target_cb=bf_suite1.target_cb,
        der_target_cb=bf_suite1.d_target_cb,
        eq_list=bf_suite1.constraints_eq_l,
        der_eq_list=bf_suite1.d_constraints_eq_l,
        ineq_list=bf_suite1.constraints_ineq_l,
        der_ineq_list=bf_suite1.d_constraints_ineq_l,
        eps=0.001
    )
    print(res7[0], res7[1])

if __name__ == "__main__":
    main()
