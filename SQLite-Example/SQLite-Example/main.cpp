//
//  main.cpp
//  SQLite-Example
//
//  Created by Rohit Priyadarshi on 4/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include <sqlite3.h>

sqlite3* open_database(std::string& file) 
{
	sqlite3 *db;
	int rc = sqlite3_open_v2(file.c_str(), &db, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
	if (rc != SQLITE_OK) 
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		exit(-1);
	}
	else 
	{
		std::cerr << "Opened database successfully" << std::endl;
	}
	
	return db;
}

void add_to_database(sqlite3 *db, const std::string& sql_str)
{
	sqlite3_stmt *stmt = NULL;
	int rc = sqlite3_prepare_v2(db, sql_str.c_str(), sql_str.size(), &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Could not prepare \"" << sql_str << "\"" << std::endl;
	}
	
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "Could not step \"" << sql_str << "\"" << std::endl;
	}
	
	sqlite3_finalize(stmt);
}

void create_database(sqlite3 *db) 
{
	add_to_database(db, "CREATE TABLE tree (node INTEGER NOT NULL PRIMARY KEY, name TEXT, parent INTEGER REFERENCES tree);");
	add_to_database(db, "INSERT INTO tree VALUES ( 1, 'A', NULL );");
	add_to_database(db, "INSERT INTO tree VALUES ( 2, 'A.1', 1 );");
	add_to_database(db, "INSERT INTO tree VALUES ( 3, 'A.1.a', 2 );");
	add_to_database(db, "INSERT INTO tree VALUES ( 4, 'A.2', 1 );");
	add_to_database(db, "INSERT INTO tree VALUES ( 5, 'A.2.a', 4 );");
	add_to_database(db, "INSERT INTO tree VALUES ( 6, 'A.2.b', 4 );");
	add_to_database(db, "INSERT INTO tree VALUES ( 7, 'A.3', 1 );");
}

void query_database(sqlite3 *db) 
{
	std::string sql_str;
	sql_str += "SELECT n.name AS node, p.name AS parent FROM tree AS n JOIN tree AS p ON n.parent = p.node;";
	sqlite3_stmt *stmt = NULL;
	int rc = sqlite3_prepare_v2(db, sql_str.c_str(), sql_str.size(), &stmt, NULL);
	if (rc != SQLITE_OK) {
		std::cerr << "Could not prepare \"" << sql_str << "\"" << std::endl;
	}
	
	int param_idx = 0;
	int param_value = 0;
	int col_index = 0;
	std::string col_value;
	int i = 0;
	while (i-- >= 0) 
	{
		sqlite3_bind_int(stmt, param_idx, param_value);
		
		while (sqlite3_step(stmt) == SQLITE_ROW) 
		{
			col_value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, col_index));
			std::cout << col_value << std::endl;
		}
        
		sqlite3_reset(stmt);
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
}

int main (int argc, char * const argv[]) 
{
	std::string file;
	
	if (argc > 1) 
	{
		file = argv[1];
	}
	
	sqlite3_initialize();
	
	sqlite3 *db = open_database(file);
	create_database(db);
	query_database(db);
	
	sqlite3_close(db);
	sqlite3_shutdown();
}
