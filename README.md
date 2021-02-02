# CameraGPSBoard
STM32L4 Camera Trigger GPS Tagging

STM32L4 A1: Camera hotshoe signal(white) wire
    D0(RX): GPS signal(green) wire
       GND: Both GNDs from hotshoe and GPS to GND on the board

When the board is running the software, it will detect the hotshoe line as an interrupt to send out GPS data near the time of trigger all the while receiving and parsing UBX NAV_PVT messages. Pixhawk is configured to receive GPS data at 10Hz.
