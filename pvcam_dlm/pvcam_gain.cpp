//pvcam_gain.cpp

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


IDL_VPTR pvcam_get_max_gain(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *max_gain;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_max_gain(hcam, max_gain);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &max_gain);

  return IDL_GettmpUInt(1);
}   


IDL_VPTR pvcam_get_gain(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *gain;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_gain(hcam, gain);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &gain);

  return IDL_GettmpUInt(1);
}   


void pvcam_set_gain(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 gain;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  gain = *(int16 *)IDL_LongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_gain(hcam, gain));
}
