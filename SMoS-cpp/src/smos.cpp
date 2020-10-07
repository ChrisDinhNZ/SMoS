/**
 * SMoS - Library for encoding and decoding of SMoS messages.
 *        Please refer to https://github.com/ChrisDinhNZ/SMoS for more details.
 * Created by Chris Dinh, 2020
 * Released under MIT license
 * 
 * The library was derived from LibGIS IHex implementation (https://github.com/vsergeev/libGIS)
 */

#include <string.h>
#include <stdio.h>
#include "smos.h"

/**
 * Takes the provided parameters and create a SMoS Hex string and assign it to hexString.
 */
smosError_t SMoS::EncodeGetMessage(
    uint8_t byteCount,
    bool confirmable,
    smosContentType_t contentType,
    uint8_t contentTypeOptions,
    uint8_t messageId,
    const uint8_t *dataContent,
    char *hexString)
{
   smosObject_t *message;

   if (dataContent == NULL || hexString == NULL)
   {
      return SMOS_ERROR_INVALID_MESSAGE;
   }

   if (byteCount > SMOS_MAX_DATA_BYTE_LEN)
   {
      return SMOS_ERROR_INVALID_MESSAGE;
   }

   memset(message, 0, sizeof(*message));
   hexString[0] = 0;

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
   message->checksum = CreateChecksum(message);

   if (ConvertMessageToHexString(message, hexString) == 0)
   {
      return SMOS_ERROR_INVALID_MESSAGE;
   }

   return SMOS_ERROR_OK;
}

static uint8_t SMoS::CreateChecksum(
   const smosObject_t *message)
{
   uint8_t checksum, i;

   checksum = message->byteCount;
   checksum += CalculateContextByteInfo(message, 0);
   checksum += CalculateContextByteInfo(message, 1);
   checksum += CalculateContextByteInfo(message, 2);

   for (i = 0; i < message->byteCount; i++)
   {
      checksum += message->dataContent[i];
   }

   /* Two's complement on checksum */
	checksum = ~checksum + 1;

   return checksum;
}

static uint16_t SMoS::ConvertMessageToHexString(
   const smosObject_t *message,
   char *hexString)
{
   uint8_t i;

   if (message == NULL || hexString == NULL)
   {
      return 0;
   }

   if (message->byteCount > SMOS_MAX_DATA_BYTE_LEN)
   {
      return 0;
   }

   hexString += sprintf(hexString, "%c", message->startCode);
   hexString += sprintf(hexString, "%02X", message->byteCount);
   hexString += sprintf(hexString, "%02X", CalculateContextByteInfo(message, 0));
   hexString += sprintf(hexString, "%02X", CalculateContextByteInfo(message, 1));
   hexString += sprintf(hexString, "%02X", CalculateContextByteInfo(message, 2));

   for (i = 0; i < message->byteCount; i++)
   {
      hexString += sprintf(hexString, "%02X", message->dataContent[i]);
   }

   hexString += sprintf(hexString, "%02X", message->checksum);

   return strlen(hexString);
}

static uint8_t SMoS::CalculateContextByteInfo(
    const smosObject_t *message,
    uint8_t contextByteIndex)
{
   uint8_t tempByte = 0;

   switch (contextByteIndex)
   {
      case 0:
         tempByte |= ((message->contextType << SMOS_CONTEXT_TYPE_LSB_OFFSET) & SMOS_CONTEXT_TYPE_BIT_MASK);
         tempByte |= ((message->contentType << SMOS_CONTENT_TYPE_LSB_OFFSET) & SMOS_CONTENT_TYPE_BIT_MASK);
         tempByte |= ((message->contentTypeOptions << SMOS_CONTENT_TYPE_OPTIONS_LSB_OFFSET) & SMOS_CONTENT_TYPE_OPTIONS_BIT_MASK);
         break;

      case 1:
         tempByte |= ((message->codeClass << SMOS_CODE_CLASS_LSB_OFFSET) & SMOS_CODE_CLASS_BIT_MASK);
         tempByte |= ((message->codeDetail << SMOS_CODE_DETAIL_LSB_OFFSET) & SMOS_CODE_DETAIL_BIT_MASK);
         break;

      case 2:
         tempByte |= ((message->messageId << SMOS_MESSAGE_ID_LSB_OFFSET) & SMOS_MESSAGE_ID_BIT_MASK);
         tempByte |= ((message->tokenId << SMOS_TOKEN_ID_LSB_OFFSET) & SMOS_TOKEN_ID_BIT_MASK);
         break;

      default:
         break;
   }

   return tempByte;
}

