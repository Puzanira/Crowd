/*********************************************************************/
/*                                                                   */
/*               ������� ������������ ����������                     */
/*                                                                   */
/*********************************************************************/

#include "gl\gl.h"
#include "gl\glu.h"

/*--------------------------------------------- ��������� ���������� */

 typedef  struct {
                      char  name[256] ;
                      HWND  hWnd ;
                     HGLRC  hOpenGL ;               
                    double  Look_x ;
                    double  Look_y ;
                    double  Look_z ;
                    double  Look_azim ;
                    double  Look_elev ;
                    double  Look_roll ;
                    double  Range_strobe ;
                    double  Zoom ;
                      char  AtObject[256] ;

                 }  WndContext ;

/*-------------------------------------------------------- ��������� */

    int  CrowdRoot_show_init       (void) ;            /* ������������� ������� ����������� */
    int  CrowdRoot_show_getlist    (int) ;             /* �������������� ������ ����������� ������ */
   void  CrowdRoot_show_releaselist(int) ;             /* ������������ ������ ����������� ������ */
    int  CrowdRoot_first_context   (char *) ;          /* ���������� ������ �������� */
    int  CrowdRoot_next_context    (char *) ;          /* ���������� ��������� �������� */
   void  CrowdRoot_show_context    (char *) ;          /* ���������� ������� �������� */
 double  CrowdRoot_get_context     (char *) ;          /* ������ �������� ��������� */
   void  CrowdRoot_read_context    (std::string *) ;   /* ������� ��������� ��������� */
   void  CrowdRoot_write_context   (std::string *) ;   /* �������� ��������� ��������� */
    int  CrowdRoot_redraw          (char *) ;          /* ������������ ���� */
    int  CrowdRoot_look            (char *, char *,    /* ������ � ������ ������ ������ */
                                    double *, double *, double *,
                                    double *, double *, double * ) ;
    int  CrowdRoot_zoom            (char *, char *,    /* ������ � ����� ������ ������ */
                                          double * ) ;
    int  CrowdRoot_lookat          (char *, char *,    /* ������ � ������ ���������� ������ */ 
                                            char * ) ;
    int  CrowdRoot_lookat_point    (WndContext *) ;    /* ��������� ����� ���������� */

/*------------------------------------------------------ ����������� */

   LRESULT CALLBACK  CrowdRoot_show_prc(HWND, UINT, WPARAM, LPARAM) ;
