/*
 * File: STM32SerialRtiostream.h
 *
 * External mode interface functions
 */

#ifndef __STM32SerialRtiostream_H__
#define __STM32SerialRtiostream_H__

#ifdef __cplusplus
extern "C" {
#endif

/***************** DEFINES ****************************************************/
#define RTIOSTREAM_NO_ERROR  (0)
#define RTIOSTREAM_ERROR    (-1)
#define SERVER_STREAM_ID     (1) /* Allow a single server-side connection. */

#ifndef RTIOSTREAMAPI
#define RTIOSTREAMAPI extern
#endif


RTIOSTREAMAPI int rtIOStreamOpen(int argc, void * argv[]);
RTIOSTREAMAPI int rtIOStreamClose(int streamID);
RTIOSTREAMAPI int rtIOStreamSend(int streamID, const void * src, size_t size, size_t * sizeSent);
RTIOSTREAMAPI int rtIOStreamRecv(int streamID, void * dst, size_t size, size_t * sizeRecv);


#ifdef __cplusplus
}
#endif

#endif



