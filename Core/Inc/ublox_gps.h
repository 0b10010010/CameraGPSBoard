/*
 * ublox_gps.h
 *
 *  Created on: Feb 2, 2021
 *      Author: alexk
 */

#ifndef INC_UBLOX_GPS_H_
#define INC_UBLOX_GPS_H_

#include <stdio.h>
#include <stdbool.h>
#include "CircularBuffer.h"

const unsigned char UBX_HEADER[]         = { 0xB5, 0x62 };
const unsigned char NAV_DOP_HEADER[]     = { 0x01, 0x04 };
const unsigned char NAV_PVT_HEADER[]     = { 0x01, 0x07 };
const unsigned char NAV_TIMEGPS_HEADER[] = { 0x01, 0x20 };

enum _ubxMsgType {
  MT_NONE,
  MT_NAV_DOP,
  MT_NAV_PVT,
  MT_NAV_TIMEGPS
};

struct NAV_DOP {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;          // GPS time of week of the navigation epoch (ms)

  unsigned short gDOP;         // Geometric DOP
  unsigned short pDOP;         // Position DOP
  unsigned short tDOP;         // Time DOP
  unsigned short vDOP;         // Vertical DOP
  unsigned short hDOP;         // Horizontal DOP
  unsigned short nDOP;         // Northing DOP
  unsigned short eDOP;         // Easting DOP
};

struct NAV_PVT {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;          // GPS time of week of the navigation epoch (ms)

  unsigned short year;         // Year (UTC)
  unsigned char month;         // Month, range 1..12 (UTC)
  unsigned char day;           // Day of month, range 1..31 (UTC)
  unsigned char hour;          // Hour of day, range 0..23 (UTC)
  unsigned char minute;        // Minute of hour, range 0..59 (UTC)
  unsigned char second;        // Seconds of minute, range 0..60 (UTC)
  char valid;                  // Validity Flags (see graphic below)
  unsigned long tAcc;          // Time accuracy estimate (UTC) (ns)
  long nano;                   // Fraction of second, range -1e9 .. 1e9 (UTC) (ns)
  unsigned char fixType;       // GNSSfix Type, range 0..5
  char flags;                  // Fix Status Flags
  char flags2;                 // Additional Flags
  unsigned char numSV;         // Number of satellites used in Nav Solution

  long lon;                    // Longitude (deg)
  long lat;                    // Latitude (deg)
  long height;                 // Height above Ellipsoid (mm)
  long hMSL;                   // Height above mean sea level (mm)
  unsigned long hAcc;          // Horizontal Accuracy Estimate (mm)
  unsigned long vAcc;          // Vertical Accuracy Estimate (mm)

  long velN;                   // NED north velocity (mm/s)
  long velE;                   // NED east velocity (mm/s)
  long velD;                   // NED down velocity (mm/s)
  long gSpeed;                 // Ground Speed (2-D) (mm/s)
  long heading;                // Heading of motion 2-D (deg)
  unsigned long sAcc;          // Speed Accuracy Estimate
  unsigned long headingAcc;    // Heading Accuracy Estimate
  unsigned short pDOP;         // Position dilution of precision

  char reserved[6];           // Reserved
  long headVeh;                // Heading of Vehicle (2-D)
  short magDec;                // Magnetic Declination
  unsigned short magAcc;       // Magnetic Declination Accuracy
};

struct NAV_TIMEGPS {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;          // GPS time of week of the navigation epoch (ms)

  long fTOW;                   // Fractional part of iTOW (range: +/- 500000)
  short week;                  // GPS week number of the navigation epoch
  char leapS;                  // GPS leap seconds (GPS-UTC)
  char valid;                  // Validity Flags (see graphic below)
  unsigned long tAcc;          // Time Accuracy Estimate
};

union UBXMessage {
  struct NAV_DOP dop;
  struct NAV_PVT pvt;
  struct NAV_TIMEGPS t_gps;
};

union UBXMessage ubxMessage;

bool compareMsgHeader(const unsigned char*);
void calcChecksum(unsigned char*, int);
int readGPS(commBuffer_t*);

#endif /* INC_UBLOX_GPS_H_ */
