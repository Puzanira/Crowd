/********************************************************************/
/*								    */
/*		������ ������������ �����������        	            */
/*								    */
/********************************************************************/

#ifdef C_STD_EXPORTS
#define C_STD_API __declspec(dllexport)
#else
#define C_STD_API __declspec(dllimport)
#endif


/*---------------------------------------------- ��������� ��������� */

/*----------------------------------------------- �������� ��������� */

 typedef struct {  
                   struct L_module  module_decl ; 

                               int  compiled ;
 
                }  Crowd_Calc_Std_context ;

/*------------------------- �������� ������ ������������ ����������� */

  class C_STD_API Crowd_Calc_Std : public Crowd_Kernel {

    public:
     virtual         int  vCalculate   (char *, char *,         /* ��������� ��������� */                                       
                                        struct Crowd_Parameter *,
                                        struct Crowd_Parameter *,
                                        double *,
                                        void **, char *) ;

    public:

     virtual         int  vGetParameter(char *, char *) ;       /* �������� �������� */
     virtual        void  vStart       (void) ;                 /* ��������� �������� */

                    void  iDebug       (char *, char *, int) ;  /* ���������� ������ � ���� */ 
                    void  iDebug       (char *, char *) ;

	                  Crowd_Calc_Std() ;                     /* ����������� */
	                 ~Crowd_Calc_Std() ;                     /* ���������� */
                                                   } ;

/*---------------------------------------------------- ��������� �/� */

  void  Crowd_Calc_Std_text_norm(char *) ; /* ������������ ������ ��������� */
  char *Crowd_Calc_Std_get_text (void) ;   /* ��������� ���������� ������ ������ ����������� */
  char *Crowd_Calc_Std_error    (int) ;    /* ������ ������ ������ �� ���� */
  char *Crowd_Calc_Std_warning  (int) ;    /* ������ ������ �������������� �� ���� */
  void  Crowd_Calc_Std_debug    (int) ;    /* ��������� ������� ����������� */
