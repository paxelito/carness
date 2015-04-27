/** class influxspecies_protocell
 *	\brief This class contains implementation of the influxspecies_protocell class
 *
 *  @authors Alessandro Filisetti
 *  @version 0.0
 *
 *  Created by Alessandro Filisetti on 27/04/15.
 *  Copyright 2015 Alessandro Filisetti. All rights reserved.
 */

#include "influxspecies.h"
#include "influxspecies_protocell.h"

/** \brief Default constructor
*/
influxspecies_protocell::influxspecies_protocell(acs_longInt tmpID, acs_double tmpExtConc, acs_double tmpKin):influxspecies(tmpID)
{
	id = tmpID;
	externalconc = tmpExtConc;
	kin = tmpKin;
	remainingConc = 0;
}
