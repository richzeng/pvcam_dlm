// ipvcam.cpp : Defines the entry point for the DLL application.
//
///////////////////////////////////////////////////////////////////////////////
/// @mainpage
/// IDL wrappers for all pvcam functions (version 2.6)
/// Written March 2008 by Bob Gunion to support Ken Goldberg's IDL
/// application.
///
/// The comments below were copied directly from the pvcam.h file.  The
/// function definitions have been modified in the following ways:
/// - function names are prepended with 'I' (as in 'IDL')
/// - return type is unsigned short IPVCAM_API, rather than rs_bool (which is typedef'd
///    to unsigned short IPVCAM_API, so it's really not a difference)
/// - parameters are int argc, void * argv[] to conform to the IDL way
///    of calling external code
/// - Functions marked as obsolete are not included.
///
/// $Id
///
/// Copyright (c) 2008 Lawrence Berkeley National Laboratory
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ipvcam.h"
#include "master.h"
#include "pvcam.h"
#include <stdio.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}

uns16 *circular_buffer = NULL;
uns32 frame_size = 0;

extern "C" {

  ///////////////////////////////////////////////////////////////////////
  // Simplified camera interface
  // (aka libSnap version 2)
  // Provides a simpler interface for some of the pvcam functions.

  /// @name Initialization Functions
  //@{

  /**
  * Initialize the data collection functions
  * Initializes the pvcam library and opens the camera specified by 
  * the hcam parameter.  Verifies that the camera is on and
  * connected.
  * <br/>Referenced pvcam functions:
  *  - pl_pvcam_init
  *  - pl_exp_init_seq
  *  - pl_cam_get_total
  *  - pl_cam_get_name
  *  - pl_cam_open
  *  - pl_cam_get_diags
  * @param hcam The camera number (0 for the first camera in the system)
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_init(int16 *hcam)
  {
    /* Local Variables */
    int16 total_cams;                    /* The number of cameras connected. */
    char cam_name[1000];                  /* The device name of the camera. */

    /* Initialize driver. */
    if (!pl_pvcam_init())
    {
      return(0);
    }

    /* Initialize the data collection functions. */
    if (!pl_exp_init_seq())
    {
      pl_pvcam_uninit();                  /* Uninitialize the driver. */
      return(0);      
    }

    /* Check the number of cameras. */
    if (!pl_cam_get_total(&total_cams) || (total_cams <= 0))
    {
      pl_exp_uninit_seq();                /* Uninitialize data collection. */
      pl_pvcam_uninit();                  /* Uninitialize the driver. */
      return(0);
    }

    /* Get the camera's name. */
    if (!pl_cam_get_name(*hcam, cam_name))  /* pass hcam instead of 0*/
    {
      pl_exp_uninit_seq();                /* Uninitialize data collection. */
      pl_pvcam_uninit();                  /* Uninitialize the driver. */
      return(0);
    }

    /* Open the camera's connection. */
    if (!pl_cam_open(cam_name, hcam, OPEN_EXCLUSIVE))
    {
      pl_exp_uninit_seq();                /* Uninitialize data collection. */
      pl_pvcam_uninit();                  /* Uninitialize the driver. */
      return(0);
    }

    /* Check to make sure the camera is on and connected */
    if (!pl_cam_get_diags(*hcam))
    {
      printf("The camera is not ready.\n");
      pl_cam_close(*hcam);                /* Close the camera's connection. */
      pl_exp_uninit_seq();                /* Uninitialize data collection. */
      pl_pvcam_uninit();                  /* Uninitialize the driver. */
      return(0);
    }

    /* Initialize the scripting functions. */
    /*
    if (!pl_exp_init_script())
    {
    pl_cam_close(*hcam);                // Close the camera's connection. 
    pl_exp_uninit_seq();                // Uninitialize data collection. 
    pl_pvcam_uninit();                  // Uninitialize the driver. 
    return(0);      
    }
    */

    return(TRUE);
  }

  /**
  * Uninitialize the camera functions, freeing any resources
  * <br/>Referenced pvcam functions:
  *  - pl_cam_close
  *  - pl_exp_uninit_seq
  *  - pl_pvcam_uninit
  * @param hcam The camera number
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_uninit(int16 hcam)
  {
    //   pl_exp_uninit_script();              /* Uninitialize scripting */
    pl_cam_close(hcam);                 /* Close the camera's connection. */
    pl_exp_uninit_seq();                 /* Uninitialize data collection. */
    pl_pvcam_uninit();                   /* Uninitialize the driver. */
    return(1);
  }

  //@}

  /// @name Single-exposure functions
  //@{

  /**
  * Setup the ccd for an exposure.  Assumes 1 exposure, 1 region,
  * timed exposure mode.
  * <br/>Referenced pvcam functions:
  *  - pl_exp_setup_seq
  * @param hcam the camera number
  * @param exposure_time exposure time in the currently selected resolution
  * @param region the region, consisting of:
  *     - x_min minimum in the x direction
  *     - x_max maximum in the x direction
  *     - y_min minimum in the y direction
  *     - y_max maximum in the y direction
  *     - x_bin (default = 1) binning in the x direction
  *     - y_bin (default = 1) binning in the y direction
  * @param stream_size (output) the required stream size for the buffer
  *        to be passed to ccd_exp_start
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_setup(int16 hcam,
    uns32 exposure_time,
    uns16 s1,
    uns16 s2,
    uns16 p1,
    uns16 p2,
    uns16 sbin,
    uns16 pbin,
    uns32 *stream_size)
  {

    rgn_type region;
    region.s1 = s1;
    region.s2 = s2;
    region.p1 = p1;
    region.p2 = p2;
    region.sbin = sbin;
    region.pbin = pbin;

    /* Upload the sequence data. */
    if (!pl_exp_setup_seq(hcam, 1, 1, &region, TIMED_MODE, exposure_time,
      stream_size))   
    {
      return(0);
    }

    return(TRUE);
  }

  /**
  * Start an exposure
  * <br/>Referenced pvcam function:
  *  - pl_exp_start_seq
  * @param hcam the camera number
  * @param image the image buffer
  * @return 1 on success, 0 on failure
  * @sa ccd_setup
  */
  unsigned short ccd_exp_start(int16 hcam, uns16* image)
  {

    /* Take a picture and send the data to the image buffer. */
    if (!pl_exp_start_seq(hcam, image))
    {
      return(0);
    } 

    return(1);
  }

  /**
  * Check on the status of the exposure
  *
  * <br/>Referenced pvcam function:
  *  - pl_exp_check_status
  * @param hcam the camera number
  * @param status (output)  the status of the exposure.  One of:
  *   - (0) READOUT_NOT_ACTIVE: System is idle, no data is expected
  *   - (1) EXPOSURE_IN_PROGRESS: Data collection is active, no data have arrived yet 
  *   - (2) READOUT_IN_PROGRESS: Data collection is active, data have started to arrive
  *   - (3) READOUT_COMPLETE: All expected data have arrived, system has returned to idle
  *   - (4) READOUT_FAILED: Something went wrong.  Function returns 0 and user should
  *     check pl_error_code. 
  *   - (5) ACQUISITION_IN_PROGRESS: For PI cameras only: either EXPOSURE_IN_PROGRESS
  *     or READOUT_IN_PROGRESS (these statuses are not available in PI cameras)
  * @param byte_cnt (output)  number of bytes returned so far
  * @return 1 on success, 0 on failure or READOUT_FAILED
  */
  unsigned short ccd_exp_check_status(int16 hcam, int16 *status, uns32 *byte_cnt) {
    return pl_exp_check_status(hcam, status, byte_cnt);
  }

  /**
  * Stop an exposure immediately and (optionally) close the shutter
  *
  * <br/>Referenced pvcam function:
  *  - pl_exp_abort
  * @param hcam the camera number
  * @param cam_state (default CCS_HALT_CLOSE_SHTR)  Force the camera
  * control subsystem (CCS) into one of the states (camera dependent):
  *   - {0) CCS_NO_CHANGE: No change
  *   - (1) CCS_HALT: Halt all CCS activity, put in idle state
  *   - (2) CCS_HALT_CLOSE_SHTR: Close the shutter, then do CCS_HALT
  *   - (3) CCS_CLEAR: Put the CCS in the continuous clearing state
  *   - (4) CCS_CLEAR_CLOSE_SHTR: Close the shutter, then do CCS_CLEAR
  *   - (5) CCS_OPEN_SHTR: Open the shutter, then do CCS_HALT
  *   - (6) CCS_CLEAR_OPEN_SHTR: Open the shutter, then to CCS_CLEAR
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_exp_halt(int16 hcam, int16 cam_state) {
    return (pl_exp_abort(hcam, cam_state));
  }
  //@}

  /// @name Continuous-exposure functions
  //@{

  /**
  * Start a continuous exposure
  *
  * Begins collecting images continuously into a circular buffer.
  * This results in much faster acquisition times than collecting
  * one image at a time.
  * Assumes one region, timed mode
  * <br/>Referenced pvcam functions:
  *  - pl_exp_setup_cont
  *  - pl_exp_start_cont
  * @param hcam the camera number
  * @param exposure_time exposure time in the currently selected resolution
  * @param region the region, consisting of:
  *     - x_min minimum in the x direction
  *     - x_max maximum in the x direction
  *     - y_min minimum in the y direction
  *     - y_max maximum in the y direction
  *     - x_bin (default = 1) binning in the x direction
  *     - y_bin (default = 1) binning in the y direction
  * @param stream_size (output) the required stream size for the buffer
  *        to be passed to ccd_cont_get_frame
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_cont_start(int16 hCam,
    uns32 exposure_time,
    uns16 s1,
    uns16 s2,
    uns16 p1,
    uns16 p2,
    uns16 sbin,
    uns16 pbin,
    uns32 *stream_size)
  {
    rgn_type region;
    region.s1 = s1;
    region.s2 = s2;
    region.p1 = p1;
    region.p2 = p2;
    region.sbin = sbin;
    region.pbin = pbin;

    uns32 buffer_size;
    uns16 numberframes = 5;
    /* Init a sequence set the region, exposure mode and exposure time */
    if (!pl_exp_setup_cont( hCam, 1, &region, TIMED_MODE, exposure_time, stream_size,
      CIRC_OVERWRITE )) {
        return 0;
    }

    /* set up a circular buffer of 3 frames */
    buffer_size = *stream_size * 3;
    if (circular_buffer == NULL) {
      circular_buffer = new uns16[buffer_size];
      frame_size = *stream_size;
    } else if (frame_size != *stream_size) {
      delete[] circular_buffer;
      circular_buffer = new uns16[buffer_size];
      frame_size = *stream_size;
    }

    /* Start the acquisition */
    if (!pl_exp_start_cont(hCam, circular_buffer, buffer_size )) {
      return 0;
    }
    return 1;
  }

  /**
  * Check the status of a continuous acquisition.
  *
  * <br/>Referenced pvcam functions:
  *  - pl_exp_check_cont_status
  * @param hCam the camera number
  * @param status (output)  the status of the exposure.  One of:
  *   - (0) READOUT_NOT_ACTIVE: System is idle, no data is expected
  *   - (1) EXPOSURE_IN_PROGRESS: Data collection is active, no data have arrived yet 
  *   - (2) READOUT_IN_PROGRESS: Data collection is active, data have started to arrive
  *   - (3) READOUT_COMPLETE: At least one frame has arrived; safe to call ccd_cont_get_frame
  *   - (4) READOUT_FAILED: Something went wrong.  Function returns 0 and user should
  *     check pl_error_code. 
  *   - (5) ACQUISITION_IN_PROGRESS: For PI cameras only: either EXPOSURE_IN_PROGRESS
  *     or READOUT_IN_PROGRESS (these statuses are not available in PI cameras)
  * @param byte_cnt (output)  number of bytes returned so far for the current frame
  * @param buffer_cnt (output) number of frames collected so far
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_cont_check_status(int16 hCam, int16* status, uns32 *byte_cnt, uns32* buffer_cnt) {
    return pl_exp_check_cont_status( hCam, status, byte_cnt, buffer_cnt);
  }

  /**
  * Retrieve the latest frame during a continuous data collection cycle
  *
  * <br/>Referenced pvcam functions:
  *   - pl_exp_get_latest_frame
  * @param hCam the camera number
  * @param image (output) the buffer in which to put the frame.  Must be large
  * enough to hold the frame (see the stream_size parameter for ccd_cont_start)
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_cont_get_frame(int16 hCam, uns16* image) {
    uns16* p = NULL;
    if (!pl_exp_get_latest_frame( hCam, (void **)&p))
      return 0;
    memcpy(image, p, frame_size);
    return 1;
  }

  /**
  * Halt a continuous acquisition cycle
  *
  * Stop continuously collecting images
  * Reference pvcam functions:
  *   - pl_exp_stop_cont
  * @param hcam the camera number
  * @param cam_state (default CCS_HALT_CLOSE_SHTR)  Force the camera
  * control subsystem (CCS) into one of the states (camera dependent):
  *   - {0) CCS_NO_CHANGE: No change
  *   - (1) CCS_HALT: Halt all CCS activity, put in idle state
  *   - (2) CCS_HALT_CLOSE_SHTR: Close the shutter, then do CCS_HALT
  *   - (3) CCS_CLEAR: Put the CCS in the continuous clearing state
  *   - (4) CCS_CLEAR_CLOSE_SHTR: Close the shutter, then do CCS_CLEAR
  *   - (5) CCS_OPEN_SHTR: Open the shutter, then do CCS_HALT
  *   - (6) CCS_CLEAR_OPEN_SHTR: Open the shutter, then to CCS_CLEAR
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_cont_halt(int16 hcam, int16 cam_state) {
    uns16 ret = pl_exp_stop_cont(hcam, cam_state);
    return ret;
  }
  //@}

  /// @name Camera setup/configuration
  //@{

  /**
  * Retrieve the size of the ccd
  * <br/>Referenced pvcam functions:
  *  - pl_ccd_get_ser_size
  *  - pl_ccd_get_par_size
  * @param hcam the camera number
  * @param ser (output) the ccd size in the serial direction, pixels
  * @param par (output) the ccd size in the parallel direction, pixels
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_size(int16 hcam, uns16* ser, uns16* par)
  {

    if (!pl_ccd_get_ser_size(hcam, ser))
    {
      return(0);
    }
    if (!pl_ccd_get_par_size(hcam, par))
    {
      return(0);
    }

    return(1);
  }

  /**
  * Retrieve the status of the camera control subsystem (CCS)
  *
  * <br/>Referenced pvcam function:
  *  - pl_ccs_get_adc_offset (OBSOLETE; replaced with pl_get_param)
  * @param hcam the number of the camera
  * @param ccs_status (output) The CCS status.  One of:
  *   - (0) IDLE
  *   - (1) INITIALIZING
  *   - (2) RUNNING
  *   - (3) CONTINUOUSLY_CLEARING
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_ccs_status(int16 hcam, int16 *ccs_status) {

    //if (!pl_ccs_get_status(*hcam, shtr_status))
    if (!pl_get_param(hcam, PARAM_CCS_STATUS, ATTR_CURRENT, ccs_status))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Retrieve the status of the shutter
  *
  * <br/>Referenced pvcam function:
  *  - pl_shtr_get_status (OBSOLETE; replaced with pl_get_param)
  * @param hcam the number of the camera
  * @param shtr_status (output) The shutter status.  One of:
  *   - (0) SHTR_FAULT: Shutter has overheated
  *   - (1) SHTR_OPENING: Shutter is opening
  *   - (2) SHTR_OPEN: Shutter is open
  *   - (3) SHTR_CLOSING: Shutter is closing
  *   - (4) SHTR_CLOSED: Shutter is closed
  *   - (5) SHTR_UNKNOWN: The system cannot determine the shutter state
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_shtr_status(int16 hcam, int16 *shtr_status) {

    //if (!pl_shtr_get_status(*hcam, shtr_status))
    if (!pl_get_param(hcam, PARAM_SHTR_STATUS, ATTR_CURRENT, shtr_status))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Close the shutter, and do not open it during exposures.
  *
  * Equivalent to setting the PARAM_SHTR_OPEN_MODE parameter to
  * OPEN_NEVER
  *
  * <br/>Referenced pvcam function:
  *  - pl_shtr_set_open_mode (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_shtr_open_never(int16 hcam) {
    /* Prevents the shutter from opening on exposure. */
    if (!pl_shtr_set_open_mode(hcam, OPEN_NEVER))
    {
      return(0);
    }

    return(1);
  }

  /**
  * Open the shutter during exposures.
  *
  * Equivalent to setting the PARAM_SHTR_OPEN_MODE parameter to
  * OPEN_PRE_EXPOSURE
  * <br/>Referenced pvcam function:
  *  - pl_shtr_set_open_mode (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_shtr_open_normal(int16 hcam) {

    /* Prevents the shutter from opening on exposure. */
    if (!pl_shtr_set_open_mode(hcam, OPEN_PRE_EXPOSURE))
    {
      return(0);
    }

    return(1);
  }

  /**
  * Retrieve the shutter open delay in milliseconds
  *
  * Equivalent to getting the PARAM_SHTR_OPEN_DELAY parameter
  * <br/>Referenced pvcam function:
  *  - pl_shtr_get_open_dly (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param shtr_open_dly (output) the delay in msec
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_shtr_open_dly(int16 hcam, uns16 *shtr_open_dly) {

    if (!pl_shtr_get_open_dly(hcam, shtr_open_dly))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the shutter open delay in milliseconds
  *
  * Equivalent to setting the PARAM_SHTR_OPEN_DELAY parameter
  * <br/>Referenced pvcam function:
  *  - pl_shtr_set_open_dly (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param shtr_open_dly the delay in msec
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_shtr_open_dly(int16 hcam, uns16 shtr_open_dly) {

    if (!pl_shtr_set_open_dly(hcam, shtr_open_dly))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Retrieve the shutter close delay in milliseconds
  *
  * Equivalent to getting the PARAM_SHTR_CLOSE_DELAY parameter
  * <br/>Referenced pvcam function:
  *  - pl_shtr_get_close_dly (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param shtr_close_dly (output) the delay in msec
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_shtr_close_dly(int16 hcam, uns16 *shtr_close_dly) {

    if (!pl_shtr_get_close_dly(hcam, shtr_close_dly))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the shutter close delay in milliseconds
  *
  * Equivalent to setting the PARAM_SHTR_CLOSE_DELAY parameter
  * <br/>Referenced pvcam function:
  *  - pl_shtr_set_close_dly (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param shtr_close_dly the delay in msec
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_shtr_close_dly(int16 hcam, uns16 shtr_close_dly) {

    if (!pl_shtr_set_close_dly(hcam, shtr_close_dly))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Retrieve the clear cycles parameter
  *
  * Equivalent to getting the PARAM_CLEAR_CYCLES parameter
  * <br/>Referenced pvcam function:
  *  - pl_ccd_get_clear_cycles (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param cycles (output) the number of times the CCD is cleared
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_clear_cycles(int16 hcam, uns16 *cycles) {

    if (!pl_ccd_get_clear_cycles(hcam, cycles))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the clear cycles parameter
  *
  * Equivalent to setting the PARAM_CLEAR_CYCLES parameter
  * <br/>Referenced pvcam function:
  *  - pl_ccd_set_clear_cycles (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param cycles the number of times the CCD is cleared
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_clear_cycles(int16 hcam, uns16 clear_cycles) {

    if (!pl_ccd_set_clear_cycles(hcam, clear_cycles))
    {
      return(0);
    }

    return(1);
  }


  /**
  * Retrieve the clear strips parameter
  *
  * Equivalent to getting the PARAM_NUM_OF_STRIPS_PER_CLR parameter
  * <br/>Referenced pvcam function:
  *  - pl_get_param
  * @param hcam the camera number
  * @param strips (output) the number of strips per clear
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_clear_strips(int16 hcam, uns16 *strips) {

    if (!pl_get_param(hcam, PARAM_NUM_OF_STRIPS_PER_CLR, ATTR_CURRENT, strips))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the clear strips parameter
  *
  * Equivalent to setting the PARAM_NUM_OF_STRIPS_PER_CLR parameter
  * <br/>Referenced pvcam function:
  *  - pl_set_param
  * @param hcam the camera number
  * @param strips the number of strips per clear
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_clear_strips(int16 hcam, uns16 strips) {

    if (!pl_set_param(hcam, PARAM_NUM_OF_STRIPS_PER_CLR, &strips))
    {
      return(0);
    }

    return(1);
  }


  /**
  * Retrieve the current temperature of the ccd
  *
  * Equivalent to getting the PARAM_TEMP parameter (except that this
  * divides by 100 to get degrees centigrade)
  * <br/>Referenced pvcam function:
  *  - pl_ccd_get_tmp (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param cur_tmp (output) the measured temperature of the CCD, in degrees centigrade
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_tmp(int16 hcam, float *cur_tmp) {

    /* Local Variables */
    int16 tmp;   

    if (!pl_ccd_get_tmp(hcam, &tmp))
    {
      return(0);
    }

    *cur_tmp = (float)tmp / 100.0f;

    return(1);
  }   

  /**
  * Get the temperature setpoint of the ccd
  *
  * Equivalent to getting the PARAM_TEMP_SETPOINT parameter (except that this
  * divides by 100 to get degrees centigrade)
  * <br/>Referenced pvcam function:
  *  - pl_ccd_get_tmp_setpoint (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param tmp_setpoint (output) the desired temperature of the CCD, in degrees centigrade
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_tmp_setpoint(int16 hcam, float *tmp_setpoint) {

    /* Local Variables */
    int16 tmp_set;   

    if (!pl_ccd_get_tmp_setpoint(hcam, &tmp_set))
    {
      return(0);
    }

    *tmp_setpoint = (float)tmp_set / 100.0f;

    return(1);
  }

  /**
  * Set the temperature setpoint of the ccd
  *
  * Equivalent to setting the PARAM_TEMP_SETPOINT parameter (except that this
  * divides the input by 100 to get degrees centigrade)
  * <br/>Referenced pvcam function:
  *  - pl_ccd_set_tmp_setpoint (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param tmp_setpoint the desired temperature of the CCD, in degrees centigrade
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_tmp_setpoint(int16 hcam, float tmp_setpoint) {

    /* Local Variables */
    int16 tmp_set;   

    tmp_set = (int16)(tmp_setpoint * 100.0f);

    if (!pl_ccd_set_tmp_setpoint(hcam, tmp_set))
    {
      return(0);
    }

    return(1);
  }

  /**
  * Get the maximum gain setting for the camera
  *
  * Equivalent to getting the PARAM_GAIN_INDEX parameter with ATTR_MAX
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_get_max_gain (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param max_gain (output) the maximum gain setting (camera dependent; may
  *  be as high as 16)
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_max_gain(int16 hcam, int16 *max_gain) {

    if (!pl_spdtab_get_max_gain(hcam, max_gain))
    {
      return(0);
    };

    return(1);
  }   


  /**
  * Get the current gain setting
  *
  * Equivalent to getting the PARAM_GAIN_INDEX parameter
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_get_gain (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param gain (output) the gain setting (the meaning of the gain
  *  is camera dependent)
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_gain(int16 hcam, int16 *gain) {

    if (!pl_spdtab_get_gain(hcam, gain))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Set the current gain setting
  *
  * Equivalent to setting the PARAM_GAIN_INDEX parameter
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_set_gain (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param gain the gain setting (the meaning of the gain
  *  is camera dependent)
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_gain(int16 hcam, int16 gain) {

    if (!pl_spdtab_set_gain(hcam, gain))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Retrieve the on/off indicator for the gain multiplication functionality
  *
  * Referenced pv_(s|g)et_param ID:
  *  - PARAM_GAIN_MULT_ENABLE
  * @param hcam the number of the camera
  * @param enabled 1 if enabled, 0 if not
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_gain_mult_enable(int16 hcam, int16 *enabled) {

    if (!pl_get_param(hcam, PARAM_GAIN_MULT_ENABLE, ATTR_CURRENT, enabled))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Turn the gain multiplication functionality on or off
  *
  * Referenced pv_(s|g)et_param ID:
  *  - PARAM_GAIN_MULT_ENABLE
  * @param hcam the number of the camera
  * @param enabled 1 if enabled, 0 if not
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_gain_mult_enable(int16 hcam, int16 enabled) {

    if (!pl_set_param(hcam, PARAM_GAIN_MULT_ENABLE, &enabled))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Retrieve the gain multiplication factor
  *
  * Referenced pv_(s|g)et_param ID:
  *  - PARAM_GAIN_MULT_FACTOR
  * @param hcam the number of the camera
  * @param factor the multiplication factor
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_gain_mult_factor(int16 hcam, uns16 *factor) {

    if (!pl_get_param(hcam, PARAM_GAIN_MULT_FACTOR, ATTR_CURRENT, factor))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the gain multiplication factor
  *
  * Referenced pv_(s|g)et_param ID:
  *  - PARAM_GAIN_MULT_FACTOR
  * @param hcam the number of the camera
  * @param enabled 1 if enabled, 0 if not
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_gain_mult_factor(int16 hcam, uns16 factor) {

    if (!pl_set_param(hcam, PARAM_GAIN_MULT_FACTOR, &factor))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Get the time for each pixel in nanoseconds
  *
  * Equivalent to getting the PARAM_PIX_TIME parameter
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_get_time (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param speed (output) the actual speed for the current speed setting
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_speed(int16 hcam, uns16 *speed) {

    if (!pl_spdtab_get_time(hcam, speed))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Get the number of speed table entries
  *
  * Equivalent to getting the PARAM_SPDTAB_INDEX parameter with ATTR_MAX
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_get_entries (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param entries (output) the number of entries in the speed table
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_speed_entries(int16 hcam, int16 *entries) {

    if (!pl_spdtab_get_entries(hcam, entries))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Get the number of available readout ports
  *
  * Equivalent to getting the PARAM_READOUT_PORT parameter with ATTR_MAX
  * <br/>Referenced pvcam function:
  *  - pl_get_param
  * @param hcam the camera number
  * @param entries (output) the number of entries in the speed table
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_readout_port_entries(int16 hcam, int16 *entries) {

    if (!pl_get_param(hcam, PARAM_READOUT_PORT, ATTR_MAX, entries))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Get the bit depth for the currently selected speed choice.
  *
  * Although this number might range between 6 and
  * 16, the data will always be returned in an unsigned 16-bit
  * word. This value indicates the number of valid bits within
  * that word.
  * Equivalent to getting the PARAM_BIT_DEPTH parameter
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_get_bits (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param bits (output) the bit depth
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_bits(int16 hcam, int16 *bits) {

    if (!pl_spdtab_get_bits(hcam, bits))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Get the CCD readout speed from a table of available choices
  *
  * Equivalent to getting the PARAM_SPDTAB_INDEX parameter
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_get_num (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param speed (output) the table index
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_speed_mode(int16 hcam, int16 *speed) {

    if (!pl_spdtab_get_num(hcam, speed))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the CCD readout speed from a table of available choices.
  *
  * NOTE: The gain will always be reset to 1x after setting this parameter.
  * Equivalent to setting the PARAM_SPDTAB_INDEX parameter
  * <br/>Referenced pvcam function:
  *  - pl_spdtab_set_num (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param speed the table index
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_speed_mode(int16 hcam, int16 speed) {

    if (!pl_spdtab_set_num(hcam, speed))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Get the CCD readout port
  *
  * Equivalent to getting the PARAM_READOUT_PORT parameter
  * <br/>Referenced pvcam function:
  *  - pl_get_param
  * Possible readout port values (the available ports are camera-specific;
  * use ccd_get_readout_port_entries to determine the number of available ports):
  * <ul><li>READOUT_PORT_MULT_GAIN = 0</li>
  * <li>READOUT_PORT_NORMAL = 1</li>
  * <li>READOUT_PORT_LOW_NOISE = 2</li>
  * <li>READOUT_PORT_HIGH_CAP = 3</li></ul>
  * @param hcam the camera number
  * @param port (output) the port number
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_readout_port(int16 hcam, int16 *port) {

    if (!pl_get_param(hcam, PARAM_READOUT_PORT, ATTR_CURRENT, port))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the CCD readout port choice
  *
  * NOTE: The gain, speed, and bit depth may be altered as a result of
  * setting this parameter.  You should maintain a list of available readout
  * ports and associated settings, and set all of them after calling this function.
  * Equivalent to setting the PARAM_READOUT_PORT parameter
  * <br/>Referenced pvcam function:
  *  - pl_set_param
  * @param hcam the camera number
  * @param port the readout port index
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_readout_port(int16 hcam, int16 port) {

    if (!pl_set_param(hcam, PARAM_READOUT_PORT, &port))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Get the maximum number of command retries.  This should normally
  * not be changed since it "is matched to the
  * communications link, hardware platform, and operating
  * system" [PVCAM 2.6 Manual, p. 36]
  *
  * Equivalent to getting the PARAM_DD_RETRIES parameter
  * <br/>Referenced pvcam function:
  *  - pl_dd_get_retries (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param retries (output) the maximum number of retries
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_retries(int16 hcam, uns16 *retries) {

    if (!pl_dd_get_retries(hcam, retries))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the maximum number of command retries.  This should normally
  * not be changed since it "is matched to the
  * communications link, hardware platform, and operating
  * system" [PVCAM 2.6 Manual, p. 36]
  *
  * Equivalent to setting the PARAM_DD_RETRIES parameter
  * <br/>Referenced pvcam function:
  *  - pl_dd_set_retries (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param retries the maximum number of retries
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_retries(int16 hcam, uns16 retries) {

    if (!pl_dd_set_retries(hcam, retries))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Get the maximum time to wait for acknowledgement.  This should normally
  * not be changed since it "is matched to the
  * communications link, hardware platform, and operating
  * system" [PVCAM 2.6 Manual, p. 36]
  *
  * Equivalent to getting the PARAM_DD_TIMEOUT parameter
  * <br/>Referenced pvcam function:
  *  - pl_dd_get_timeout (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param m_sec (output) the timeout setting in milliseconds
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_timeout(int16 hcam, uns16 *m_sec) {

    if (!pl_dd_get_timeout(hcam, m_sec))
    {
      return(0);
    }

    return(TRUE);
  }   

  /**
  * Set the maximum time to wait for acknowledgement.  This should normally
  * not be changed since it "is matched to the
  * communications link, hardware platform, and operating
  * system" [PVCAM 2.6 Manual, p. 36]
  *
  * Equivalent to setting the PARAM_DD_TIMEOUT parameter
  * <br/>Referenced pvcam function:
  *  - pl_dd_set_timeout (OBSOLETE: should be replaced with pl_set_param)
  * @param hcam the camera number
  * @param m_sec the timeout setting in milliseconds
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_set_timeout(int16 hcam, uns16 m_sec) {

    if (!pl_dd_set_timeout(hcam, m_sec))
    {
      return(0);
    }

    return(1);
  }   

  /**
  * Determine whether this camera can run in frame transfer mode
  * (set through PARAM_PMODE)
  * 
  * Equivalent to getting the PARAM_FRAME_CAPABLE parameter
  * <br/>Referenced pvcam function:
  *  - pl_ccd_get_frame_capable (OBSOLETE: should be replaced with pl_get_param)
  * @param hcam the camera number
  * @param frame_capable (output) 1 if the camera is frame capable, 0 if not
  * @return 1 on success, 0 on failure
  */
  unsigned short ccd_get_frame_capable(int16 hcam, uns16 *frame_capable) {

    if (!pl_ccd_get_frame_capable(hcam, frame_capable))
    {
      return(0);
    }

    return(TRUE);
  }
}
//@}
