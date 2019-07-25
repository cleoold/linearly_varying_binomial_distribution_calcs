/*
the linearly increasing probability in the
binomial-like distribution problem

(c) cleoold in July 2019 */


#include <math.h>
#include "prob_func.h"
#include <stdio.h>
#include <stdlib.h>


distr create_model( probability base_prob_of_success,
                    probability additional_prob_of_success,
                    int threshold_to_activate_addition)
{
    distr res = {   base_prob_of_success,
                    additional_prob_of_success,
                    threshold_to_activate_addition };
    res.max_times = (int)((1.0 - base_prob_of_success) / additional_prob_of_success
                            + threshold_to_activate_addition);
    return res;
}


probability have_success_given_no_successes_before(distr *s, int n)
{
    if (n < 1) return 0.0;
    return fmin(1.0, 
        s->base_prob + fmax(0, s->additional_prob * (n - s->threshold)) );
}


probability no_success_given_no_successes_before(distr *s, int n)
{
    return 1.0 - have_success_given_no_successes_before(s, n);
}


probability have_first_success_at_n(distr *s, int n)
{
    probability res = have_success_given_no_successes_before(s, n);
    for (int j = 1; j < n; ++j)
    {
        res *= no_success_given_no_successes_before(s, j);
    }
    return res;
}


count have_first_success_at_n_E(distr *s)
{
    count res = 0.0;
    for (int j = 1; j <= s->max_times; ++j)
    {
        res += have_first_success_at_n(s, j) * j;
    }
    return res;
}


probability no_success_within_n_attempts(distr *s, int n)
{
    probability res = 1.0;
    for (int j = 1; j <= n; ++j)
    {
        res *= no_success_given_no_successes_before(s, j);
    }
    return res;
}


probability have_success_within_n_attempts(distr *s, int n)
{
    return 1.0 - no_success_within_n_attempts(s, n);
}


static double **_create_2d_array(int outer, int inner)
{
    // and sets all values to 0
    double **arr;
    arr = malloc(sizeof(*arr) * outer);
    for (int j = 0; j < outer; ++j)
    {
        arr[j] = malloc(sizeof(*arr[j]) * inner);
        if (!arr[j]) 
        {
            puts("可能存在内存错误 / possible memory error.");
            break;
        }
        for (int k = 0; k < inner; arr[j][k++] = 0.0);
    }
    return arr;
}

static void _deallocate_2d_array(double **arr, int outer)
{
    for (int j = 0; j < outer; free(arr[j++]));
    free(arr);
}

static double _sum_of_array(double *arr, int len)
{
    double res = 0.0;
    for (int j = 0; j < len; res += arr[j++]);
    return res;
}

probability **_have_m_successes_within_n_attempts_dist(distr *s, int n, int m)
{
    probability **last = _create_2d_array(m + 2, s->max_times + 2);
    last[0][1] = 1.0;
    for (int i = 1; i <= n; ++i)
    {
        probability **this = _create_2d_array(m + 2, s->max_times + 2);
        for (int j = 1; j <= s->max_times; ++j)
        {
            for (int c = 0; c <= m; ++c)
            {
                this[c][j+1] += last[c][j] * no_success_given_no_successes_before(s, j);
                this[c+1][1] += last[c][j] * have_success_given_no_successes_before(s, j);
            }
        }
        _deallocate_2d_array(last, m + 2);
        last = this;
        _deallocate_2d_array(this, m + 2);
    }
    return last;
}

probability have_m_successes_within_n_attempts(distr *s, int n, int m)
{
    probability **res_arr = _have_m_successes_within_n_attempts_dist(s, n, m);
    probability res = _sum_of_array(res_arr[m], s->max_times + 2);
    _deallocate_2d_array(res_arr, m + 2);
    return res;
}