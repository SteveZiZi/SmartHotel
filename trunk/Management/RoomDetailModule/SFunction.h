///////////////////////////////////////////////////////////////////////
#define ROOM_MODULE_API __declspec(dllexport)
//#define ROOM_MODULE_API __declspec(dllimport)
//�����������Ӻ�����������
extern "C"
{
   ROOM_MODULE_API  int CallDetailModule(LPVOID lParam,LPVOID wParam,int Index = 0);








}