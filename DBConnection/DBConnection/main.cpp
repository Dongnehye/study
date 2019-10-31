#include <iostream>
#include <WinSock2.h>
#include <mysql.h>

using namespace std;

int main()
{
	MYSQL conn;
	MYSQL_RES* pSqlRes;
	MYSQL_ROW sqlRow;

	if (mysql_init(&conn) == nullptr)
	{
		cout << "mysql_init" << endl;
		return 1;
	}

	if (mysql_real_connect(&conn, "localhost", "root", "123456789", "test_game",3306, NULL, 0) == nullptr)
	{
		cout << "mysql_real_connect fail" << endl;
	}
	if (mysql_select_db(&conn, "test_game"))
	{
		cout << "mysql_select_db fail : " << mysql_errno(&conn) << " : "
			<< mysql_error(&conn) << endl;
		return 1;
	}

	const char* query = "SELECT * FROM user_data";

	int state = mysql_query(&conn, query);
	if (state == 0)
	{
		pSqlRes = mysql_store_result(&conn);
		if (pSqlRes != nullptr)//SELECT 문을 뺀 나머지는 null
		{
			int numCol = mysql_num_fields(pSqlRes);
			while ((sqlRow = mysql_fetch_row(pSqlRes)) != nullptr)
			{
				for (int i = 0; i < numCol; i++)
					cout << sqlRow[i] << " ";

				cout << endl;
			}
		}
		else
		{
			int errNo = mysql_errno(&conn);
			if (errNo != 0)
			{
				cout << "Error : " << mysql_error(&conn) << endl;
			}
		}

		mysql_free_result(pSqlRes);
	}

	mysql_close(&conn);

	return 0;
}