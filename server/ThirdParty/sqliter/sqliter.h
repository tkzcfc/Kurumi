//Copyright 2015 Nathan Bossett

#pragma once

//user preferences
#define DB_DEFAULT_TIMEOUT_MILLISECONDS (5000)

//\user preferences

#include <string>
#include <sstream> //necessary only for a workaround to std::to_string which an older version of G++ doesn't support
#include <vector>
#include <fstream>

#include <cstdio>

#include "sqlite3.h"

enum dbresulttype {
	successdb =0,//execution is complete, successfully.  In a query, there are no more rows of results.
	rowresultdb,//not an database error per se.  an indication that a row of results is available and more MAY be
	typesdifferentdberror, //nonfatal if you're prepared to deal with it
	compilesqldberror,
	binddberror,
	busydberror,
	resultcountmismatchdberror,//can be silenced and reported as successdb
	resulttypemismatchdberror,//can be silenced and reported as successdb
	otherdberror
};

enum dbvaltype {//matches SQLITE SQLITE_INTEGER, etc.
	intdbval = 1,
	floatdbval = 2,
	strdbval = 3,
	blobdbval = 4,
	nulldbval = 5
};

typedef sqlite3_int64 sqliter_int64;

typedef std::vector<unsigned char> unsignedcharvector;

typedef std::vector<dbvaltype> dbvaltypevector;

//note: using something like a union would save memory, but this way we can guarantee
//	client access to any element is safe even if meaningless (such as "" for a string when
//	the actual type and value are NULL)
class cdbval {
public:
	dbvaltype valtype;
	sqliter_int64 ival;
	double fval;
	std::string sval;
	unsignedcharvector blob;
};

typedef std::vector<cdbval> dbvals;
typedef std::vector<dbvals> dbvalsvector;

class cdbparameter{
public:
	std::string name;
	cdbval val;
};

typedef std::vector<cdbparameter> dbparameters;

class csqliteroptions {
public:
	csqliteroptions (void);
	friend class csqliter;
	void setvaltypemismatchcausesfailure(bool mismatchisfailure);//if an individual field being of a different type than requested is a fatal error
	void setnullisavaltypemismatch(bool nullisamismatch); //for purposes of val type mismatches on SELECT's, if you specify an Int (or TEXT/etc.) and get a null back is that a type mismatch?
	void setvalcountmismatchcausesfailure(bool mismatchisfailure);//if the number of result fields returned in a row not matching the expected number is a fatal error. Normally should be true except on "*" calls which should be unusual
protected:
	bool valtypemismatchcausesfailure;
	bool nullisavaltypemismatch; // For purposes of ValTypeMismatchCausesFailure, if the nominal type is Int (or TEXT, etc.) is Null a type mismatch?
	bool valcountmismatchcausesfailure;
};

class csqliter
{
public:
	csqliter(void);
	~csqliter(void);

/* Database Level Functions/members */
	dbresulttype openexistingdb(std::string &fullpath);
	dbresulttype openexistingdb(const char *fullpath);
	dbresulttype createdb(std::string &fullpath);
	dbresulttype createdb(const char *fullpath);
	dbresulttype closedb();
	dbresulttype removedatabase(const char *fullpath);
	dbresulttype removedatabase(std::string &fullpath);

	sqlite3 *getdbhandle();
	void setdbhandle(sqlite3 *dbhandle);

	int startlog(std::string &fullpath);
	int startlog(const char *fullpath);
	void stoplog();

	csqliteroptions options;
/* End Database Level Functions*/

/* Statement Level */
	//void resetstatement();
	void setsql(std::string &sql);
	void setsql(const char *sql);

	void bindstr(std::string &name, std::string &arg);
	void bindstr(const char *name, std::string &arg);
	void bindstr(const char *name, const char *arg);
	void bindstr(std::string &name, const char *arg);

	void bindint(std::string &name, sqliter_int64);
	void bindint(const char *name, sqliter_int64 arg);

	void bindfloat(std::string &name, double arg);
	void bindfloat(const char *name, double arg);

	void bindblob(std::string &name, unsignedcharvector &arg);
	void bindblob(const char *name, unsignedcharvector &arg);

	void bindnull(std::string &name);
	void bindnull(const char *name);	

	void pushvaltypeout(dbvaltype valtype);
	void pushvaltypesout(dbvaltype valtype);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7, dbvaltype typ8);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7, dbvaltype typ8, dbvaltype typ9);
	void pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7, dbvaltype typ8, dbvaltype typ9, dbvaltype typ10);

	dbresulttype runstep();//one step (which, if returning results, will return one row)	
	void closestatement();//signal that the current use of an incomplete statement is finished.
	//	most significant intended use: calling it if you're only interested in one row of a potentially multi-row result and therefore haven't seen successdb from the runstep function, only rowresultdb 

	dbresulttype runsinglestepstatement(int &numresultrowsreturned);//returns either 0 or 1 result rows. more than 1 being present results in an error being returned
	dbresulttype runsinglestepstatement();//if you know it returns zero rows, skip creating/passing a value to explain that

/* End Statement Level Functions */

	dbvals rowdata;
	int lastinsertrowid;

	int runinternaltests();//END USERS SHOULD NEVER HAVE OCCASION TO CALL THIS EXCEPT DURING DEVELOPMENT/DEBUGGING

private:
	dbresulttype openorcreate(std::string &fullpath, bool create);

	dbresulttype compilesql();
	dbresulttype compilestatement();
	dbresulttype stepstatement();
	int finalizestatement();
	int bindparameter(cdbparameter &param);

	inline void log(std::string &str);
	inline void log(const char *str);
	//inline void log(std::string &str, int sqliter_errorcode);
	//inline void log(const char *str, int sqliter_errorcode);
	inline void log(const char *str, int sqliter_errorcode, int sqlite_errorcode);
	inline void log(std::string &str, int sqliter_errorcode, int sqlite_errorcode);

	sqlite3 *db;

	std::ofstream logfile;
	int logdepth;

	/*active statement members */
	sqlite3_stmt *litestmnt;
	bool statementdirty;

	std::string stmntsql;
	dbparameters valsin;
	dbvaltypevector valtypesout;
	bool valcountandtypesmatch;
	dbvalsvector valsout;
	/* end active statement members */
};

void geterrorname(int code, std::string &str);


//INTERNAL USE, THESE ARE NOT RETURNED BY THE sqLITER LIBRARY
//THEY ARE USED IN LOG FILES AND SUCH FOR ERROR TRACKING INSIDE THE LIBRARY
//the names and values are dependent on the particular implementation at the time
//and so may change from version to version
#define SQLITER_ERROR_NONE 0
#define SQLITER_ERROR_OTHER 1

#define SQLITER_ERROR_CREATEDB_FAILEDOPEN 101

#define SQLITER_ERROR_OPENORCREATE_FAILEDSQLITE3OPEN 201
#define SQLITER_ERROR_OPENORCREATE_FAILEDSQLITE3SETBUSYTIMEOUT 201

#define SQLITER_ERROR_REMOVEDB_FAILEDSTDREMOVE 301

#define SQLITER_ERROR_BIND_OBTAININDEX 400
#define SQLITER_ERROR_BIND_INT64 401
#define SQLITER_ERROR_BIND_DOUBLE 402
#define SQLITER_ERROR_BIND_TEXT 403
#define SQLITER_ERROR_BIND_BLOB 404
#define SQLITER_ERROR_BIND_NULL 403
#define SQLITER_ERROR_BIND_BADTYPE 404

#define SQLITER_ERROR_COMPILESQL_NULLDB 501
#define SQLITER_ERROR_COMPILESQL_NULLSTATEMENT 501
#define SQLITER_ERROR_COMPILESQL_FAILEDPREPARE 501

#define SQLITER_ERROR_COMPILESTATEMENT_FAILCOMPILESQL 601
#define SQLITER_ERROR_COMPILESTATEMENT_FAILBIND 602

#define SQLITER_ERROR_RUNSTEP_FAILSTEPSTATEMENT 701

#define SQLITER_ERROR_STEPSTATEMENT_DBNULL 801
#define SQLITER_ERROR_STEPSTATEMENT_FAILSQLITE3STEP 802
#define SQLITER_ERROR_STEPSTATEMENT_BADTYPE 803

#define SQLITER_ERROR_RUNSINGLESTEPSTATEMENT_FAILED_RUNSTEP 901

#define SQLITER_ERROR_FINALIZESTATEMENT_DBNULL 1001
#define SQLITER_ERROR_FINALIZESTATEMENT_STATEMENTNULL 1002

#define SQLITER_ERROR_CLOSEDB_FAILSQLITE3CLOSE 1101

#define SQLITER_ERROR_STARTLOG_FAILOPEN 1201


