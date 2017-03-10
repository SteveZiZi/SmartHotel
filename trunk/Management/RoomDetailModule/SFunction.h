///////////////////////////////////////////////////////////////////////
#define ROOM_MODULE_API __declspec(dllexport)
//#define ROOM_MODULE_API __declspec(dllimport)
//下面用于增加函数声明部分
extern "C"
{
   ROOM_MODULE_API  int CallDetailModule(LPVOID lParam,LPVOID wParam,int Index = 0);








}