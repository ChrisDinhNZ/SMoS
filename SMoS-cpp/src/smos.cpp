/**
 * SMoS - Library for encoding and decoding of SMoS messages.
 *        Please refer to https://github.com/ChrisDinhNZ/SMoS for more details.
 * Created by Chris Dinh, 2020
 * Released under MIT license
 * 
 * The library was derived from LibGIS IHex implementation (https://github.com/vsergeev/libGIS)
 */

#include "smos.h"

/**
 * Takes the provided parameters and create a SMoS Hex string and assign it to smosMessage.
 */
smosError_t SMoS::EncodeGetMessage(
    uint8_t byteCount,
    bool confirmable,
    smosContentType_t contentType,
    uint8_t contentTypeOptions,
    uint8_t messageId,
    const uint8_t *dataContent,
    char *smosMessage)
{
   smosObject_t *message;

   smosMessage[0] = 0;

   if (byteCount > SMOS_MAX_DATA_BYTE_LEN)
   {
      return SMOS_ERROR_INVALID_MESSAGE;
   }

   if (dataContent == NULL)
   {
      return SMOS_ERROR_INVALID_MESSAGE;
   }

   message->startCode = SMOS_START_CODE;
   message->byteCount = byteCount;
   message->contextType = confirmable ? SMOS_CONTEXT_TYPE_CON : SMOS_CONTEXT_TYPE_NON;
   message->contentType = contentType;
   message->contentTypeOptions = contentTypeOptions;
   message->codeClass = SMOS_CODE_CLASS_REQ;
   message->codeDetail = SMOS_CODE_DETAIL_GET;
   message->messageId = messageId;
   message->tokenId = 0;
   memcpy(message->dataContent, dataContent, sizeof(dataContent[0]) * byteCount);
   
   message.checksum = CreateChecksum(message);
   return SMOS_ERROR_OK;
}

static uint8_t SMoS::CreateChecksum(
   const smosObject_t *message)
{
   uint8_t checksum, tempByte, i;

   checksum = message->byteCount;

   /* The next 3 bytes contains the context of the message.
      Byte 1: Context type, content type, content type options
      Byte 2: Code class, code detail
      Byte 3: Message Id, token Id */
   tempByte = 0; /* Start putting byte 1 together */
   tempByte |= ((message->contextType << SMOS_CONTEXT_TYPE_LSB_OFFSET) & SMOS_CONTEXT_TYPE_BIT_MASK);
   tempByte |= ((message->contentType << SMOS_CONTENT_TYPE_LSB_OFFSET) & SMOS_CONTENT_TYPE_BIT_MASK);
   tempByte |= ((message->contentTypeOptions << SMOS_CONTENT_TYPE_OPTIONS_LSB_OFFSET) & SMOS_CONTENT_TYPE_OPTIONS_BIT_MASK);
   checksum += tempByte;
   tempByte = 0; /* Start putting byte 2 together */
   tempByte |= ((message->codeClass << SMOS_CODE_CLASS_LSB_OFFSET) & SMOS_CODE_CLASS_BIT_MASK);
   tempByte |= ((message->codeDetail << SMOS_CODE_DETAIL_LSB_OFFSET) & SMOS_CODE_DETAIL_BIT_MASK);
   checksum += tempByte;
   tempByte = 0; /* Start putting byte 3 together */
   tempByte |= ((message->messageId << SMOS_MESSAGE_ID_LSB_OFFSET) & SMOS_MESSAGE_ID_BIT_MASK);
   tempByte |= ((message->tokenId << SMOS_TOKEN_ID_LSB_OFFSET) & SMOS_TOKEN_ID_BIT_MASK);
   checksum += tempByte;

   for (i = 0; i < message->byteCount; i++)
   {
      checksum += message->dataContent[i];
   }

   /* Two's complement on checksum */
	checksum = ~checksum + 1;

   return checksum;
}
