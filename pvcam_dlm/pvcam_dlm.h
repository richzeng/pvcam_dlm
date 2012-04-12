//pvcam_dlm.h

/******************************************************************************
Copyright (c) Richie Zeng rfzeng@lbl.gov
Date: March 2012
Lawrence Berkeley National Lab


IDL wrapper to support functions from the PVCam API. Adapted from code written
by Bob Gunion in 2008.

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "export.h"
#include "master.h"

#ifndef PVCAM_DLM
#define PVCAM_DLM


/* Handy macro to find the size of an array */
#define ARRLEN(arr) (sizeof(arr)/sizeof(arr[0]))

extern "C" {
/*****************************************************************************
  pvcam_init.cpp
*****************************************************************************/

  /* pvcam_init(short *hcam); */
  void pvcam_init(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_uninit(short hcam); */
  void pvcam_uninit(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_size(short hcam, unsigned short* ser, unsigned short* par); */
  IDL_VPTR pvcam_get_size(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_setup(short hcam,
                 unsigned long exposure_time,
                 unsigned short s1,
                 unsigned short s2,
                 unsigned short p1,
                 unsigned short p2,
                 unsigned short sbin,
                 unsigned short pbin,
                 unsigned long *stream_size); */
  void pvcam_setup(int argc, IDL_VPTR argv[], char *argk);


/*****************************************************************************
  pvcam_exposure.cpp
*****************************************************************************/

  /* pvcam_exp_start(short hcam, unsigned short* image); */
  void pvcam_exp_start(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_exp_check_status(short hcam, short *status, unsigned long *byte_cnt); */
  IDL_VPTR pvcam_exp_check_status(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_exp_halt(short hcam, short cam_state); */
  void pvcam_exp_halt(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_ccs_status(short hcam, short *ccs_status); */
  IDL_VPTR pvcam_get_ccs_status(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_shtr_status(short hcam, short *shtr_status); */
  IDL_VPTR pvcam_get_shtr_status(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_shtr_open_never(short hcam); */
  void pvcam_shtr_open_never(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_shtr_open_normal(short hcam); */
  void pvcam_shtr_open_normal(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_shtr_open_dly(short hcam, unsigned short *shtr_open_dly); */
  IDL_VPTR pvcam_get_shtr_open_dly(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_shtr_open_dly(short hcam, unsigned short shtr_open_dly); */
  void pvcam_set_shtr_open_dly(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_shtr_close_dly(short hcam, unsigned short *shtr_close_dly); */
  IDL_VPTR pvcam_get_shtr_close_dly(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_shtr_close_dly(short hcam, unsigned short shtr_close_dly); */
  void pvcam_set_shtr_close_dly(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_clear_cycles(short hcam, unsigned short *cycles); */
  IDL_VPTR pvcam_get_clear_cycles(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_clear_cycles(short hcam, unsigned short clear_cycles); */
  void pvcam_set_clear_cycles(int argc, IDL_VPTR argv[], char *argk);

  /* pvcam_get_frame_capable(short hcam, unsigned short *frame_capable); */
  IDL_VPTR pvcam_get_frame_capable(int argc, IDL_VPTR argv[], char *argk);


/*****************************************************************************
  pvcam_temperature.cpp
*****************************************************************************/

  /* pvcam_get_tmp(short hcam, float *cur_tmp); */
  IDL_VPTR pvcam_get_tmp(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_tmp_setpoint(short hcam, float *tmp_setpoint); */
  IDL_VPTR pvcam_get_tmp_setpoint(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_tmp_setpoint(short hcam, float tmp_setpoint); */
  void pvcam_set_tmp_setpoint(int argc, IDL_VPTR argv[], char *argk);
 

/*****************************************************************************
  pvcam_gain.cpp
*****************************************************************************/

  /* pvcam_get_max_gain(short hcam, short *max_gain); */
  IDL_VPTR pvcam_get_max_gain(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_gain(short hcam, short *gain); */
  IDL_VPTR pvcam_get_gain(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_gain(short hcam, short gain); */
  void pvcam_set_gain(int argc, IDL_VPTR argv[], char *argk);


/*****************************************************************************
  pvcam_speed.cpp
*****************************************************************************/

  /* pvcam_get_speed(short hcam, unsigned short *speed); */
  IDL_VPTR pvcam_get_speed(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_speed_entries(short hcam, short *entries); */
  IDL_VPTR pvcam_get_speed_entries(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_speed_mode(short hcam, short *speed); */
  IDL_VPTR pvcam_get_speed_mode(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_speed_mode(short hcam, short speed); */
  void pvcam_set_speed_mode(int argc, IDL_VPTR argv[], char *argk);

  /* pvcam_get_bits(short hcam, short *bits); */
  IDL_VPTR pvcam_get_bits(int argc, IDL_VPTR argv[], char *argk);


/*****************************************************************************
  pvcam_timeout.cpp
*****************************************************************************/

  /* pvcam_get_retries(short hcam, unsigned short *retries); */
  IDL_VPTR pvcam_get_retries(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_retries(short hcam, unsigned short retries); */
  void pvcam_set_retries(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_get_timeout(short hcam, unsigned short *m_sec); */
  IDL_VPTR pvcam_get_timeout(int argc, IDL_VPTR argv[], char *argk);
  
  /* pvcam_set_timeout(short hcam, unsigned short m_sec); */
  void pvcam_set_timeout(int argc, IDL_VPTR argv[], char *argk);
}

#endif
