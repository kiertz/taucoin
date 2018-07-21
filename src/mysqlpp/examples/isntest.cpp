/***********************************************************************
 ssqls1.cpp - Example that produces the same results as simple1, but it
	uses a Specialized SQL Structure to store the results instead of a
	MySQL++ Result object.
 
 Copyright (c) 1998 by Kevin Atkinson, (c) 1999-2001 by MySQL AB, and
 (c) 2004-2009 by Educational Technology Resources, Inc.  Others may
 also hold copyrights on code in this file.  See the CREDITS.txt file
 in the top directory of the distribution for details.

 This file is part of MySQL++.

 MySQL++ is free software; you can redistribute it and/or modify it
 under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 MySQL++ is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with MySQL++; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
 USA
***********************************************************************/

#include "cmdline.h"
#include "isnreward.h"

#include <iostream>
#include <vector>

using namespace std;

int
main(int argc, char *argv[])
{
	try {						
		// Establish the connection to the database server.
		//mysqlpp::Connection con(mysqlpp::examples::db_name,
		//cmdline.server(), cmdline.user(), cmdline.pass());
		mysqlpp::Connection con("imreward", "localhost", "immysql", "im123456");

		// Retrieve a subset of the stock table's columns, and store
		// the data in a vector of 'stock' SSQLS structures.  See the
		// user manual for the consequences arising from this quiet
		// ability to store a subset of the table in the stock SSQLS.
		mysqlpp::Query query= con.query();
		query << "select %0"", %1"" from %2"" where %3""= %4q";
		query.parse();
		mysqlpp::StoreQueryResult res= query.store("address", "ttc", "clubinfo", "club_id", "1");
		if(res.empty())
		{
			cout << "Error in query, no data " << endl;
		}
		// Display the items
		cout << "We have:" << endl;
		cout << '\t' << res[0]["address"]<< endl;
		cout << '\t' << res[0]["ttc"]<< endl;
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return -1;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions; e.g. type mismatch populating 'stock'
		cerr << "Conversion error: " << er.what() << endl <<
				"\tretrieved data size: " << er.retrieved <<
				", actual size: " << er.actual_size << endl;
		return -1;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return -1;
	}

	return 0;
}