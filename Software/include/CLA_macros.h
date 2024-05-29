/*
 * CLA_macros.h
 *
 *  Created on: 2017. júl. 24.
 *      Author: Andras Futo
 */

#ifndef INCLUDE_CLA_MACROS_H_
#define INCLUDE_CLA_MACROS_H_

#define MAG_CLA(A,B) (CLAsqrt(A*A + B*B))                          //magnitude of comlpex vector

static inline float __cla_fsat(float val, float max, float min)
{
  float temp;
  // (val < min)? temp = min : temp = val
  temp = __mmaxf32(val, min);
  // (temp > max)? temp = max : temp = temp
  temp = __mminf32(temp, max);
  return(temp);
}


#endif /* INCLUDE_CLA_MACROS_H_ */
