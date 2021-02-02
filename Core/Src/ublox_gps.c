/*
 * ublox_gps.c
 *
 *  Created on: Feb 2, 2021
 *      Author: alexk
 */

#include "ublox_gps.h"

// Compares the first two bytes of the ubxMessage struct with a specific message header.
// Returns true if the two bytes match.
bool compareMsgHeader(const unsigned char* msgHeader) {
  unsigned char* ptr = (unsigned char*)(&ubxMessage);
  return ptr[0] == msgHeader[0] && ptr[1] == msgHeader[1];
}

void calcChecksum(unsigned char* CK, int msgSize) {
  memset(CK, 0, 2);
  for (int i = 0; i < msgSize; i++) {
    CK[0] += ((unsigned char*)(&ubxMessage))[i];
    CK[1] += CK[0];
  }
  // ensure unsigned byte range
  CK[0] = CK[0] & 0xFF;
  CK[1] = CK[1] & 0xFF;
}

int readGPS(commBuffer_t* rxBuffer)
{
  static int fpos = 0;
  static unsigned char checksum[2];
  static uint8_t currentMsgType = MT_NONE;
  static int payloadSize = sizeof(ubxMessage);

  while ( getBufferSize(rxBuffer) ) {
	char c = getChar(rxBuffer);
	if ( fpos < 2 ) {
	  // For the first two bytes we are simply looking for a match with the UBX header bytes (0xB5,0x62)
	  if ( c == UBX_HEADER[fpos] )
		fpos++;
	  else
		fpos = 0; // Reset to beginning state.
	}
	else {
	  // If we come here then fpos >= 2, which means we have found a match with the UBX_HEADER
	  // and we are now reading in the bytes that make up the payload.

	  // Place the incoming byte into the ubxMessage struct. The position is fpos-2 because
	  // the struct does not include the initial two-byte header (UBX_HEADER).
	  if ( (fpos - 2) < payloadSize )
		((unsigned char*)(&ubxMessage))[fpos - 2] = c;

	  fpos++;

	  if ( fpos == 4 ) {
		// We have just received the second byte of the message type header,
		// so now we can check to see what kind of message it is.
		//        if ( compareMsgHeader(NAV_DOP_HEADER) ) {
		//          currentMsgType = MT_NAV_DOP;
		//          payloadSize = sizeof(NAV_DOP);
		//        }
		if ( compareMsgHeader(NAV_PVT_HEADER) ) {
		  currentMsgType = MT_NAV_PVT;
		  payloadSize = sizeof(ubxMessage.pvt);
		}
		//        else if ( compareMsgHeader(NAV_TIMEGPS_HEADER) ) {
		//          currentMsgType = MT_NAV_TIMEGPS;
		//          payloadSize = sizeof(NAV_TIMEGPS);
		//        }
		else {
		  // unknown message type, bail
		  fpos = 0;
		  continue;
		}
	  }

	  if ( fpos == (payloadSize + 2) ) {
		// All payload bytes have now been received, so we can calculate the
		// expected checksum value to compare with the next two incoming bytes.
		calcChecksum(checksum, payloadSize);
	  }
	  else if ( fpos == (payloadSize + 3) ) {
		// First byte after the payload, ie. first byte of the checksum.
		// Does it match the first byte of the checksum we calculated?
		if ( c != checksum[0] ) {
		  // Checksum doesn't match, reset to beginning state and try again.
		  fpos = 0;
		}
	  }
	  else if ( fpos == (payloadSize + 4) ) {
		// Second byte after the payload, ie. second byte of the checksum.
		// Does it match the second byte of the checksum we calculated?
		fpos = 0; // We will reset the state regardless of whether the checksum matches.
		if ( c == checksum[1] ) {
		  // Checksum matches, we have a valid message.
		  //ubxMessage = temp_ubxMessage;
		  //memcpy(&ubxMessage, &temp_ubxMessage, sizeof(temp_ubxMessage));
		  return currentMsgType;
		}
	  }
	  else if ( fpos > (payloadSize + 4) ) {
		// We have now read more bytes than both the expected payload and checksum
		// together, so something went wrong. Reset to beginning state and try again.
		fpos = 0;
	  }
	}
  }
  return MT_NONE;
}
