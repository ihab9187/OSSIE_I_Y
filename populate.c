// Create database, create plotting data and log the data to the database
// Student Pair: Zhao Yang, Ihab Zine
#include <stdio.h>
#include <my_global.h>
#include <mysql.h>



//halo world.


// Function to insert data into database
void put_data(MYSQL * con,double x, double y, double z)
{
	char SQLString[100];
	sprintf(SQLString,"INSERT INTO inputs VALUES (%f,%f,%f)",x,y,z);
	printf("%s\n",SQLString);
	if(mysql_query(con,SQLString))
	{
		printf("%s\n",mysql_error(con));
	}
}
// Main function for establishing the connection to MySQL database, create database and table, create the data for plot
int main()
{	
	int i;
	//Initialises a MYSQL object
	MYSQL *con=mysql_init(NULL);
	//Check if the mysql_init() function fails
	if (con==NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
	}
	//Establishes a connection to the database
	if (mysql_real_connect(con,"localhost","root","",NULL,0,NULL,0)==NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
	}
	//Drop the database with the same name as the one will be created
	if (mysql_query(con, "DROP DATABASE IF EXISTS drawing_app"))
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
	}
	//Create a database "drawing_app"
	if (mysql_query(con, "CREATE DATABASE drawing_app")) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	//Using the database "drawing_app"
	if (mysql_query(con, "USE drawing_app"))
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
	}
	//Drop the table with the same name as the table will be created
	if (mysql_query(con, "DROP TABLE IF EXISTS inputs"))
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
	}
	//Create the table "inputs"
	if (mysql_query(con, "CREATE TABLE inputs(x float, y float, z float)"))
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
	}
	//Create data for plot
	for (i=0;i<100;i++)
	{
		//create 3 columes of data one sinwave, one square wave and one half amplitude wave	
		put_data(con,sin(2.0*3.141592 * (double)i/100.0),i<50?1:-1,-0.5*sin(2.0*3.141592 * (double)i/100.0));
	}
	//Close the MySQL connection
	mysql_close(con);
	exit(0);
}
