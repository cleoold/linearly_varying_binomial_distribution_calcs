
/* 
to test the correctness of implemented prob_func module
*/

// gcc -o tests.exe tests.c .\prob_func.c

#include <stdio.h>
#include <assert.h>
#include "prob_func.h"

#define absval(a) ((a) > 0 ? (a) : -(a))
#define eq(a, b) absval((a) - (b)) < 0.00001

int main()
{
    distr x = create_model(0.02, 0.02, 50);

    assert(x.max_times == 99);

    assert(eq(have_success_given_no_successes_before(&x, 1), 0.02));
    assert(eq(have_success_given_no_successes_before(&x, 49), 0.02));
    assert(eq(have_success_given_no_successes_before(&x, 50), 0.02));
    assert(eq(have_success_given_no_successes_before(&x, 51), 0.04));
    assert(eq(have_success_given_no_successes_before(&x, 99), 1.0));
    assert(eq(have_success_given_no_successes_before(&x, 100), 1.0));

    assert(eq(no_success_given_no_successes_before(&x, 49), 0.98));
    assert(eq(no_success_given_no_successes_before(&x, 50), 0.98));
    assert(eq(no_success_given_no_successes_before(&x, 51), 0.96));
    assert(eq(no_success_given_no_successes_before(&x, 99), 0.0));
    assert(eq(no_success_given_no_successes_before(&x, 100), 0.0));

    assert(eq(have_first_success_at_n(&x, 1), 0.02));
    assert(eq(have_first_success_at_n(&x, 60), 0.024964));
    assert(eq(have_first_success_at_n(&x, 100), 0.0));
    assert(eq(have_first_success_at_n_E(&x), 34.594555));

    assert(eq(have_success_within_n_attempts(&x, 0), 0.0));
    assert(eq(have_success_within_n_attempts(&x, 1), 0.02));
    assert(eq(have_success_within_n_attempts(&x, 60), 0.911490));
    assert(eq(have_success_within_n_attempts(&x, 99), 1.0));

    assert(eq(no_success_within_n_attempts(&x, 0), 1.0));
    assert(eq(no_success_within_n_attempts(&x, 1), 0.98));
    assert(eq(no_success_within_n_attempts(&x, 60), 0.088501));
    assert(eq(no_success_within_n_attempts(&x, 99), 0.0));

    assert(eq(have_m_successes_within_n_attempts(&x, 0, 1), 0.0));
    assert(eq(have_m_successes_within_n_attempts(&x, 1, 1), 0.02));
    assert(eq(have_m_successes_within_n_attempts(&x, 99, 1), 0.184785));
    assert(eq(have_m_successes_within_n_attempts(&x, 400, 6), 0.005329));

    puts("all tests passed!");
}