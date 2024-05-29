/*
 * ADC.h
 *
 *  Created on: 2016 márc. 20
 *      Author: Szako
 */

#ifndef INCLUDE_ADC_H_
  #define INCLUDE_ADC_H_
  #include "F2806x_Device.h"
  #include "F2806x_GlobalPrototypes.h"
  #include "F2806x_usDelay.h"
  #include "usefulmacros.h"
  #define ADC_usDELAY  1000L

  typedef struct {
    float value;
    float gain;
    float offset;
    float compensation;
  } Meas_t;

  void ADC_Init(void);
  void adc_isr_assign_function(fprt_g fptr_recieved);

#endif /* INCLUDE_ADC_H_ */
