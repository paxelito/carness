/** class influxspecies_protocell
 *	\brief This class contains declarations of the influxspecies_protocell class. It contains the code dealing
 *	with the inflow process in case of protocell.
 *
 *  @authors Alessandro Filisetti
 *  @version 0.0
 *
 *  Created by Alessandro Filisetti on 27/04/15.
 *  Copyright 2015 Alessandro Filisetti. All rights reserved.
 */

#ifndef INFLUXSPECIES_PROTOCELL
#define INFLUXSPECIES_PROTOCELL

#include "acs_headers.h"
#include "commonFunctions.h"
#include "influxspecies.h"

class influxspecies_protocell: public influxspecies
{
private:
	acs_double externalconc; /**< External concentration of the species */
	acs_double kin; /**< membrane permeability rate*/
	acs_double remainingConc; /** Remaining concentration (according to dt) to add or remove in the next time interval */

public:
	influxspecies_protocell(acs_longInt tmpID, acs_double tmpExtConc, acs_double tmpKin);
	acs_double getExtConc()const{return externalconc;}
	acs_double getKin()const{return kin;}
	acs_double getRemConc()const{return remainingConc;}

	void changeRemainingConc(acs_double tmpRemConc){remainingConc = tmpRemConc;}

};

#endif
