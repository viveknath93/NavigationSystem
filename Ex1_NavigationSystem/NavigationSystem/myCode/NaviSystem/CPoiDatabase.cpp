/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOIDATABASE.CPP
 * Author          : Viveknath Thulasi
 * Description     : file contains the manipulating functions with Database of POIs
 *
 *
 ****************************************************************************/

//System Include Files
#include <iostream>
//Own Include Files
#include "CPoiDatabase.h"
#include "CPOI.h"

using namespace std;
//Method Implementations

/*
 * Constructor of CPoiDatabase*/
CPoiDatabase::CPoiDatabase()
{
	m_noPoi = 0;

}

/*
 * function to add the POIs to the generic database
 * @param	t_poi type type of POI	(IN)
 * @param	string name name of POI	(IN)
 * @param	string description of POI	(IN)
 * @param	double latitude		(IN)
 * @param	double longitude	(IN)
 * @returnvalue void */
void CPoiDatabase::addPoi(t_poi type, string name, string description,double latitude, double longitude)
{
	if(m_noPoi<10)
	{
		CPOI temp_cpoi_obj(type, name, description, latitude, longitude);
		m_POI[m_noPoi] = temp_cpoi_obj;
		m_noPoi++;
	}
	else
	{
		cout<<"\nERROR in "<<__FUNCTION__<<" : Only 10 POIs can be added to database";
	}
}

/*
 * Function gets the pointer to the POI of the input POI name
 * @param string name	(IN)
 * @returnvalue	CPOI* pointer to location of POI in database
 * */
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	string fetch_name;
	double latitude, longitude;
	t_poi type;
	string description;
	CPOI* ptemp_POI = NULL;
	for (int i = 0; i < m_noPoi; i++)
	{
		m_POI[i].getAllDataByReference(fetch_name, latitude, longitude, type,description);
		if (fetch_name == name)
		{
			ptemp_POI = &m_POI[i];
		}
	}

	// if NULL pointer is returned, implies that no data of input string "name" is present
	return ptemp_POI;
}
