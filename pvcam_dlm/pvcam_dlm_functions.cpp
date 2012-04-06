//pvcam_dlm_functions.cpp

/******************************************************************************
Copyright (c) Richie Zeng rfzeng@lbl.gov
Date: March 2012
Lawrence Berkeley National Lab


IDL wrapper to support functions from the PVCam API. Adapted from code written
by Bob Gunion in 2008.

******************************************************************************/

/// @name IDL Wrappers for the Simplified CCD interface
//@{

///////////////////////////////////////////////////////////////////////////////
// IDL DLM wrappers for the simplified ccd functions
// Example usage from IDL:
// hcam = 0
// x = 0
// y = 0
// result = pvcam_init(hcam)
// result = pvcam_get_size(hcam, x, y)
// image = INTARR(x, y)
// result = pvcam_setup(hcam, 8000l, 0, x - 1, 0, y - 1)
// result = pvcam_exp_start(hcam, image)
//
// (call ccd_exp_check_status repeatedly until status is READOUT_COMPLETE,
//  then display the image)
//
// result = pvcam_uninit(hcam)
///////////////////////////////////////////////////////////////////////////////

#include "ipvcam.h"
#include "pvcam_dlm.h"
#include "stdafx.h"
#include "pvcam.h"


void pvcam_init(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 *hcam;                         /* A pointer to the camera's handle. */

  /* Return an error if the parameters are incorrect. */
  if (argc != 1)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = (int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_init(hcam));
}

void pvcam_uninit(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */

  /* Return an error if the parameters are incorrect. */
  if (argc != 1)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_uninit(hcam));
}

IDL_VPTR pvcam_get_size(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *ser, *par;                    /* Pointers to the max image size. */

  /* Return an error if the parameters are incorrect. */
  if (argc != 3)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

void pvcam_exp_start(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *image;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  image = (uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_exp_start(hcam, image));
}

IDL_VPTR pvcam_exp_check_status(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *status;
  uns32 *byte_cnt;

  /* Return an error if the parameters are incorrect. */
  if (argc != 3)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  status = (int16 *)IDL_LongScalar(argv[1]);
  byte_cnt = (uns32 *)IDL_ULongScalar(argv[2]);

  return IDL_GettmpUInt(ccd_exp_check_status(hcam, status, byte_cnt));
  //pl_exp_check_status(*hcam, status, byte_cnt);

  return IDL_GettmpUInt(1);
}

void pvcam_exp_halt(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 cam_state = CCS_HALT_CLOSE_SHTR;

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

  //return IDL_GettmpUInt(ccd_exp_halt(hcam, cam_state));
}

IDL_VPTR pvcam_get_ccs_status(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *ccs_status;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_ccs_status(hcam, ccs_status);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &ccs_status);

  return IDL_GettmpUInt(1);
}   

IDL_VPTR pvcam_get_shtr_status(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *shtr_status;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 1)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_shtr_open_never(hcam));
}

void pvcam_shtr_open_normal(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */

  /* Return an error if the parameters are incorrect. */
  if (argc != 1)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    ///return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);

  //return IDL_GettmpUInt(ccd_shtr_open_normal(hcam));
}

IDL_VPTR pvcam_get_shtr_open_dly(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *shtr_open_dly;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  clear_cycles = *(uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_clear_cycles(hcam, clear_cycles));
}

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

IDL_VPTR pvcam_get_max_gain(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *max_gain;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  gain = *(int16 *)IDL_LongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_gain(hcam, gain));
}   

IDL_VPTR pvcam_get_speed(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *speed;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_speed_mode(hcam, speed);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &speed);

  return IDL_GettmpUInt(1);
}   

/**
* Set the CCD readout speed from a table of available choices.
* NOTE: The gain will always be reset to 1x after setting this parameter.
* Equivalent to setting the PARAM_SPDTAB_INDEX parameter
* Referenced pvcam function:
*  - pl_spdtab_set_num (OBSOLETE: should be replaced with pl_set_param)
* @param hcam the camera number
* @param speed the table index
* @return 1 on success, 0 on failure
*/
void pvcam_set_speed_mode(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 speed;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  speed = *(int16 *)IDL_LongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_speed_mode(hcam, speed));
}   

/**
* Get the bit depth for the currently selected speed choice.
* Although this number might range between 6 and
* 16, the data will always be returned in an unsigned 16-bit
* word. This value indicates the number of valid bits within
* that word.
* Equivalent to getting the PARAM_BIT_DEPTH parameter
* Referenced pvcam function:
*  - pl_spdtab_get_bits (OBSOLETE: should be replaced with pl_get_param)
* @param hcam the camera number
* @param bits (output) the bit depth
* @return 1 on success, 0 on failure
*/
IDL_VPTR pvcam_get_bits(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  int16 *bits;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_bits(hcam, bits);
  IDL_StoreScalar(argv[1], IDL_TYP_LONG, (IDL_ALLTYPES *) &bits);

  return IDL_GettmpUInt(1);
}

IDL_VPTR pvcam_get_retries(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *retries;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_retries(hcam, retries);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &retries);

  return IDL_GettmpUInt(1);
}   

/**
* Set the maximum number of command retries.  This should normally
* not be changed since it "is matched to the
* communications link, hardware platform, and operating
* system" [PVCAM 2.6 Manual, p. 36]
* Equivalent to setting the PARAM_DD_RETRIES parameter
* Referenced pvcam function:
*  - pl_dd_set_retries (OBSOLETE: should be replaced with pl_set_param)
* @param hcam the camera number
* @param retries the maximum number of retries
* @return 1 on success, 0 on failure
*/
void pvcam_set_retries(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 retries;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

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

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_timeout(hcam, m_sec);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &m_sec);

  return IDL_GettmpUInt(1);
}   

/**
* Set the maximum time to wait for acknowledgement.  This should normally
* not be changed since it "is matched to the
* communications link, hardware platform, and operating
* system" [PVCAM 2.6 Manual, p. 36]
* Equivalent to setting the PARAM_DD_TIMEOUT parameter
* Referenced pvcam function:
*  - pl_dd_set_timeout (OBSOLETE: should be replaced with pl_set_param)
* @param hcam the camera number
* @param m_sec the timeout setting in milliseconds
* @return 1 on success, 0 on failure
*/
void pvcam_set_timeout(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 m_sec;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    //return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  m_sec = *(uns16 *)IDL_ULongScalar(argv[1]);

  //return IDL_GettmpUInt(ccd_set_timeout(hcam, m_sec));
}   

IDL_VPTR pvcam_get_frame_capable(int argc, IDL_VPTR argv[], char *argk)
{
  /* Parameter Variables */
  int16 hcam;                         /* A pointer to the camera's handle. */
  uns16 *frame_capable;

  /* Return an error if the parameters are incorrect. */
  if (argc != 2)
  {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, "You entered the wrong number of parameters!\n");
    return IDL_GettmpUInt(0);
  }

  /* Point parameter variables to the actual IDL values. */
  hcam = *(int16 *)IDL_LongScalar(argv[0]);
  ccd_get_frame_capable(hcam, frame_capable);
  IDL_StoreScalar(argv[1], IDL_TYP_ULONG, (IDL_ALLTYPES *) &frame_capable);

  return IDL_GettmpUInt(1);
}

//@}