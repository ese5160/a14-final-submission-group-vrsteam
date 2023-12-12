# ESE516-VRSTeam

## Team members
Runlong Hu, Yijie Ding

## Video
[![Watch the video](https://img.youtube.com/vi/uA40hQ0PbCM/hqdefault.jpg)](https://www.youtube.com/embed/uA40hQ0PbCM)

## Pictures
<p align="center">
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/Front_view.png" width="18%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/Block_diagram.png" width="18%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/Top_view.png" width="20%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/Bottom_view.png" width="20%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/Heart_rate_mode.png" width="20%"></img> 

<p align="center">
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/2D1.png" width="18%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/3d1.png" width="18%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/3d2.png" width="20%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/Nodered.png" width="20%"></img> 
<img src="https://github.com/watsom3ed/ESE516-DarkMoon/blob/main/figures/Dashboard.png" width="20%"></img> 
</p>

## Inspiration
The inspiration for designing this wearable IoT smartwatch comes from the growing need to support the aging population and address their safety concerns. With an increasing number of elderly people living alone or without regular caregivers, it becomes imperative to ensure their safety and well-being. So we create a device that can track their physical activity, monitor vital signs, and provide emergency assistance in case of falls or accidents.

## What it does 
This wearable IoT smartwatch can monitor temperature and health information including heart rate and blood oxygen saturation. An alarm will be sent to the terminal if any abnormal data is detected. Also, If the user accidentally falls, the watch can also detect by using an accelerometer, and send an alarm. The smartwatch can receive messages from the terminal and display them on the screen, allowing communication between the elderly and their children. All the functions can be used through CLI commands or buttons on the watch.

## How we built it
1. Firstly, we determined the functionalities of this watch and selected suitable chips to realize them. 
2. Then we designed a compact PCB which holds all the sensors to make our device wearable and occupy a small space. 
3. After this PCB was manufactured, we wrote the drivers for the sensors and screens. 
4. Algorithms for sensors were also designed and the function of communicating between the terminal and the watch was added. 
5. Finally,  we conducted the complete test and all functionalities worked well.

## Challenges we ran into
### Hardware:
- The power regulator did not work correctly initially. We found that the regulator chip is a constant output chip and no additional resistors are needed to balance the output voltage. So we removed the redundant resistors and this made the regulator work correctly.

### Software:
- The data got from the heart rate click is not readable data of heart rate and blood oxygen saturation. This sensor measures the light reflected by the finger, which changes along with the heartbeat. The reflected light signal is noisy and it is challenging to convert the raw data to heart rate and blood oxygen saturation. We designed an algorithm that can smooth the raw data and count the number of peaks in the light signal to make the sensor work.
- The SPI communication utilized in the ST7735 screen driver is relatively slow, resulting in a low screen refresh rate. To address this issue, the DMA method is implemented in SPI communication, allowing direct data reading from the main memory and subsequently enhancing the screen's refresh rate.

## Accomplishments that we're proud of
- Designed a wearable IoT smartwatch, which is able to detect temperature, health information, and accidents. 
- Implemented the communication between the watch and the terminal. 
- Developed I2C driver and SPI driver interface for sensors and actuators. 
- Developed the algorithm of heart rate click (max30102).
- Brought up PCB by detecting and overcoming several hardware issues. 

## What we learned 
- Designing PCBA while adhering to guidelines to ensure proper functionality.
- Getting familiar with communication protocols such as SPI, UART, I2C etc.
- Understanding the working principles of FreeRTOS and implementing it in our project.
- Transferring and receiving data via MQTT and displaying information on a dashboard using Node-RED.
- Developing a program to download files from the internet, ultimately realizing OTAFU on our smartwatch.

In summary, we gained valuable skills in PCB design and coding for unfamiliar devices. Our ability to pinpoint the sources of issues has also improved. Hardware design problems can sometimes be unpredictable, but with systematic testing and patience, we can successfully identify and resolve the underlying causes.

## What's next for ESE516 IoT Smart Watch Prototype
- Make the interface more user-friendly. Bigger font and simpler operation will be realized for the elderly.
- Implement sensors get into hibernation mode when not used in order to make the battery last longer. The code logic and algorithms can also be improved to make the detection quicker and more accurate.
- Develop the GPS function on the board and improve its working performance.

## Link to our Node-RED demo URL
[link](https://pleasant-whinchat-5522.flowforge.cloud/ui/#!/0?socketid=mXLtKAlgD6xP0WeeAAFP)
