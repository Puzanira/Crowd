
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <malloc.h>


#include "Crowd_Feature.h"


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

     Crowd_Feature::Crowd_Feature()

{
}


/********************************************************************/
/*								    */
/*		        ���������� ������			    */

    Crowd_Feature::~Crowd_Feature()

{
}


/********************************************************************/
/*								    */
/*		        ������� ������ �� ������		    */

    void Crowd_Feature::vReadSave(char *title, std::string *text, char *reference)

{
}


/********************************************************************/
/*								    */
/*		        �������� ������ � ������		    */

    void Crowd_Feature::vWriteSave(std::string *text)

{
     *text="" ;
}


/********************************************************************/
/*								    */
/*		      ���������� �������        		    */

    void Crowd_Feature::vFree(void)

{
}


/********************************************************************/
/*								    */
/*                     ������ ���������� � ��������   		    */

    void Crowd_Feature::vGetInfo(std::string *text)

{
        *text="" ;
}


/********************************************************************/
/*								    */
/*                     ������ � �����������           		    */

     int Crowd_Feature::vParameter(char *name, char *action, char *value)

{
   return(-1) ;
}


/********************************************************************/
/*								    */
/*       ����� ��������� �������� ������������������ ��������       */  

    int Crowd_Feature::vResetCheck(void *data)

{
   return(0) ;
}


/********************************************************************/
/*								    */
/*       ���������� � �������� ������������������ ��������          */  

    int Crowd_Feature::vPreCheck(void *data)

{
   return(0) ;
}


/********************************************************************/
/*								    */
/*                �������� ������������������ ��������              */  

    int Crowd_Feature::vCheck(void *data, Crowd_Objects_List *checked)

{
   return(0) ;
}


/********************************************************************/
/*								    */
/*                          �������� ����                           */

    void Crowd_Feature::vBodyAdd(char *body)
{
}


/********************************************************************/
/*								    */
/*                          ������� ����                            */

    void Crowd_Feature::vBodyDelete(char *body)
{
}


/********************************************************************/
/*								    */
/*                   ������� ������� ����� ����                     */

    void Crowd_Feature::vBodyBasePoint(   char *body,                   
                                        double  x, 
                                        double  y, 
                                        double  z )
{
}


/********************************************************************/
/*								    */
/*                     ������� ���������� ����                      */

    void Crowd_Feature::vBodyAngles(   char *body,                   
                                     double  azimuth, 
                                     double  tangage, 
                                     double  roll    )
{
}


/********************************************************************/
/*								    */
/*              ������� ������� ��������� ����                      */

    void Crowd_Feature::vBodyMatrix(   char *body,
                                     double  matrix[4][4] )
{
}


/********************************************************************/
/*								    */
/*           ������� �������� ��������� � ���������� ����           */

    void Crowd_Feature::vBodyShifts(   char *body,                   
                                     double  x, 
                                     double  y, 
                                     double  z, 
                                     double  azimuth, 
                                     double  tangage, 
                                     double  roll    )
{
}


/********************************************************************/
/*								    */
/*              ������� ������ ���������� ����                      */

    void Crowd_Feature::vBodyPars(char *body, struct Crowd_Parameter *)
{
}


