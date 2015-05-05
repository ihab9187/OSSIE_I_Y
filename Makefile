all: fetch

fetch: populate fetch.c
	gcc fetch.c -std=c99  `mysql_config --cflags --libs` -o fetch

populate : populate.c
	gcc populate.c -I/usr/include/mysql -lmysqlclient -o populate
