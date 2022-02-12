//Copyright 2015 Nathan Bossett

#include "sqliter.h"


csqliter::csqliter(void)
{
	db = NULL;
	litestmnt = NULL;
}


csqliter::~csqliter(void)
{
}

dbresulttype csqliter::openexistingdb(std::string &fullpath) {
//DB must exist for success (won't create a new one)
dbresulttype rslt;
	
	log("openexistingdb(std::string)");

	rslt = openorcreate(fullpath,false);

	if (rslt) {
		//detailed failure already logged as part of the openorcreate call
		log("\tFailure in openorcreate");
	}

	return(rslt);
}

dbresulttype csqliter::openexistingdb(const char *fullpath) {
//DB must already exist for success (won't create a new one)
dbresulttype rslt;

	std::string full;
	log("opendb(const char *)");
	full = fullpath;
	rslt = openexistingdb(full);

	if (rslt) {
		//just a pipe to the string version but log it anyway
		log("\tFailure in opendb");
	}
	return(rslt);
}

dbresulttype csqliter::createdb(std::string &fullpath) {
	//sqlite doesn't let us _only_ create, only (open must exist | create) or (open must exist)
	//so, try opening first, if that fails try creating.  If opening succeeds, it's a failure
	//from our point of view
	dbresulttype rslt;
	log("createdb(std::string)");
	rslt = openorcreate(fullpath, false);
	if (!rslt) {
		//that should not have worked
		closedb();
		log("\tcreatedb failed on calling openorcreate",SQLITER_ERROR_CREATEDB_FAILEDOPEN,SQLITER_ERROR_NONE);
		return(otherdberror);
	}
	rslt = openorcreate(fullpath,true);

	if (rslt) {
		log("\tcreatedb failed on calling openorcreate(std::string, bool)");
	}

	return(rslt);
}

dbresulttype csqliter::createdb(const char *fullpath) {
std::string str;
dbresulttype rslt;

	str = fullpath;

	log("createdb(cont char *)");
	rslt = createdb(str);

	if (rslt) {
		log("\tFailure in createdb");
	}

	return(rslt);
}

dbresulttype csqliter::openorcreate(std::string &fullpath, bool create) {
	//note: per "Using SQLite", p 463, you can't just pass in SQLITE_OPEN_CREATE but have to choose
	//	between opening with the possibility of creation or opening without the possibility of creating
	int flags;
	int rc;
	log("openorcreate(std::string, bool)");

	if (create) {
		flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
	} else {
		flags = SQLITE_OPEN_READWRITE;
	}
	
	rc = sqlite3_open_v2(fullpath.c_str(), &db, flags, NULL);
	switch(rc) {
	case SQLITE_OK:
		//...excellent
		break;
	default:
		db = NULL;
		log("\topenorcreate, sqlite3_open_v2 failed", SQLITER_ERROR_OPENORCREATE_FAILEDSQLITE3OPEN, rc);
		return(otherdberror);
	}

	rc = sqlite3_busy_timeout(db, DB_DEFAULT_TIMEOUT_MILLISECONDS);
	switch (rc) {
	case SQLITE_OK:
		return(successdb);
		break;
	default:
		log("\topenorcreate, sqlite3_busy_timeout failed", SQLITER_ERROR_OPENORCREATE_FAILEDSQLITE3SETBUSYTIMEOUT, rc);
		return(otherdberror);
	}

}

dbresulttype csqliter::removedatabase(const char *fullpath) { 
//std::remove is only defined in terms of success or failure, not detailed error codes
	log("removedatabase(const char *)");
	if (std::remove(fullpath)) {
		log("\tremovedatabase failed, std::remove failed",SQLITER_ERROR_REMOVEDB_FAILEDSTDREMOVE,0);
		return(otherdberror);
	} else {
		return(successdb);
	}
}

dbresulttype csqliter::removedatabase(std::string &fullpath) {
dbresulttype rslt;
	log("removedatabase(std::string)");
	rslt = removedatabase(fullpath.c_str());
	if (rslt) {
		log("\tFailure in removedatabase");
	}
	return(rslt);
}


sqlite3 *csqliter::getdbhandle() {
	log("getdbhandle");
	return(db);
}

void csqliter::setdbhandle(sqlite3 *dbhandle) {
	log("setdbhandle");
	finalizestatement();
	db = dbhandle;
}

void csqliter::bindstr(std::string &name, std::string &arg) {
	log("bindstr(std::string, std::string)");
	statementdirty = true;
	valsin.resize(valsin.size()+1);
	valsin[valsin.size()-1].name = name;
	valsin[valsin.size()-1].val.valtype = strdbval;
	valsin[valsin.size()-1].val.sval = arg;
}

void csqliter::bindstr(std::string &name, const char *arg) {
std::string ar;
	log("bindstr(std::string, const char *)");
	ar = arg;
	bindstr(name,ar);
}

void csqliter::bindstr(const char *name, std::string &arg) {
std::string nam;
	log("bindstr(const char *, std::string)");
	nam = name;
	bindstr(nam, arg);
}

void csqliter::bindstr(const char *name, const char *arg) {
std::string nam;
std::string ar;
	
	log("bindstr(const char *, const char *)");
	nam = name;
	ar = arg;

	bindstr(nam,ar);

}

void csqliter::bindint(std::string &name, sqlite3_int64 arg) {//int arg) {
	log("bindint(std::string, sqlite3_int64)");
	statementdirty = true;

	valsin.resize(valsin.size()+1);
	valsin[valsin.size()-1].name = name;
	valsin[valsin.size()-1].val.valtype = intdbval;
	valsin[valsin.size()-1].val.ival = arg;
}

void csqliter::bindint(const char *name, sqlite3_int64 arg) {//int arg) {
std::string nam;
	log("bindint(const char *, sqlite3_int64)");
	nam = name;
	bindint(nam,arg);

}

void csqliter::bindfloat(std::string &name, double arg) {
	log("bindfloat(std::string, double)");
	statementdirty = true;

	valsin.resize(valsin.size()+1);
	valsin[valsin.size()-1].name = name;
	valsin[valsin.size()-1].val.valtype = floatdbval;
	valsin[valsin.size()-1].val.fval = arg;
	
}

void csqliter::bindfloat(const char *name, double arg) {
std::string nam;
	log("bindfloat(const char *, double)");
	nam = name;
	bindfloat(nam, arg);

}

void csqliter::bindnull(std::string &name) {
	log("bindnull(std::string)");
	statementdirty = true;

	valsin.resize(valsin.size() + 1);
	valsin[valsin.size()-1].name = name;
	valsin[valsin.size()-1].val.valtype = nulldbval;
}

void csqliter::bindnull(const char *name) {
std::string nam;
	log("bindnull(const char *)");
	nam = name;
	bindnull(nam);

}

void csqliter::bindblob(std::string &name, unsignedcharvector &arg) {
	log("bindblob(std::string, unsignedcharvector)");
	statementdirty = true;

	valsin.resize(valsin.size() + 1);
	valsin[valsin.size()-1].name = name;
	valsin[valsin.size()-1].val.valtype = blobdbval;
	valsin[valsin.size()-1].val.blob = arg;

}

void csqliter::bindblob(const char *name, unsignedcharvector &arg) {
std::string nam;

	log("bindblob(const char *, unsignedcharvector)");
	nam = name;
	bindblob(nam,arg);

}

int csqliter::bindparameter(cdbparameter &param) {
std::string name;
int index;
int rc;

	log("bindparameter(cdbparameter)");
	if (db == NULL) {
		log("\tbindparameter failed, database is NULL");
		return(1);
	}

	name = ":" + param.name;
	index = sqlite3_bind_parameter_index(litestmnt, name.c_str());
	if (index == 0) {
		log("\tbindparameter failed, sqlite3_bind_parameter_index failed with index of zero",SQLITER_ERROR_BIND_OBTAININDEX,0);
		return(binddberror);
	}

	switch (param.val.valtype) {
	case intdbval:
		rc = sqlite3_bind_int64(litestmnt, index, param.val.ival);
		if (rc != SQLITE_OK) {
			log("\tbindparameter failed, sqlite3_bind_int64 failed",SQLITER_ERROR_BIND_INT64,rc);
			return(binddberror);
		}
		break;
	case floatdbval:
		rc = sqlite3_bind_double(litestmnt, index, param.val.fval);
		if (rc != SQLITE_OK) {
			log("\tbindparameter failed, sqlite3_bind_double failed",SQLITER_ERROR_BIND_DOUBLE,rc);
			return(binddberror);
		}
		break;
	case strdbval:
		rc = sqlite3_bind_text(litestmnt, index, param.val.sval.c_str(), param.val.sval.length(), SQLITE_TRANSIENT);
		if (rc != SQLITE_OK) {
			log("\tbindparameter failed, sqlite3_bind_text failed",SQLITER_ERROR_BIND_TEXT,rc);
			return(binddberror);
		}
		break;
	case blobdbval:
		rc = sqlite3_bind_blob(litestmnt, index, &(param.val.blob[0]), param.val.blob.size(), SQLITE_TRANSIENT);
		if (rc != SQLITE_OK) {
			log("\tbindparameter failed, sqlite3_bind_blob failed",SQLITER_ERROR_BIND_BLOB,rc);
			return(binddberror);
		}
		break;
	case nulldbval:
		rc = sqlite3_bind_null(litestmnt, index);
		if (rc != SQLITE_OK) {
			log("\tbindparameter failed, sqlite3_bind_blob failed",SQLITER_ERROR_BIND_NULL,rc);
			return(binddberror);
		}
		break;
	default:
		log("\tbindparameter failed, Unrecognized type of val",SQLITER_ERROR_BIND_BADTYPE, 0);
		return(binddberror);
	}

	return(successdb);


}

void csqliter::pushvaltypeout(dbvaltype valtype) {
	log("pushvaltypeout(dbvaltype)");
	valtypesout.push_back(valtype);
}

void csqliter::pushvaltypesout(dbvaltype valtype) {
	log("pushvaltypesout(1 dbvaltype)");
	pushvaltypeout(valtype);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2) {
	log("pushvaltypesout(2 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3) {
	log("pushvaltypesout(3 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4) {
	log("pushvaltypesout(4 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
	pushvaltypeout(typ4);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5) {
	log("pushvaltypesout(5 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
	pushvaltypeout(typ4);
	pushvaltypeout(typ5);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6) {
	log("pushvaltypesout(6 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
	pushvaltypeout(typ4);
	pushvaltypeout(typ5);
	pushvaltypeout(typ6);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7) {
	log("pushvaltypesout(7 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
	pushvaltypeout(typ4);
	pushvaltypeout(typ5);
	pushvaltypeout(typ6);
	pushvaltypeout(typ7);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7, dbvaltype typ8) {
	log("pushvaltypesout(8 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
	pushvaltypeout(typ4);
	pushvaltypeout(typ5);
	pushvaltypeout(typ6);
	pushvaltypeout(typ7);
	pushvaltypeout(typ8);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7, dbvaltype typ8, dbvaltype typ9) {
	log("pushvaltypesout(9 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
	pushvaltypeout(typ4);
	pushvaltypeout(typ5);
	pushvaltypeout(typ6);
	pushvaltypeout(typ7);
	pushvaltypeout(typ8);
	pushvaltypeout(typ9);
}
void csqliter::pushvaltypesout(dbvaltype typ1, dbvaltype typ2, dbvaltype typ3, dbvaltype typ4, dbvaltype typ5, dbvaltype typ6, dbvaltype typ7, dbvaltype typ8, dbvaltype typ9, dbvaltype typ10) {
	log("pushvaltypesout(10 dbvaltype)");
	pushvaltypeout(typ1);
	pushvaltypeout(typ2);
	pushvaltypeout(typ3);
	pushvaltypeout(typ4);
	pushvaltypeout(typ5);
	pushvaltypeout(typ6);
	pushvaltypeout(typ7);
	pushvaltypeout(typ8);
	pushvaltypeout(typ9);
	pushvaltypeout(typ10);
}

void csqliter::setsql(std::string &sql) {
	log("setsql(std::string)");
	setsql(sql.c_str());
}

void csqliter::setsql(const char *sql) {
	log("setsql(const char *)");
	finalizestatement();
	statementdirty = true;
	stmntsql = sql;
}

dbresulttype csqliter::compilesql() {
int rc;

	log("compilesql");

	if (db == NULL) {
		log("\tcompilesql failed, db is null");
		return(otherdberror);
	}

	if (stmntsql == "") {
		log("\tcompilesql failed, sql statement is null");
		return(otherdberror);
	}

	if (litestmnt != NULL) {
		litestmnt = NULL;
		sqlite3_finalize(litestmnt);
	}
	rc = sqlite3_prepare_v2(db, stmntsql.c_str(), -1, &litestmnt, NULL);

	switch (rc) {
	case SQLITE_OK:
		return(successdb);
	case SQLITE_BUSY:
		log("\tcompilesql failed, db is busy", SQLITER_ERROR_NONE,rc);
		return(busydberror);
	default:
		log("\tcompilesql failed, failed sqlite3_prepare_v2", SQLITER_ERROR_COMPILESQL_FAILEDPREPARE,rc);
		return(otherdberror);
	}
}

dbresulttype csqliter::compilestatement() {
dbresulttype rval;
int rslt;
unsigned int i;

	log("compilestatement");
	log("\t");log(stmntsql);log("\n");

	valcountandtypesmatch = true;
	lastinsertrowid = 0;

	rval = compilesql();
	if (rval != successdb) {
		finalizestatement();
		log("\tcompilestatement failed", SQLITER_ERROR_COMPILESTATEMENT_FAILCOMPILESQL,rval);
		return(rval);
	}

	for (i=0;i < valsin.size(); i++) {
		rslt = bindparameter(valsin[i]);
		if (rslt) {
			finalizestatement();
			log("\tcompilestatment failed, bind error\n", SQLITER_ERROR_COMPILESTATEMENT_FAILBIND,rslt);
			return(binddberror);
		}
	}

	return(successdb);

}

dbresulttype csqliter::runstep() {
dbresulttype rval;

	log("runstep\n");
	if (statementdirty) {
		//rval = compilesql();
		//if (rval) {
		//	return(rval);
		//}
		rval = compilestatement();
		if (rval) {
			log("\trunstep failed, compilestatement.");
			return(rval);
		}
		statementdirty = false;
	}

	rval = stepstatement();

	switch (rval) {
	case successdb:
		finalizestatement();
		return(successdb);
		break;
	case rowresultdb:
		//extract the results
		return(rowresultdb);
		break;
	default:
		log("\trunstep failed, stepstatement failed",SQLITER_ERROR_RUNSTEP_FAILSTEPSTATEMENT,rval);
		return(rval);
	}
	
	return(successdb);
}

dbresulttype csqliter::stepstatement() {
int rc;
int numout;
int coltype;
int size;
int i;
int pos;
	log("stepstatement\n");
	if (db == NULL) {
		log("\tstepstatment failed, db null",SQLITER_ERROR_STEPSTATEMENT_DBNULL,0);
		return(otherdberror);
	}

	//done = false;

	rc = sqlite3_step(litestmnt);

	switch (rc) {
	case SQLITE_BUSY:
		log("\tstepstatement failed, db is busy\n",SQLITER_ERROR_NONE, 0);
		return(busydberror);
	case SQLITE_DONE:
		lastinsertrowid = sqlite3_last_insert_rowid(db);
		return(successdb);
	case SQLITE_ROW:
		numout = sqlite3_column_count(litestmnt);
		if (numout != valtypesout.size()) {
			if (options.valcountmismatchcausesfailure) {
				valcountandtypesmatch = false;
				log("\tstepstatement failed, result count wrong\n",SQLITER_ERROR_NONE,0);
				return(resultcountmismatchdberror);
			}
		}

		if (rowdata.size() != numout) {rowdata.resize(numout);}
		for (i=0;i<numout;i++) {
			coltype = sqlite3_column_type(litestmnt, i);
			if (options.valtypemismatchcausesfailure) {
				//if the types not matching is an error
				if (coltype != valtypesout[i]) {
					//...and if the types don't match
					if (coltype == nulldbval) {
						//the expected and actual types didn't match.  The actual is a null; therefore the expected isn't.
						if (options.nullisavaltypemismatch) {
							//...and if, should the type be returned is null, then is it a permitted or a not
							//	permitted null to find in a field like an INT or TEXT?
							log("\tstepstatement failed, result types wrong for a null value\n",SQLITER_ERROR_NONE,0);
							valcountandtypesmatch = false;
							return(resulttypemismatchdberror);}
						else {
							//it's a NULL when we were expecting INT, TEXT, etc.
							//however, the options have not chosen to flag that as an error
							//(as is quite normal to SQL devs but maybe not all newer SQLiter users)

							//OK, fall back out of the conditionals and process as regular data.
						}
					} else {
						log("\tstepstatement failed, result types wrong for non-null value\n",SQLITER_ERROR_NONE,0);
						return(resulttypemismatchdberror);
					}
				}
			}
			switch (coltype) {
			case intdbval:
				rowdata[i].valtype = intdbval;
				rowdata[i].ival = (int) sqlite3_column_int(litestmnt,i);
				break;
			case floatdbval:
				rowdata[i].valtype = floatdbval;
				rowdata[i].fval = (double) sqlite3_column_double(litestmnt, i);
				break;
			case strdbval:
				rowdata[i].valtype = strdbval;
				rowdata[i].sval = (char *) sqlite3_column_text(litestmnt,i);
				break;
			case blobdbval:
				rowdata[i].valtype = blobdbval;
				size = sqlite3_column_bytes(litestmnt,i);
				rowdata[i].blob.resize(size);
				if (size > 0) {
					const unsigned char *blb;
					std::vector<unsigned char>::iterator it;
					std::string foo;
					blb = (const unsigned char*) sqlite3_column_blob(litestmnt,i);
					size = sqlite3_column_bytes(litestmnt, i);
					rowdata[i].blob.assign(blb, blb + size);
				}
				break;
			case nulldbval:
				rowdata[i].valtype = nulldbval;
				rowdata[i].ival = 0;
				rowdata[i].sval = "";
				break;
			default:
				log("\tstepstatment failed, Unknown type",SQLITER_ERROR_STEPSTATEMENT_BADTYPE, 0);
				return(otherdberror);
			}
		}
		return(rowresultdb);
	default:
		log("\tstepstatement failed, sqlite3_step failed",SQLITER_ERROR_STEPSTATEMENT_FAILSQLITE3STEP,rc);
		return(otherdberror);
	}

}

dbresulttype csqliter::runsinglestepstatement() {
	int rval;
	dbresulttype rslt;
	log("runsinglestepstatement()");
	rslt = runsinglestepstatement(rval);
	if (rslt) {
		log("\trunsinglestepstatement failed, Failure in runsinglestepstatement(int &) at runsinglestepstatement(int)");
	}
	return(rslt);
}

dbresulttype csqliter::runsinglestepstatement(int &numresultrowsreturned) {
//reduces boilerplate code by providing a single call which can return zero or one result rows.
//examples: a query by ID.
dbvals firstrow;
dbresulttype rval;
int count;
	log("runsinglestepstatment(int &)");
	count = 0;
	
	switch((rval=runstep())) {
	case successdb:
		//it worked and returned no results
		numresultrowsreturned = 0;
		return(successdb);
		break;
	case rowresultdb:
		numresultrowsreturned = 0;
		//make sure there's only the one and that the final result is success.
		firstrow = rowdata;
		switch ((rval = runstep())) {
		case successdb:
			rowdata = firstrow;
			numresultrowsreturned = 1;
			return(successdb);
		default:
			return(rval);
		}
		break;
	default:
		log("\trunsinglestestatement failed, runstep failed\n",SQLITER_ERROR_RUNSINGLESTEPSTATEMENT_FAILED_RUNSTEP,0);
		return(rval);
	}

}

int csqliter::finalizestatement() {
	valsin.resize(0);
	valtypesout.resize(0);
	log("finalizestatement\n");
	if (db == NULL) {
		log("\tfinalizestatement failed, db is null",SQLITER_ERROR_FINALIZESTATEMENT_DBNULL,0);
		return(1);
	}

	if (litestmnt == NULL) {
		log("\tfinalizestatement failed, statement is already null");//not actually an error
		return(0);
	}
	sqlite3_finalize(litestmnt);
	litestmnt = NULL;
	return(0);

}

dbresulttype csqliter::closedb() {
int rc;
	log("closedb()");
	if (litestmnt != NULL) {
		sqlite3_finalize(litestmnt);
	}
	rc = sqlite3_close(db);
	db = NULL;
	switch (rc) {
	case SQLITE_OK:
		return(successdb);
	default:
		log("\tsqlite3_close failed",SQLITER_ERROR_CLOSEDB_FAILSQLITE3CLOSE,rc);
		return(otherdberror);
	}
}

inline void csqliter::log(std::string &str) {
	log(str.c_str());
}

inline void csqliter::log(const char *str) {
	if (logfile.good()) {
		logfile << str;
		logfile << "\n";
	}
}

inline void csqliter::log(std::string &str, int sqliter_errorcode, int sqlite_errorcode) {
	log(str.c_str(),sqliter_errorcode, sqlite_errorcode);
}

inline void csqliter::log(const char *str, int sqliter_errorcode, int sqlite_errorcode) {
//work around older g++'s (4.2.1) not supporting std::string
	std::string errstr;
	std::string logstr;
	std::ostringstream strstrm;

	geterrorname(sqlite_errorcode, errstr);
	logstr = str;
	logstr += "\t";
	//logstr += std::to_string(sqliter_errorcode);
	strstrm << sqliter_errorcode;
	logstr += strstrm.str();strstrm.str("");
	logstr += "\t";
	//logstr += std::to_string(sqlite_errorcode);
	strstrm << sqliter_errorcode;
	logstr += strstrm.str();strstrm.str("");
	logstr += "\t";
	logstr += errstr;
	logstr += "\n";
	log(logstr);
}

int csqliter::startlog(const char *fullpath) {
int rval;

std::string fp;
	fp = fullpath;
	rval = startlog(fp);
	if (rval) {
		log("Failure in startlog(const char *fullpath) at startlog(std::string)");
	}
	return(rval);
}

int csqliter::startlog(std::string &fullpath) {
	log("opening log file - WHILE ALREADY OPEN\n\t");
	//log(fullpath.c_str());
	//log("\n");
	logfile.open(fullpath.c_str());
	log("startlog");

	if (!(logfile.good())) {
		log("\tfailed ofstream.open",SQLITER_ERROR_STARTLOG_FAILOPEN,0);
		return(1);
	}

	return(0);

}

void csqliter::stoplog() {
	log("stoplog");
	logfile.close();
}

csqliteroptions::csqliteroptions(void) {
	valtypemismatchcausesfailure = true;
	nullisavaltypemismatch = false;
	valcountmismatchcausesfailure = true;
}

void csqliteroptions::setvaltypemismatchcausesfailure(bool mismatchisfailure) {
	//log("setvaltypemismatchcausesfailure(bool)");
	valtypemismatchcausesfailure = mismatchisfailure;
}

void csqliteroptions::setvalcountmismatchcausesfailure(bool mismatchisfailure) {
	//log("setvalcountmismatchcausesfailure(bool)");
	valcountmismatchcausesfailure = mismatchisfailure;
}

void geterrorname(int code, std::string &str) {
	switch (code) {
//Error codes native to the SQLite layer, modified to report string errors
	case SQLITE_ERROR: str=      "SQL error or missing database";break;
	case SQLITE_INTERNAL: str=    "Internal logic error in SQLite";break;
	case SQLITE_PERM: str=        "Access permission denied";break;
	case SQLITE_ABORT: str=       "Callback routine requested an abort";break;
	case SQLITE_BUSY: str=        "The database file is locked";break;
	case SQLITE_LOCKED: str=      "A table in the database is locked";break;
	case SQLITE_NOMEM: str=       "A malloc() failed";break;
	case SQLITE_READONLY: str=    "Attempt to write a readonly database";break;
	case SQLITE_INTERRUPT: str=   "Operation terminated by sqlite3_interrupt()";break;
	case SQLITE_IOERR: str=       "Some kind of disk I/O error occurred";break;
	case SQLITE_CORRUPT: str=     "The database disk image is malformed";break;
	case SQLITE_NOTFOUND: str=    "Unknown opcode in sqlite3_file_control()";break;
	case SQLITE_FULL: str=        "Insertion failed because database is full";break;
	case SQLITE_CANTOPEN: str=    "Unable to open the database file";break;
	case SQLITE_PROTOCOL: str=    "Database lock protocol error";break;
	case SQLITE_EMPTY: str=      "Database is empty";break;
	case SQLITE_SCHEMA: str=      "The database schema changed";break;
	case SQLITE_TOOBIG: str=      "String or BLOB exceeds size limit";break;
	case SQLITE_CONSTRAINT: str=  "Abort due to constraint violation";break;
	case SQLITE_MISMATCH: str=    "Data type mismatch";break;
	case SQLITE_MISUSE: str=      "Library used incorrectly";break;
	case SQLITE_NOLFS: str=       "Uses OS features not supported on host";break;
	case SQLITE_AUTH: str=        "Authorization denied";break;
	case SQLITE_FORMAT: str=      "Auxiliary database format error";break;
	case SQLITE_RANGE: str=       "2nd parameter to sqlite3_bind out of range";break;
	case SQLITE_NOTADB: str=      "File opened that is not a database file";break;
	case SQLITE_NOTICE: str=      "Notifications from sqlite3_log()";break;
	case SQLITE_WARNING: str=     "Warnings from sqlite3_log()";break;
	case SQLITE_ROW: str=         "sqlite3_step() has another row ready";break;
	case SQLITE_DONE: str=        "sqlite3_step() has finished executing";break;
	default:
		str = "UNKOWN SQLITE ERROR CODE";
		break;
	}
}

int csqliter::runinternaltests() {
//this function tests some things which are most easily done with access to the private members.  An alternative
//	would be declaring a friend class but that starts additing conditionals.
//an example is assuring that equivalent functions actually are, such as using either a char* or a &string
std::string name;
std::string val;
std::string str;
char nameaschar[1024];
int i;

	valsin.clear();
	name = "testname";
	val = "testval";
	bindstr(name, val);
	bindstr(name, "testval");
	bindstr("testname", val);
	bindstr("testname", "testval");
	for (i=0;i<=3;i++) {
		if (valsin[i].val.valtype != strdbval) {
			return(1);
		}
		if (valsin[i].name != "testname") {
			return(1);
		}
		if (valsin[i].val.sval != "testval") {
			return(1);
		}
	}

	valsin.clear();
	bindint(name, 3);
	bindint("testname",3);
	for (i=0;i<=1;i++) {
		if (valsin[i].val.valtype != intdbval) {
			return(2);
		}
		if (valsin[i].name != "testname") {
			return(2);
		}
		if (valsin[i].val.ival != 3) {
			return(2);
		}
	}

	valsin.clear();
	bindfloat(name,3.14);
	bindfloat("testname",3.14);
	for (i=0;i<=1;i++) {
		if (valsin[i].val.valtype != floatdbval) {
			return(3);
		}
		if (valsin[i].name != "testname") {
			return(3);
		}
		if (valsin[i].val.fval != 3.14) {
			return(3);
		}
	}

	unsignedcharvector blob;
	valsin.clear();
	blob.resize(1);
	blob[0] = 4;
	bindblob(name,blob);
	bindblob("testname", blob);
	for (i=0;i<=1;i++) {
		if (valsin[i].val.valtype != blobdbval) {
			return(4);
		}
		if (valsin[i].name != "testname") {
			return(4);
		}
		if (valsin[i].val.blob.size() != 1) {
			return(4);
		}
		if (valsin[i].val.blob[0] != 4) {
			return(4);
		}
	}

	//picking float because it's not a possible variable default value like 0 or 1
	pushvaltypeout(floatdbval);
	pushvaltypesout(floatdbval);
	pushvaltypesout(floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval, floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval);
	pushvaltypesout(floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval, floatdbval);
	if (valtypesout.size() != 56) {
		return(5);
	}
	for (i=0;i<=55;i++) {
		if (valtypesout[i] != floatdbval) {
			return(5);
		}
	}

	//just testing the polymorphism
	//testing here depends on the implementation... here we know that one of the functions does the work,
	//	so if the other causes any of the work to be done the piping through must have worked (in this case, setting the internal stmntsql variable
	//and elsewhere we have plenty of testing to make sure that the SQL is actually processed correctly
	setsql("Hello World!");
	if (stmntsql != "Hello World!") {
		return(6);
	}
	
	str = "Hello World!";
	stmntsql = "...";
	setsql(str);
	if (stmntsql != "Hello World!") {
		return(6);
	}

	finalizestatement();

	return(0);

}

