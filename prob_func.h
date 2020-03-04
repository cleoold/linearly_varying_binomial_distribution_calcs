/*
    the linearly increasing probability in the
    binomial-like distribution problem

    one can flip a card. there is a probability [base_prob] to have a good one at the beginning.
    if one does not have the good one for some attempts in a row, the constant will be added
    to the existing probability (so that the chance of having the good one is increasing) until
    one finally has the good card, at which point the chance will reset to the original one.

    for some computed results see function_tests.c

    (c) cleoold in July 2019 
*/

#ifndef _PROB_FUNC_H
#define _PROB_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef double probability;
typedef double count; // this is number of successes

// probability, count are numbers
typedef double number;

// the varying binomial distribution parameters
// stack allocated
typedef struct LVBdistribution
{
    probability base_prob;       // probability of one success event at the beginning
    probability additional_prob; // constant to add to the base probability above, can't be 0
    int         threshold;       // after how many times to start adding constant to the probability
    int         max_times;       // until how many times so that there must be one success
} LVBdistribution;


// creates probability distribution model (stack allocated)
LVBdistribution create_model(   probability base_prob_of_success,
                                probability additional_prob_of_success,
                                int threshold_to_activate_addition);

// given that one failed for n-1 times, the chance of success at n-th
probability have_success_given_no_successes_before(LVBdistribution *s, int n);

    // given that one failed for n-1 times, the chance of failure at n-th
    probability no_success_given_no_successes_before(LVBdistribution *s, int n);

// the chance for one fails for n-1 times, then succeed at n-th
probability have_first_success_at_n(LVBdistribution *s, int n);

    // expectation of [have_first_success_at_n]
    count have_first_success_at_n_E(LVBdistribution *s);

// the chance of having at least one success within n trails
probability have_success_within_n_attempts(LVBdistribution *s, int n);

    // the chance of not having any success within n trails
    probability no_success_within_n_attempts(LVBdistribution *s, int n);

// the chance of having m successes within n trails
probability have_m_successes_within_n_attempts(LVBdistribution *s, int n, int m);

    // the chance of having m or more successes within n trails
    probability have_m_or_more_successes_within_n_attempts(LVBdistribution *s, int n, int m);

    // expectation of [have_m_successes_within_n_attempts] ignoring n
    count have_m_successes_within_n_attempts_E(LVBdistribution *s, int n);

// an event with probability p given a success is a special success, 
// the chance of having at least one special success within n trails
probability have_special_success_within_n_attempts(LVBdistribution *s, int n, probability p);

    // an event with probability p given a success is a special success, 
    // the chance of not having any special success within n trails
    probability no_special_success_within_n_attempts(LVBdistribution *s, int n, probability p);

    // expectation of [have_special_success_within_n_attempts] 
    count have_special_success_within_n_attempts_E(LVBdistribution *s, probability p);

    // waiting to add...
    //probability have_m_special_success_within_n_attempts(LVBdistribution *s, int n, int m, probability p);


#ifdef __cplusplus
}
#endif

#endif // define _PROB_FUNC_H
