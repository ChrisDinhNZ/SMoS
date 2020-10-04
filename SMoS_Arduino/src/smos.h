/**
 * SMoS - Library for encoding and decoding of SMoS messages
 * Created by Chris Dinh, 2020
 * Released under MIT license
 * 
 * The library was derived from LibGIS IHex implementation (https://github.com/vsergeev/libGIS)
 */

#ifndef SMOS_H
#define SMOS_H

#include <stdint.h>

enum _SMoSDefinitions
{
   /* Start code */
   SMOS_START_CODE_OFFSET = 0,
   SMOS_START_CODE_VALUE = 0x3A,
   SMOS_START_CODE_BYTE_LEN = 1,

   /* Byte count */
   SMOS_COUNT_OFFSET = 1,
   SMOS_COUNT_BYTE_LEN = 1,

   /* Context Overall */
   SMOS_DATA_CONTEXT_BYTE_LEN = 3,

   /* Context type */
   SMOS_CONTEXT_TYPE_OFFSET = 2,
   SMOS_CONTEXT_TYPE_LSB_OFFSET = 6,
   SMOS_CONTEXT_TYPE_BIT_MASK = 0xC0,

   /* Content type */
   SMOS_CONTENT_TYPE_OFFSET = 2,
   SMOS_CONTENT_TYPE_LSB_OFFSET = 4,
   SMOS_CONTENT_TYPE_BIT_MASK = 0x30,

   /* Content type */
   SMOS_CONTENT_TYPE_OPTIONS_OFFSET = 2,
   SMOS_CONTENT_TYPE_OPTIONS_LSB_OFFSET = 0,
   SMOS_CONTENT_TYPE_OPTIONS_BIT_MASK = 0x0F,

   /* Code class */
   SMOS_CODE_CLASS_OFFSET = 3,
   SMOS_CODE_CLASS_LSB_OFFSET = 5,
   SMOS_CODE_CLASS_BIT_MASK = 0xE0,

   /* Code detail */
   SMOS_CODE_DETAIL_OFFSET = 3,
   SMOS_CODE_DETAIL_LSB_OFFSET = 0,
   SMOS_CODE_DETAIL_BIT_MASK = 0x1F,

   /* Message Id */
   SMOS_MESSAGE_ID_OFFSET = 4,
   SMOS_MESSAGE_ID_LSB_OFFSET = 4,
   SMOS_MESSAGE_ID_BIT_MASK = 0xF0,

   /* Token Id */
   SMOS_TOKEN_ID_OFFSET = 4,
   SMOS_TOKEN_ID_LSB_OFFSET = 0,
   SMOS_TOKEN_ID_BIT_MASK = 0x0F,

   /* Data content */
   SMOS_DATA_OFFSET = 5,
   SMOS_MAX_DATA_BYTE_LEN = 255,

   /* Checksum offset depends on Byte Count */
   SMOS_CHECKSUM_BYTE_LEN = 1,

   SMOS_MESSAGE_BUFF_SIZE = SMOS_START_CODE_BYTE_LEN +
                            SMOS_COUNT_BYTE_LEN +
                            SMOS_DATA_CONTEXT_BYTE_LEN +
                            SMOS_MAX_DATA_BYTE_LEN +
                            SMOS_CHECKSUM_BYTE_LEN,
};

/**
 * All possible error codes the Intel HEX8 record utility functions may return.
 */
enum IHexErrors
{
   SMOS_ERROR_OK,             /**< Error code for success or no error. */
   SMOS_ERROR_INVALID_MESSAGE /**< Error code for error if an invalid message was received. */
};

/**
 * Structure to hold the fields of an SMoS message.
 */
typedef struct
{
   uint8_t startCode;
   uint8_t byteCount;
   uint8_t contextType;
   uint8_t contentType;
   uint8_t contentTypeOptions;
   uint8_t codeClass;
   uint8_t codeDetail;
   uint8_t messageId;
   uint8_t tokenId;
   uint8_t dataContent[SMOS_MAX_DATA_BYTE_LEN];
   uint8_t checksum;
} SMoSMessage_t;

#endif
