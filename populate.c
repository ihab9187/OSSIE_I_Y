#include <stdio.h>
#include <my_global.h>
#include <mysql.h>

void put_data(MYSQL * con,double x, double y)
{
	char SQLString[100];
	sprintf(SQLString,"INSERT INTO inputs VALUES (%f,%f)",x,y);
	printf("%s\n",SQLString);
	if(mysql_query(con,SQLString))
	{
		printf("%s\n",mysql_error(con));
	}
}
int main()
{
	int i;
	MYSQL *con=mysql_init(NULL);
	if (con==NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
		
	}
	if (mysql_real_connect(con,"localhost","root","newpwd","drawing_app",0,NULL,0)==NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(2);
	}
	for (i=0;i<100;i++)
	{
		put_data(con,sin(2.0*3.141592 * (double)i/100.0),i<50?1:-1);
	}
	mysql_close(con);
	exit(0);
}
