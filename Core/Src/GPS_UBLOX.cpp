///*
// * GPS_UBLOX.cpp
// *
// *  Created on: Feb 23, 2020
// *      Author: alexk
// */
//#include <GPS.h>
//#include <GPS_UBLOX.h>
//#include <RingBuffer.h>
//#include "usart.h"
//
//GPS_UBLOX::GPS_UBLOX(GPS &_gps, GPS::GPS_State &_state, USART_Driver *_port) :
//	port(_port),
//	gps(_gps),
//	state(_state)
//{
//	MX_USART1_UART_Init(); // Receive GPS data from UBLOX M8N unit
//	state.have_speed_accuracy = false;
//    state.have_horizontal_accuracy = false;
//    state.have_vertical_accuracy = false;
//}
//
//
////{
////	MX_USART1_UART_Init(); // Receive GPS data from UBLOX M8N unit
////
////}
//
//
//
//bool GPS_UBLOX::read(void)
//{
//    uint8_t data;
//    int16_t numc;
//    bool parsed = false;
//
//    numc = port->available();
//    for (int16_t i=0; i<numc; i++) {
//
//    }
//
//    return parsed;
//}
