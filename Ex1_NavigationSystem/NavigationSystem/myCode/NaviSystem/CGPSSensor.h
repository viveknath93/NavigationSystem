/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.H
* Author          : Viveknath Thulasi
* Description     : include file for CGPSSensor operating to get current location of user
*
*
****************************************************************************/
#include "CWaypoint.h"
#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

class CGPSSensor {
public:
    CGPSSensor();
    CWaypoint getCurrentPosition();
};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
