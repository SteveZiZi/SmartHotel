@echo off
cd /d D:
md MySQLbak
cd /d C:\MySQL\MySQL Server 5.0\bin
mysqldump -uroot -p123456 -hlocalhost hoteldb --lock-all-tables >D:\MySQLbak\±¸·Ý%date:~0,4%-%date:~5,2%-%date:~8,2%.sql
