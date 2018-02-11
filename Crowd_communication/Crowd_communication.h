
#ifndef  CROWD_COMMUNICATION_H 

#define  CROWD_COMMUNICATION_H 

#include <string>

#ifdef CROWD_COMMUNICATION_EXPORTS
#define CROWD_COMMUNICATION_API __declspec(dllexport)
#else
#define CROWD_COMMUNICATION_API __declspec(dllimport)
#endif

/*---------------------------------- �������� ������ "����� �������" */

    class CROWD_COMMUNICATION_API Crowd_Communication {

    public:
                               char  Type[128] ;          /* ��� ����� */
                               char  Kind[64] ;           /* ��� ����� */
                 class Crowd_Object *Object_m ;           /* ������, �������� */ 
                 class Crowd_Object *Object_s ;           /* ������, ��������� */ 

                                int  Visible ;            /* ��������� */
                           COLORREF  Color ;              /* ���� */

    public:
               virtual void  vReadSave     (char *, std::string *,    /* ������� ������ �� ������ */
                                                           char * ) ;
               virtual void  vWriteSave    (std::string *) ;          /* �������� ������ � ������ */  
               virtual void  vFree         (void) ;                   /* ���������� ������� */  
               virtual void  vGetInfo      (std::string *) ;          /* ���������� � �������� */  

               virtual  int  vCheck        (void *,                   /* �������� ������������������ �������� */  
                                            class Crowd_Objects_List *) ;

			     Crowd_Communication() ;                  /* ����������� */
			    ~Crowd_Communication() ;                  /* ���������� */
                                      } ;

/*-------------------------------------------------------------------*/

#endif        // CROWD_FEATURE_H 
