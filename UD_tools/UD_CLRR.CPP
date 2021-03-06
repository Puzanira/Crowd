/*********************************************************************/
/*                                                                   */
/*               ������� ������������ ����������                     */
/*                                                                   */
/*********************************************************************/

#include <windows.h>

#include "UserDlg.h"

#pragma warning(disable : 4996)

   void  UD_color_lamp_rect(HDC, RECT *, HBRUSH) ;    /* "��������" - ������������� */


/*********************************************************************/
/*                                                                   */
/*                     ���� ������ �����                             */

 LRESULT CALLBACK  UD_color_panel_prc(  HWND  hWnd,     UINT  Msg,
 			              WPARAM  wParam, LPARAM  lParam)
{
             HDC  hDC ;
     PAINTSTRUCT  PaintCfg ;
          HBRUSH  BkBrush ;
            RECT  Rect ;
  UD_color_panel *data ;                /* �������� �������� */
            char  data_ptr[32] ;        /* ����� ��������, ������������ */

/*------------------------------------------------ ���������� ������ */

   if(Msg==WM_PAINT        ||
      Msg==WM_LBUTTONDBLCLK  ) {
  
        SendMessage(hWnd, WM_GETTEXT, (WPARAM)sizeof(data_ptr),
                                      (LPARAM)       data_ptr  ) ;

           data=(UD_color_panel *)UD_ptr_decode(data_ptr) ;
                               }
/*--------------------------------------------------- ����� �������� */

  switch(Msg) {

/*----------------------------------------------- �������� ��������� */

    case WM_CREATE:   break ;

    case WM_COMMAND:  break ;

/*-------------------------------------------------------- ��������� */

    case WM_PAINT:   {
/*- - - - - - - - - - - - - - - - - - - - - - - -  ���������� ������ */
                InvalidateRect(hWnd, NULL, false) ;

        if(data==NULL) {
                          ValidateRect(hWnd,  NULL) ;
                              break ;
                       }
/*- - - - - - - - - - - - - - - - - - - - - - - ����� �������� ����� */
                  hDC=BeginPaint(hWnd, &PaintCfg) ;

                   GetClientRect(hWnd, &Rect) ;
        BkBrush=CreateSolidBrush(data->color) ;
                        FillRect(hDC, &Rect, BkBrush) ;
                    DeleteObject(BkBrush) ;

                    ValidateRect(hWnd,  NULL) ;
                        EndPaint(hWnd, &PaintCfg) ;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
			     break ;
		     }
/*------------------------------------- ������� ������� ����� ������ */

    case WM_LBUTTONDBLCLK: {

        if(data==NULL)  break ;
                
        if(data->choice_proc==NULL)  break ;
  
                  data->color=data->choice_proc(data->color) ;
        
                          SendMessage(hWnd, WM_PAINT, 0, 0) ;       /* �������������� */

     		                      break ;
                           }
/*------------------------------------------------- ������ ��������� */

    default :        {
		return( DefWindowProc(hWnd, Msg, wParam, lParam) ) ;
			    break ;
		     }
/*-------------------------------------------------------------------*/
	      }
/*-------------------------------------------------------------------*/

    return(0) ;
}


/*********************************************************************/
/*                                                                   */
/*                     ���� ������ "��������"                        */

 LRESULT CALLBACK  UD_color_bank_prc(  HWND  hWnd,     UINT  Msg,
 			             WPARAM  wParam, LPARAM  lParam)
{
             HDC  hDC_wnd ;
             HDC *hDC ;
         HBITMAP *hBM ;
     PAINTSTRUCT  PaintCfg ;
          HBRUSH  BkBrush ;
          HBRUSH  Brush ;
            RECT  Rect ;
            RECT  Lamp_zone ;
   UD_color_bank *data ;                /* �������� �������� */
            char  data_ptr[32] ;        /* ����� ��������, ������������ */
             int  row ;
             int  col ;
             int  i ;

/*------------------------------------------------ ���������� ������ */

   if(Msg==WM_PAINT        ||
      Msg==WM_LBUTTONDBLCLK  ) {
  
        SendMessage(hWnd, WM_GETTEXT, (WPARAM)sizeof(data_ptr),
                                      (LPARAM)       data_ptr  ) ;

           data=(UD_color_bank *)UD_ptr_decode(data_ptr) ;
                               }
/*--------------------------------------------------- ����� �������� */

  switch(Msg) {

/*----------------------------------------------- �������� ��������� */

    case WM_CREATE:   break ;

    case WM_COMMAND:  break ;

/*-------------------------------------------------------- ��������� */

    case WM_PAINT:   {
/*- - - - - - - - - - - - - - - - - - - - - - - -  ���������� ������ */
                InvalidateRect(hWnd, NULL, false) ;

        if(data==NULL) {
                          ValidateRect(hWnd,  NULL) ;
                              break ;
                       }
/*- - - - - - - - - - - - - - - - - - - - - - - ���������� ��������� */
                         hDC_wnd=BeginPaint(hWnd, &PaintCfg) ;

                         hDC=&data->hDC ;
                         hBM=&data->hBitMap ;

       if(*hBM!=NULL)  DeleteObject(*hBM) ;
       if(*hDC!=NULL)  DeleteDC    (*hDC) ;

          *hDC=CreateCompatibleDC    ( hDC_wnd) ; 
          *hBM=CreateCompatibleBitmap( hDC_wnd, GetDeviceCaps(hDC_wnd, HORZRES), 
                                                GetDeviceCaps(hDC_wnd, VERTRES) ) ; 
                         SelectObject(*hDC, *hBM) ;

               GetClientRect(hWnd, &Rect) ;
/*- - - - - - - - - - - - - - - - - - - - - - - - ��������� �������� */
        BkBrush=CreateSolidBrush(data->backcolor) ;                 /* ������� ���� */ 
                        FillRect(*hDC, &Rect, BkBrush) ;
                    DeleteObject(BkBrush) ;

      for(i=0 ; i<data->colors_cnt ; i++) {

           Brush=CreateSolidBrush(data->colors[i]) ;                /* ���������� ����� */ 

             row=i/data->cols ;                                     /* ���������� ������ � ������� */
             col=i-row*data->cols ;

             Lamp_zone.left  =data->lamp_x_prefix+                  /* ���� ������ �������� */
                              data->lamp_x_size*col+
                              data->lamp_x_pause*col ;
             Lamp_zone.top   =data->lamp_y_prefix+
                              data->lamp_y_size*row+
                              data->lamp_y_pause*row ;
             Lamp_zone.right =Lamp_zone.left+data->lamp_x_size-1 ;
             Lamp_zone.bottom=Lamp_zone.top +data->lamp_y_size-1 ;
        
         if(data->lamp_form==_UD_LAMP_RECT)                         /* ��������� �������� */
                UD_color_lamp_rect(*hDC, &Lamp_zone, Brush) ;

                     DeleteObject(Brush) ;                          /* ������������ �������� */
                                          }
/*- - - - - - - - - - - - - - - - - - - - - - - ���������� ��������� */
            BitBlt(hDC_wnd, 0, 0, Rect.right-Rect.left+1,
                                  Rect.bottom-Rect.top, 
                  *hDC,     0, 0, SRCCOPY                ) ;

                 ValidateRect(hWnd,  NULL) ;
                     EndPaint(hWnd, &PaintCfg) ;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
			     break ;
		     }
/*------------------------------------- ������� ������� ����� ������ */

    case WM_LBUTTONDBLCLK: {

        if(data==NULL)  break ;
                
        if(data->choice_proc==NULL)  break ;
  
//                data->color=data->choice_proc(data->color[i]) ;
        
                          SendMessage(hWnd, WM_PAINT, 0, 0) ;       /* �������������� */

     		                      break ;
                           }
/*------------------------------------------------- ������ ��������� */

    default :        {
		return( DefWindowProc(hWnd, Msg, wParam, lParam) ) ;
			    break ;
		     }
/*-------------------------------------------------------------------*/
	      }
/*-------------------------------------------------------------------*/

    return(0) ;
}


/*********************************************************************/
/*                                                                   */
/*                     "��������" - �������������                    */

   void  UD_color_lamp_rect(HDC  hDC, RECT *zone, HBRUSH  brush)

{
     FillRect(hDC, zone, brush) ;
}
