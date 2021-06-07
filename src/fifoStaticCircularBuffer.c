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
#include "string.h"

/*****************************************************************************/
/*PRIVATE MACROS                                                             */
/*****************************************************************************/

/*****************************************************************************/
/*PRIVATE function declarations                                              */
/*****************************************************************************/

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
 * Initialises the instance of the fifoStaticCircularBuffer. If you are silly
 * enough to create a buffer with a size of anything less than 2, you deserve
 * the inevitable segmentation fault.
 * 
 * @param   
 * @return
 */
void FIFOBuffer_init(
  FIFOBuffer *instance, 
  void* buffer, 
  uint32_t dataSize,
  unsigned int bufferSize)
{

  instance->_buffer = buffer;
  instance->_dataSize = dataSize;
  instance->_bufferSize = bufferSize;
  instance->_head = 0U;
  instance->_tail = 0U;
  instance->_fullFlag = 0U;
  instance->_emptyFlag = 1U;
  /** 
   * 0U is essentially nullptr. We will check for this later on to see if a 
   * function has been defined.
   */
  instance->_emptyCallbackFunction = 0U;
  instance->_fullCallbackFunction = 0U;
  return;
}

/*****************************************************************************/
/* Private Function Implementation                                           */
/*****************************************************************************/
/**
 * @brief 
 * Adds data to a FIFOBuffer. Overwrites data if the buffer is already full.
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * data Data to enqueue to the FIFOBuffer.
 * @return
 * 1 if the data was successfully enqueued
 * 0 if the enqueued data overwrote existing data because the buffer was full.
 */
uint8_t FIFOBuffer_enqueue(FIFOBuffer *instance, void* data)
{
  uint8_t success;
  uint32_t head;
  uint32_t tail;
  uint32_t bufferSize;
  success = 1U;

  /**
   * Getting these values so we do not have to repeatadly get them
   * via the instance pointer.
   */
  head = instance->_head;
  tail = instance->_tail;
  bufferSize = instance->_bufferSize;

  /** Copy the data to the next place in the buffer. This will 
   * either succeed or segfault. I know which one I hope happens 
   */
  memcpy(&((uint8_t*)instance->_buffer)[head], data, instance->_dataSize);
  
  /**
   * Increment the tail and head. Check for if the buffer is full.
   * Call the fullcallback if it is.
   * 
   */
  head++;
  tail++;

  if(1U == instance->_fullFlag)
  {
    if(bufferSize <= tail)
    {
      tail = 0U;
      success = 0U;
    }
  }

  if(bufferSize <= head)
  {
    head = 0U;
  }

  if(bufferSize == head)
  {
    instance->_fullFlag = 1U;
    instance->_fullCallbackFunction(instance);
  }
  
  return success;
}

/**
 * @brief 
 * Adds data to a FIFOBuffer if it is not already full. 
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * data Data to enqueue to the FIFOBuffer.
 * @return
 * 1 if the data was successfully enqueued
 * 0 if the data was not enqueued.
 */
uint8_t FIFOBuffer_enqueueIfNotFull(FIFOBuffer *instance, void* data)
{
  uint8_t success;
  uint32_t head;
  uint32_t tail;
  uint32_t bufferSize;

  success = 1U;
  /**
   * Getting these values so we do not have to repeatadly get them
   * via the instance pointer.
   */
  head = instance->_head;
  tail = instance->_tail;
  bufferSize = instance->_bufferSize;
  
  /** Check if buffer is full before doing anything */
  if(1U == instance->_fullFlag)
  {
    /** Copy the data to the next place in the buffer. This will 
     * either succeed or segfault. I know which one I hope happens 
     */
    memcpy(&((uint8_t*)instance->_buffer)[head], data, instance->_dataSize);
    /** Obviously it is not empty anymore. */
    instance->_emptyFlag = 0U;
    
    /**
     * Increment the tail and head. Check for if the buffer is full.
     * Call the fullcallback if it is.
     * 
     */
    head++;
    tail++;

    if(1U == instance->_fullFlag)
    {
      if(bufferSize <= tail)
      {
        tail = 0U;
      }
    }

    if(bufferSize <= head)
    {
      head = 0U;
    }

    if(bufferSize == head)
    {
      instance->_fullFlag = 1U;
      if(0U != (uintptr_t)instance->_fullCallbackFunction)
      {
        instance->_fullCallbackFunction(instance);
      }
    }
  }
  else
  {
    success = 0;
  }

  /* Set the actual buffer instance head and tail objects before returing. */
  instance->_head = head;
  instance->_tail = tail;

  return success;
}

/**
 * @brief 
 * Dequques the first data in the queue to the buffer pointer. If you 
 * have not given a valid buffer pointer you deserve the segfault.
 * 
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * data Pointer to the buffer which will be dequeued to.
 * @return
 * 1 if the data was successfully dequeued
 * 0 if the data was not dequeued.
 */
uint8_t FIFOBuffer_dequeue(FIFOBuffer *instance, void* buffer)
{
  uint8_t success;
  uint32_t head;
  uint32_t tail;
  uint32_t bufferSize;

  success = 1U;
  /**
   * Getting these values so we do not have to repeatadly get them
   * via the instance pointer.
   */
  head = instance->_head;
  tail = instance->_tail;
  bufferSize = instance->_bufferSize;

  if(0U != instance->_emptyFlag)
  {
    /** Copy the data to the buffer object. This will 
     *  either succeed or segfault. I know which one I hope happens 
     */
    memcpy(buffer, &((uint8_t*)instance->_buffer)[tail], instance->_dataSize);
    /** Obviously it is not full anymore. */
    instance->_fullFlag = 0U;
    tail++;

    if(bufferSize <= tail)
    {
      tail = 0;
    }

    success = 1U;
  }

  if(1U == instance->_fullFlag)
  {
    if(head == tail)
    {
      instance->_emptyFlag = 1U;
      if(0U != (uintptr_t)instance->_emptyCallbackFunction)
      {
        instance->_emptyCallbackFunction(instance);
      }
    }
  }

  
  /* Set the actual buffer instance head and tail objects before returing. */
  instance->_head = head;
  instance->_tail = tail;

  return success;
}

/**
 * @brief 
 * Checks if the buffer is empty.
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * @return
 * 1 if buffer is empty.
 * 0 if buffer is not empty.
 */
uint8_t FIFOBuffer_isEmpty(FIFOBuffer *instance)
{
  return instance->_emptyFlag;
}

/**
 * @brief 
 * Checks if the buffer is full.
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * @return
 * 1 if buffer is full.
 * 0 if buffer is not full.
 */
uint8_t FIFOBuffer_isFull(FIFOBuffer *instance)
{
  return instance->_fullFlag;
}

/**
 * @brief 
 * Sets the function which will be called as soon as the buffer becomes empty.
 * This should be done after FIFOBuffer_init is called. It is up to you to 
 * make sure the callback function pointer actually points to a valid function.
 * I cannot hold your hand forever. 
 * 
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * callbackFunction Pointer to the function which will be called as soon as 
 * the buffer is empty.
 * @return
 * none
 */
void FIFOBuffer_setEmptyCallback(
  FIFOBuffer *instance, 
  void (*callbackFunction)(void*))
{
  instance->_emptyCallbackFunction = callbackFunction;
  return;
}

/**
 * @brief 
 * Sets the function which will be called as soon as the buffer becomes full.
 * This should be done after FIFOBuffer_init is called. It is up to you to 
 * make sure the callback function pointer actually points to a valid function.
 * I cannot hold your hand forever. 
 * 
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * callbackFunction Pointer to the function which will be called as soon as 
 * the buffer is full.
 * @return
 * none
 */
void FIFOBuffer_setFullCallback(
  FIFOBuffer *instance, 
  void (*callbackFunction)(void*))
{
  instance->_fullCallbackFunction = callbackFunction;
  return;
}

/**
 * @brief 
 * Resets the FIFO Buffer. It DOES NOT remove the set callback functions and will
 * call the buffer empty callback if it has been set.
 * 
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * @return
 * none
 */
void FIFOCircularBuffer_reset(FIFOBuffer *instance)
{
  
  instance->_head = 0U;
  instance->_tail = 0U;
  instance->_fullFlag = 0U;
  instance->_emptyFlag = 0U;
  if(0U != (uintptr_t)instance->_emptyCallbackFunction)
  {
    instance->_emptyCallbackFunction(instance);
  }
  return;
}

/**
 * @brief 
 * Gets the number of elements current filled in the buffer
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * @return
 * Number of elements current filled in the buffer
 */
uint32_t FIFOBuffer_size(FIFOBuffer *instance)
{
  uint32_t size;

  size = instance->_bufferSize;

	if(0U == instance->_fullFlag)
	{
    if(instance->_head >= instance->_tail)
    {
      size = instance->_head - instance->_tail;
    }
    else
		{
			size = (instance->_bufferSize + instance->_head) - instance->_tail;
		}
	}

	return size;
}

/**
 * @brief 
 * Gets the size of an individual buffer element in bytes.
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * @return
 * Size of individual buffer element in bytes 
 */
uint32_t FIFOBuffer_dataSize(FIFOBuffer *instance)
{
  return instance->_dataSize;
}

/**
 * @brief 
 * Gets the number of buffer elements in a capacity sense.
 * @param   
 * instance Pointer to the FIFOBuffer object instance.
 * @return
 * Size of buffer capacity in elements. 
 */
uint32_t FIFOBuffer_capacity(FIFOBuffer *instance)
{
  return instance->_bufferSize;
}

