/*
	GENERATOR_FACTORY.H
	-------------------
*/

#include "generator.h"
#include "generator_distance.h"
#include "generator_entropy.h"
#include "generator_greedy_cheat.h"
#include "generator_item_avg.h"
#include "generator_naive_bayes.h"
#include "generator_other_greedy.h"
#include "generator_other_greedy_pers.h"
#include "generator_popularity.h"
#include "generator_predictor.h"
#include "generator_random.h"
#include "generator_tree.h"

#ifndef GENERATOR_FACTORY_H_
#define GENERATOR_FACTORY_H_

class CSP_generator_factory
{
public:
	enum {
		BAYESIAN,
		DISTANCE,
		ENTROPY,
		GREEDY_CHEAT,
		ITEM_AVERAGE,
		NONE,
		OTHER_GREEDY,
		OTHER_GREEDY_PERS,
		POPULARITY,
		PREDICTOR,
		RANDOM,
		TREE
	};
};

#endif /* GENERATOR_FACTORY_H_ */
