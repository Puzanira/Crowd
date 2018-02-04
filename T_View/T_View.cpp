/********************************************************************/
/*								    */
/*		������ ������ "����� �����������"    		    */
/*								    */
/********************************************************************/

#pragma warning( disable : 4996 )
#define  stricmp  _stricmp

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <malloc.h>
#include <io.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys\stat.h>

#include "..\Matrix\Matrix.h"

#include "..\Crowd_Feature\Crowd_Feature.h"
#include "..\Crowd_Object\Crowd_Object.h"
#include "..\Crowd_Kernel\Crowd_Kernel.h"

#include "T_View.h"


#define  _SECTION_FULL_NAME   "VIEW"
#define  _SECTION_SHRT_NAME   "VIEW"

#define  SEND_ERROR(text)    SendMessage(Crowd_Kernel::kernel_wnd, WM_USER,  \
                                         (WPARAM)_USER_ERROR_MESSAGE,        \
                                         (LPARAM) text)

#define  CREATE_DIALOG  CreateDialogIndirectParam


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
/*		    	����������� ������                          */

     static   Crowd_Module_View  ProgramModule ;


/********************************************************************/
/*								    */
/*		    	����������������� ����                      */

 T_VIEW_API char *Identify(void)

{
	return(ProgramModule.keyword) ;
}


 T_VIEW_API Crowd_Kernel *GetEntry(void)

{
	return(&ProgramModule) ;
}

/********************************************************************/
/********************************************************************/
/**							           **/
/**	       �������� ������ ������ "����� �����������"          **/
/**							           **/
/********************************************************************/
/********************************************************************/

/********************************************************************/
/*								    */
/*                            ������ ������                         */

  struct Crowd_Module_View_instr  Crowd_Module_View_InstrList[]={

 { "help",       "?",  "#HELP (?) - ������ ��������� ������", 
                        NULL,
                       &Crowd_Module_View::cHelp   },
 { "ring",       "r",  "#RING (R) - ���������� ������� �� �����", 
                        NULL,
                       &Crowd_Module_View::cRing  },
 {  NULL }
                                                              } ;


/********************************************************************/
/*								    */
/*		     ����� ����� ������             		    */

    struct Crowd_Module_View_instr *Crowd_Module_View::mInstrList       =NULL ;


/********************************************************************/
/*								    */
/*		       ����������� ������			    */

     Crowd_Module_View::Crowd_Module_View(void)

{
                keyword="Crowd" ;
         identification="View" ;
               category="Task" ;

             mInstrList=Crowd_Module_View_InstrList ;
}


/********************************************************************/
/*								    */
/*		        ���������� ������			    */

    Crowd_Module_View::~Crowd_Module_View(void)

{
}


/********************************************************************/
/*								    */
/*		        �������� ��������       		    */

     int  Crowd_Module_View::vGetParameter(char *name, char *value)

{
/*-------------------------------------------------- �������� ������ */

    if(!stricmp(name, "$$MODULE_NAME")) {

         sprintf(value, "%-20.20s -  ����� �����������", identification) ;
                                        }
/*-------------------------------------------------------------------*/

   return(0) ;
}


/********************************************************************/
/*								    */
/*		        ��������� �������       		    */

  int  Crowd_Module_View::vExecuteCmd(const char *cmd)

{
   return( vExecuteCmd(cmd, NULL) ) ;
}


  int  Crowd_Module_View::vExecuteCmd(const char *cmd, Crowd_IFace *iface)

{
  static  int  direct_command ;   /* ���� ������ ������ ������� */
         char  command[1024] ;
         char *instr ;
         char *end ;
          int  status ;
          int  i ;

/*--------------------------------------------- ������������� ������ */

             memset(command, 0, sizeof(command)) ;
            strncpy(command, cmd, sizeof(command)-1) ;
/*- - - - - - - - - - - - - - - - - - - -  ��������� �������� ������ */
        if(command[0]=='&') {
                                end=command+1 ;
                            }
/*- - - - - - - - - - - - - - - - - - - - -  ��������� ������ ������ */
   else if(!direct_command) {

         end=strchr(command, ' ') ;
      if(end!=NULL) {  *end=0 ;  end++ ;  }

      if(stricmp(command, _SECTION_FULL_NAME) &&
         stricmp(command, _SECTION_SHRT_NAME)   )  return(1) ;
                            }
/*- - - - - - - - - - - - - - - - - - - -  ��������� �������� ������ */
   else                     {
                                end=command ;
                            }
/*----------------------- ���������/���������� ������ ������ ������� */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - -  ��������� */
   if(end==NULL || end[0]==0) {
     if(!direct_command) {
                            direct_command=1 ;

        SendMessage(this->kernel_wnd, WM_USER,
                     (WPARAM)_USER_COMMAND_PREFIX, (LPARAM)"Task View:") ;
        SendMessage(this->kernel_wnd, WM_USER,
                     (WPARAM)_USER_DIRECT_COMMAND, (LPARAM)identification) ;
                         }
                                    return(0) ;
                              }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - ���������� */
   if(end!=NULL && !strcmp(end, "..")) {

                            direct_command=0 ;

        SendMessage(this->kernel_wnd, WM_USER,
                     (WPARAM)_USER_COMMAND_PREFIX, (LPARAM)"") ;
        SendMessage(this->kernel_wnd, WM_USER,
                     (WPARAM)_USER_DIRECT_COMMAND, (LPARAM)"") ;

                                           return(0) ;
                                       }
/*--------------------------------------------- ��������� ���������� */

       instr=end ;                                                  /* �������� ����� � ��������� ������� */

     for(end=instr ; *end!= 0  &&
                     *end!=' ' &&
                     *end!='>' &&
                     *end!='.' &&
                     *end!='/'    ; end++) ;

      if(*end!= 0 &&
         *end!=' '  )  memmove(end+1, end, strlen(end)+1) ;

      if(*end!=0) {  *end=0 ;  end++ ;  }
      else            end="" ;

   for(i=0 ; mInstrList[i].name_full!=NULL ; i++)                   /* ���� ������� � ������ */
     if(!stricmp(instr, mInstrList[i].name_full) ||
        !stricmp(instr, mInstrList[i].name_shrt)   )   break ;

     if(mInstrList[i].name_full==NULL) {                            /* ���� ����� ������� ���... */

          status=this->kernel->vExecuteCmd(cmd, iface) ;            /*  �������� �������� ������ ����... */
       if(status)  SEND_ERROR("������ VIEW: ����������� �������") ;
                                            return(-1) ;
                                       }
 
     if(mInstrList[i].process!=NULL)                                /* ���������� ������� */
                status=(this->*mInstrList[i].process)(end, iface) ;
     else       status=  0 ;

/*-------------------------------------------------------------------*/

   return(status) ;
}


/********************************************************************/
/*								    */
/*		      ���������� ���������� HELP                    */

  int  Crowd_Module_View::cHelp(char *cmd, Crowd_IFace *iface)

{ 
    DialogBoxIndirect(GetModuleHandle(NULL),
			(LPCDLGTEMPLATE)Resource("IDD_HELP", RT_DIALOG),
			   GetActiveWindow(), Task_View_Help_dialog) ;

   return(0) ;
}


/********************************************************************/
/*								    */
/*		      ���������� ���������� RING                    */
/*								    */
/*       RING                                                       */

  int  Crowd_Module_View::cRing(char *cmd, Crowd_IFace *iface)

{
  double  rad ;
  double  angle ;
    char  text[1024] ;
     int  i ;

#define   OBJECTS       Crowd_Kernel::kernel->kernel_objects
#define   OBJECTS_CNT   Crowd_Kernel::kernel->kernel_objects_cnt

/*----------------------------- ����������� ���������� ������������� */

         if(OBJECTS_CNT==0)  return(0) ;

             angle=6.283/(double)OBJECTS_CNT ;
               rad=(OBJECTS_CNT*1.0)/6.283  ;

/*--------------------------------------------- ����������� �������� */

    if(OBJECTS_CNT==1) {
                          OBJECTS[0]->x_base=0. ;
                          OBJECTS[0]->y_base=0. ;
                          OBJECTS[0]->z_base=0. ;
                               return(0) ;
                       }

       for(i=0 ; i<OBJECTS_CNT ; i++) {

            OBJECTS[i]->x_base=rad*cos(angle*i) ;
            OBJECTS[i]->y_base=rad*sin(angle*i) ;
            OBJECTS[i]->z_base=0. ;

            OBJECTS[i]->vCalculateShow() ;

                                      }
/*------------------------------------------------------ ����������� */

                                 sprintf(text, "zoom %lf", rad*2.+0.5) ;
       Crowd_Kernel::kernel->vExecuteCmd(text) ;

                       this->kernel->vShow(NULL) ;

/*-------------------------------------------------------------------*/

#undef    OBJECTS
#undef    OBJECTS_CNT

   return(0) ;
}
