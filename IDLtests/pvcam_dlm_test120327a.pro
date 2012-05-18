; (c) Kenneth A. Goldberg  http://goldberg.lbl.gov  KAGoldberg(at)lbl.gov
; Lawrence Berkeley National Laboratory
; 3/26/12
; IDL files: pvcam_dlm_test120326a.pro
;
; IDL Script to test the functionality of the pvcam code
; contained in pvcam_dlm, created by Richie Zeng, based 
; on Bob Gunion's code. See pvcam_dlm.cpp
;


; THIS CODE IS DESIGNED TO SNAP AN IMAGE.
; IN A FEW DIFFERENT WAYS.


;
; 
; Check how the hcam handle is treated here.
; Test by turning ON-OFF-ON
;
;
print, '***** pvcam_dlm_test120326a.pro *****'
print, '===== INIT ====='

hcam = 0
pvcam_uninit, hcam, error=error

print, 'INIT: Initializing...'
pvcam_init, hcam, error=error  ;--- does hcam get returned here?
print, 'INIT: Init Error state = ', error

shtr_open_dly0 = 1UL
shtr_close_dly0 = 1UL

pvcam_set_shtr_open_dly, hcam, shtr_open_dly0, error=error
print, 'SHUTTER: shtr_open_dly = ',  pvcam_get_shtr_open_dly(hcam, error=error),  '    error = ', error

pvcam_set_shtr_close_dly, hcam, shtr_close_dly0, error=error
print, 'SHUTTER: shtr_close_dly = ',  pvcam_get_shtr_close_dly(hcam, error=error),  '   error = ', error

pvcam_set_retries, hcam, 100, error=error
;
;--- SET TEMPERATURE TO ROOM TEMP
;
pvcam_set_tmp_setpoint, hcam, 20.0, error=error
print, 'TEMP: setpoint = ',pvcam_get_tmp_setpoint(hcam, error=error)
print, 'TEMP: temp now = ',pvcam_get_tmp(hcam, error=error)

;
;--- GET DETECTOR SIZE, TO MAKE THIS ROUTINE MORE GENERAL
;
print, '===== CCD SIZE ====='
Nxy = pvcam_get_size(hcam, error=error)
print, Nxy
if error then message, 'pvcam_get_size error'

pvcam_set_clear_cycles, hcam, 0, error=error
pvcam_set_speed_mode, hcam, 1


DOMAIN = uint([0, Nxy[0]-1, 0, Nxy[1]-1])   ;--- unsigned short integer
BIN = [32U,32U]   ;--- this is an unsigned short integer

;--- Allocate memory for the image we are about to snap
;    We use a pointer to an unsigned integer array [0-65535]
;    The /nozero keyword tells the IDL that there's no need
;    to fill the array with zeros as an initial state. 
;    The initial values will be random bits of recycled memory.
;    The size of the array is the full array size Nxy, scaled
;    down by the binning, and rounded down.

image = uintarr(Nxy[0]/BIN[0], Nxy[1]/BIN[1], /nozero)

stream_size = 0UL  ;--- *** I don't remember what this does!! ***
status = 0
bytcnt = 0UL       ;--- this is the number of bytes transferred so far
buffer_cnt = 0UL   ;--- number of frames collected so far


;--- Note status values are like this:
exp_status = ['READOUT_NOT_ACTIVE', 'EXPOSURE_IN_PROGRESS', 'READOUT_IN_PROGRESS', $
              'READOUT_COMPLETE', 'READOUT_FAILED', 'ACQUISITION_IN_PROGRESS']

exp_time_fp = 0.001                      ;---- single-precision, floating point [seconds]
exp_time_ul = ulong(exp_time_fp * 1000.)  ;---- unsigned long [msec]
print, 'Exposure time (ms): ', exp_time_ul

  ;--- Here we code-up several different tests that we can run.
  ;    To change from one test to a different test, change test_number here
test_number = 1


case test_number of

 1: begin  ;--- this will be a test of continuous exposing. 5 shots
    for ii=0,2 do begin
     
     print, 'TESTING CONTINUOUS EXPOSURE ', ii
 
     tstart = systime(1)  ;--- note the initial system clock time [in seconds]
     pvcam_cont_start, hcam, exp_time_ul, DOMAIN[0], DOMAIN[1], DOMAIN[2], DOMAIN[3], BIN[0], BIN[1], stream_size, error=error
       if error then message, 'pvcam_cont_exp_start ERROR!'

     last_print_time = systime(1)-10d

     repeat begin
       es = pvcam_cont_check_status(hcam, bytcnt, buffer_cnt, error=error)
       if error then message, 'pvcam_exp_check_status ERROR!'
       if (systime(1) - last_print_time) GT 0.1d then begin
         pvcam_cont_get_frame, hcam, image, error=error
         ;print, image
         print, 'bytcnt, buffer_cnt, status,elapsed_time = ', bytcnt, buffer_cnt, exp_status[es], systime(1)-tstart, ii
         last_print_time = systime(1)
       endif
     endrep until (es EQ 0) or (es EQ 3) or (es EQ 4)
     ; pvcam_exp_halt, hcam, 2, error=error ;2 is close shutter
     print, 'Camera halted. Error = ', error
     ;pvcam_cont_get_frame, hcam, image, error=error
     print, 'Exposure loop ended because ', exp_status[es]
     print, 'Elapsed time = ', systime(1) - tstart 
     
     print, 'Getting the image'
     ; window, xsize=512,ysize=512
     print, 'Size of image = '
     print, size(image)
     ; tvscl, congrid(image, 512,512)
    endfor ; ii
  end
  
 2: begin
     print, 'TESTING SINGLE EXPOSURE'

     tstart = systime(1)  ;--- note the initial system clock time [in seconds]

     pvcam_exp_setup, hcam, exp_time_ul, DOMAIN[0], DOMAIN[1], DOMAIN[2], DOMAIN[3], BIN[0], BIN[1], stream_size, error=error
     pvcam_exp_start, hcam, image, error=error
       if error then message, 'pvcam_exp_start ERROR!'

     last_print_time = systime(1)-10d

     repeat begin
       es = pvcam_exp_check_status(hcam, bytcnt, error=error)
       if error then message, 'pvcam_exp_check_status ERROR!'
       if (systime(1) - last_print_time) GT 0.1d then begin
         ;pvcam_cont_get_frame, hcam, image, error=error
         ;print, image
         print, 'bytcnt, status,elapsed_time = ', bytcnt, ' es= ',es,'  ', exp_status[es], systime(1)-tstart
         last_print_time = systime(1)
         print, 'min image = ', min(image)
       endif
     endrep until (es EQ 0) or (es EQ 3) or (es EQ 4)
     print, 'bytcnt, status,elapsed_time = ', bytcnt, ' es= ',es,'  ', exp_status[es], systime(1)-tstart
     
     ; pvcam_exp_halt, hcam, 2, error=error ;2 closes the shutter
     print, 'Camera halted. Error = ', error
     print, 'Exposure loop ended because ', exp_status[es]
     print, 'Elapsed time = ', systime(1) - tstart 
     
     print, 'Getting the image'
     ;window, xsize=512,ysize=512
     print, 'Size of image = '
     print, size(image)
     ;erase, 50b
     ;tvscl, congrid(image, 512,512)
  end

else:
endcase




print, 'INIT: Un-Initializing...'
pvcam_uninit, hcam, error=error


           

end
