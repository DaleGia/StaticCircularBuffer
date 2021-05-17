/**
 * @file fifoStaticCircularBuffer.h
 * Copyright (c) 2021 Dale Giancono All rights reserved.
 * 
 * @brief
 * An implementation of a FIFO static circular buffer.
 * inspired by https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 */

/*****************************************************************************/
/*INLCUDES                                                                   */
/*****************************************************************************/

/*****************************************************************************/
/*INLCUDES                                                                   */
/*****************************************************************************/
#include "fifoStaticCircularBuffer.h"

/*****************************************************************************/
/*PRIVATE MACROS                                                             */
/*****************************************************************************/

/*****************************************************************************/
/*PRIVATE function declarations                                              */
/*****************************************************************************/
static void FIFOCircularBuffer_enqueue(void* data);
static unsigned short FIFOCircularBuffer_dequeue(void* buffer);
static unsigned short FIFOCircularBuffer_enqueueIfNotFull(void* data);
static unsigned short FIFOCircularBuffer_isEmpty(void);
static unsigned short FIFOCircularBuffer_isFull(void);
static void FIFOCircularBuffer_setEmptyCallback(void (*callbackFunction)(void));
static void FIFOCircularBuffer_setFullCallback(void (*callbackFunction)(void));
static void FIFOCircularBuffer_reset(void);
static unsigned int FIFOCircularBuffer_size(void);
static unsigned int FIFOCircularBuffer_capacity(void);

/*****************************************************************************/
/*PRIVATE data                                                               */
/*****************************************************************************/

/**
 * @brief
 */
/*****************************************************************************/
/* Public Function Implementation                                            */
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
  unsigned int bufferSize)
{
  instance->enqueue = FIFOCircularBuffer_enqueue;
  instance->dequeue = FIFOCircularBuffer_dequeue;
  instance->enqueueIfNotFull = FIFOCircularBuffer_enqueueIfNotFull;
  instance->isEmpty = FIFOCircularBuffer_isEmpty;
  instance->isFull = FIFOCircularBuffer_isFull;
  instance->setEmptyCallback = FIFOCircularBuffer_setEmptyCallback;
  instance->setFullCallback = FIFOCircularBuffer_setFullCallback;
  instance->reset = FIFOCircularBuffer_reset;
  instance->size = FIFOCircularBuffer_size;
  instance->capacity = FIFOCircularBuffer_capacity;

  instance->_buffer = buffer;
  instance->_bufferSize = bufferSize;
  instance->_head = 0U;
  instance->_tail = 0U;
  instance->_fullFlag = 0U;
  instance->_emptyFlag = 1U;
  instance->_emptyCallbackFunction = 0U;
  instance->_fullCallbackFunction = 0U;
  return;
}

/*****************************************************************************/
/* Private Function Implementation                                           */
/*****************************************************************************/
/**
 * @brief 
 * 
 * @param   
 * @return
 */
static void FIFOCircularBuffer_enqueue(void* data)
{
  return;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static unsigned short FIFOCircularBuffer_enqueueIfNotFull(void* data)
{
  return 0;
}


/**
 * @brief 
 * 
 * @param   
 * @return
 */
static unsigned short FIFOCircularBuffer_dequeue(void* buffer)
{
  return 0;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static unsigned short FIFOCircularBuffer_isEmpty(void)
{
  return 0;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static unsigned short FIFOCircularBuffer_isFull(void)
{
  return 0;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static void FIFOCircularBuffer_setEmptyCallback(void (*callbackFunction)(void))
{
  return;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static void FIFOCircularBuffer_setFullCallback(void (*callbackFunction)(void))
{
  return;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static void FIFOCircularBuffer_reset(void)
{
  return;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static unsigned int FIFOCircularBuffer_size(void)
{
  return 0;
}

/**
 * @brief 
 * 
 * @param   
 * @return
 */
static unsigned int FIFOCircularBuffer_capacity(void)
{
  return 0;
}

