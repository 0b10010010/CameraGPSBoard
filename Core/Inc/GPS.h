/*
 * GPS_State.h
 *
 *  Created on: Feb 28, 2020
 *      Author: alexk
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include <Location.h>

class GPS
{
	friend class GPS_UBLOX;

public:
    struct GPS_State {

        // all the following fields must all be filled by the backend driver
//        GPS_Status status;                  ///< driver fix status
//        uint32_t time_week_ms;              ///< GPS time (milliseconds from start of GPS week)
//        uint16_t time_week;                 ///< GPS week number
        Location location;                  ///< last fix location
        float ground_speed;                 ///< ground speed in m/sec
        float ground_course;                ///< ground course in degrees
        float gps_yaw;                      ///< GPS derived yaw information, if available (degrees)
        bool  gps_yaw_configured;           ///< GPS is configured to provide yaw
        uint16_t hdop;                      ///< horizontal dilution of precision in cm
        uint16_t vdop;                      ///< vertical dilution of precision in cm
        uint8_t num_sats;                   ///< Number of visible satellites
        float speed_accuracy;               ///< 3D velocity RMS accuracy estimate in m/s
        float horizontal_accuracy;          ///< horizontal RMS accuracy estimate in m
        float vertical_accuracy;            ///< vertical RMS accuracy estimate in m
        float gps_yaw_accuracy;           ///< heading accuracy of the GPS in degrees
        bool have_vertical_velocity;      ///< does GPS give vertical velocity? Set to true only once available.
        bool have_speed_accuracy;         ///< does GPS give speed accuracy? Set to true only once available.
        bool have_horizontal_accuracy;    ///< does GPS give horizontal position accuracy? Set to true only once available.
        bool have_vertical_accuracy;      ///< does GPS give vertical position accuracy? Set to true only once available.
        bool have_gps_yaw;                ///< does GPS give yaw? Set to true only once available.
        bool have_gps_yaw_accuracy;       ///< does the GPS give a heading accuracy estimate? Set to true only once available
        uint32_t last_gps_time_ms;          ///< the system time we got the last GPS timestamp, milliseconds
        uint32_t uart_timestamp_ms;         ///< optional timestamp from set_uart_timestamp()

    };
};

#endif /* INC_GPS_H_ */
