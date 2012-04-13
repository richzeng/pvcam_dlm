//pvcam_shutter.cpp

/******************************************************************************
Copyright (c) Richie Zeng rfzeng@lbl.gov
Date: March 2012
Lawrence Berkeley National Lab


IDL wrapper to support functions from the PVCam API. Adapted from code written
by Bob Gunion in 2008.

******************************************************************************/

#include "ipvcam.h"
#include "pvcam_dlm.h"
#include "stdafx.h"
#include "pvcam.h"

IDL_VPTR pvcam_get_shtr_status(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 shtr_status;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_get_shtr_status(hcam, &shtr_status);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpInt(shtr_status);
}   


void pvcam_shtr_open_never(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_shtr_open_never(hcam);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}


void pvcam_shtr_open_normal(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_shtr_open_normal(hcam);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}


IDL_VPTR pvcam_get_shtr_open_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 shtr_open_dly;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_get_shtr_open_dly(hcam, &shtr_open_dly);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
  
  return IDL_GettmpUInt(shtr_open_dly);
}   


void pvcam_set_shtr_open_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 shtr_open_dly;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  shtr_open_dly = *(uns16 *)IDL_ULongScalar(argv[1]);
  error = !ccd_set_shtr_open_dly(hcam, shtr_open_dly);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}


IDL_VPTR pvcam_get_shtr_close_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 shtr_close_dly;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_get_shtr_close_dly(hcam, &shtr_close_dly);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpUInt(shtr_close_dly);
}   


void pvcam_set_shtr_close_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 shtr_close_dly;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  shtr_close_dly = *(uns16 *)IDL_ULongScalar(argv[1]);
  error = ccd_set_shtr_close_dly(hcam, shtr_close_dly);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}   


IDL_VPTR pvcam_get_clear_cycles(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 cycles;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_get_clear_cycles(hcam, &cycles);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpUInt(cycles);
}


void pvcam_set_clear_cycles(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 clear_cycles;                 /* The number of clears. */
  char error = 0;

  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  clear_cycles = *(uns16 *)IDL_ULongScalar(argv[1]);
  error = !ccd_set_clear_cycles(hcam, clear_cycles);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}
