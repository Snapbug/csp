/*
	GENERATOR_NAIVE_BAYES.C
	-----------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "generator_naive_bayes.h"

/*
	CSP_GENERATOR_NAIVE_BAYES::CSP_GENERATOR_NAIVE_BAYES()
	------------------------------------------------------
*/
CSP_generator_naive_bayes::CSP_generator_naive_bayes(CSP_dataset *dataset, uint32_t *coraters) : CSP_generator_entropy(dataset), coraters(coraters)
{
	if (!dataset->loaded_extra)
		exit(puts("Need to load data sorted by movie to use Naive Bayes"));
	
	most_probable = new movie[dataset->number_items];
}

/*
	CSP_GENERATOR_NAIVE_BAYES::NUMBER_TIMES_CMP()
	---------------------------------------------
*/
int CSP_generator_naive_bayes::number_times_cmp(const void *a, const void *b)
{
	movie *x = (movie *)a;
	movie *y = (movie *)b;
	
	return (x->count < y->count) - (x->count > y->count);
}

/*
	CSP_GENERATOR_NAIVE_BAYES::PROBABILITY_CMP()
	--------------------------------------------
*/
int CSP_generator_naive_bayes::probability_cmp(const void *a, const void *b)
{
	movie *x = (movie *)a;
	movie *y = (movie *)b;
	double prob_x = x->top / (x->top + x->bot);
	double prob_y = y->top / (y->top + y->bot);
	
#ifdef ASC	
	return (prob_x > prob_y) - (prob_x < prob_y);
#else
	return (prob_x < prob_y) - (prob_x > prob_y);
#endif
}

/*
	CSP_GENERATOR_NAIVE_BAYES::CALCULATE_PROBABILITY()
	--------------------------------------------------
*/
double CSP_generator_naive_bayes::calculate_probability(uint64_t movie, uint64_t other, uint64_t *key)
{
	uint64_t count, other_count;
	
	dataset->ratings_for_movie(movie, &count);
	dataset->ratings_for_movie(other, &other_count);
	
	if (key)
		return (1.0 * coraters[tri_offset(MIN(movie, other), MAX(movie, other), dataset->number_items)] + 1.0) / (count + 1.0);
	else
		return (1.0 * other_count - coraters[tri_offset(MIN(movie, other), MAX(movie, other), dataset->number_items)] + 1.0) / (1.0 + dataset->number_users - count);
}

/*
	CSP_GENERATOR_NAIVE_BAYES::NEXT_MOVIE()
	---------------------------------------
*/
uint64_t CSP_generator_naive_bayes::next_movie(uint64_t user, uint64_t which_one, uint64_t *key)
{
	UNUSED(user);
	uint64_t i;
	int64_t index;
	double probability;
	
	if (which_one == 0)
	{
		for (i = 0; i < dataset->number_items; i++)
		{
			dataset->ratings_for_movie(i, &most_probable[i].count);
			most_probable[i].movie_id = i;
			most_probable[i].top = 1e300;
			most_probable[i].bot = 1e300;
		}
		qsort(most_probable, dataset->number_items, sizeof(*most_probable), CSP_generator_naive_bayes::number_times_cmp);
	}
	else
	{
		/*
			For each remaining item, need to update the probabilities we've seen them.
		*/
		#pragma omp parallel for private(probability, i)
		for (index = (int64_t)which_one; index < (int64_t)dataset->number_items; index++)
		{
			i = index;
			probability = calculate_probability(most_probable[i].movie_id, most_probable[which_one - 1].movie_id, key);
			most_probable[i].top *= probability;
			most_probable[i].bot *= 1 - probability;
		}
		qsort(most_probable + which_one, dataset->number_items - which_one, sizeof(*most_probable), CSP_generator_naive_bayes::probability_cmp);
	}
	
	return most_probable[which_one].movie_id;
}
