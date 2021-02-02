# CameraGPSBoard
STM32L4 Camera Trigger GPS Tagging

When the board is running the software, it will detect the hotshoe line as an interrupt to send out GPS data near the time of trigger all the while receiving and parsing UBX NAV_PVT messages. Pixhawk is configured to receive GPS data at 10Hz.
