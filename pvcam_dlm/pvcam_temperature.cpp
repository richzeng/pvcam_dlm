//pvcam_temperature.cpp

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

IDL_VPTR pvcam_get_tmp(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  float cur_tmp;

  /* Point parameter variables to the actual IDL values. */
  hcam = (int16)IDL_LongScalar(argv[0]);
  ccd_get_tmp(hcam, &cur_tmp);
  int rtn = (int)cur_tmp;             /* NOTE: NEED TO FIGURE OUT HOW TO RETURN FLOATS TO IDL */

  //return IDL_GettmpDouble(cur_tmp);
  return IDL_GettmpInt(rtn);
}

IDL_VPTR pvcam_get_tmp_setpoint(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  float tmp_setpoint;

  /* Point parameter variables to the actual IDL values. */
  hcam = IDL_LongScalar(argv[0]);
  ccd_get_tmp_setpoint(hcam, &tmp_setpoint);
  int rtn = (int)tmp_setpoint;        /* NOTE: NEED TO FIGURE OUT HOW TO RETURN FLOATS TO IDL */

  return IDL_GettmpUInt(rtn);
}

void pvcam_set_tmp_setpoint(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  float tmp_setpoint;

  /* Point parameter variables to the actual IDL values. */
  hcam = IDL_LongScalar(argv[0]);
  tmp_setpoint = (float)IDL_DoubleScalar(argv[1]);
  ccd_set_tmp_setpoint(hcam, tmp_setpoint);
}