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
Our inspiration for the project came from the need for a reliable and effective solution for vehicle rescue in case of accidents. Every year, millions of people lose their lives or suffer injuries due to car accidents. We wanted to develop a product that could help save the driver’s life by detecting and responding to these situations automatically and promptly. With the advancement of IoT and edge computing, we were able to leverage the power of embedded systems and sensors to create a vehicle rescue system that can sense collision, overturning, fire, and wading, and activate appropriate countermeasures, such as spraying water to extinguish the fire and opening the sunproof for escape. Our system can also communicate with a remote vehicle rescue center via the Internet, and send the accident information and location, so that the driver can get help as soon as possible. Our goal with this project is to make vehicle rescue more efficient and effective, while also reducing the risk of fatalities and injuries. 

## What it does 
Our inspiration for the project came from the need for a reliable and effective solution for vehicle rescue in case of accidents. Every year, millions of people lose their lives or suffer injuries due to car accidents. We wanted to develop a product that could help save the driver’s life by detecting and responding to these situations automatically and promptly. With the advancement of IoT and edge computing, we were able to leverage the power of embedded systems and sensors to create a vehicle rescue system that can sense collision, overturning, fire, and wading, and activate appropriate countermeasures, such as spraying water to extinguish the fire and opening the sunproof for escape. Our system can also communicate with a remote vehicle rescue center via the Internet, and send the accident information and location, so that the driver can get help as soon as possible. Our goal with this project is to make vehicle rescue more efficient and effective, while also reducing the risk of fatalities and injuries. 

## How we built it
1. Firstly, we determined the functionalities of the vehicle rescue system and selected suitable chips to realize them. 
2. Then we designed a compact PCB which holds accelerometer, gyroscope, temperature & humidity sensor, GPS, and servo to make our device mountable and occupy a small space. 
3. After this PCB was manufactured, we wrote the drivers for the sensors and actuators. 
4. Algorithms for sensors were also designed and the function of communicating with the terminal and the cloud server. 
5. Finally,  we conducted the complete test and all functionalities worked well.

## Challenges we ran into
### Hardware:
- We assigned PA24 as the pin muxed to WO2 of TCC1 to generate PWM signal at the beginning according to the datasheet. However, it doesn't work on our board. We first tried to generate PWM signal on SAMW25 Xplain Pro dev board to ensure our program is fully correct. Then we experimented on our own board and found we can successfully generate PWM signal using pin PA17 and muxing it to WO2 of TCC2. Finally, we attached a jumper from the testpoint of PA17 to the connector and managed to control the servo.

### Software:
- The handler of accidents were repeatedly triggered when an accident was detected, resulting in redundant computation and server access. We added a flag to make the handler triggered only once in the case of an accident. The flag is set to block generating the request after the an semaphore is issued, and is reset when the accident is actually handled.

- The synchronization of our program doesn't work fine in the beginning. As a result, the command line often got stuck, and mqtt broker cannot be connected sometimes. We carefully ajusted the priority of each thread, and tuned the suspension period of each task to solve this issue.

## Accomplishments that we're proud of
- Designed a vehicle rescue system that can detect combust, flooding, collision and overturning, as well as a gps location.
- Designed our own PCBA which works perfectly fine, including the battery system and peripherals.
- Developed the UI page which reflects real time information from the sensors and the severity of the situation.
- Implemented the connection between the system and the cloud.
- Built a model with high integration of our PCBA, actuators and the casework.

## What we learned 
- The process of having an idea to bringing the project to life ultimately and how to deal with every step of it.
- Designing PCBA and choosing parts according to power assumptions and functionality.
- How to build the communications using FreeRtos and CLI.
- How to connect our board to cloud and design our UI using Node-RED.
- Multiple communication protocols and how to implement them in our sensors and actuators.
- Techniques to display our project to the audience with pics and videos and emphasizing our highlights.
- The beauty of IoT.

## What's next for ESE516 IoT Smart Watch Prototype
- Improve the actuators, associated with PWM.
- Improve our casework and mechanical connections.
- Develop a control interface.
- Improve the gps accuracy and other performances.
- Test our system in real vehicles.

## Link to our Node-RED demo URL
[link](https://urldefense.com/v3/__http://20.102.85.166:1880/ui/*!/2?socketid=2aQrE-XEIavbcpYjAAAB__;Iw!!IBzWLUs!SQBM2Ocf-4c6Tx-cR8XIjrAddaftF89aK1PXuFJ0L9vQYlaqKbhOuqs6xS7pKp9lN79EsX_AWTW2lYEGT9__uGYo$)
