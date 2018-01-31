/********************************************************************/
/*								    */
/*                   ������ DCL-�����������        	            */
/*								    */
/********************************************************************/

#ifdef C_DCL_EXPORTS
#define C_DCL_API __declspec(dllexport)
#else
#define C_DCL_API __declspec(dllimport)
#endif


/*---------------------------------------------- ��������� ��������� */

/*----------------------------------------------- �������� ��������� */

 typedef struct {  
                    int  dummy ;
 
                }  Crowd_Calc_Dcl_context ;

/*------------------------- �������� ������ ������������ ����������� */

  class C_DCL_API Crowd_Calc_Dcl : public Crowd_Kernel {

    public:
     virtual         int  vCalculate   (char *, char *,         /* ��������� ��������� */                                       
                                        Crowd_Object *,
                                        struct Crowd_Event *,
                                        struct Crowd_Parameter *,
                                        struct Crowd_Parameter *,
                                        double *,
                                        void **, char *) ;

    public:

     virtual         int  vGetParameter(char *, char *) ;       /* �������� �������� */
     virtual        void  vStart       (void) ;                 /* ��������� �������� */

                    void  iDebug       (char *, char *, int) ;  /* ���������� ������ � ���� */ 
                    void  iDebug       (char *, char *) ;

	                  Crowd_Calc_Dcl() ;                     /* ����������� */
	                 ~Crowd_Calc_Dcl() ;                     /* ���������� */
                                                   } ;

/*---------------------------------------------------- ��������� �/� */

  void  Crowd_Calc_Dcl_text_norm(char *) ; /* ������������ ������ ��������� */
  char *Crowd_Calc_Dcl_get_text (void) ;   /* ��������� ���������� ������ ������ ����������� */
  char *Crowd_Calc_Dcl_error    (int) ;    /* ������ ������ ������ �� ���� */
  char *Crowd_Calc_Dcl_warning  (int) ;    /* ������ ������ �������������� �� ���� */
  void  Crowd_Calc_Dcl_debug    (int) ;    /* ��������� ������� ����������� */
