# CameraGPSBoard
STM32L4 Camera Trigger GPS Tagging

Table below shows the connection scheme for the image analysis hardware used

| STM32L4 | SONY A6000 |  GPS  |
| :-----: | :--------: | :---: |
|   A1    |    White   |  N/A  |
|  D0(RX) |     N/A    | Green |
|   GND   |    Black   | Black |

When the &mu;controller is running the software, it will detect the hotshoe line as a hardware interrupt to send out GPS data at the time of trigger. Output data is in text file format in order for onboard computer to read and manipulate the data in order to extract the GPS coordinates of targets within the image frames. Main while loop is receiving and parsing `UBX NAV_PVT` messages. Pixhawk is configured to receive GPS data at 10Hz.

Example output format is shown below:
```text
Image index: 1 Date:2020/2/1 18:16:32:200239166 lat/lon: 39.2027969,-96.5458908
Image index: 2 Date:2020/2/1 18:16:35:400238232 lat/lon: 39.2027969,-96.5442504
Image index: 3 Date:2020/2/1 18:16:38:200237413 lat/lon: 39.2027931,-96.5458908
Image index: 4 Date:2020/2/1 18:16:41:400236475 lat/lon: 39.2027931,-96.5458908
```
