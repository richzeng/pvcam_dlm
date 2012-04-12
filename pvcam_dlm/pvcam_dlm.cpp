//pvcam_dlm.cpp

/******************************************************************************
Copyright (c) Richie Zeng rfzeng@lbl.gov
Date: March 2012
Lawrence Berkeley National Lab


IDL wrapper to support functions from the PVCam API. Adapted from code written
by Bob Gunion in 2008.

******************************************************************************/

#include "pvcam_dlm.h"
#include "stdafx.h"


int IDL_Load(void)
{
  /*Call the startup function to add the routines to IDL.*/

	//functions in the strings are recognized by IDL and must be in all caps
	static IDL_SYSFUN_DEF2 PVCAM_functions[] = {
		{(IDL_FUN_RET)pvcam_init, "PVCAM_INIT", 1, 1, 0, 0},
		{(IDL_FUN_RET)pvcam_uninit, "PVCAM_UNINIT", 1, 1, 0, 0},
		{(IDL_FUN_RET)pvcam_get_size, "PVCAM_GET_SIZE", 3, 3, 0, 0},
		{(IDL_FUN_RET)pvcam_setup, "PVCAM_SETUP", 7, 9, 0, 0},

		{(IDL_FUN_RET)pvcam_exp_start, "PVCAM_EXP_START", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_exp_check_status, "PVCAM_EXP_CHECK_STATUS", 3, 3, 0, 0},
		{(IDL_FUN_RET)pvcam_exp_halt, "PVCAM_EXP_HALT", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_ccs_status, "PVCAM_GET_CCS_STATUS", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_shtr_status, "PVCAM_GET_SHTR_STATUS", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_shtr_open_never, "PVCAM_SHTR_OPEN_NEVER", 1, 1, 0, 0},
		{(IDL_FUN_RET)pvcam_shtr_open_normal, "PVCAM_SHTR_OPEN_NORMAL", 1, 1, 0, 0},

		{(IDL_FUN_RET)pvcam_get_shtr_open_dly, "PVCAM_GET_SHTR_OPEN_DLY", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_shtr_open_dly, "PVCAM_SET_SHTR_OPEN_DLY", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_shtr_close_dly, "PVCAM_GET_SHTR_CLOSE_DLY", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_shtr_close_dly, "PVCAM_SET_SHTR_CLOSE_DLY", 2, 2, 0, 0},

		{(IDL_FUN_RET)pvcam_get_clear_cycles, "PVCAM_GET_CLEAR_CYCLES", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_clear_cycles, "PVCAM_SET_CLEAR_CYCLES", 2, 2, 0, 0},

		{(IDL_FUN_RET)pvcam_get_tmp, "PVCAM_GET_TMP", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_tmp_setpoint, "PVCAM_GET_TMP_SETPOINT", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_tmp_setpoint, "PVCAM_SET_TMP_SETPOINT", 2, 2, 0, 0},

		{(IDL_FUN_RET)pvcam_get_max_gain, "PVCAM_GET_MAX_GAIN", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_gain, "PVCAM_GET_GAIN", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_gain, "PVCAM_SET_GAIN", 2, 2, 0, 0},

		{(IDL_FUN_RET)pvcam_get_speed, "PVCAM_INIT", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_speed_entries, "PVCAM_INIT", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_speed_mode, "PVCAM_INIT", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_speed_mode, "PVCAM_INIT", 2, 2, 0, 0},

		{(IDL_FUN_RET)pvcam_get_bits, "PVCAM_GET_BITS", 2, 2, 0, 0},

		{(IDL_FUN_RET)pvcam_get_retries, "PVCAM_GET_RETRIES", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_retries, "PVCAM_SET_RETRIES", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_timeout, "PVCAM_GET_TIMEOUT", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_set_timeout, "PVCAM_SET_TIMEOUT", 2, 2, 0, 0},
		{(IDL_FUN_RET)pvcam_get_frame_capable, "PVCAM_GET_FRAME_CAPABLE", 2, 2, 0, 0},
	};

	return IDL_SysRtnAdd(PVCAM_functions, IDL_TRUE, ARRLEN(PVCAM_functions));
}
