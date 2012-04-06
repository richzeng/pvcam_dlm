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

print, 'INIT: Initializing...'
pvcam_init, hcam, error=error  ;--- does hcam get returned here?
print, 'INIT: Init Error state = ', error

;
;--- SET TEMPERATURE TO ROOM TEMP
;
pvcam_set_tmp_setpoint, hcam, 20.0, error=error
print, 'TEMP: setpoint = ',pvcam_get_tmp_setpoint(hcam, error=error)
print, 'TEMP: temp now = ',pvcam_get_tmp(hcam, error=error)

;
;--- GET DETECTOR SIZE, TO MAKE THIS ROUTINE MORE GENERAL
;
print, '===== SIZE ====='
Nxy = pvcam_get_size(hcam, error=error)
if error then message, 'pvcam_get_size error'

pvcam_set_clear_cycles, hcam, 2, error=error


DOMAIN = uint([0, Nxy[0]-1, 0, Nxy[1]-1])   ;--- unsigned short integer
BIN = 8U   ;--- this is an unsigned short integer

;--- Allocate memory for the image we are about to snap
;    We use a pointer to an unsigned integer array [0-65535]
;    The /nozero keyword tells the IDL that there's no need
;    to fill the array with zeros as an initial state. 
;    The initial values will be random bits of recycled memory.
;    The size of the array is the full array size Nxy, scaled
;    down by the binning, and rounded down.

pimage = ptr_new(uintarr(Nxy[0]/BIN, Nxy[1]/Bin, /nozero) )


stream_size = 0UL  ;--- *** I don't remember what this does!! ***
status = 0
bytcnt = 0UL      ;--- this is the number of bytes transferred so far
buffer_cnt = 0UL  ;--- number of frames collected so far


;--- Note status values are like this:
exp_status = ['READOUT_NOT_ACTIVE', 'EXPOSURE_IN_PROGRESS', 'READOUT_IN_PROGRESS', $
              'READOUT_COMPLETE', 'READOUT_FAILED', 'ACQUISITION_IN_PROGRESS']


  ;--- Here we code-up several different tests that we can run.
  ;    To change from one test to a different test, change test_number here
test_number = 1


case test_number of

 1: begin  ;--- this will be a test of continuous exposing. 5 shots
 
     exp_time_fp = 0.25                        ;---- single-precision, floating point [seconds]
     exp_time_ul = ulong(exp_time_fp * 1000.)  ;---- unsigned long [msec]

     tstart = systime(1)  ;--- note the initial system clock time [in seconds]
     pvcam_cont_exp_start, hcam, exp_time_ul, DOMAIN[0], DOMAIN[1], DOMAIN[2], DOMAIN[3], BIN[0], BIN[1], stream_size, error=error
       if error then message, 'pvcam_cont_exp_start ERROR!'

     repeat begin
       es = pvcam_exp_check_status(hcam, bytcnt, buffer_cnt, error=error)
       if error then message, 'pvcam_exp_check_status ERROR!'
       print, 'bytcnt, buffer_cnt, status = ', bytcnt, buffer_cnt, exp_status[es]
       until 
     endrep (es EQ 0) or (es EQ 3) or (es EQ 4)
     print, 'Exposure loop ended because ', exp_status[es]
     print, 'Elapsed time = ', systime(1) - tstart 
 
  end
  
 2: begin
 
 
  end

else:
endcase




print, 'INIT: Un-Initializing...'
pvcam_uninit, hcam, error=error


           

end
