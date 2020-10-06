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


