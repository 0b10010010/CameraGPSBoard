///*
// * GPS_UBLOX.h
// *
// *  Created on: Feb 23, 2020
// *      Author: alexk
// */
//
//#ifndef GPS_UBLOX_H_
//#define GPS_UBLOX_H_
//
//#include <stdint.h>
//#include <RingBuffer.h>
//#include <usart.h>
//
//#define PACKED __attribute__((packed))
//
//class GPS_UBLOX {
//public:
//	GPS_UBLOX(GPS &_gps, GPS::GPS_State &_state, USART_Driver *_port);
//	void init();
//	bool read();
//protected:
//	USART_Driver *port;
//	GPS &gps;
//	GPS::GPS_State &state;
//private:
//	RingBuffer _readbuffer{2048};
//
//	struct PACKED ubx_header {
//		uint8_t preamble1;
//		uint8_t preamble2;
//		uint8_t msg_class;
//		uint8_t msg_id;
//		uint16_t length;
//	};
//	struct PACKED ubx_nav_pvt {
//		uint8_t msg_class;
//		uint8_t msg_id;
//		uint16_t length;
//		uint32_t itow;
//
//		uint16_t year;
//		uint8_t month, day, hour, min, sec;
//		uint8_t valid;
//		uint32_t t_acc;
//		int32_t nano;
//		uint8_t fix_type;
//		uint8_t flags;
//		uint8_t flags2;
//		uint8_t num_sv;
//		int32_t lon, lat;
//		int32_t height, h_msl;
//		uint32_t h_acc, v_acc;
//		int32_t velN, velE, velD, gspeed;
//		int32_t head_mot;
//		uint32_t s_acc;
//		uint32_t head_acc;
//		uint16_t p_dop;
//		uint8_t reserved1[6];
//		uint32_t headVeh;
//		uint8_t reserved2[4];
//	};
//    struct PACKED ubx_ack_ack {
//        uint8_t clsID;
//        uint8_t msgID;
//    };
//	union PACKED {
//		ubx_nav_pvt pvt;
//	} _buffer;
//	enum ubx_protocol_bytes {
//		PREAMBLE1 = 0xb5,
//		PREAMBLE2 = 0x62,
//		CLASS_NAV = 0x01,
//		MSG_NAV_PVT = 0x07
//	};
//    // Packet checksum accumulators
//    uint8_t         _ck_a;
//    uint8_t         _ck_b;
//    // State machine state
//    uint8_t         _step;
//    uint8_t         _msg_id;
//    uint16_t        _payload_length;
//    uint16_t        _payload_counter;
//
//    uint8_t         _class;
//
//    uint32_t        _last_vel_time;
//    uint32_t        _last_pos_time;
//
//    // do we have new position information?
//    bool            _new_position:1;
//    // do we have new speed information?
//    bool            _new_speed:1;
//
//    // Buffer parse & GPS state update
//    bool        _parse_gps();
//};
//#endif /* GPS_UBLOX_H_ */
