//pvcam_exposure.cpp

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


void pvcam_exp_start(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 image;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  image = (uns16)IDL_ULongScalar(argv[1]);

  error = !ccd_exp_start(hcam, &image);
  IDL_StoreScalar(argv[1], IDL_TYP_UINT, (IDL_ALLTYPES*) &image);
  
  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}


IDL_VPTR pvcam_exp_check_status(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 status;
  uns32 byte_cnt;
  char error = 0;
  int *arr;
  IDL_VPTR rtnArray;
  IDL_LONG n[IDL_MAX_ARRAY_DIM];
  n[0]=2;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  arr = (int*) IDL_MakeTempArray(IDL_TYP_UINT, 1, n, IDL_ARR_INI_ZERO, &rtnArray);

  error = !ccd_exp_check_status(hcam, &status, &byte_cnt);
  arr[0] = status;
  arr[1] = byte_cnt;
  
  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return rtnArray;
}


void pvcam_exp_halt(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 cam_state = CCS_HALT_CLOSE_SHTR;
  char error = 0;

  /* Return an error if the parameters are incorrect. */
  if (argc == 1) {
    hcam = *(int16 *)IDL_LongScalar(argv[0]);
  } else if (argc == 2) {
    hcam = *(int16 *)IDL_LongScalar(argv[0]);
    cam_state = *(int16 *)IDL_LongScalar(argv[1]);
  } else {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  error = !ccd_exp_halt(hcam, cam_state);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}


IDL_VPTR pvcam_get_ccs_status(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 ccs_status;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_get_ccs_status(hcam, &ccs_status);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpUInt(ccs_status);
}


IDL_VPTR pvcam_get_frame_capable(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 frame_capable;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  error = !ccd_get_frame_capable(hcam, &frame_capable);
  
  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpUInt(frame_capable);
}
