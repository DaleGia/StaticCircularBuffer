/**
 * @file fifoStaticCircularBuffer.h
 * Copyright (c) 2021 Dale Giancono All rights reserved.
 * 
 * @brief
 * An implementation of a FIFO static circular buffer.
 * inspired by https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 */

/*****************************************************************************/
/*INLCUDE GUARD                                                              */
/*****************************************************************************/
#ifndef FIFOSTATICCIRCULARBUFFER_H_
#define FIFOSTATICCIRCULARBUFFER_H_

/*****************************************************************************/
/*INLCUDES                                                                   */
/*****************************************************************************/
#include "stdint.h"

/*****************************************************************************/
/*PUBLIC MACROS                                                              */
/*****************************************************************************/

/*****************************************************************************/
/*PUBLIC object definition                                                   */
/*****************************************************************************/
 /**
* @brief 
* Enqueues data to the circular buffer.
* 
* @param data 
* Data to be enqueued to circular buffer.
*
* @return none
*/
typedef struct 
{  
  void* _buffer;
  uint32_t _dataSize;
  uint32_t _bufferSize;
  uint32_t _head;
  uint32_t _tail;
  uint8_t _fullFlag;
  uint8_t _emptyFlag;
  void (*_emptyCallbackFunction)(void* bufferInstance);
  void (*_fullCallbackFunction)(void* bufferInstance);
} FIFOBuffer;

/*****************************************************************************/
/*PUBLIC Data                                                                */
/*****************************************************************************/

/*****************************************************************************/
/*PUBLIC Functions                                                           */
/*****************************************************************************/
/**
 * @brief 
 * 
 * @param   
 * @return
 */
void FIFOBuffer_init(
  FIFOBuffer *instance, 
  void* buffer, 
  uint32_t dataSize,
  unsigned int bufferSize);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
uint8_t FIFOCircularBuffer_enqueue(void* data);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
uint8_t FIFOCircularBuffer_dequeue(void* buffer);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
uint8_t FIFOCircularBuffer_enqueueIfNotFull(void* data);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
uint8_t FIFOBuffer_isEmpty(FIFOBuffer *instance);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
uint8_t FIFOBuffer_isFull(FIFOBuffer *instance);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
void FIFOBuffer_setEmptyCallback(
  FIFOBuffer *instance, 
  void (*callbackFunction)(void*));
/**
 * @brief 
 * 
 * @param   
 * @return
 */
void FIFOBuffer_setFullCallback(
  FIFOBuffer *instance, 
  void (*callbackFunction)(void*));

/**
 * @brief 
 * 
 * @param   
 * @return
 */
void FIFOCircularBuffer_reset(FIFOBuffer *instance);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
uint32_t FIFOCircularBuffer_size(FIFOBuffer *instance);

/**
 * @brief 
 * 
 * @param   
 * @return
 */
uint32_t FIFOCircularBuffer_capacity(FIFOBuffer *instance);

#endif /*FIFOSTATICCIRCULARBUFFER_H_*/
