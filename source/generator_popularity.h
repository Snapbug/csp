/*
	GENERATOR_POPULARITY.H
	----------------------
*/
#include "generator.h"

#ifndef GENERATOR_POPULARITY_H_
#define GENERATOR_POPULARITY_H_

class CSP_generator_popularity : public CSP_generator
{
public:
	CSP_generator_popularity(CSP_dataset *dataset);
	virtual ~CSP_generator_popularity() {}

	virtual uint64_t next_movie(uint64_t user, uint64_t which_one, uint64_t *key);

private:
	static int number_ratings_cmp(const void *a, const void *b);
	
	typedef struct {
		uint64_t number_ratings;
		uint64_t movie_id;
	} movie;
	movie *most_popular;

};

#endif /* GENERATOR_POPULARITY_H_ */

