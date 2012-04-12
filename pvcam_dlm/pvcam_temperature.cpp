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
  float *cur_tmp;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_tmp(hcam, cur_tmp);
  IDL_StoreScalar(argv[1], IDL_TYP_FLOAT, (IDL_ALLTYPES *) &cur_tmp);

  return IDL_GettmpUInt(1);
}   

IDL_VPTR pvcam_get_tmp_setpoint(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  float *tmp_setpoint;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_tmp_setpoint(hcam, tmp_setpoint);
  IDL_StoreScalar(argv[1], IDL_TYP_FLOAT, (IDL_ALLTYPES *) &tmp_setpoint);

  return IDL_GettmpUInt(1);
}

void pvcam_set_tmp_setpoint(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  float tmp_setpoint;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  tmp_setpoint = *(float *)argv[1];

  //return IDL_GettmpUInt(ccd_set_tmp_setpoint(hcam, tmp_setpoint));
}