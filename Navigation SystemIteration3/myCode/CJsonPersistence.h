/*
 * CJsonPersistence.h
 *
 *  Created on: 22 Dec 2018
 *      Author: Viveknath Thulasi
 */

#ifndef CJSONPERSISTENCE_H_
#define CJSONPERSISTENCE_H_

#include "CPersistentStorage.h"

enum error_codes
	{
		SUCCESS,
		TOO_FEW_FIELDS,
		TOO_MANY_FIELDS,
		BAD_PARAM,
		FIELD_EMPTY,
		INVALID_DB_TYPE,
		EXPECTED_BEGIN_OBJECT,
		EXPECTED_STRING,
		EXPECTED_NAME_SEPERATOR,
		EXPECTED_ARRAY_BEGIN,
		EXPECTED_VALUE,
		UNEXPECTED_TOKEN,
		FIRST_TOKEN_NOT_PARSED,
		END_TOKEN_NOT_PARSED,
		INVALID_ATTR_NAME,
	};
enum eparser_states {
	wait_for_object_begin,
	wait_for_object_end,
	wait_for_db_name,
	wait_for_db_begin,
	wait_for_attr_name,
	wait_for_attr_value,
	wait_for_name_seperator,
	wait_for_value_seperator,
	wait_for_array_begin,
	wait_for_array_end
};
const static string error_code_JSON_description[] = {
		"Success",
		"Too few fields",
		"Too many fields",
		"Bad parameters",
		"field missing",
		"Invalid DB Type",
		"Expected '{' begin object",
		"Expected string",
		"EXpected a ':' name seperator",
		"Expected a '['array begin ",
		"Expected value - string or number",
		"Expected ',' or ']' or '}'",
		"First Token not parsed",
		"End Token missing",
		"Invalid attribute name for this DB"
};
class CJsonPersistence : public CPersistentStorage
{
public:
	CJsonPersistence();


	/**
	* Set the name of the media to be used for persistent storage.
	* The exact interpretation of the name depends on the implementation
	* of the component.
	*
	* @param name the media to be used
	*/
	void setMediaName(std::string name);
	/**
	* Write the data to the persistent storage.
	*
	* @param waypointDb the data base with way points
	* @param poiDb the database with points of interest
	* @return true if the data could be saved successfully
	*/
	bool writeData (const CWpDatabase& waypointDb,const CPoiDatabase& poiDb);

	/**
	* Fill the databases with the data from persistent storage. If
	* merge mode is MERGE, the content in the persistent storage
	* will be merged with any content already existing in the data
	* bases. If merge mode is REPLACE, already existing content
	* will be removed before inserting the content from the persistent
	* storage.
	*
	* @param waypointDb the the data base with way points
	* @param poiDb the database with points of interest
	* @param mode the merge mode
	* @return true if the data could be read successfully
	*/
	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode mode);
private:
	std::string media_name;

	/*
	 * Inbuilt private funtion to check the count of attributes corresponding to a particular database type
	 * @param dbtype database type
	 * @param referecne to count no of attributes in particular databse type
	 * @returnvalue : EXCEEDED_LIMIT 0 if count exceeds limit
	 * 				  UNDER_LIMIT 1 if count is under limit
	 * 				  LIMIT_MATCH 2 if limit matches
	 **/
	int underlimits(string &dbtype,int &count);

	/*
	 * function to return the error code corresponding to enum value
	 * @param error_code error code types of enum
	 * @returnvalue error text corresponding to the error code
	 * */
	string getErrorText(enum error_codes  temp_err_code);

	/*
	 * function to check the validity of attribute name
	 * @param attr_name attribute name extracted from file
	 * @param db_type database type
	 * @returnvalue none
	 * */
	void checkValidAttributeName(string attr_name, string db_type);
};

#endif /* CJSONPERSISTENCE_H_ */
