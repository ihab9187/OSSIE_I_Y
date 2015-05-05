#include <my_global.h>
#include <mysql.h>
#include <stdio.h>

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main(int argc, char **argv)
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
	fprintf(stderr, "mysql_init() failed\n");
	exit(1);		
	}

	if (mysql_real_connect(con, "localhost","root","newpwd","drawing_app",0,NULL,0)==NULL)
	{
	finish_with_error(con);
	}
	
	if (mysql_query(con, "SELECT*FROM inputs"))
	{
	finish_with_error(con);
	}

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL)
	{
	finish_with_error(con);
	}

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

	FILE * fp;
	fp = fopen("fetch.csv","w");
	

	while ((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < num_fields; i++)
		{
		fprintf(fp,"%s ", row[i] ? row[i] : "NULL");
		if (i < (num_fields - 1))
			fprintf(fp,",");
		}
		fprintf(fp,"\n");

		
	}
	fclose(fp);

	mysql_free_result(result);
	mysql_close(con);

	exit(0);	
}



