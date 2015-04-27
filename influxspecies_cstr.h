/** class influxspecies_cstr
 *	\brief This class contains declarations of the influxspecies_cstr class
 *
 *  @authors Alessandro Filisetti
 *  @version 0.0
 *
 *  Created by Alessandro Filisetti on 27/04/15.
 *  Copyright 2015 Alessandro Filisetti. All rights reserved.
 */

#ifndef INFLUXSPECIES_CSTR
#define INFLUXSPECIES_CSTR

#include "acs_headers.h"
#include "commonFunctions.h"
#include "influxspecies.h"

class influxspecies_cstr: public influxspecies
{
private:
	acs_double prob2BeSelected; /**< External concentration of the species */
	acs_double remainingConc; /** Remaining concentration (according to dt) to add or remove in the next time interval */

public:
	influxspecies_cstr(acs_longInt tmpID, acs_double tmpProb2BeSelected);
	acs_double getprob2beselected()const{return prob2BeSelected;}

	void changeRemainingConc(acs_double tmpRemConc){remainingConc = tmpRemConc;}
	void print_cstr_inflow();

};



#endif
