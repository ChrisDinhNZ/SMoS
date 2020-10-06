/**
 * SMoS - Library for encoding and decoding of SMoS messages.
 *        Please refer to https://github.com/ChrisDinhNZ/SMoS for more details.
 * Created by Chris Dinh, 2020
 * Released under MIT license
 * 
 * The library was derived from LibGIS IHex implementation (https://github.com/vsergeev/libGIS)
 */

#ifndef SMOS_H
#define SMOS_H

#include <stdint.h>

typedef enum smosDefinitions_t
{
   /* Start code */
   SMOS_START_CODE_OFFSET = 0,
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

   /* SMoS maximum message length */
   SMOS_MESSAGE_BUFF_SIZE = SMOS_START_CODE_BYTE_LEN +
                            SMOS_COUNT_BYTE_LEN +
                            SMOS_DATA_CONTEXT_BYTE_LEN +
                            SMOS_MAX_DATA_BYTE_LEN +
                            SMOS_CHECKSUM_BYTE_LEN,

   SMOS_START_CODE = 0x3A,
};

typedef enum smosContextType_t
{
   SMOS_CONTEXT_TYPE_CON = 0x00,
   SMOS_CONTEXT_TYPE_NON = 0x01,
   SMOS_CONTEXT_TYPE_ACK = 0x02,
   SMOS_CONTEXT_TYPE_NACK = 0x03,
};

typedef enum smosContentType_t
{
   SMOS_CONTENT_TYPE_GENERIC = 0x00,
   SMOS_CONTENT_TYPE_GATT = 0x01,
};

typedef enum smosCodeClass_t
{
   SMOS_CODE_CLASS_REQ = 0x00,
   SMOS_CODE_CLASS_RESP_SUCCESS = 0x02,
   SMOS_CODE_CLASS_RESP_CLIENT_ERROR = 0x04,
   SMOS_CODE_CLASS_RESP_SERVER_ERROR = 0x05,
};

typedef enum smosCodeDetailRequest_t
{
   SMOS_CODE_DETAIL_GET = 0x01,
   SMOS_CODE_DETAIL_OBSERVE = SMOS_CODE_DETAIL_GET,
   SMOS_CODE_DETAIL_POST = 0x02,
   SMOS_CODE_DETAIL_PUT = 0x03,
   SMOS_CODE_DETAIL_DELETE = 0x04,
};

typedef enum smosCodeDetailResponse_t
{
   SMOS_CODE_DETAIL_SUCCESS_CREATED = 0x01,
   SMOS_CODE_DETAIL_SUCCESS_DELETED = 0x02,
   SMOS_CODE_DETAIL_SUCCESS_VALID = 0x03,
   SMOS_CODE_DETAIL_SUCCESS_CHANGED = 0x04,
   SMOS_CODE_DETAIL_SUCCESS_CONTENT = 0x05,

   SMOS_CODE_DETAIL_CLIENT_ERROR_BAD_REQUEST = 0x00,
   SMOS_CODE_DETAIL_CLIENT_ERROR_UNAUTHORIZED = 0x01,
   SMOS_CODE_DETAIL_CLIENT_ERROR_BAD_OPTION = 0x02,
   SMOS_CODE_DETAIL_CLIENT_ERROR_FORBIDDEN = 0x03,
   SMOS_CODE_DETAIL_CLIENT_ERROR_NOT_FOUND = 0x04,
   SMOS_CODE_DETAIL_CLIENT_ERROR_METHOD_NOT_ALLOWED = 0x05,
   SMOS_CODE_DETAIL_CLIENT_ERROR_NOT_ACCEPTABLE = 0x06,
   SMOS_CODE_DETAIL_CLIENT_ERROR_PRECONDITION_FAILED = 0x0C,
   SMOS_CODE_DETAIL_CLIENT_ERROR_REQUEST_ENTITY_TOO_LARGE = 0x0D,
   SMOS_CODE_DETAIL_CLIENT_ERROR_UNSUPPORTED_CONTENT_FORMAT = 0x0F,

   SMOS_CODE_DETAIL_SERVER_ERROR_INTERNAL_SERVER_ERROR = 0x00,
   SMOS_CODE_DETAIL_SERVER_ERROR_NOT_IMPLEMENTED = 0x01,
   SMOS_CODE_DETAIL_SERVER_ERROR_BAD_GATEWAY = 0x02,
   SMOS_CODE_DETAIL_SERVER_ERROR_SERVICE_UNAVAILABLE = 0x03,
   SMOS_CODE_DETAIL_SERVER_ERROR_GATEWAY_TIMEOUT = 0x04,
   SMOS_CODE_DETAIL_SERVER_ERROR_PROXYING_NOT_SUPPORTED = 0x05
};

typedef enum smosError_t
{
   SMOS_ERROR_OK,             /**< Error code for success or no error. */
   SMOS_ERROR_INVALID_MESSAGE /**< Error code for error if an invalid message was received. */
};

/**
 * Structure to hold the fields of an SMoS message.
 */
typedef struct smosObject_t
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
};

class SMoS
{
   private:
      static uint8_t CreateChecksum(smosObject_t const *message);
   public:      
      smosError_t EncodeGetMessage(
         uint8_t byteCount,
         bool confirmable,
         smosContentType_t contentType,
         uint8_t contentTypeOptions,
         uint8_t messageId,
         uint8_t const *dataContent,
         char *smosMessage);
};

#endif
