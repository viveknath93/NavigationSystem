 /***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CCSV.CPP
 * Author          : Viveknath Thulasi
 * Description     : This is used to read and write from and to the database file
 *
 ****************************************************************************/
#ifndef CCSV_H_
#define CCSV_H_

#include "CPersistentStorage.h"


const static string error_code_description[] = {
		"Success",
		"Too few fields",
		"Too many fields",
		"No delimiter found",
		"Bad parameters",
		"Problem opening the file",
		"Empty line",
		"field missing"
};

class CCSV : public CPersistentStorage
{

public:

/**
* Constructor for class CCSV
* Initialising merge mode and media name by default.
*
* @param None
* @return None
*/
	CCSV();
	virtual ~CCSV();

/**
* writeData - function from which data from the database is written into the database file
*
* @param waypointDb the reference of the way points database.(IN)
* @param poiDb the reference of POI database.(IN)
* @return True of successful writing of data, false if any issue is present in POI or way point
*/
	bool writeData (const CWpDatabase& waypointDb,const CPoiDatabase& poiDb);

/**
* readData - function to read the database and add or replace corresponding database
*
* @param waypointDb the reference of the way points database.(OUT)
* @param poiDb the reference of POI database.(OUT)
* @param mode - option to replace or merge the existing database(IN)
* @return True of successful writing of data, false if any issue is present in POI or way point
*/
	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode_t mode);

/*
 * setMediaName function to set the file name for reading and writing
 * @param  : String name - database name from user (IN)
 * @return : None
 * */
	void setMediaName(std::string name);

/**
 * function to modify and get the file name from media name for writing and reading
 * @param filetype - Based on way point or database the type changes
 * @return filename of waypoint of database
 * */
	std::string fetch_filename(int filetype);

	enum error_codes
	{
		SUCCESS,
		TOO_FEW_FIELDS,
		TOO_MANY_DELIMITERS,
		NO_DELIMITER,
		BAD_PARAM,
		FILE_OPEN_ERROR,
		LINE_EMPTY,
		FIELD_EMPTY
	};
	typedef enum error_codes error_code_t;
	static error_code_t err_code;
	MergeMode_t storage_merge_mode;
private:

	std::string media_name;
/*
 * function to convert string to double value and also look for error checks
 * @buffer : input string on which check needs to be made (IN)
 * @latitude_or_longitude: reference for returning values (OUT)
 * @return : true on success, false on error condtion
 * */
	static bool buffer2double(string &buffer,double &latitude_or_longitude);

/**
 * function that returns the error text happening in whole of read and write operations
 * @param : temp_err_code - current error code that is set
 * @return : error text
 * */
	static string getErrorText(error_code_t err_code);
/*
 * function to set the POI from the description read in txt file
 * @param : poitype - input string fetched from db file
 * @param : poi_type - return the enum value corresponding to description
 * @return: true on success false on error condition
 * */
	static bool setPoiType(string poitype,CPOI::t_poi& poi_type);

/**
* scanline_get_Wp_attr - function to scan the waypoint database line and fetch the attributes
*
* @param line line of data in Way point db.(IN)
* @param WpName - Way point name.(OUT)
* @param latitude - Way point latitude.(OUT)
* @param longitude - Way point longitude.(OUT)
* @return True on success, false on error condition
*/
	static bool scanline_get_Wp_attr(string line,string& WpName,double& latitude,double& longitude);

/**
* scanline_get_Poi_attr - function to scan the poi database line and fetch the attributes
*
* @param line line of data in Way point db.(IN)
* @param POI - Way point name.(OUT)
* @param latitude - Way point latitude.(OUT)
* @param longitude - Way point longitude.(OUT)
* @param Poi_type - Type of POI(OUT)
* @param Poi_description - description of POI(OUT)
* @return True on success, false on error condition
*/
	static bool scanline_get_Poi_attr(string line,CPOI::t_poi& Poi_type,string& Poi_description,string& PoiName,double& latitude,double& longitude);
/*
 * function to check the correctness of line and find the delimiter to be searched
 * @param line_type variable defining Waypoint db or POI database(IN).
 * @param line - Line to check for delimiter (IN).
 * @param delimiter - decided delimiter , or ; to be used for find (OUT).
 * */
	static bool check_delimiter(int line_type,string line,char & delimiter);

/*
 * function to fetch field in a line.
 * @param current_pos gives the current position of parsing in line(IN).
 * @param buffer - value to get as feedback to calling function(OUT)
 * @param line - Line to check for delimiter (IN).
 * @param delimiter - decided delimiter , or ; to be used for find (IN).
 * */
	static bool fetch_field(string line,string &buffer ,char delimiter,int &current_pos,int &pos);
};

#endif /* CCSV_H_ */
