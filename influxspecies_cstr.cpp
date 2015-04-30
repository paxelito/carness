/** class influxspecies_cstr
 *	\brief This class contains implementation of the influxspecies_cstr class
 *
 *  @authors Alessandro Filisetti
 *  @version 0.0
 *
 *  Created by Alessandro Filisetti on 27/04/15.
 *  Copyright 2015 Alessandro Filisetti. All rights reserved.
 */

#include "influxspecies.h"
#include "influxspecies_cstr.h"

/** \brief Default constructor
*/
influxspecies_cstr::influxspecies_cstr(acs_longInt tmpID, acs_double tmpProb2BeSelected):influxspecies(tmpID)
{
	id = tmpID;
	prob2BeSelected = tmpProb2BeSelected;
}

void influxspecies_cstr::print_cstr_inflow()
{
	cout << "\t\t|- Inflow Species [" << id << "] Prob to be selected: " << prob2BeSelected << endl;
}

