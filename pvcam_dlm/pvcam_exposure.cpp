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
  uns16 *image;
  char error;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  image = (uns16 *)IDL_ULongScalar(argv[1]);

  error = ccd_exp_start(hcam, image);
  
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
  int16 *status;
  uns32 *byte_cnt;
  char error;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  status = (int16 *)IDL_LongScalar(argv[1]);
  byte_cnt = (uns32 *)IDL_ULongScalar(argv[2]);

  error = ccd_exp_check_status(hcam, status, byte_cnt);
  
  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
  return IDL_GettmpUInt(1);

}


void pvcam_exp_halt(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 cam_state = CCS_HALT_CLOSE_SHTR;
  char error;

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

  error = ccd_exp_halt(hcam, cam_state);

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
  int16 *ccs_status;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_ccs_status(hcam, ccs_status);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &ccs_status);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpUInt(1);
}   


IDL_VPTR pvcam_get_frame_capable(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *frame_capable;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_frame_capable(hcam, frame_capable);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &frame_capable);
  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpUInt(1);
}
