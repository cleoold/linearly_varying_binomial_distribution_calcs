/*
    the linearly increasing probability in the
    binomial-like distribution problem

    one can flip a card. there is a probability [base_prob] to have a good one at the beginning.
    if one does not have the good one for some attempts in a row, the constant will be added
    to the existing probability (so that the chance of having the good one is increasing) until
    one finally has the good card, at which point the chance will reset to the original one.

    the console-based calculator
    a toy app that you can use with small amount of data; this is not serious

    (c) cos / cleoold in July 2019 
*/

// includes
#include <stdio.h>
#include <string.h>
#include "prob_func.h"

// common settings
#define MAX_INPUT_LEN 5

// utilities
#define boolean char
#define INVALID_N -1.0

#define CHAR_IS_EMPTY(STR) ((STR) == '\0' || (STR) == '\n')
//#define INPUT_IS_TOO_LONG(STR) !strchr((STR), '\n')
#define ISDIGIT(CH) ((CH) >= '0' && (CH) <= '9')

#define FLUSH_STDIN()                                    \
    do                                                   \
    {                                                    \
        char c;                                          \
        while ( (c = getchar()) != '\n' && c != EOF );   \
    } while (0)


#define GENERIC_READ(TYPE, FORMAT_STR, COND_CHAR, COND_RES)                 \
    TYPE read_##TYPE(void)                                                  \
    {                                                                       \
        TYPE res;                                                           \
        boolean valid;                                                      \
        char buf[MAX_INPUT_LEN+2];                                          \
        do                                                                  \
        {                                                                   \
            valid = 1;                                                      \
            printf("Your input: ");                                         \
            fgets(buf, MAX_INPUT_LEN+2, stdin);                             \
            for (char *this = buf; !CHAR_IS_EMPTY(*this); ++this)           \
                if (!(COND_CHAR)) valid = 0;                                \
                                                                            \
            boolean too_long = !strchr(buf, '\n');                          \
            if (valid == 0 || CHAR_IS_EMPTY(*buf) || too_long)              \
            {                                                               \
                valid = 0;                                                  \
                puts("Check your format; is it a number? Is it too long?"); \
                if (too_long) FLUSH_STDIN();                                \
            }                                                               \
            if (valid == 1)                                                 \
            {                                                               \
                sscanf(buf, FORMAT_STR, &res);                              \
                if (!(COND_RES))                                            \
                {                                                           \
                    valid = 0;                                              \
                    puts("That data/input doesn't make sense");             \
                }                                                           \
            }                                                               \
        } while (!valid);                                                   \
        return res;                                                         \
    }                                    


GENERIC_READ(char, "%c", 1, 1)

GENERIC_READ(int, "%d", ISDIGIT(*this), res > 0)
// cuts off contents after the second period, if any
GENERIC_READ(probability, "%lf", ISDIGIT(*this) || (*this) == '.', 
                                    res > 0.0 && res < 1.0)

// repeated dialogs
#define dialog_loading()                                                    \
    puts("        NOW CALCULATING...")
#define displayed_title()                                                   \
    puts("\n\nBinomial distribution with linearly varying probabilities tool\n")
#define displayed_help()                                                    \
    puts(   "\n  1 - compute the average waiting attempts before success\n" \
            "  2 - compute the chance of success at N attempts\n"           \
            "  3 - compute the chance of M successes at N attempts\n"       \
            "  4 - compute the chance of 'special' success at N attempts\n")  




LVBdistribution acquire_distribution(void)
{
    puts("To use the calculator, enter the information below");

    puts("Enter here the starting probability:");
    probability base = read_probability();
    puts("After how many successive failures will the chance start to increase?");
    int threshold = read_int();
    printf("What is the constant to add to the probability after %d successive failures?"
            " So that the chance will increase failure-by-failure.\n", threshold);
    probability constant = read_probability();
    LVBdistribution res = create_model(base, constant, threshold);
    printf( "\n    normal probability:               %.08lf\n"
            "    increased probability:            %.08lf\n"
            "    minimum attempts before increase: %d\n"
            "    maximum attempts to ensure:       %d\n",
            base, 
            constant, 
            threshold, 
            res.max_times);
    return res;
}


void print_average_waiting_time(LVBdistribution *s, count *distr_E) // detects any pre-calculated E
{
    dialog_loading();
    if (*distr_E == INVALID_N)
        *distr_E = have_first_success_at_n_E(s);          // writes E if not pre-calculated yet
    printf( "\n    average attempts for one success: %.08lf\n\n",
            *distr_E);
}


void print_have_success_within_attempts(LVBdistribution *s)
{
    puts("How many attempts does one make?");
    int n = read_int();
    dialog_loading();

    printf( "\n    P of having success (CDF):          %.08lf\n"
            "    P of having first success at %d-th: %.08lf\n\n",
            have_success_within_n_attempts(s, n),
            n, have_first_success_at_n(s, n));
}


void print_have_variable_successes_within_attempts(LVBdistribution *s)
{
    puts("How many attempts does one make?");
    int n = read_int();
    puts("How many successes does one want?");
    int m = read_int();
    dialog_loading();

    printf( "\n    P of having %d or more successes (CDF): %.08lf\n"
            "    P of having %d success(es)              %.08lf\n"
            "    average success count after %d-th:     %.08lf\n\n",
            // see function in prob.func.c
            m, have_m_or_more_successes_within_n_attempts(s, n, m),
            m, have_m_successes_within_n_attempts(s, n, m),
            n, have_m_successes_within_n_attempts_E(s, n));
}


void print_have_special_success_within_attempts(LVBdistribution *s, count * distr_E)
{
    puts("Given an success event has occurred, a special success will occur at a chance p:");
    probability p = read_probability();
    puts("How many attempts does one make?");
    int n = read_int();
    dialog_loading();

    printf( "\n    P of having success (CDF): %.08lf\n",
            have_special_success_within_n_attempts(s, n, p));
    if (*distr_E == INVALID_N)
        *distr_E = have_first_success_at_n_E(s);
    printf( "    average attempts for one success: %.08lf\n\n",
            //have_m_successes_within_n_attempts_E(s, n)
            *distr_E / p);
}


int main(int argc, char** argv)
{
    displayed_title();
    
    LVBdistribution my_dist = acquire_distribution();
    count distr_E = INVALID_N;
    displayed_help();
    while (1)
    {
        char op = read_char();
        switch (op)
        {
        case ('1'):
            print_average_waiting_time(&my_dist, &distr_E);
            break;
        case ('2'):
            print_have_success_within_attempts(&my_dist);
            break;
        case ('3'):
            print_have_variable_successes_within_attempts(&my_dist);
            break;
        case ('4'):
            print_have_special_success_within_attempts(&my_dist, &distr_E);
            break;
        default:
            puts("That option seems not valid.");
            break;
        }
    }
}
