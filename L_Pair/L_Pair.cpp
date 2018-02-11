/*********************************************************************/
/*								     */
/*		������ ���������� ������ "������ ������"             */
/*								     */
/*********************************************************************/


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

#include "gl\gl.h"
#include "gl\glu.h"

#include "..\Crowd_Communication\Crowd_Communication.h"
#include "..\Crowd_Object\Crowd_Object.h"
#include "..\Crowd_Kernel\Crowd_Kernel.h"

#include "L_Pair.h"

#pragma warning(disable : 4996)

#define  SEND_ERROR(text)    SendMessage(Crowd_Kernel::kernel_wnd, WM_USER,  \
                                         (WPARAM)_USER_ERROR_MESSAGE,        \
                                         (LPARAM) text)

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

/*********************************************************************/
/*								     */
/*		    	����������� ������                           */

     static   Crowd_Module_Pair  ProgramModule ;


/*********************************************************************/
/*								     */
/*		    	����������������� ����                       */

 L_PAIR_API char *Identify(void)

{
	return(ProgramModule.keyword) ;
}


 L_PAIR_API Crowd_Kernel *GetEntry(void)

{
	return(&ProgramModule) ;
}

/*********************************************************************/
/*********************************************************************/
/**							            **/
/**     �������� ������ ������ ���������� ������ "������ ������"    **/
/**							            **/
/*********************************************************************/
/*********************************************************************/

/*********************************************************************/
/*								     */
/*                            ������ ������                          */

  struct Crowd_Module_Pair_instr  Crowd_Module_Pair_InstrList[]={

 { "help",    "?", "#HELP   - ������ ��������� ������", 
                    NULL,
                   &Crowd_Module_Pair::cHelp       },
 { "kind",    "k", "#KIND   - ����������� ���� �����", 
                   " KIND <���>\n",
                   &Crowd_Module_Pair::cKind       },
 { "link",    "l", "#LINK   - ��������� �������", 
                   " LINK <��� 1> <��� 2> [<��� �����>] \n"
                   "   ��� ����� ������ ���� �������������� ��������������� �� ������� KIND\n",
                   &Crowd_Module_Pair::cLink       },
 { "color",   "c", "#COLOR   - ���������� ���� ����������� ���������� ����� ��� ���� �����", 
                   " COLOR <��� 1> <��� 2> <�������� �����>\n"
                   " COLOR <��� �����> <�������� �����>\n"
                   "   ���������� ���� ����� �� ��������: RED, GREEN, BLUE\n"
                   " COLOR <��� 1> <��� 2> RGB <R-������>:<G-������>:<B-������>\n"
                   " COLOR <��� �����> RGB <R-������>:<G-������>:<B-������>\n"
                   "   ���������� ���� ����� �� RGB-�����������\n",
                   &Crowd_Module_Pair::cColor      },
 {  NULL }
                                                            } ;


/*********************************************************************/
/*								     */
/*		     ����� ����� ������             		     */

          struct Crowd_Module_Pair_instr *Crowd_Module_Pair::mInstrList=NULL ;

    struct Crowd_Communication_Pair_Kind  Crowd_Module_Pair::mKinds[_PAIR_KIND_MAX] ;
                                     int  Crowd_Module_Pair::mKinds_cnt ;

/*********************************************************************/
/*								     */
/*		       ����������� ������			     */

     Crowd_Module_Pair::Crowd_Module_Pair(void)

{
	   keyword="Crowd" ;
    identification="Pair" ;
          category="Communication" ;

        mInstrList=Crowd_Module_Pair_InstrList ;

        mShow_dlist=0 ;
}


/*********************************************************************/
/*								     */
/*		        ���������� ������			     */

    Crowd_Module_Pair::~Crowd_Module_Pair(void)

{
}


/********************************************************************/
/*								    */
/*		        �������� ��������       		    */

     int  Crowd_Module_Pair::vGetParameter(char *name, char *value)

{
/*-------------------------------------------------- �������� ������ */

    if(!stricmp(name, "$$MODULE_NAME")) {

         sprintf(value, "%-20.20s -  ���������� ������ '������ ������'", identification) ;
                                        }
/*-------------------------------------------------------------------*/

   return(0) ;
}


/*********************************************************************/
/* 								     */
/*		        ��������� ��������                           */

    void  Crowd_Module_Pair::vStart(void)

{
}


/*********************************************************************/
/*								     */
/*		        ������� ��������                	     */

    Crowd_Communication *Crowd_Module_Pair::vCreateCommunication(Crowd_Object        *object_m,
                                                                 Crowd_Object        *object_s,
                                                                 Crowd_Communication *link_ext)

{
  Crowd_Communication *link ;


    if(link_ext!=NULL)  link= link_ext ;
    else                link=new Crowd_Communication_Pair ;

         link->Object_m=object_m ;
         link->Object_s=object_s ;

  return(link) ;
}


/********************************************************************/
/*								    */
/*                    ���������� ��������� ������                   */

    void  Crowd_Module_Pair::vShow(char *layer)

{
   if(!stricmp(layer, "SCENE"))  this->iShowScene() ;
}


/*********************************************************************/
/*								     */
/*		        ��������� �������       		     */

  int  Crowd_Module_Pair::vExecuteCmd(const char *cmd)

{
  static  int  direct_command ;   /* ���� ������ ������ ������� */
         char  command[1024] ;
         char *instr ;
         char *end ;
          int  status ;
          int  i ;

#define  _SECTION_FULL_NAME   "PAIR"
#define  _SECTION_SHRT_NAME   "PAIR"

/*--------------------------------------------- ������������� ������ */

             memset(command, 0, sizeof(command)) ;
            strncpy(command, cmd, sizeof(command)-1) ;

   if(!direct_command) {
         end=strchr(command, ' ') ;
      if(end!=NULL) {  *end=0 ;  end++ ;  }

      if(stricmp(command, _SECTION_FULL_NAME) &&
         stricmp(command, _SECTION_SHRT_NAME)   )  return(1) ;
                       }
   else                {
                             end=command ;
                       }
/*----------------------- ���������/���������� ������ ������ ������� */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - -  ��������� */
   if(end==NULL || end[0]==0) {
     if(!direct_command) {
                            direct_command=1 ;

        SendMessage(this->kernel_wnd, WM_USER,
                     (WPARAM)_USER_COMMAND_PREFIX, (LPARAM)"Pair communication:") ;
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
         end=strchr(instr, ' ') ;
      if(end!=NULL) {  *end=0 ;  end++ ;  }
      else              end="" ;

   for(i=0 ; mInstrList[i].name_full!=NULL ; i++)                   /* ���� ������� � ������ */
     if(!stricmp(instr, mInstrList[i].name_full) ||
        !stricmp(instr, mInstrList[i].name_shrt)   )   break ;

     if(mInstrList[i].name_full==NULL) {                            /* ���� ����� ������� ���... */

          status=this->kernel->vExecuteCmd(cmd) ;                   /*  �������� �������� ������ ����... */
       if(status)  SEND_ERROR("������ PAIR: ����������� �������") ;
                                            return(0) ;
                                       }
 
     if(mInstrList[i].process!=NULL)                                /* ���������� ������� */
                status=(this->*mInstrList[i].process)(end) ;
     else       status=  0 ;

/*-------------------------------------------------------------------*/

   return(status) ;
}


/********************************************************************/
/*								    */
/*		        �������� ������ � ������		    */

    void  Crowd_Module_Pair::vWriteSave(std::string *text)

{

/*----------------------------------------------- ��������� �������� */

     *text="#BEGIN MODULE PAIR\n" ;

/*------------------------------------------------ �������� �������� */

     *text+="#END\n" ;

/*-------------------------------------------------------------------*/
}


/********************************************************************/
/*								    */
/*		      ���������� ���������� Help                    */

  int  Crowd_Module_Pair::cHelp(char *cmd)

{ 
    DialogBoxIndirect(GetModuleHandle(NULL),
			(LPCDLGTEMPLATE)Resource("IDD_HELP", RT_DIALOG),
			   GetActiveWindow(), Communication_Pair_Help_dialog) ;

   return(0) ;
}


/********************************************************************/
/*								    */
/*		      ���������� ���������� KIND                    */
/*								    */
/*        KIND <��� �����>                                          */

  int  Crowd_Module_Pair::cKind(char *cmd)

{
#define   _PARS_MAX  10

                char  *pars[_PARS_MAX] ;
                char  *name ;
                char  *end ;
                 int   i ;

/*---------------------------------------- �������� ��������� ������ */
/*- - - - - - - - - - - - - - - - - - -  ��������� ������ ���������� */
/*- - - - - - - - - - - - - - - - - - - - - - - -  ������ ���������� */        
    for(i=0 ; i<_PARS_MAX ; i++)  pars[i]=NULL ;

    for(end=cmd, i=0 ; i<_PARS_MAX ; end++, i++) {
      
                pars[i]=end ;
                   end =strchr(pars[i], ' ') ;
                if(end==NULL)  break ;
                  *end=0 ;
                                                 }

                     name= pars[0] ;

/*---------------------------------------- �������� ����� ���� ����� */

    if(name==NULL) {                                                /* ���� ��� �� ������... */
                      SEND_ERROR("������ ���� ������ ��� ���� �����. \n"
                                 "��������: KIND <��� ����>") ;
                                     return(-1) ;
                   }

    for(i=0 ; i<_PAIR_KIND_MAX ; i++) {
      if(         mKinds[i].name[0]==0 )  break ;
      if(!stricmp(mKinds[i].name, name)) {
                                           SEND_ERROR("����� ��� ����� ��� ����������") ;
                                                 return(-1) ;
                                         }
                                      }

      if(i>=_PAIR_KIND_MAX) {
                                SEND_ERROR("������ ����� ������ ���������� (50 ��������)") ;
                                      return(-1) ;
                            }
/*------------------------------------------- ����������� ���� ����� */

       strncpy(mKinds[i].name, name, sizeof(mKinds[i].name)) ;
               mKinds[i].color=RGB(0,0,0) ;

/*-------------------------------------------------------------------*/

#undef   _PARS_MAX    

   return(0) ;
}


/********************************************************************/
/*								    */
/*		      ���������� ���������� LINK                    */
/*								    */
/*        LINK <��� 1> <��� 2>                                      */

  int  Crowd_Module_Pair::cLink(char *cmd)

{
#define   _PARS_MAX  10

                          char *pars[_PARS_MAX] ;
                          char *name_1 ;
                          char *name_2 ;
                          char *kind_name ;
                  Crowd_Object *object_1 ;
                  Crowd_Object *object_2 ;
      Crowd_Communication_Pair *link ;
 Crowd_Communication_Pair_Kind *kind ;
                          char *end ;
                           int   i ;

/*---------------------------------------- �������� ��������� ������ */
/*- - - - - - - - - - - - - - - - - - -  ��������� ������ ���������� */
/*- - - - - - - - - - - - - - - - - - - - - - - -  ������ ���������� */        
    for(i=0 ; i<_PARS_MAX ; i++)  pars[i]=NULL ;

    for(end=cmd, i=0 ; i<_PARS_MAX ; end++, i++) {
      
                pars[i]=end ;
                   end =strchr(pars[i], ' ') ;
                if(end==NULL)  break ;
                  *end=0 ;
                                                 }

                     name_1   = pars[0] ;
                     name_2   = pars[1] ;
                     kind_name= pars[2] ;

/*------------------------------------------- �������� ����� ������� */

    if(name_2==NULL) {                                              /* ���� ��� �� ������... */
                      SEND_ERROR("������ ���� ������ 2 ����� ��������. \n"
                                 "��������: LINK <��� 1> <��� 2>") ;
                                     return(-1) ;
                     }

       object_1=FindObject(name_1) ;                                /* ���� ������� �� ����� */
    if(object_1==NULL)  return(-1) ;
       object_2=FindObject(name_2) ;                                /* ���� ������� �� ����� */
    if(object_2==NULL)  return(-1) ;

/*---------------------------------------- �������� ����� ���� ����� */

                            kind=NULL ;

   if(kind_name!=NULL) {

        for(i=0 ; i<_PAIR_KIND_MAX ; i++) 
          if(!stricmp(mKinds[i].name, kind_name))  break ; 

          if(i>=_PAIR_KIND_MAX) {
                                   SEND_ERROR("����������� ��� �����. ����������� ������� KIND ��� ����������� ������ ���� �����.") ;
                                           return(-1) ;
                                }

                            kind=&mKinds[i] ;
                       }
/*--------------------------------------------------- �������� ����� */

      object_1->Communications=(Crowd_Communication **)
                                 realloc(object_1->Communications, 
                                         sizeof(object_1->Communications)*(object_1->Communications_cnt+1)) ;

                            link=(Crowd_Communication_Pair *)ProgramModule.vCreateCommunication(object_1, object_2, NULL) ;
   if(kind!=NULL) {
                     strcpy(link->Kind, kind->name) ;
                            link->Color=kind->color ;
                  }

      object_1->Communications[object_1->Communications_cnt]=link ;
                               object_1->Communications_cnt++ ;

      object_2->Communications=(Crowd_Communication **)
                                 realloc(object_2->Communications, 
                                         sizeof(object_2->Communications)*(object_2->Communications_cnt+1)) ;

                            link=(Crowd_Communication_Pair *)ProgramModule.vCreateCommunication(object_1, object_2, NULL) ;
   if(kind!=NULL) {
                     strcpy(link->Kind, kind->name) ;
                            link->Color=kind->color ;
                  }

      object_2->Communications[object_2->Communications_cnt]=link ;
                               object_2->Communications_cnt++ ;

/*------------------------------------------------------ ����������� */

                      this->kernel->vShow(NULL) ;

/*-------------------------------------------------------------------*/

#undef   _PARS_MAX    

   return(0) ;
}


/********************************************************************/
/*								    */
/*                   ���������� ���������� Color                    */
/*       COLOR  <���> <�������� �����>                              */
/*       COLOR  <���> RGB <R-������>:<G-������>:<B-������>          */

  int  Crowd_Module_Pair::cColor(char *cmd)

{ 
#define   _PARS_MAX   10
                          char *pars[_PARS_MAX] ;
                          char  *name_1 ;
                          char  *name_2 ;
                          char  *rgb ;
 Crowd_Communication_Pair_Kind *kind ;
                  Crowd_Object  *object_1 ;
                  Crowd_Object  *object_2 ;
                      COLORREF  color ;
                           int  red, green, blue ;
                          char *end ;
                          char  text[1024] ;
                           int  n ;
                           int  i ;

/*------------------------------------------------ ������ ���������� */        

    for(i=0 ; i<_PARS_MAX ; i++)  pars[i]=NULL ;

    for(end=cmd, i=0 ; i<_PARS_MAX ; end++, i++) {
      
                pars[i]=end ;
                   end =strchr(pars[i], ' ') ;
                if(end==NULL)  break ;
                  *end=0 ;
                                                 }

                     name_1= pars[0] ;
                     name_2= pars[1] ;
                      rgb  = pars[2] ;

     if(name_1==NULL) {
                         SEND_ERROR("������ ���� ������ ����� ��������� �������� ��� ��� �����. \n"
                                    " COLOR <���_������� 1> <���_������� 2> GREEN\n"
                                    " COLOR <��� �����> GREEN") ;
                                        return(-1) ;
                      }
/*-------------------------------------------- �������� �� ��� ����� */

                            kind=NULL ;

        for(i=0 ; i<_PAIR_KIND_MAX ; i++) 
          if(!stricmp(mKinds[i].name, name_1))  break ; 

          if(i<_PAIR_KIND_MAX) {
                                   kind=&mKinds[i] ;                                  
                                    rgb= name_2 ;
                               }
/*----------------------------------------------------- ������ ����� */

     if(rgb==NULL) {
                         SEND_ERROR("������ ���� ����. \n"
                                    " COLOR <���_������� 1> <���_������� 2> GREEN\n"
                                    " COLOR <��� �����> GREEN") ;
                                        return(-1) ;
                   } 

              if(!stricmp(rgb, "RED"  ))  color=RGB(255,   0,   0) ;
         else if(!stricmp(rgb, "GREEN"))  color=RGB(  0, 255,   0) ;
         else if(!stricmp(rgb, "BLUE" ))  color=RGB(  0,   0, 255) ;
         else if(!stricmp(rgb, "WHITE"))  color=RGB(255, 255, 255) ;
         else if(!stricmp(rgb, "RGB"  )) {

                 if(pars[3]!=NULL) {
                                       green=0 ;
                                        blue=0 ;
                                         red=strtoul(pars[3], &end, 10) ;
                         if(*end==':') green=strtoul(end+1  , &end, 10) ;
                         if(*end==':')  blue=strtoul(end+1  , &end, 10) ;

                                       color=RGB(red, green, blue) ;                                          
                                   }
                                             } 
         else                                {
                         SEND_ERROR("����������� �������� �����") ;
                                        return(-1) ;
                                             }
/*------------------------------------------- �������� ��� �������� */

  if(kind==NULL) {                                                  /* ���� ��� �� ��� �����... */

       object_1=FindObject(name_1) ;                                /* ���� ������� �� ����� */
    if(object_1==NULL)  return(-1) ;
       object_2=FindObject(name_2) ;
    if(object_2==NULL)  return(-1) ;

                 }
/*------------------------------------------- ������� ����� �� ����� */
/*- - - - - - - - - - - - - - - - - - - - - - -  ���� ��� ���� ����� */
   if(kind!=NULL) {                                                 /* ���� ��� �� ��� �����... */
                        kind->color=color ;

#define   OBJECTS       this->kernel->kernel_objects 
#define   OBJECTS_CNT   this->kernel->kernel_objects_cnt 

#define   LINK          OBJECTS[n]->Communications[i]

       for(n=0 ; n<OBJECTS_CNT ; n++)                               /* ������ ���� �� ���� ������ ������� ���� */
        for(i=0 ; i<OBJECTS[n]->Communications_cnt ; i++)
          if(!stricmp(LINK->Type, "Pair"    ) &&
             !stricmp(LINK->Kind, kind->name)   )  LINK->Color=color ;
       
#undef   LINK

#undef   OBJECTS
#undef   OBJECTS_CNT

                  }
/*- - - - - - - - - - - - - - - - - - - - - - -  ���� ��� ���� ����� */
   else           {

#define  LINK   object_1->Communications[i]

    for(i=0 ; i<object_1->Communications_cnt ; i++) 
      if(!stricmp(LINK->Type, "Pair"))  
       if(LINK->Object_m==object_2 ||
          LINK->Object_s==object_2   ) {  LINK->Color=color ;  break ;  }

      if(i>=object_1->Communications_cnt) {
                            sprintf(text, "������ ����� � ������� %s �� �������", name_1) ;
                         SEND_ERROR(text) ;
                              return(-1) ;
                                          }

#undef   LINK

#define  LINK   object_2->Communications[i]

    for(i=0 ; i<object_2->Communications_cnt ; i++) 
      if(!stricmp(LINK->Type, "Pair"))  
       if(LINK->Object_m==object_1 ||
          LINK->Object_s==object_1   ) {  LINK->Color=color ;  break ;  }

      if(i>=object_2->Communications_cnt) {
                            sprintf(text, "������ ����� � ������� %s �� �������", name_2) ;
                         SEND_ERROR(text) ;
                              return(-1) ;
                                          }

#undef   LINK
                  }

/*------------------------------------------------------ ����������� */

                      this->kernel->vShow(NULL) ;

/*-------------------------------------------------------------------*/

#undef   _PARS_MAX

   return(0) ;
}


/********************************************************************/
/*								    */
/*		   ����� ������� �� �����                           */

  Crowd_Object *Crowd_Module_Pair::FindObject(char *name)

{
     char   text[1024] ;
      int   i ;

#define   OBJECTS       this->kernel->kernel_objects 
#define   OBJECTS_CNT   this->kernel->kernel_objects_cnt 

/*------------------------------------------- ����� ������� �� ����� */ 

       for(i=0 ; i<OBJECTS_CNT ; i++)                               /* ���� ������ �� ����� */
         if(!stricmp(OBJECTS[i]->Name, name))  break ;

    if(i==OBJECTS_CNT) {                                            /* ���� ��� �� �������... */
                           sprintf(text, "������� � ������ '%s' "
                                         "�� ����������", name) ;
                        SEND_ERROR(text) ;
                            return(NULL) ;
                       }
/*-------------------------------------------- �������� ���� ������� */ 

/*-------------------------------------------------------------------*/ 

   return((Crowd_Object *)OBJECTS[i]) ;
  
#undef   OBJECTS
#undef   OBJECTS_CNT

}


/********************************************************************/
/*								    */
/*                   ����������� �����                              */

  int  Crowd_Module_Pair::iShowScene(void)

{ 
  int  status ;
  int  i ;
  int  j ;
  
#define   OBJECTS       Crowd_Kernel::kernel->kernel_objects 
#define   OBJECTS_CNT   Crowd_Kernel::kernel->kernel_objects_cnt 

/*-------------------------------- �������������� ����������� ������ */

     if(mShow_dlist==0) {
           mShow_dlist=Crowd_Kernel::display.GetList(2) ;
                        }

     if(mShow_dlist==0)  return(0) ;

/*---------------------------------- ���������� ����������� �������� */

#define  LINK   OBJECTS[i]->Communications[j]

          status=Crowd_Kernel::display.SetFirstContext("Show") ;
    while(status==0) {

             glNewList(mShow_dlist, GL_COMPILE) ;                   /* �������� ������ */
          glMatrixMode(GL_MODELVIEW) ;

       for(i=0 ; i<OBJECTS_CNT ; i++)
        for(j=0 ; j<OBJECTS[i]->Communications_cnt ; j++) {

          if(LINK->Object_m>LINK->Object_s)  continue ;

             glColor4d(GetRValue(LINK->Color)/256., 
                       GetGValue(LINK->Color)/256.,
                       GetBValue(LINK->Color)/256., 1.) ;

               glBegin(GL_LINES) ;
            glVertex3d(LINK->Object_m->x_base, LINK->Object_m->y_base, LINK->Object_m->z_base) ;
            glVertex3d(LINK->Object_s->x_base, LINK->Object_s->y_base, LINK->Object_s->z_base) ;
                 glEnd();
                                                          }

             glEndList() ;                                          /* �������� ������ */

          status=Crowd_Kernel::display.SetNextContext("Show") ;
                     }

#undef  LINK

/*-------------------------------------------------------------------*/

#undef    OBJECTS
#undef    OBJECTS_CNT

   return(0) ;
}


/********************************************************************/
/********************************************************************/
/**							           **/
/**           �������� ������ ����� "������ ������"                **/
/**							           **/
/********************************************************************/
/********************************************************************/

/********************************************************************/
/*								    */
/*		       ����������� ������			    */

     Crowd_Communication_Pair::Crowd_Communication_Pair(void)

{
   strcpy(Type, "Pair") ;
   strcpy(Kind, "") ;

      Color=RGB(0, 0, 0) ;
}


/********************************************************************/
/*								    */
/*		        ���������� ������			    */

    Crowd_Communication_Pair::~Crowd_Communication_Pair(void)

{
}


/********************************************************************/
/*								    */
/*		        ������� ������ �� ������		    */

    void  Crowd_Communication_Pair::vReadSave(       char *title,  
                                              std::string *data, 
                                                     char *reference)

{
/*----------------------------------------------- �������� ��������� */

       if(stricmp(title, "COMMUNICATION PAIR"))  return ;

/*-------------------------------------------------------------------*/

}


/********************************************************************/
/*								    */
/*                     ������ ���������� � �����   		    */

    void Crowd_Communication_Pair::vGetInfo(std::string *text)

{
//        *text="Show: Yes\r\n" ;
}


/********************************************************************/
/*								    */
/*                     ������ � �����������           		    */

     int Crowd_Communication_Pair::vParameter(char *name, char *action, char *value)

{
/*------------------------------------------------- ������� �������� */

    if(name  ==NULL)  return(-1) ;
    if(action==NULL)  return(-2) ;

/*-------------------------------------------------------------------*/

   return(-1) ;
}


/********************************************************************/
/*								    */
/*                       �������� ����� � �����                     */

    void  Crowd_Communication_Pair::Show(void)

{
}
