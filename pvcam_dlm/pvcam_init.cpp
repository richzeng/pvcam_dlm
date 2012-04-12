//pvcam_init.cpp

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


void pvcam_init(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 *hcam;                         /* A pointer to the camera's handle. */

  /* Point parameter variables to the actual IDL values. */
  hcam = (int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_init(hcam));
}


void pvcam_uninit(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_uninit(hcam));
}


IDL_VPTR pvcam_get_size(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *ser, *par;                    /* Pointers to the max image size. */

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_size(hcam, ser, par);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &ser);
  IDL_StoreScalar(argv[2], IDL_TYP_ULONG, (IDL_ALLTYPES *) &par);

  return IDL_GettmpUInt(ccd_get_size(hcam, ser, par));
}


void pvcam_setup(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns32 exposure_time;                /* The time to open the shutter. */
  uns16 s1, s2, p1, p2, sbin, pbin;   /* The region data for the camera. */
  uns32 *stream_size;                 /* The number of bytes needed. */

  /* Return an error if the parameters are incorrect. */
  if ((argc != 7) && (argc != 9))
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  exposure_time = *(uns32 *)IDL_ULongScalar(argv[1]);

  /* Set serial and parallel transfer regions. */
  s1   = *((uns16 *)IDL_ULongScalar(argv[2]));
  s2   = *((uns16 *)IDL_ULongScalar(argv[3]));
  p1   = *((uns16 *)IDL_ULongScalar(argv[4]));
  p2   = *((uns16 *)IDL_ULongScalar(argv[5]));

  /* Set or default the binning factors. */
  if (argc == 9)
  {
    sbin = *((uns16 *)IDL_ULongScalar(argv[6]));
    pbin = *((uns16 *)IDL_ULongScalar(argv[7]));
    stream_size = (uns32 *)IDL_ULongScalar(argv[8]);
  }
  else
  {
    sbin = 1;
    pbin = 1;
    stream_size = (uns32 *)IDL_ULongScalar(argv[6]);
  }

  //return IDL_GettmpUInt(ccd_setup(hcam, exposure_time, s1, s2, p1, p2, sbin, pbin, stream_size));
}