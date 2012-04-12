//pvcam_speed.cpp

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


IDL_VPTR pvcam_get_speed(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *speed;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_speed(hcam, speed);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &speed);

  return IDL_GettmpUInt(1);
}   


IDL_VPTR pvcam_get_speed_entries(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *entries;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_speed_entries(hcam, entries);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &entries);

  return IDL_GettmpUInt(1);
}   


IDL_VPTR pvcam_get_speed_mode(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *speed;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_speed_mode(hcam, speed);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &speed);

  return IDL_GettmpUInt(1);
}   


void pvcam_set_speed_mode(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 speed;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  speed = *(int16 *)IDL_LongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_speed_mode(hcam, speed));
}


IDL_VPTR pvcam_get_bits(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *bits;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_bits(hcam, bits);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &bits);

  return IDL_GettmpUInt(1);
}
