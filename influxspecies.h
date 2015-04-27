/** class influxspecies
 *	\brief This class contains declarations of the influxspecies class
 *
 *  @authors Alessandro Filisetti
 *  @version 0.0
 *
 *  Created by Alessandro Filisetti on 27/04/15.
 *  Copyright 2015 Alessandro Filisetti. All rights reserved.
 */

#ifndef INFLUXSPECIES
#define INFLUXSPECIES

#include "acs_headers.h"
#include "commonFunctions.h"

class influxspecies
{
protected:
	acs_longInt id; /**< species id */

public:
	influxspecies(acs_longInt tmpID);
	acs_longInt getID()const{return id;}
};

#endif
