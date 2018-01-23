
#ifndef  CROWD_FEATURE_H 

#define  CROWD_FEATURE_H 

#include <string>

#ifdef CROWD_FEATURE_EXPORTS
#define CROWD_FEATURE_API __declspec(dllexport)
#else
#define CROWD_FEATURE_API __declspec(dllimport)
#endif

/*------------------------------- �������� ������ "�������� �������" */

    class CROWD_FEATURE_API Crowd_Feature {

    public:
                         char  Type[128] ;      /* ��� �������� */
           class Crowd_Object *Object ;         /* ������ �������������� */ 

    public:
               virtual void  vReadSave     (char *, std::string *,    /* ������� ������ �� ������ */
                                                           char * ) ;
               virtual void  vWriteSave    (std::string *) ;          /* �������� ������ � ������ */  
               virtual void  vFree         (void) ;                   /* ���������� ������� */  
               virtual void  vGetInfo      (std::string *) ;          /* ���������� � �������� */  

               virtual  int  vParameter    (char *, char *, char *) ; /* ������ � ����������� */  

               virtual  int  vResetCheck   (void *) ;                 /* ����� ��������� �������� ������������������ �������� */  
               virtual  int  vPreCheck     (void *) ;                 /* ���������� � �������� ������������������ �������� */  
               virtual  int  vCheck        (void *,                   /* �������� ������������������ �������� */  
                                            class Crowd_Objects_List *) ;
               virtual void  vBodyAdd      (char *) ;                 /* �������� ���� */
               virtual void  vBodyDelete   (char *) ;                 /* ������� ���� */
               virtual void  vBodyBasePoint(char *,                   /* ������� ������� ����� ���� */
                                             double, double, double) ;
               virtual void  vBodyAngles   (char *,                   /* ������� ���������� ���� */
                                             double, double, double) ;
               virtual void  vBodyMatrix   (char *, double[4][4]) ;   /* ������� ������� ��������� ���� */
               virtual void  vBodyShifts   (char *,                   /* ������� �������� ��������� �  */
                                             double, double, double,  /*    ���������� ����            */
                                             double, double, double ) ;
               virtual void  vBodyPars     (char *,                   /* ������� ������ ���������� */
                                             struct Crowd_Parameter *) ;

			     Crowd_Feature() ;                       /* ����������� */
			    ~Crowd_Feature() ;                       /* ���������� */
                                      } ;

/*-------------------------------------------------------------------*/

#endif        // CROWD_FEATURE_H 
