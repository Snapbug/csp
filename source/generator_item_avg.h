/*
	GENERATOR_ITEM_AVG.H
	--------------------
*/
#include "generator.h"

#ifndef GENERATOR_ITEM_AVG_H_
#define GENERATOR_ITEM_AVG_H_

class CSP_generator_item_avg : public CSP_generator
{
public:
	CSP_generator_item_avg(CSP_dataset *dataset);
	virtual ~CSP_generator_item_avg() {}

	virtual void generate(uint64_t user, uint64_t *presentation_list, uint64_t number_presented);

private:
	static int average_cmp(const void *a, const void *b);
	
	typedef struct {
		double average;
		uint64_t count;
		uint64_t movie_id;
	} movie;
	movie *most_liked;

};

#endif /* GENERATOR_ITEM_AVG_H_ */

