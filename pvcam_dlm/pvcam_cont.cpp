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


void pvcam_cont_start(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns32 exposure_time;                /* The time to open the shutter. */
  uns16 s1, s2, p1, p2, sbin, pbin;   /* The region data for the camera. */
  uns32 stream_size;                 /* The number of bytes needed. Make sure to pass this by reference. */
  char error = 0;


  /* Point parameter variables to the actual IDL values. */
  hcam = (int16)IDL_LongScalar(argv[0]);
  exposure_time = (uns32)IDL_ULongScalar(argv[1]);

  /* Set serial and parallel transfer regions. */
  s1   = (uns16)IDL_ULongScalar(argv[2]);
  s2   = (uns16)IDL_ULongScalar(argv[3]);
  p1   = (uns16)IDL_ULongScalar(argv[4]);
  p2   = (uns16)IDL_ULongScalar(argv[5]);

  /* Set or default the binning factors. */
  sbin = (uns16)IDL_ULongScalar(argv[6]);
  pbin = (uns16)IDL_ULongScalar(argv[7]);
  stream_size = (uns32)IDL_ULongScalar(argv[8]);

  error = !ccd_cont_start(hcam, exposure_time, s1, s2, p1, p2, sbin, pbin, &stream_size);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}

IDL_VPTR pvcam_cont_check_status(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 status;
  uns32 byte_cnt;
  uns32 buffer_cnt;
  char error = 0;

  /* Point parameter variables to the actual IDL values. */
  hcam = (int16)IDL_LongScalar(argv[0]);
  //byte_cnt = (uns32)IDL_ULongScalar(argv[1]);
  //buffer_cnt = (uns32)IDL_ULongScalar(argv[2]);

  error = !ccd_cont_check_status(hcam, &status, &byte_cnt, &buffer_cnt);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &byte_cnt);
  IDL_StoreScalar(argv[2], IDL_TYP_ULONG, (IDL_ALLTYPES *) &buffer_cnt);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;

  return IDL_GettmpLong(status);
}

void pvcam_cont_get_frame(int argc, IDL_VPTR argv[], char *argk)
{
  int16 hcam;
  //uns16 image;
  char error = 0;

  IDL_ENSURE_ARRAY(argv[1]);

  hcam = (int16)IDL_LongScalar(argv[0]);
  //image = (uns16)IDL_ULongScalar(argv[1]);
  error = !ccd_cont_get_frame(hcam, (uns16 *)argv[1]->value.arr->data);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}

void pvcam_cont_halt(int argc, IDL_VPTR argv[], char *argk)
{
  int16 hcam, cam_state;
  char error = 0;

  hcam = (int16)IDL_LongScalar(argv[0]);
  cam_state = (int16)IDL_LongScalar(argv[1]);
  error = !ccd_cont_halt(hcam, cam_state);

  /* Handling the error keyword */
  KW_RESULT kw;
  argc = IDL_KWProcessByOffset(argc,argv,argk,kw_pars,(IDL_VPTR *)0,1,&kw);
  if (kw.iError) {
    IDL_StoreScalar(kw.iError, IDL_TYP_BYTE, (IDL_ALLTYPES*) &error);
  }
  IDL_KW_FREE;
}
