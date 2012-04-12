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
  int16 *shtr_status;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_shtr_status(hcam, shtr_status);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &shtr_status);

  return IDL_GettmpUInt(1);
}   


void pvcam_shtr_open_never(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_shtr_open_never(hcam));
}


void pvcam_shtr_open_normal(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_shtr_open_normal(hcam));
}


IDL_VPTR pvcam_get_shtr_open_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *shtr_open_dly;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_shtr_open_dly(hcam, shtr_open_dly);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &shtr_open_dly);
  
  return IDL_GettmpUInt(1);
}   


void pvcam_set_shtr_open_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 shtr_open_dly;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  shtr_open_dly = *(uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_shtr_open_dly(hcam, shtr_open_dly));
}   


IDL_VPTR pvcam_get_shtr_close_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *shtr_close_dly;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_shtr_close_dly(hcam, shtr_close_dly);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &shtr_close_dly);

  return IDL_GettmpUInt(1);
}   


void pvcam_set_shtr_close_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 shtr_close_dly;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  shtr_close_dly = *(uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_shtr_close_dly(hcam, shtr_close_dly));
}   


IDL_VPTR pvcam_get_clear_cycles(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *cycles;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_clear_cycles(hcam, cycles);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &cycles);

  return IDL_GettmpUInt(1);
}


void pvcam_set_clear_cycles(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 clear_cycles;                 /* The number of clears. */

  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  clear_cycles = *(uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_clear_cycles(hcam, clear_cycles));
}
