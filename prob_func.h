/*
the linearly increasing probability in the
binomial-like distribution problem

(c) cleoold in July 2019 */

#ifndef _PROB_FUNC_H
#define _PROB_FUNC_H


typedef double probability;
typedef double count;

// the varying binomial distribution parameters
typedef struct distr
{
    // probability of one success event at the beginning
    probability base_prob;
    // constant to add to the base probability above
    probability additional_prob;
    // after how many times to start adding constant to the probability
    int threshold;
    // until how many times so that there must be one success
    int max_times;
} distr;


// creates probability distribution model
distr create_model( probability base_prob_of_success,
                    probability additional_prob_of_success,
                    int threshold_to_activate_addition);

// given that one failed for n-1 times, the chance of success at n-th
probability have_success_given_no_successes_before(distr *s, int n);

// given that one failed for n-1 times, the chance of failure at n-th
probability no_success_given_no_successes_before(distr *s, int n);

// the chance for one fails for n-1 times, then succeed at n-th
probability have_first_success_at_n(distr *s, int n);

    // expectation of [have_first_success_at_n]
    count have_first_success_at_n_E(distr *s);

// the chance of having at least one success within n trails
probability have_success_within_n_attempts(distr *s, int n);

// the chance of not having any success within n trails
probability no_success_within_n_attempts(distr *s, int n);

// the chance of having m successes within n trails
probability have_m_successes_within_n_attempts(distr *s, int n, int m);

#endif