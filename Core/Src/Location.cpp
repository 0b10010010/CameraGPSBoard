/*
 * Location.cpp
 *
 *  Created on: Feb 28, 2020
 *      Author: alexk
 */

#include <Location.h>
#include <string.h>

Location::Location()
{
	zero();
}

void Location::zero(void)
{
    memset(this, 0, sizeof(*this));
}
