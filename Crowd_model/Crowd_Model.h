
#ifndef  CRWOD_MODEL_H 

#define  CROWD_MODEL_H 

#include <string>

#ifdef CROWD_MODEL_EXPORTS
#define CROWD_MODEL_API __declspec(dllexport)
#else
#define CROWD_MODEL_API __declspec(dllimport)
#endif

/*---------------------------------------------- ��������� ��������� */

#define    _MODEL_PARS_MAX    8
#define    _MODEL_SECT_MAX    8

/*--------------------------------------------- ���������� ��������� */

  typedef  struct {
                     char  text[32] ;        /* ������� ��������� */
                     char  value[32] ;       /* �������� ��������� */
                  } Crowd_Model_parameter ;

  typedef  struct {
                            char  title[32] ;       /* ������������ ������ */
                     std::string *decl ;            /* ������ ������ */
                  } Crowd_Model_section ;

  typedef  struct {
                           char  name[32] ;                   /* �������� ������� */
                           char  lib_path[FILENAME_MAX] ;     /* ���� � ������� ���������� */
                           char  path[FILENAME_MAX] ;         /* ���� � ����� */
                           char  object[32] ;                 /* ��� ������� */
                           char  model[32] ;                  /* �������� ������ */
                           char  picture[FILENAME_MAX] ;      /* ���� �������� */
          Crowd_Model_parameter  pars[_MODEL_PARS_MAX] ;      /* ��������� */
            Crowd_Model_section  sections[_MODEL_SECT_MAX] ;  /* ������ ����������� ������ */
                  } Crowd_Model_data ;

/*---------------------------------------------------- ��������� �/� */

/* Crowd_model.cpp */
 CROWD_MODEL_API int  Crowd_Model_list    (char *, char *,       /* ������������ ������ ������ ������� � ������� */
                                            int  , char * ) ;
 CROWD_MODEL_API int  Crowd_Model_ReadPars(Crowd_Model_data *) ; /* ���������� ���������� ������ */ 
 CROWD_MODEL_API int  Crowd_Model_ReadSect(Crowd_Model_data *) ; /* ���������� ������ �������� ������ */ 
 CROWD_MODEL_API int  Crowd_Model_Picture (Crowd_Model_data *,   /* ���������� �������� ������ */ 
                                            HBITMAP *, RECT *) ;

#endif        // CROWD_MODEL_H
