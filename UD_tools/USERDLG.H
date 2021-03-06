/*********************************************************************/
/*                                                                   */
/*               ������� ������������ ����������                     */
/*                                                                   */
/*********************************************************************/

/*------------------------------------------------- ����������� ���� */

typedef  int (CALLBACK *UD_CALLBACK)(int, int, void *) ;

  #define  _UD_ZOOM             1
//#define  _UD_SCANNER_MOVE     2   /* ���������� � ���� �� ������ */
//#define  _UD_SCANNER_CLEAR    3   /* ���������� � ���� �� ������ */
  #define  _UD_PROFILE          4

/*---------------------------------------------- ��������� ��������� */

  struct UD_metrics {                     /* ����������� �������� */ 
                      int  zoom_flag ;     /* ���� ����������� ���� */
                      int  zoom_num ;      /* ����� ����������� ���� */

                      int  x_base ;        /* ��������� ���� �������� */
                      int  y_base ;
                      int  x_size ;        /* ������� ���� �������� */
                      int  y_size ;

                      int  draw_x_base ;   /* ��������� ���� ��������� */
                      int  draw_y_base ;
                      int  draw_x_size ;   /* ������� ���� ��������� */
                      int  draw_y_size ;

                      int  x_scale_h ;     /* ������ ���� ��������� �� X */
                      int  y_scale_w ;     /* ������ ���� ��������� �� Y */

                      int  stream_base ;   /* ������� ����� (����� � ������) */
                   double  x_base_min ;    /* ��������� ���� �������� ������� */
		   double  x_base_max ;
		   double  y_base_min ;
		   double  y_base_max ;

               TEXTMETRIC  font ;          /* ��������� ������ */     
                    } ;

 struct UD_value_zone {                    /* �������� ���� ������ */
                        double  value ;     /* �������� */
			  char  buff[64] ;  /* ����� ������ */
			   int  len  ;      /* ����� ����� */
			   int  digits ;    /* ����� ���� + ������� */
			   int  point ;     /* ����� ������ ����� ������� */
			   int  power ;     /* ����� ������� */
			   int  pos  ;      /* ���������� */
		      } ;

/*--------------------------------------------------- ����� �������� */

  struct UD_zoom_scale {                         /* ���������� ���� - "������" */
                          HWND  hWnd ;          
                           HDC  hDC ;
                       HBITMAP  hBitMap ;  

             struct UD_metrics  metrics ;         /* ������� ����������� */      

		        double  x_min ;           /* ��������� "�������" �� ���� */
		        double  x_max ;
		        double  y_min ;
		        double  y_max ;
		        double  x_min_prv ;       /* ��������� "�������" �� ����, ���������� */
		        double  x_max_prv ;
		        double  y_min_prv ;
		        double  y_max_prv ;
                       } ;

  struct UD_data_scale {                         /* ������� ����������� ������ */
			   int  scale_regime ;    /* ����������� ������ */
#define                          _UD_X_SCALE   1
#define                          _UD_Y_SCALE   2
		        double  x_min ;           /* ��������� �� ���� */
		        double  x_max ;
		        double  y_min ;
		        double  y_max ;
		       } ;

  struct UD_color_range {                         /* ������� ��������� */
                           COLORREF  color ;       /* ���� */
		             double  value ;       /* �������� */
		                int  use ;         /* ���� ������������� */
		        } ;
/*---------------------------------------------------------- ������� */

     struct UD_profile {                         /* ������� */
		        double  x_1 ;             /* ����� ������� */
		        double  y_1 ;
		        double  x_2 ;             
		        double  y_2 ;
       struct UD_profile_point *points ;          /* ����� ������� */
                           int  points_cnt ;
                          HWND  hWnd ;            /* ���� ������� */
           struct UD_diag_data *diag  ;           /* �������� ��������� */
                           int  trace_flag ;      /* ����� ����������� ����� */
                           int  line_style ;      /* ��� ����� ������� */
                       } ;

     struct UD_profile_point {                   /* ����� ������� */
                               int  index_1 ;       
                               int  index_2 ;
                            double  coef_1 ;
                            double  x ;
                            double  y ;
                             } ;
/*--------------------------------------------- "���������" �������� */

     struct UD_draw_elem {                         /* �������� �������� ������� */
                              int  type ;           /* ��� �������� */
#define                           _UD_LINE_ELEM  1       
                           double  x1 ;             /* ��������� ����� */
                           double  y1 ;
                           double  x2 ;             /* �������� ����� */
                           double  y2 ;
                         } ;

     struct UD_draw_contur {                       /* �������� ������� */
                             char  name[128] ;      /* ��������/������������ ������� */
                             char  parent[128] ;    /* ��������������� ������������ ������ */
                         COLORREF  color ;          /* ���� ������� */
              struct UD_draw_elem *elements ;       /* ������ ��������� */
                              int  elements_cnt ;
                           } ;
/*---------------------------------------- ���� ����������� �������� */

  struct UD_show_panel {
                         char *text ;           /* ��������� ����� */
                     COLORREF  fore_color ;     /* ���� ������ */
                     COLORREF  back_color ;     /* ���� ���� */
                       } ;
/*---------------------------------------- ���� ��������� ���������� */

  struct UD_color_panel {
                     COLORREF   color ;                   /* ���� */
                     COLORREF (*choice_proc)(COLORREF) ;  /* ������� ���������� ����� */
                        } ;
/*--------------------------------------------- ���� �������� ������ */

  struct UD_color_bank {
                     COLORREF  *colors ;                       /* ����� ������� */
                          int   colors_cnt ;                   /* ����� ������� */
                          int   rows ;                         /* ����� ����� */
                          int   cols ;                         /* ����� ������� */
                     COLORREF   backcolor ;                    /* ���� ���� */

                          int   lamp_x_size ;                  /* ������ �������� */
                          int   lamp_y_size ;
                          int   lamp_x_prefix ;                /* ������ ������ �������� */
                          int   lamp_y_prefix ;
                          int   lamp_x_pause ;                 /* ���������� ����� ���������� */
                          int   lamp_y_pause ;
                          int   lamp_form ;                    /* ����� �������� */
#define                          _UD_LAMP_RECT    0            /*  ������������� */

                     COLORREF (*choice_proc)(COLORREF, int) ;  /* ������� ���������� */

                          HDC   hDC ;
                      HBITMAP   hBitMap ;
                       } ;
/*-------------------------------------------------- ������� ������� */

  struct UD_diag_data {                          /* ������������ ������ */
                          void *parent_data ;     /* ������ �� ������� ������ */
                           int   spec_oper ;      /* ����������� �������� */
#define                          _UD_GRID_CHANGE     1    /* ������� ����� */
#define                          _UD_SCANNER_MOVE    2    /* ������� ��������� ������� */
#define                          _UD_SCANNER_CLEAR   3    /* ������� ������ */

	   struct UD_data_list **data_list ;      /* ������ ������ */
			   int   data_list_cnt ;  /* ����� ������� ������ */

          struct UD_data_scale  *spec_scale ;     /* '�������' ������� */

                      COLORREF   fore_color ;     /* ���� ������ */
                      COLORREF   grid_color ;     /* ���� ����� */
                      COLORREF   back_color ;     /* ���� ���� */

             struct UD_metrics   metrics ;        /* ������� ����������� */      

                          HWND   hWnd_scan ;      /* ���� � ������� ����� ������ */

          struct UD_zoom_scale  *zooms ;          /* ���������� ���� - "������" */
                           int   zooms_cnt ;

                   UD_CALLBACK   ctrl_proc ;      /* ����������� ��������� */
		      } ;

  struct UD_data_list {                          /* �������� ������� ������ */
			  int  type ;              /* ��� ������ ������:  */
#define                         _UD_MONO_DATA   0  /*   ���������� ������ */
#define                         _UD_PHASE_DATA  1  /*   ������� ������    */
#define                         _UD_POINT_DATA  2  /*   ������ �����      */
			 void *data ;              /* ����� ������ */
			  int  data_cnt ;          /* ������� ������ */

                     COLORREF  color ;             /* ���� ����������� */
                          int  line_style ;        /* ��� ����� */

			  int  use_flag ;          /* ���� ������������� */
			  int  grid_flag ;         /* ���� ������ ����� */
			  int  grid_values_flag ;  /* ���� ������ ��������� */

			  int  x_scale_type ;      /* ��� X-����� */
			  int  y_scale_type ;      /* ��� Y-����� */
#define                         _UD_FREE_SCALE  0  /*   ��������� ����� */
#define                         _UD_ZERO_SCALE  1  /*   ����� � ������������ ���������� ���� */
			  int  x_scale_group ;     /* ������ ����������� X-��������� */
			  int  y_scale_group ;     /* ������ ����������� Y-��������� */
		       double  x_min ;             /* ��������� ������ */
		       double  x_max ;
		       double  y_min ;
		       double  y_max ;
                       double  x_grid_0 ;          /* ���� ������� ����� */
                       double  y_grid_0 ; 
                       double  x_grid_step ;       /* ��� ����� */
                       double  y_grid_step ; 

		       double  x_scanner ;         /* ��������� ������� */
		       double  y_scanner ;
		       double  y_scn_value ;       /* ������� ������� �� ������� */
                          int  y_scn_null ;        /* �������� �� Y �� ���������� */
                       double  x_scanner_prv ;     /* ���������� ��������� ������� */
                       double  y_scanner_prv ;
                          int  scanner_prv_flag ;  /* ���� ������� prv-�������� */

			 void *mark ;              /* ����� �������� */
			  int  mark_cnt ;          /* ������� �������� */
			} ;

  struct UD_data_2Dpoint {                        /* ������� 2-������ ������ */
			   double  x ;             /* '����������' */
			   double  y ;
			      int  mark ;          /* ������������ ����� */
#define                          _UD_X_MARKER   1
#define                          _UD_Y_MARKER   2
			 } ;
/*---------------------------------------------------- ������� ����� */

  struct UD_area_data {                          /* ������������ ������ */
                          void *parent_data ;     /* ������ �� ������� ������ */
                           int  spec_oper ;       /* ����������� �������� */
			   int  type ;            /* ��� ������ ������:  */
#define                           _UD_GRID_DATA  1  /* ����� */
#define                         _UD_SCALAR_DATA  2  /* ������� */
#define                         _UD_VECTOR_DATA  4  /* ������� */
#define                        _UD_ISOLINE_DATA  8  /* ������� - �������� */

        struct UD_area_2Dpoint  *points ;         /* ������ ����� */
			   int   points_cnt ;

        struct UD_data_2Dpoint  *spots ;          /* ������ ����� ������ ����� */
			   int   spots_cnt ;

         struct UD_color_range  *scalar_colors ;  /* �������� �������� ������� */
         struct UD_color_range  *vector_colors ;  /* �������� �������� ������� */

                           int   scalar_regime ;  /* ����� ����������� */
                           int   vector_regime ;
#define                         _UD_FIXED_COLOR  1  /* ���������� ���� */
#define                          _UD_ZONE_COLOR  2  /* ������ ���� */
#define                         _UD_SMART_COLOR  4  /* ���������� ���� */
#define                         _UD_FIXED_LEN    8  /* ���������� ����� ������� */
#define                        _UD_RASTER_SIZE  16  /* ����� ����� ��� �������� */

                           int   prop_scale ;     /* ���� X/Y ������������������ */  

          struct UD_data_scale  *spec_scale ;     /* '�������' ������� */

                      COLORREF   fore_color ;     /* ���� ������ */
                      COLORREF   grid_color ;     /* ���� ����� */
                      COLORREF   back_color ;     /* ���� ���� */

             struct UD_metrics   metrics ;        /* ������� ����������� */      

                          HWND   hWnd_scan ;      /* ���� � ������� ����� ������ */

          struct UD_zoom_scale  *zooms ;          /* ���������� ���� - "������" */
                           int   zooms_cnt ;

             struct UD_profile  *profiles ;       /* ������� */
                           int   profiles_cnt ;

          struct UD_draw_contur *figures ;        /* ������ "���������" ��������� */
                            int  figures_cnt ;

                   UD_CALLBACK   ctrl_proc ;      /* ����������� ��������� */

		         double  x_data_min ;     /* ��������� ��������� ����� ����� ������ */
		         double  x_data_max ;
		         double  y_data_min ;
		         double  y_data_max ;
		         double  x_min ;          /* ��������� ��������� ����� */
		         double  x_max ;
		         double  y_min ;
		         double  y_max ;
                         double  x_grid_0 ;       /* ���� ������� ����� */
                         double  y_grid_0 ; 
                         double  x_grid_step ;    /* ��� ����� */
                         double  y_grid_step ; 

                         double  x_scanner ;      /* ��������� ������� */
                         double  y_scanner ;
         struct UD_area_2Dpoint *v_scanner_list ; /* ������ ������-�������� */
                            int  v_scanner_cnt ;

		         double  v_len_max ;      /* ������������ ����� ������� */

                            HDC  hDC ;
                        HBITMAP  hBitMap ;
		      } ;

  struct UD_area_2Dpoint {                        /* ������� 2-������� ���� */
			   double  x ;             /* '����������' */
			   double  y ;
			      int  mark ;          /* ������������ ����� */
                              int  obstacle ;      /* ������� ����������� */
			   double  x_vector ;      /* �������� ������� ����  */
			   double  y_vector ;
			   double  value ;         /* ������ ���� */
                         COLORREF  color ;         /* ���� */

                              int *spot_list ;     /* ������ �������� ����� ������� ����� ������ */
                              int  spot_cnt ;

                              int *link_list ;     /* ������ ��������� ����� */
                              int  link_cnt ;
                              int  boundary ;      /* ���� ��������� ����� */

                              int  rare_active ;   /* ���� ������������� ����� */
                              int  rare_node ;     /* ����� ������� ����� ����� */
                              int  layer ;         /* ���� */ 
                              int  inside ;        /* ���� ���������� ����� ���� */ 
                         } ;
/*----------------------------------------------- ������� � �������� */

#define    _UD_CLEAR  1
#define    _UD_SET    2
#define    _UD_GET    3

/*-------------------------------------------------------- ��������� */

      int  UD_init      (void) ;                       /* ������������� ������� ������� */
      int  UD_error     (char *) ;                     /* ��������� �� ������ */
     char *UD_ptr_incode(void *) ;                     /* �������������� ������ ������ � ������ */
     void *UD_ptr_decode(char *) ;                     /* �������������� ������ � ����� ������ */

/*------------------------------------------ ��������������� ������� */

     void  UDi_form_rect   (RECT *, int, int, int, int) ;   /* ������������ ������������� �������������� */
 COLORREF  UDi_assign_color(int, double,                    /* ������� ����� �� �������� ������� */
                             struct UD_color_range *) ;   
      int  UDi_assign_index(double,                         /* ������� ������� �� �������� ������� */
                             struct UD_color_range *) ;
     void  UDi_zone_invert (HDC, UD_metrics *, RECT *) ;    /* �������� �� ������� ���� */
     void  UDi_cross_invert(HDC, UD_metrics *, int, int) ;  /* �������� "������" ������� */
   double  UDi_range_step  (double) ;                       /* ����������� ������������ ��������� ��������� */
     void  UDi_value_zone  (double, double, double,         /* ����������� ��������� ����� ���� ��������� */
                             UD_value_zone *) ;
     void  UDi_value_cvt   (double, UD_value_zone *, int) ; /* ������� ����� � ����� */

/*---------------------------------------------- ����������� ������� */

typedef  struct {  double  x ;
                   double  y ;  }  UD_point_w ;

      int  UDg_setviewport(HDC, int, int, int, int) ;        /* ������� ���� ����������� */
      int  UDg_setwindow  (HDC, int, double, double,         /* ��������������� ���� ����������� */
                                     double, double ) ;  
      int  UDg_xpos_w     (HDC, double) ;                    /* ������ �������� ��������� �� ������� */ 
      int  UDg_ypos_w     (HDC, double) ;
   double  UDg_xcoord_w   (HDC, int, double *, double *) ;
   double  UDg_ycoord_w   (HDC, int, double *, double *) ;
      int  UDg_setpixel_w (HDC, double, double, COLORREF) ;  /* ��������� ����� */ 
      int  UDg_moveto_w   (HDC, double, double) ;            /* ������� ���� � ����� */ 
      int  UDg_lineto_w   (HDC, double, double) ;            /* ��������� ����� � ����� */ 
      int  UDg_marker_w   (HDC, double, double, int) ;       /* ��������� ������� ����� */ 
      int  UDg_polygon_w  (HDC, UD_point_w *, int) ;         /* ��������� �������������� */ 

/*------------------------------------------------------ ����������� */

   LRESULT CALLBACK  UD_show_panel_prc (HWND, UINT, WPARAM, LPARAM) ;
   LRESULT CALLBACK  UD_color_panel_prc(HWND, UINT, WPARAM, LPARAM) ;
   LRESULT CALLBACK  UD_color_bank_prc (HWND, UINT, WPARAM, LPARAM) ;
   LRESULT CALLBACK  UD_diagram_2D_prc (HWND, UINT, WPARAM, LPARAM) ;
   LRESULT CALLBACK  UD_area_2D_prc    (HWND, UINT, WPARAM, LPARAM) ;
