/*
 * lhdcUtil.h
 *
 */

#ifndef LHDC_UTIL_H
#define LHDC_UTIL_H

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

// Define for LHDC stream type.
typedef enum {
  VERSION_2 = 200,
  VERSION_3 = 300,
  VERSION_4 = 400,
  VERSION_LLAC = 500
}lhdc_ver_t;

typedef enum {
  LHDCV2_BLOCK_SIZE = 512,
  LHDCV3_BLOCK_SIZE = 256,
}lhdc_block_size_t;

typedef struct _lhdc_frame_Info
{
  uint32_t frame_len; // bytes of an encoded frame
  uint32_t isSplit;   // if need to output in split channel? (split: 1, not-split:0)
  uint32_t isLeft;    // if isSplit is 1, the output data format: (left channel: 1; right channel: 0)

} lhdc_frame_Info_t;

typedef enum {
  LHDC_OUTPUT_STEREO = 0,
  LHDC_OUTPUT_LEFT_CAHNNEL,
  LHDC_OUTPUT_RIGHT_CAHNNEL,
} lhdc_channel_t;

typedef enum{
  LHDC_DEC_LOG_LEVEL_EMERG = 0,
  LHDC_DEC_LOG_LEVEL_ALERT,
  LHDC_DEC_LOG_LEVEL_CRIT,
  LHDC_DEC_LOG_LEVEL_ERROR,
  LHDC_DEC_LOG_LEVEL_WARNING,
  LHDC_DEC_LOG_LEVEL_NOTICE,
  LHDC_DEC_LOG_LEVEL_INFO,
  LHDC_DEC_LOG_LEVEL_DEBUG
}lhdc_dec_log_level;

typedef int LHDCSample;

#define LHDC_DEC_HDR_LATENCY_LOW   (0x00)
#define LHDC_DEC_HDR_LATENCY_MID   (0x01)
#define LHDC_DEC_HDR_LATENCY_HIGH  (0x02)
#define LHDC_DEC_HDR_LATENCY_MASK  (LHDC_DEC_HDR_LATENCY_MID | LHDC_DEC_HDR_LATENCY_HIGH)

#define LHDC_DEC_HDR_FRAME_NO_MASK (0xfc)

//Return
#define LHDC_UTIL_DEC_SUCCESS 0
#define LHDC_UTIL_DEC_ERROR_NO_INIT -1
#define LHDC_UTIL_DEC_ERROR_PARAM -2
#define LHDC_UTIL_DEC_ERROR -3
#define LHDC_UTIL_DEC_ERROR_WRONG_DEC -10

//----------------------------------------------------------------
// lhdc_util_dec_get_mem_req ()
//
//  Get internal memory size requirement of decoder
//  Parameter
//      [in] version: LHDC decoder subversion
//      [in] mem_req_bytes: a returned value to report size bytes of memory requirement
//  Return
//      LHDC_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdc_util_dec_get_mem_req(lhdc_ver_t version, uint32_t *mem_req_bytes);

//----------------------------------------------------------------
// lhdcInit ()
//
//  Initialize the decoder library
//  Parameter
//      [in] ptr: a pointer to the memory resource allocated  from external to the decoder.
//      [in] bitPerSample: bits per sample.
//      [in] sampleRate: sample rate.
//      [in] reserved: currently not-used
//      [in] version: LHDC decoder subversion
//  Return
//      None
//----------------------------------------------------------------
void lhdcInit(uint32_t *ptr, uint32_t bitPerSample, uint32_t sampleRate, uint32_t reserved, lhdc_ver_t version);

//----------------------------------------------------------------
// lhdcDecodeProcess ()
//
//  Input an encoded frame data to decode process
//  Parameter
//      [in] pOutBuf: a pointer to the output PCM buffer
//      [in] pInput: a pointer to the head of the input encoded frame
//      [in] len: size bytes of the encoded frame
//  Return
//      Number of bytes of PCM data outputed after decoding
//----------------------------------------------------------------
uint32_t lhdcDecodeProcess(uint8_t *pOutBuf, uint8_t *pInput, uint32_t len);

//----------------------------------------------------------------
// getVersionCode ()
//
//  Return a char string of the software version of library
//  Parameter
 //     None
//  Return
//      A char string of lib version information.
//----------------------------------------------------------------
char* getVersionCode(void);

//----------------------------------------------------------------
// lhdcDestroy ()
//
//  Clean/Reset resources in library
//  Note:
//    1. Not to call the API when initializing the library at first-time.
//    2. call this before lhdcInit() when re-initializing the library.
//  Parameter
 //     None
//  Return
//      None
//----------------------------------------------------------------
void lhdcDestroy(void);

//----------------------------------------------------------------
// lhdc_register_log_cb ()
//
//  Register a logger(printing function) callback instance from external
//  Parameter
//      [in] cb: a pointer to the callback function of logger.
//      [in] msg_buff: buffer for storing the char string.
//      [in] level: an integer of log level(see, lhdcv5_dec_log_level).
//  Return
//      LHDC_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
int32_t lhdc_register_log_cb(void *cb, char *msg_buff, int32_t level);

//----------------------------------------------------------------
// lhdcGetSampleSize ()
//
//  Get the number of samples per frame
//  Parameter
//      None
//  Return
//      (value > 0): Number of samples per frame
//      otherwise: Failure
//----------------------------------------------------------------
uint32_t lhdcGetSampleSize(void);

//----------------------------------------------------------------
// lhdcFetchFrameInfo ()
//
//  Get the number of samples per frame
//  Parameter
//      [in] frameData: a pointer to the head of a frame.
//      [in] frameInfo: a returned pointer to frame info.
//  Return
//      true: Succeed
//      false: Failure
//----------------------------------------------------------------
bool lhdcFetchFrameInfo(uint8_t *frameData, lhdc_frame_Info_t *frameInfo);

//----------------------------------------------------------------
// lhdcChannelSelsect ()
//
//  Setup channel allocation
//  Parameter
//      [in] channel_type: type of channel allocation
//  Return
//      LHDC_UTIL_DEC_SUCCESS: Succeed
//      otherwise: Failure
//----------------------------------------------------------------
uint32_t lhdcChannelSelsect(lhdc_channel_t channel_type);


#ifdef __cplusplus
}
#endif
#endif /* End of LHDC_UTIL_H */
