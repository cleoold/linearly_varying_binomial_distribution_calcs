
/* 
    to test the correctness of implemented prob_func module

    this test file creates the same model that's used in the game Arknights

    this successfully passed on gcc compiler installed on a PC running Windows 10
    gcc -Wall -o function_tests.exe .\function_tests.c .\prob_func.c

    (c) cleoold in July 2019
*/

#include <stdio.h>
#include <assert.h>
#include "prob_func.h"

#define absval(a) ((a) > 0 ? (a) : -(a))
#define eq(a, b) absval((a) - (b)) < 0.0001

int main(int argc, char **argv)
{
    puts("if any assertion fails, try reopen this file for few times to see"
            " if the problem persists. If it does, then the code is wrong.");

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
    assert(eq(have_m_successes_within_n_attempts(&x, 99, 2), 0.360283));
    assert(eq(have_m_successes_within_n_attempts(&x, 400, 6), 0.000888));

    assert(eq(have_m_successes_within_n_attempts_E(&x, 0), 0.0));
    assert(eq(have_m_successes_within_n_attempts_E(&x, 1), 0.02));
    assert(eq(have_m_successes_within_n_attempts_E(&x, 50), 1.0));
    assert(eq(have_m_successes_within_n_attempts_E(&x, 100), 2.566319));
    assert(eq(have_m_successes_within_n_attempts_E(&x, 320), 8.947578));

    assert(eq(have_m_or_more_successes_within_n_attempts(&x, 0, 1), 0.0));
    assert(eq(have_m_or_more_successes_within_n_attempts(&x, 1, 1), 0.02));
    assert(eq(have_m_or_more_successes_within_n_attempts(&x, 99, 1), 1.0));
    assert(eq(have_m_or_more_successes_within_n_attempts(&x, 70, 5), 0.013407));
    assert(eq(have_m_or_more_successes_within_n_attempts(&x, 300, 8), 0.650686));

    assert(eq(have_special_success_within_n_attempts(&x, 0, 0.5), 0.0));
    assert(eq(have_special_success_within_n_attempts(&x, 1, 0.5), 0.01));
    assert(eq(have_special_success_within_n_attempts(&x, 50, 0.5), 0.394994));
    assert(eq(have_special_success_within_n_attempts(&x, 150, 0.5), 0.9124559));

    assert(eq(have_special_success_within_n_attempts_E(&x, 0.5), 69.18911));

    puts("all tests passed!");
}