/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CCSV.CPP
 * Author          : Viveknath Thulasi
 * Description     : This is used to read and write from and to the database file
 *
 ****************************************************************************/
#include "CCSV.h"
#include "CPOI.h"
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

#define WAYPOINT_DB 1
#define POI_DB		2

//Initialising the error code to be success
CCSV::error_code_t CCSV::err_code = SUCCESS;

/**
	* Constructor for class CCSV
	* Initialising merge mode and media name by default.
	*
	* @param None
	* @return None
	*/
CCSV::CCSV()
{
	//By default unless specified, Merge is specified to avoid errors
	storage_merge_mode = MERGE;
	media_name = "database";
}

/**
	* writeData - function from which data from the database is written into the database file
	*
	* @param waypointDb the reference of the way points database.(IN)
	* @param poiDb the reference of POI database.(IN)
	* @return True of successful writing of data, false if any issue is present in POI or way point
	*/
bool CCSV::writeData(const CWpDatabase& waypointDb, const CPoiDatabase& poiDb)
{
	bool return_status = true;
	ofstream myWpOutfile;
	ofstream myPoiOutfile;
	string filename;

	filename = fetch_filename(WAYPOINT_DB);
	myWpOutfile.open(filename.c_str(),ios::out);
	if(myWpOutfile.is_open())
	{
		CWpDatabase::myWpMap_t myTemp_waypointdb;
		CWpDatabase::myWpMap_t :: iterator it;
		myTemp_waypointdb = waypointDb.getWpdatabase();
		for (it = myTemp_waypointdb.begin();it!= myTemp_waypointdb.end();++it )
		{
			myWpOutfile<<it->second.getName()<<";"<<it->second.getLatitude()<<";"<<it->second.getLongitude()<<endl;
		}
		myWpOutfile.close();
	}
	else
	{
		err_code= FILE_OPEN_ERROR;
		cout<<__FUNCTION__<<"Way point Database"<<getErrorText(err_code);
		return_status = false;
	}

	filename = fetch_filename(POI_DB);
	myPoiOutfile.open(filename.c_str(),ios::out);
	if(myPoiOutfile.is_open())
	{
		CPoiDatabase::myPoiMap_t temp_poi_db;
		CPoiDatabase::myPoiMap_t :: iterator it_poi;
		temp_poi_db = poiDb.getPoiDatabase();

		for(it_poi = temp_poi_db.begin();it_poi!= temp_poi_db.end();++it_poi)
		{
			myPoiOutfile<<it_poi->second.getPoiType()<<";"<<it_poi->second.getName()<<";"<<it_poi->second.getPoiDescription()<<";"<<it_poi->second.getLatitude()<<";"<<it_poi->second.getLongitude()<<endl;
		}
		myPoiOutfile.close();
	}
	else
	{
		err_code= FILE_OPEN_ERROR;
		cout<<__FUNCTION__<<" : POI Database"<<getErrorText(err_code);
		return_status = false;
	}

return return_status;
}

/**
	* readData - function to read the database and add or replace corresponding database
	*
	* @param waypointDb the reference of the way points database.(OUT)
	* @param poiDb the reference of POI database.(OUT)
	* @param mode - option to replace or merge the existing database(IN)
	* @return True of successful writing of data, false if any issue is present in POI or way point
	*/
bool CCSV::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode_t mode)
{
	string filename;
	string line,WpName;
	int line_no =1;
	bool ret_val = true,api_return = true;
	double latitude,longitude;

	//Parsing Waypoint file starts here . . .
	ifstream myinWpfile;
	filename = fetch_filename(WAYPOINT_DB);
	myinWpfile.open(filename.c_str(),ifstream::in);
	if(myinWpfile.is_open())
	{
		if(mode == REPLACE)
		{waypointDb.clear_WayptDatabase();}
		while(getline(myinWpfile,line))
		{
			ret_val = scanline_get_Wp_attr(line,WpName,latitude,longitude);
			if(ret_val == true)
			{
				CWaypoint obj(WpName,latitude,longitude);
				waypointDb.addWaypoint(obj);
			}
			else
			{
				cout<<__FUNCTION__<<" : Way point DB :"<<getErrorText(err_code)<<" in line no: "<<line_no<<" : "<<line<<endl;
				api_return = false;
			}
			line_no++;
		}
		myinWpfile.close();
	}
	else
	{
		err_code = FILE_OPEN_ERROR;
		cout<<__FUNCTION__<<"Waypoint Db"<<getErrorText(err_code);
		api_return = false;
	}

	string PoiName,PoiDescription;
	CPOI::t_poi Poitype;
	line_no = 1;//Reset line no for POI Db

	//Parsing POI Data base starts here. .
	ifstream myinPoifile;
	filename = 	fetch_filename(POI_DB);
	myinPoifile.open(filename.c_str(),ifstream::in);
	if(myinPoifile.is_open())
	{
		if(mode == REPLACE)
		{poiDb.clear_PoiDatabase();}
		while(getline(myinPoifile,line))
		{
			if(line.empty())
			{
				err_code = LINE_EMPTY;
				cout<<__FUNCTION__<<" : Poi DB :"<<getErrorText(err_code)<<" in line no: "<<line_no<<" : "<<line<<endl;
				api_return = false;
			}
			else
			{
				ret_val = scanline_get_Poi_attr(line,Poitype,PoiDescription,PoiName,latitude,longitude);
				if(ret_val == true)
				{
					CPOI poi_obj(Poitype,PoiName,PoiDescription,latitude,longitude);
					poiDb.addPoi(poi_obj);
				}
				else
				{
					cout<<__FUNCTION__<<" : Poi DB :"<<getErrorText(err_code)<<" in line no: "<<line_no<<" : "<<line<<endl;
					api_return = false;
				}
			}

			line_no++;
		}
		myinPoifile.close();
	}
	else
	{
		err_code = FILE_OPEN_ERROR;
		cout<<__FUNCTION__<<"POI Database"<<getErrorText(err_code);
		api_return = false;
	}
return api_return;
}


/*
 * setMediaName function to set the file name for reading and writing
 * @param  : String name - database name from user (IN)
 * @return : None
 * */
void CCSV::setMediaName(string name)
{
	this->media_name = name;
}

/**
	* scanline_get_Wp_attr - function to scan the waypoint database line and fetch the attributes
	*
	* @param line line of data in Way point db.(IN)
	* @param WpName - Way point name.(OUT)
	* @param latitude - Way point latitude.(OUT)
	* @param longitude - Way point longitude.(OUT)
	* @return True on success, false on error condition
	*/
bool CCSV::scanline_get_Wp_attr(string line,string& WpName,double& latitude,double& longitude)
{
	std::string buffer;
	int pos=0,current_pos=0;
	char delimiter;
	bool return_val = true;
	return_val = check_delimiter(WAYPOINT_DB,line,delimiter);
	if(return_val == false)	{return return_val;}

	//Fetch POI name
	return_val = fetch_field(line,WpName,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}

	//fetch latitude
	return_val = fetch_field(line,buffer,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}
	return_val = buffer2double(buffer,latitude);
	if(return_val == false){return return_val;}

	//fetch longitude
	return_val = fetch_field(line,buffer,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}
	return_val = buffer2double(buffer,longitude);
	if(return_val == false){return return_val;}

	return return_val;
}

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
bool CCSV::scanline_get_Poi_attr(string line,CPOI::t_poi& Poi_type,string& Poi_description,string& PoiName,double& latitude,double& longitude)
{
	std::string buffer;
	int pos=0,current_pos=0;
	bool return_val = true;
	char delimiter;

	return_val = check_delimiter(POI_DB,line,delimiter);
	if(return_val == false){return return_val;}

	// Fetch poitype
	return_val = fetch_field(line,buffer,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}
	return_val =  CCSV::setPoiType(buffer,Poi_type);
	if(return_val == false){return return_val;}

	//Fetch POI name
	return_val = fetch_field(line,PoiName,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}

	//fetch POI description
	return_val = fetch_field(line,Poi_description,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}

	//fetch latitude
	return_val = fetch_field(line,buffer,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}
	return_val = buffer2double(buffer,latitude);
	if(return_val == false){return return_val;}

	//fetch longitude
	return_val = fetch_field(line,buffer,delimiter,current_pos,pos);
	if(return_val == false){return return_val;}
	return_val = buffer2double(buffer,longitude);
	if(return_val == false){return return_val;}

	//if it comes until here, parsing success
	return return_val;
}

/*
 * function to set the POI from the description read in txt file
 * @param : poitype - input string fetched from db file
 * @param : poi_type - return the enum value corresponding to description
 * @return: true on success false on error condition
 * */
bool CCSV::setPoiType(string poitype,CPOI::t_poi &poi_type){

	if(poitype == "RESTAURANT" )
		poi_type =CPOI::RESTAURANT;
	else if(poitype == "TOURISTIC")
		poi_type =CPOI::TOURISTIC;
	else if(poitype == "GASSTATION")
		poi_type =CPOI::GASSTATION;
	else if(poitype == "UNIVERSITY")
		poi_type =CPOI::UNIVERSITY;
	else if(poitype == "DEFAULT")
		poi_type =CPOI::DEFAULT;
	else
	{
		cout<<__FUNCTION__<<"Error: Setting enum values\n";
		err_code = BAD_PARAM;
		return false;
	}

return true;
}

CCSV::~CCSV()
{

}
/*
 * function to convert string to double value and also look for error checks
 * @buffer : input string on which check needs to be made (IN)
 * @latitude_or_longitude: reference for returning values (OUT)
 * @return : true on success, false on error condtion
 * */
bool CCSV::buffer2double(string& buffer, double& latitude_or_longitude)
{

	stringstream ss(buffer);
	ss>>latitude_or_longitude;

	if(ss.fail())
	{
		err_code = BAD_PARAM;
		return false;
	}
	return true;
}
/*
 * function to check the correctness of line and find the delimiter to be searched
 * @param line_type variable defining Waypoint db or POI database(IN).
 * @param line - Line to check for delimiter (IN).
 * @param delimiter - decided delimiter , or ; to be used for find (OUT).
 * */
bool CCSV::check_delimiter(int line_type,string line,char & delimiter)
{
	//line_type = 1 - > reading a Waypoint line
	//line_type = 2 - > reading a Poi line
	//Check no of comas or semi colen in a line string

	unsigned int i, coma_count=0,semicolen_count=0,max_delimiter_no,delimiter_count;

	if(line.empty())
	{
		err_code = LINE_EMPTY;
		return false;
	}
	for(i=0;i<line.length();i++)
	{
		if(line[i]==';')
		{semicolen_count +=1;}

		if(line[i]== ',')
		{coma_count +=1;}
	}

	// Set delimiter value
	if(coma_count>0)
	{
		delimiter = ',';
		delimiter_count = coma_count;
	}
	else if(semicolen_count>0)
	{
		delimiter = ';';
		delimiter_count = semicolen_count;
	}
	else
	{
		err_code = NO_DELIMITER;
		return false;
	}

	//Set max no of Delimiter value
	//	1 ->A WayPoint can have 2 delimiter : Konzerthaus;19.0909;26.658
	//	2 ->A POI line can have 4 delimiter : RESTAURANT;LuisenPlatz;center for Darmstadt;83.471;23.6589
	if(line_type == 1)
	{
		max_delimiter_no = 2;
	}
	else
	{
		max_delimiter_no = 4;
	}

	if(delimiter_count < max_delimiter_no)
	{
		err_code = TOO_FEW_FIELDS;
		return false;
	}
	else if(delimiter_count > max_delimiter_no)
	{
		err_code = TOO_MANY_DELIMITERS;
		return false;
	}
	else
	{
		return true;
	}
}
/**
 * function that returns the error text happening in whole of read and write operations
 * @param : temp_err_code - current error code that is set
 * @return : error text*/
string CCSV::getErrorText(error_code_t  temp_err_code)
{
	string error_txt;
	error_txt = error_code_description[temp_err_code];
	err_code = SUCCESS;// Resetting error code after once message is given
	return error_txt;
}

/**
 * function to modify and get the file name from media name for writing and reading
 * @param filetype - Based on wp or db the type changes
 * @return filename
 * */
string CCSV:: fetch_filename(int filetype)
{
	std::string filename =  media_name;
	if(filetype == WAYPOINT_DB)
	{
		filename.append("-wp.txt");
	}
	else if(filetype == POI_DB)
	{
		filename.append("-poi.txt");
	}

	return filename;
}

/*
 * function to fetch field in a line.
 * @param current_pos gives the current position of parsing in line(IN).
 * @param buffer - value to get as feedback to calling function(OUT)
 * @param line - Line to check for delimiter (IN).
 * @param delimiter - decided delimiter , or ; to be used for find (IN).
 * */
bool CCSV::fetch_field(string line,string &buffer ,char delimiter,int &current_pos,int &pos )
{

	buffer.clear();
	pos = line.find(delimiter,current_pos);
	buffer = line.substr(current_pos,pos-current_pos);
	if(buffer.empty())
	{
		err_code = FIELD_EMPTY;
		return false;
	}
	current_pos = pos+1;
	return true;
}
