echo off
cd /d D:\MySQL\MySQL Server 5.0
mysql -hlocalhost -uroot -p123456 hoteldb <D:\百牧项目\SecondProject_140113\OutPut\start_mysql\备份.sql
pause;