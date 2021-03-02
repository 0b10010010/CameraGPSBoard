# CameraGPSBoard
STM32L4 Camera Trigger GPS Tagging

Table below shows the connection scheme for the image analysis hardware used

| STM32L4 | SONY A6000 |  GPS  |
| :-----: | :--------: | :---: |
|   A1    |    White   |  N/A  |
|  D0(RX) |     N/A    | Green |
|   GND   |    Black   | Black |

When the &mu;controller is running the software, it will detect the hotshoe line as a hardware interrupt to send out GPS data at the time of trigger. Main while loop is receiving and parsing `UBX NAV_PVT` messages. Pixhawk is configured to receive GPS data at 10Hz.
