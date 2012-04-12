//pvcam_timeout.cpp

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


IDL_VPTR pvcam_get_retries(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *retries;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_retries(hcam, retries);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &retries);

  return IDL_GettmpUInt(1);
}   


void pvcam_set_retries(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 retries;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  retries = *(uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_retries(hcam, retries));
}   


IDL_VPTR pvcam_get_timeout(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *m_sec;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_timeout(hcam, m_sec);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &m_sec);

  return IDL_GettmpUInt(1);
}   


void pvcam_set_timeout(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 m_sec;

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  m_sec = *(uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_timeout(hcam, m_sec));
}   