/*
 * lhdcv5_util_dec.h
 *
 */

#ifndef LHDCV5_UTIL_DEC_H
#define LHDCV5_UTIL_DEC_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void * HANDLE_LHDCV5_BT;

typedef enum {
  VERSION_5 = 550
} lhdcv5_ver_t;

typedef struct _lhdcv5_frame_Info {
  uint32_t frame_len;
  uint32_t isSplit;
  uint32_t isLeft;
} lhdcv5_frame_Info_t;

typedef enum {
  LHDCV5_OUTPUT_STEREO = 0,
  LHDCV5_OUTPUT_LEFT_CAHNNEL,
  LHDCV5_OUTPUT_RIGHT_CAHNNEL,
} lhdcv5_channel_t;

typedef enum {
  LHDCV5_DEC_LLESS_OFF = 0,
  LHDCV5_DEC_LLESS_ON = 1,
} lhdcv5_dec_lossless_status_t;

typedef enum {
  LHDCV5_DEC_LLESS_RAW_OFF = 0,
  LHDCV5_DEC_LLESS_RAW_ON = 1,
} lhdcv5_dec_lossless_raw_status_t;

typedef enum {
  LHDCV5_DEC_LOG_LEVEL_EMERG = 0,
  LHDCV5_DEC_LOG_LEVEL_ALERT,
  LHDCV5_DEC_LOG_LEVEL_CRIT,
  LHDCV5_DEC_LOG_LEVEL_ERROR,
  LHDCV5_DEC_LOG_LEVEL_WARNING,
  LHDCV5_DEC_LOG_LEVEL_NOTICE,
  LHDCV5_DEC_LOG_LEVEL_INFO,
  LHDCV5_DEC_LOG_LEVEL_DEBUG
} lhdcv5_dec_log_level_t;

typedef enum __LHDCV5_DEC_FUNC_RET__ {
  LHDCV5_UTIL_DEC_SUCCESS = 0,
  LHDCV5_UTIL_DEC_ERROR_NO_INIT = -1,
  LHDCV5_UTIL_DEC_ERROR_PARAM = -2,
  LHDCV5_UTIL_DEC_ERROR = -3,
  LHDCV5_UTIL_DEC_ERROR_RESOURCE_NOT_CLEANED = -4,
  LHDCV5_UTIL_DEC_ERROR_WRONG_DEC = -10,
} lhdcv5_dec_func_ret_t;

#define LHDCV5_DEC_HDR_LATENCY_LOW   (0x00)
#define LHDCV5_DEC_HDR_LATENCY_MID   (0x01)
#define LHDCV5_DEC_HDR_LATENCY_HIGH  (0x02)
#define LHDCV5_DEC_HDR_LATENCY_MASK  (LHDCV5_DEC_HDR_LATENCY_MID | LHDCV5_DEC_HDR_LATENCY_HIGH)

#define LHDCV5_DEC_HDR_FRAME_NO_MASK (0xfc)

//----------------------------------------------------------------
// lhdcv5_util_dec_get_mem_req ()
//
//  Get internal memory size requirement of decoder
//  Parameter
//      [in] version: LHDC decoder subversion
//      [in] mem_req_bytes: a returned value to report size bytes of memory requirement
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_get_mem_req(lhdcv5_ver_t version, uint32_t *mem_req_bytes);

//----------------------------------------------------------------
// lhdcv5_util_init_decoder ()
//
//  Initial LHDC 5.0 Decoder
//  Parameter
//      [in] ptr: a pointer to the memory resource allocated to the decoder.
//      [in] bitPerSample: bit per sample
//      [in] sampleRate: sample rate
//      [in] bitrate: bit rate (not-used anymore, set to 0)
//      [in] is_lossless_enable: configure if lossless feature is enable/disable
//      [in] is_lossless_raw_enable: configure if lossless raw mode is enable/disable
//      [in] version: LHDC decoder subversion
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_init_decoder(uint32_t *ptr, uint32_t bitPerSample, uint32_t sampleRate, uint32_t bitrate,
    uint32_t is_lossless_enable, uint32_t is_lossless_raw_enable, lhdcv5_ver_t version);

//----------------------------------------------------------------
// lhdcv5_util_dec_process ()
//
//  Input an encoded frame data to decode process
//  Parameter
//      [in] pOutBuf: a pointer to the output PCM buffer
//      [in] pInput: a pointer to the head of the input encoded frame
//      [in] InLen: size bytes of the encoded frame
//      [in] OutLen: a returned value to report size bytes of the output PCM frame
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_process(uint8_t *pOutBuf, uint8_t *pInput, uint32_t InLen, uint32_t *OutLen);

//----------------------------------------------------------------
// lhdcv5_util_dec_destroy ()
//
//  Reset decoder resources(only clean the database field, not including free memory)
//  Parameter
//      [in] none
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_destroy(void);

//----------------------------------------------------------------
// lhdcv5_util_dec_get_sample_size ()
//
//  Get number of samples in an encoded frame
//  Parameter
//      [in] frame_samples: a returned value to report number of samples in an encoded frame
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_get_sample_size (uint32_t *frame_samples);

//----------------------------------------------------------------
// lhdcv5_util_dec_fetch_frame_info ()
//
//  Get number of samples in an encoded frame
//  Parameter
//      [in] frameData: a pointer to an encoded frame header.
//      [in] frameDataLen: size bytes of an encoded frame header.
//      [in] frameInfo: a returned value to report the frame information
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_fetch_frame_info(uint8_t *frameData, uint32_t frameDataLen, lhdcv5_frame_Info_t *frameInfo);

//----------------------------------------------------------------
// lhdcv5_util_dec_channel_selsect ()
//
//  Configure format type of decoder output to buffer
//  Parameter
//      [in] channel_type: type of output
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_channel_selsect(lhdcv5_channel_t channel_type);

//----------------------------------------------------------------
// lhdcv5_util_dec_register_log_cb ()
//
//  Register a logger(printing function) callback instance from external
//  Parameter
//      [in] cb: a pointer to the callback function of logger.
//      [in] msg_buff: buffer for storing the char string.
//      [in] level: an integer of log level(see, lhdcv5_dec_log_level).
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_register_log_cb(void *cb, char *msg_buff, int32_t level);

//----------------------------------------------------------------
// lhdcv5_util_dec_set_log_level ()
//
//  Configure log level condition to logger
//  Parameter
//      [in] level: an integer of log level(see, lhdcv5_dec_log_level).
//  Return
//      LHDCV5_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_set_log_level(int32_t level);

//----------------------------------------------------------------
// lhdcv5_util_dec_get_version ()
//
//  Get the LHDC V5 decoder library software version
//  Parameter
//      [in] none
//  Return
//      A char string of "LHDC V5 decoder lib software version"
//----------------------------------------------------------------
char *lhdcv5_util_dec_get_version(void);

//----------------------------------------------------------------
// lhdcv5_util_dec_get_lib_auth_string ()
//
// Get license authentication string form LHDC library
//  Parameter
//      [in] str_buf: a pointer to the buffer to store returned string
//      [in] buf_byte_size: byte size of str_buf
//  Return
//      LHDCV5_FRET_SUCCESS: Succeed
//      otherwise: Fail
//----------------------------------------------------------------
int32_t lhdcv5_util_dec_get_lib_auth_string
(
    uint8_t  *str_buf,
    uint32_t  buf_byte_size
);


#ifdef __cplusplus
}
#endif
#endif /* End of LHDCV5_UTIL_DEC_H */
