; (c) Kenneth A. Goldberg  http://goldberg.lbl.gov  KAGoldberg(at)lbl.gov
; Lawrence Berkeley National Laboratory
; 3/26/12
; IDL files: pvcam_dlm_test120326a.pro
;
; IDL Script to test the functionality of the pvcam code
; contained in pvcam_dlm, created by Richie Zeng, based 
; on Bob Gunion's code. See pvcam_dlm.cpp
;


; 
; Check how the hcam handle is treated here.
; Test by turning ON-OFF-ON
; Note: Just in case the camera is already initialized, always make a call to
; pvcam_unit to make sure you don't get any unnecessary errors.
;
print, '***** pvcam_dlm_test120326a.pro *****'
print, ''
print, '===== INIT ====='

print, 'INIT: Initializing...'
hcam = 0

pvcam_uninit, hcam, error=error
pvcam_init, hcam, error=error  ;--- hcam gets returned here 
print, 'INIT: Init    Error state = ', error

print, 'INIT: Un-Initializing...'
pvcam_uninit, hcam, error=error
print, 'INIT: UnInit    Error state = ', error

print, 'Re-Initializing...'
pvcam_init, hcam, error=error
print, 'INIT: Init    Error state = ', error


;
; Returns the size of the image
;
print, ' '
print, '===== SIZE ====='
print, 'SIZE: pvcam_get_size = ',  pvcam_get_size(hcam, error=error),  ' error = ', error


;
;  We don't want to screw up these values (!!), although we need the ability to test them
;  and set them. Let's read them before uncommenting the lines below that enable setting.
;  We should also test to see if values are reset when the camera is power-cycled.
;
;  Lookup what the pvcam_get_shtr_status return values are.
;
print, ' '
print, '===== SHUTTER ====='  ;********************************
;--- Report and remember the initial values. I think they are in msec.
shtr_open_dly0  = pvcam_get_shtr_open_dly(hcam, error=error)
print, 'SHUTTER: initial shtr_open_dly = ',  shtr_open_dly0,  '    error = ', error
shtr_close_dly0 = pvcam_get_shtr_close_dly(hcam, error=error)
print, 'SHUTTER: initial shtr_close_dly = ', shtr_close_dly0, '    error = ', error

shtr_open_dly0 = 10UL
shtr_close_dly0 = 10UL

  ;--- Change the values and test the changes  (be careful here about the variable type!!!!!
  ;     it may need a typecast like uint() or fix()
  ;
pvcam_set_shtr_open_dly, hcam, shtr_open_dly0 +10, error=error
print, 'SHUTTER: shtr_open_dly = ',  pvcam_get_shtr_open_dly(hcam, error=error),  '    error = ', error

pvcam_set_shtr_close_dly, hcam, shtr_close_dly0 + 10, error=error
print, 'SHUTTER: shtr_close_dly = ',  pvcam_get_shtr_close_dly(hcam, error=error),  '   error = ', error

   ;--- restore the original values
pvcam_set_shtr_open_dly, hcam, shtr_open_dly0, error=error
pvcam_set_shtr_open_dly, hcam, shtr_close_dly0, error=error
print, 'SHUTTER: original values restored'

;print, 'SHUTTER: set to never open'
;pvcam_shtr_open_never, hcam, error=error
;print, 'SHUTTER: Open Never    Error state = ', error

;print, 'SHUTTER: set to open normally'
;pvcam_shtr_open_normal, hcam, error=error
;print, 'SHUTTER: Open Normal    Error state = ', error


  ;--- reports the current status of the shutter
  ;--- {SHTR_FAULT, SHTR_OPENING, SHTR_OPEN, SHTR_CLOSING, SHTR_CLOSED, SHTR_UNKNOWN}
print, 'SHUTTER: pvcam_get_shtr_status = ',  pvcam_get_shtr_status(hcam, error=error),  '    error = ', error


;
; There should be a command to set the clear 'mode' not just the number of clears.
;     See page 59 of the PVCAM 2.6 User Manual. We should experiment with this!
;
;  {CLEAR_NEVER, CLEAR_PRE_EXPOSURE, CLEAR_PRE_SEQUENCE, CLEAR_POST_SEQUENCE,
;     CLEAR_PRE_POST_SEQUENCE, CLEAR_PRE_EXPOSURE_POST_SEQ}
;
print, ' '
print, '===== CLEARS ====='  ;********************************
pvcam_set_clear_cycles, hcam, 0, error=error
  print, 'CLEARS: clear_cycles = ', pvcam_get_clear_cycles(hcam, error=error),   ' error= ', error
pvcam_set_clear_cycles, hcam, 1, error=error
  print, 'CLEARS: clear_cycles = ', pvcam_get_clear_cycles(hcam, error=error),   ' error= ', error
pvcam_set_clear_cycles, hcam, 2, error=error
  print, 'CLEARS: clear_cycles = ', pvcam_get_clear_cycles(hcam, error=error),   ' error= ', error


pvcam_set_clear_cycles, hcam, 0, error=error



;
; Temperature is self-explanatory  
;
print, ' '
print, '===== TEMPERATURE ====='  ;********************************
pvcam_set_tmp_setpoint, hcam, 18.5, error=error
print, 'TEMP: setpoint = ',pvcam_get_tmp_setpoint(hcam, error=error)
pvcam_set_tmp_setpoint, hcam, 20.0, error=error
print, 'TEMP: setpoint = ',pvcam_get_tmp_setpoint(hcam, error=error)
print, 'TEMP: temp now = ',pvcam_get_tmp(hcam, error=error)


;
; I don't remember the distinction between get_speed and get_speed_mode
; We should nail this down and put the answer in comments so we always know
; what it means.
;
print, ' '
print, '===== SPEED ====='  ;********************************
print, 'SPEED: Speed Entries = ', pvcam_get_speed_entries(hcam, error=error), '    error= ', error

; returns the time for each pixel in nanoseconds
print, 'SPEED: Get Speed = ', pvcam_get_speed(hcam, error=error), '    error= ', error
pvcam_set_speed_mode, hcam, 1, error=error
print, '    Setting speed mode: 1    error = ', error
; returns the table index that contains several predefined settings for gain, pixel speed, etc
print, 'SPEED: Get Speed Mode = ', pvcam_get_speed_mode(hcam, error=error), '     error= ', error
pvcam_set_speed_mode, hcam, 2, error=error
print, '    Setting speed mode: 2    error = ', error
print, 'SPEED: Get Speed Mode = ', pvcam_get_speed_mode(hcam, error=error), '     error =', error

pvcam_set_speed_mode, hcam, 1UL, error=error


;
;
; If I remember correctly, allowed gain settings are {1,2,3}
; We should test this. The code below exercises each option. Modify as necessary.
;
print, ' '
print, '===== GAIN ====='  ;********************************
max_gain = pvcam_get_max_gain(hcam, error=error)
  print, 'GAIN: Max Gain = ', max_gain

  print, 'Checking the 3 gain settings. We should see 1,2,3 below'
pvcam_set_gain, hcam, 1, error=error
  print, 'GAIN: gain = ', pvcam_get_gain(hcam, error=error), ' error=', error
pvcam_set_gain, hcam, 2, error=error
  print, 'GAIN: gain = ', pvcam_get_gain(hcam, error=error), ' error=', error
pvcam_set_gain, hcam, 3, error=error
  print, 'GAIN: gain = ', pvcam_get_gain(hcam, error=error), ' error=', error

;
; The retries is the number of times that the system signals for a retransmission before it quits 
; and returns an error. A retransmission happens when a command or signal is garbled.
; If we can change it, then read the initial, increment by one, test, then set it back to initial.
;
print, ' '
print, '===== RETRIES ====='  ;********************************
retries0  = pvcam_get_retries(hcam, error=error)
print, 'RETRIES: initial retries = ',  retries0,  ' error=', error

;--- Change the value and test the change  (be careful here about the variable type!!!!!
;     it may need a typecast like uint() or fix()
pvcam_set_retries, hcam, retries0 + 1, error=error
print, 'RETRIES: pvcam_set_retries to ', retries0+1, '     error = ', error
print, 'RETRIES: pvcam_get_retries = ',  pvcam_get_retries(hcam, error=error),  ' error=', error

   ;--- restore the original value
pvcam_set_retries, hcam, retries0, error=error


;
; The timeout is the maximum amount of time that the driver waits to receive a response after
; issuing a command before returning an error.
; If we can change it, then read the initial, increment by one, test, then set it back to initial.
;
print, ' '
print, '===== TIMEOUT ====='  ;********************************
timeout0  = pvcam_get_timeout(hcam, error=error)
print, 'TIMEOUT: initial timeout = ',  timeout0,  '     error=', error

  ;--- Change the value and test the change  (be careful here about the variable type!!!!!
  ;     it may need a typecast like uint() or fix()
  ;
pvcam_set_timeout, hcam, timeout0 + 1, error=error
print, 'TIMEOUT: pvcam_set_timout to ', timeout0+1, '     error = ', error
print, 'TIMEOUT: pvcam_get_timeout = ',  pvcam_get_timeout(hcam, error=error),  '     error=', error

   ;--- restore the original value
pvcam_set_timeout, hcam, timeout0, error=error
print, 'TIMEOUT: Setting timeout back to original.      error = ', error

;
print, ' '
print, '===== BITS ====='  ;********************************
print, 'BITS: pvcam_get_bits = ',  pvcam_get_bits(hcam, error=error),  '     error=', error


;
print, ' '
print, '===== FRAME CAPABLE ====='  ;********************************
print, 'FRAME CAPABLE: pvcam_get_frame_capable = ',  pvcam_get_frame_capable(hcam, error=error),  '      error=', error


print, ' '
print, 'INIT: uninitializing'
pvcam_uninit, hcam, error=error
print, 'INIT: UnInit    Error state = ', error

print, ' '
print, ' '
print, 'Tests complete!'


end