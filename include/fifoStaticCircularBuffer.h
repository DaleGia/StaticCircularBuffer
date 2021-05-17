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
struct FIFOCircularBuffer
{  
  void (*enqueue)(void* data);
  unsigned short (*dequeue)(void* buffer);
  unsigned short (*enqueueIfNotFull)(void* data);
  unsigned short (*isEmpty)(void);
  unsigned short (*isFull)(void);
  void (*setEmptyCallback)(void (*callbackFunction)(void));
  void (*setFullCallback)(void (*callbackFunction)(void));
  void (*reset)(void);
  unsigned int (*size)(void);
  unsigned int (*capacity)(void);

  void* _buffer;
  unsigned int _bufferSize;
  unsigned int _head;
  unsigned int _tail;
  unsigned short _fullFlag;
  unsigned short _emptyFlag;
  void (*_emptyCallbackFunction)(void);
  void (*_fullCallbackFunction)(void);
};

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
void FIFOCircularBuffer_init(
  struct FIFOCircularBuffer *instance, 
  void* buffer, 
  unsigned int bufferSize);

#endif /*FIFOSTATICCIRCULARBUFFER_H_*/
