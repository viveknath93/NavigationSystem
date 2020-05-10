/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.H
 * Author          : Viveknath Thulasi
 * Description     : Include file for CPOI class
 *
 *
 ****************************************************************************/
//Own Include Files
#ifndef CPOI_H
#define CPOI_H

#include "CWaypoint.h"

#ifndef ENUM_t_poi
#define ENUM_t_poi
enum t_poi
{
	RESTAURANT, TOURISTIC, GASSTATION, UNIVERSITY, DEFAULT
};
#endif

void print_type(t_poi & mtype_value);
class CPOI: public CWaypoint
{
private:
	t_poi m_type;
	std::string m_description;
public:

	void print();

	CPOI(t_poi type = DEFAULT, std::string name ="Default Location" , std::string description = "Default Description", double latitude = 0.0 ,
			double longitude = 0.0);

	void getAllDataByReference(std::string& name, double & latitude,
			double& longitude, t_poi& type, std::string& description);

};
/********************
 **  CLASS END
 *********************/
#endif /* CPOI_H */
