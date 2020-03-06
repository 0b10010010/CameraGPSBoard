/*
 * Location.h
 *
 *  Created on: Feb 28, 2020
 *      Author: alexk
 */

#ifndef INC_LOCATION_H_
#define INC_LOCATION_H_

#include <stdint.h>

class Location
{
public:
	int32_t alt;
	int32_t lat;
	int32_t lon;
	// Constructor
	Location();

    void zero(void);
private:
    // scaling factor from 1e-7 degrees to meters at equator
    // == 1.0e-7 * DEG_TO_RAD * RADIUS_OF_EARTH
    static constexpr float LOCATION_SCALING_FACTOR = 0.011131884502145034f;
    // inverse of LOCATION_SCALING_FACTOR
    static constexpr float LOCATION_SCALING_FACTOR_INV = 89.83204953368922f;
};



#endif /* INC_LOCATION_H_ */
