echo off
cd /d D:\MySQL\MySQL Server 5.0
mysqldump -uroot -p123456 -hlocalhost hoteldb --lock-all-tables >±¸·Ý.sql
pause;