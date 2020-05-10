/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.H
* Author          : Viveknath Thulasi
* Description     : include file for CGPSSensor operating to get current location of user
*
*
****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H
#include "CWaypoint.h"
class CGPSSensor {
public:

    CGPSSensor();

/**
 * Gets the current position of the input from user
 * @param	None
 * @returnvalue	returns the current position
 * */
    CWaypoint getCurrentPosition();
};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
