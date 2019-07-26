### .h
* create probability struct `struct distr`
* do calculations

### Description of the math

* Please open this readme file in a viewer that supports latex equations if you want to see them.

The cardpool of the game looks like:

One can flip a card. there is a probability (here say 0.02) to have a good one at the beginning.
* If one does not have the good one for some attempts in a row, the constant (here say 0.02) will be added to the existing probability (so that the chance of having the good one is increasing) until one finally has the good card, at which point the chance will reset to the original one.

For example, one tried 52 times and there have been no successes. At this point his/her chance to success for the next time will be 0.08. If the 53-rd try is a success, then the chance for the 54-th try will be reset to 0.02, otherwise the chance becomes 0.10. Also the maximum number of tries allowed here is calculated 99, where the chance is 1.

* the distribution:
    ```c
    struct distr create_model( probability base_prob_of_success, // = 0.02
                               probability additional_prob_of_success, // = 0.02
                               int threshold_to_activate_addition); // = 50
    ```

* The (conditional) probability of success at n given that one fails for n-1 times:
    ```c
    probability have_success_given_no_successes_before(distr *s, int n);
    ```
    $$
    pf(n)=
                \begin{cases}
                    0.02, & 0<n\leq50\\ 
                    0.02+0.02(n-50), & 50<n\leq99 
                \end{cases}
    $$

* The probability of success at n AND failures at n-1, n-2, ..., 1: 
    ```c
    probability have_first_success_at_n(distr *s, int n);
    ```
    $$
    P(n)=pf(n)\prod _{j=1}^{n-1}(1-pf(j))
    $$

* The probability of having at least one success in n tries:
    ```c
    probability have_success_within_n_attempts(distr *s, int n);
    ```
    $$
    \overline{F}(n)=1-\prod _{j=1}^{n}(1-pf(j))
    $$

* The probability of having m successes in n tries:
    ```c
    probability have_m_successes_within_n_attempts(distr *s, int n, int m);
    ```
    $$
    (i,j,c)=(\textrm{current position, difference from last success, success count})
    $$$$
    \begin{aligned}
        dp(1,1,0) &= 1\\
        dp(i+1,1,c+1) &= dp(i,j,c)\cdot pf(j)\\ 
        dp(i+1,j+1,c) &= dp(i,j,c)\cdot (1-pf(j))\\
        P_{\textrm{n choose m}}(n,m) &= \sum_{\beta=1}^{99}dp(n+1,\beta,m)
    \end{aligned}
$$

* The probability of having at least one "special success" in n tries. A special success happens with chance p given that a success has occured:
    ```c
    probability have_special_success_within_n_attempts(distr *s, int n, probability p);
    ```
    In this formula case p = 0.5.
    $$
    \begin{aligned}
        P^{\textrm{spec}}(0) &= 0\\ 
        P^{\textrm{spec}}(n) &= \sum_{j=1}^{n}P(j)(0.5+(1-0.5)P^{\textrm{spec}}(n-j))
    \end{aligned}
    $$
    or indirectly
    $$
    \begin{aligned}
        dp(1,1) &= 1\\
        dp(i+1,1) &= dp(i,j)\cdot pf(j)\cdot (1-0.5)\\ 
        dp(i+1,j+1) &= dp(i,j)\cdot (1-pf(j))\\
        P_{\textrm{spec}}(n) &= 1-\sum_{\beta=1}^{99}dp(n+1,\beta)
    \end{aligned}
    $$