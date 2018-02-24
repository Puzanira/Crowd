
/********************************************************************/
/*								    */
/*		������ ������ "������������� ���� ���������"        */
/*								    */
/********************************************************************/

#ifdef T_RELAY_EXPORTS
#define T_RELAY_API __declspec(dllexport)
#else
#define T_RELAY_API __declspec(dllimport)
#endif


/*---------------------------------------------- ��������� ��������� */


/*------------------------------------ �������� �������� � ��������� */

     struct  Crowd_MQueue {
                       class Crowd_Message **messages ;
                                       int   cnt ;
                                       int   max ;
                          } ;

#define  _QUEUE_DEEP   10000

/*----------------------- �������� ������ ������ "����� �����������" */

  class T_RELAY_API Crowd_Module_Relay : public Crowd_Kernel {

    public:

     static
        struct Crowd_Module_Relay_instr *mInstrList ;                   /* ������ ������ */

     static               Crowd_MQueue  mQueue[_QUEUE_DEEP] ;           /* ������� ��������� */

     static                       HWND  mQueueDlg ;                     /* ���� ����������� ��������� ������� */
     static                       HWND  mDebugDlg ;                     /* ���� ������� */

    public:
     virtual         int  vGetParameter (char *, char *)   ;            /* �������� �������� */
     virtual         int  vExecuteCmd   (const char *) ;                /* ��������� ������� */
     virtual         int  vExecuteCmd   (const char *, Crowd_IFace *) ;
     virtual         int  vSpecial      (char *, void *, char *) ;      /* ����������� ��������� */
     virtual         int  vAddMessage   (Crowd_Message *, int) ;        /* ����������� ��������� � ������� */

    public:
                     int  cHelp         (char *, Crowd_IFace *) ;       /* ���������� HELP */
                     int  cPrepare      (char *, Crowd_IFace *) ;       /* ���������� PREPARE */
                     int  cQueue        (char *, Crowd_IFace *) ;       /* ���������� QUEUE */
                     int  cDebug        (char *, Crowd_IFace *) ;       /* ���������� DEBUG */
                     int  cRun          (char *, Crowd_IFace *) ;       /* ���������� RUN */

            Crowd_Object *FindObject    (char *) ;                      /* ����� ������� �� ����� */ 
           Crowd_Message *FindMessage   (char *) ;                      /* ����� ��������� �� ����� */ 

    public:
	                  Crowd_Module_Relay() ;               /* ����������� */
	                 ~Crowd_Module_Relay() ;               /* ���������� */
                                                             } ;

/*-------------------------------------------- ���������� ���������� */

 struct Crowd_Module_Relay_instr {

           char                      *name_full ;                        /* ������ ��� ������� */
           char                      *name_shrt ;                        /* �������� ��� ������� */
           char                      *help_row ;                         /* HELP - ������ */
           char                      *help_full ;                        /* HELP - ������ */
            int (Crowd_Module_Relay::*process)(char *, Crowd_IFace *) ;  /* ��������� ���������� ������� */
                              }  ;
/*--------------------------------------------- ���������� ��������� */

/* ����  T_Relay.cpp */

/* ����  T_Relay_dialog.cpp */
    BOOL CALLBACK  Task_Relay_Help_dialog (HWND, UINT, WPARAM, LPARAM) ;
    BOOL CALLBACK  Task_Relay_Queue_dialog(HWND, UINT, WPARAM, LPARAM) ;
    BOOL CALLBACK  Task_Relay_Debug_dialog(HWND, UINT, WPARAM, LPARAM) ;
