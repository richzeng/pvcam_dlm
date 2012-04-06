#ifndef __IPVCAM_H__
#define __IPVCAM_H__

///////////////////////////////////////////////////////////////////////////////
// IDL wrappers for all pvcam functions (version 2.6)
// Written March 2008 by Bob Gunion to support Ken Goldberg's IDL
// application.
// Some of these functions have been copied from the old libsnap,
// others have been adapted from that library to be more consistent,
// others have been added, and still others are simple wrappers
// around the pvcam functions.
//
// $Id
//
// Copyright (c) 2008 Lawrence Berkeley National Laboratory
///////////////////////////////////////////////////////////////////////////////

#ifdef IPVCAM_EXPORTS
#define IPVCAM_API __declspec(dllexport)
#else
#define IPVCAM_API __declspec(dllimport)
#endif

extern "C" {

  ///////////////////////////////////////////////////////////////////////
  // Simplified camera interface
  // (aka libSnap version 2)
  // Provides a simpler interface for some of the pvcam functions.

unsigned short ccd_init(short *hcam);
unsigned short ccd_uninit(short hcam);
unsigned short ccd_get_size(short hcam, unsigned short* ser, unsigned short* par);
unsigned short ccd_setup(short hcam,
                                    unsigned long exposure_time,
                                    unsigned short s1,
                                    unsigned short s2,
                                    unsigned short p1,
                                    unsigned short p2,
                                    unsigned short sbin,
                                    unsigned short pbin,
                                    unsigned long *stream_size);
unsigned short ccd_exp_start(short hcam, unsigned short* image);
unsigned short ccd_exp_check_status(short hcam, short *status, unsigned long *byte_cnt);
unsigned short ccd_exp_halt(short hcam, short cam_state);
unsigned short ccd_cont_start(short hCam,
                                         unsigned long exposure_time,
                                         unsigned short s1,
                                         unsigned short s2,
                                         unsigned short p1,
                                         unsigned short p2,
                                         unsigned short sbin,
                                         unsigned short pbin,
                                         unsigned long *stream_size);
unsigned short ccd_cont_check_status(short hCam,
                                                short* status,
                                                unsigned long *byte_cnt,
                                                unsigned long* buffer_cnt);
unsigned short ccd_cont_get_frame(short hCam, unsigned short* image);
unsigned short ccd_cont_halt(short hcam, short cam_state);
unsigned short ccd_get_ccs_status(short hcam, short *ccs_status);
unsigned short ccd_get_shtr_status(short hcam, short *shtr_status);
unsigned short ccd_shtr_open_never(short hcam);
unsigned short ccd_shtr_open_normal(short hcam);
unsigned short ccd_get_shtr_open_dly(short hcam, unsigned short *shtr_open_dly);
unsigned short ccd_set_shtr_open_dly(short hcam, unsigned short shtr_open_dly);
unsigned short ccd_get_shtr_close_dly(short hcam, unsigned short *shtr_close_dly);
unsigned short ccd_set_shtr_close_dly(short hcam, unsigned short shtr_close_dly);
unsigned short ccd_get_clear_cycles(short hcam, unsigned short *cycles);
unsigned short ccd_set_clear_cycles(short hcam, unsigned short clear_cycles);
unsigned short ccd_get_clear_strips(short hcam, unsigned short *strips);
unsigned short ccd_set_clear_strips(short hcam, unsigned short strips);
unsigned short ccd_get_tmp(short hcam, float *cur_tmp);
unsigned short ccd_get_tmp_setpoint(short hcam, float *tmp_setpoint);
unsigned short ccd_set_tmp_setpoint(short hcam, float tmp_setpoint);
unsigned short ccd_get_max_gain(short hcam, short *max_gain);
unsigned short ccd_get_gain(short hcam, short *gain);
unsigned short ccd_set_gain(short hcam, short gain);
unsigned short ccd_get_gain_mult_enable(short hcam, short *enabled);
unsigned short ccd_set_gain_mult_enable(short hcam, short enabled);
unsigned short ccd_get_gain_mult_factor(short hcam, unsigned short *factor);
unsigned short ccd_set_gain_mult_factor(short hcam, unsigned short factor);
unsigned short ccd_get_speed(short hcam, unsigned short *speed);
unsigned short ccd_get_speed_entries(short hcam, short *entries);
unsigned short ccd_get_readout_port_entries(short hcam, short *entries);
unsigned short ccd_get_bits(short hcam, short *bits);
unsigned short ccd_get_speed_mode(short hcam, short *speed);
unsigned short ccd_set_speed_mode(short hcam, short speed);
unsigned short ccd_get_readout_port(short hcam, short *port);
unsigned short ccd_set_readout_port(short hcam, short port);
unsigned short ccd_get_retries(short hcam, unsigned short *retries);
unsigned short ccd_set_retries(short hcam, unsigned short retries);
unsigned short ccd_get_timeout(short hcam, unsigned short *m_sec);
unsigned short ccd_set_timeout(short hcam, unsigned short m_sec);
unsigned short ccd_get_frame_capable(short hcam, unsigned short *frame_capable);

/*****************************************************************************/
/* End of function definitions.                                              */
/*****************************************************************************/

} // extern "C"

#endif // __IPVCAM_H__
