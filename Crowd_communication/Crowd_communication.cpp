
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <malloc.h>


#include "Crowd_Communication.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


/********************************************************************/
/*								    */
/*		       ����������� ����������			    */



/********************************************************************/
/*								    */
/*		       ����������� ������			    */

     Crowd_Communication::Crowd_Communication()

{
}


/********************************************************************/
/*								    */
/*		        ���������� ������			    */

    Crowd_Communication::~Crowd_Communication()

{
}


/********************************************************************/
/*								    */
/*		        ������� ������ �� ������		    */

    void Crowd_Communication::vReadSave(char *title, std::string *text, char *reference)

{
}


/********************************************************************/
/*								    */
/*		        �������� ������ � ������		    */

    void Crowd_Communication::vWriteSave(std::string *text)

{
     *text="" ;
}


/********************************************************************/
/*								    */
/*		      ���������� �������        		    */

    void Crowd_Communication::vFree(void)

{
}


/********************************************************************/
/*								    */
/*                     ������ ���������� � ��������   		    */

    void Crowd_Communication::vGetInfo(std::string *text)

{
        *text="" ;
}


/********************************************************************/
/*								    */
/*                    �������� ������� �����                        */  

    int Crowd_Communication::vCheck(void *data, Crowd_Objects_List *checked)

{
   return(0) ;
}


