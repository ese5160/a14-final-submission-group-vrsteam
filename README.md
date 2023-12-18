# ESE516-Team3 VRSTeam

## Team members
Runlong Hu, Yijie Ding

## Video
[![Watch the video](https://img.youtube.com/vi/uA40hQ0PbCM/hqdefault.jpg)](https://www.youtube.com/embed/uA40hQ0PbCM)

## Pictures
<p align="center">
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/board3D.png" width="18%"></img> 
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/PCBAtop.jpg" width="18%"></img> 
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/PCBAbottom.jpg" width="20%"></img> 
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/thermal.jpeg" width="20%"></img> 

<p align="center">
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/board2D.png" width="18%"></img> 
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/board3D.png" width="18%"></img> 
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/nodereddashboard.png" width="20%"></img> 
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/noderedbackend.png" width="20%"></img> 
<img src="https://github.com/ese5160/a14-final-submission-group-vrsteam/blob/main/imgs/blockdiagram.png" width="20%"></img> 
</p>

## Device Description
With the advancement of IoT and edge computing, we were able to leverage the power of embedded systems and sensors to create a vehicle rescue system that can sense collision, overturning, fire, and wading, and activate appropriate countermeasures, such as spraying water to extinguish the fire and opening the sunproof for escape. Our system can also communicate with a remote vehicle rescue center via the Internet, and send the accident information and location, so that the driver can get help as soon as possible.

## Inspiration
Our inspiration for the project came from the need for a reliable and effective solution for vehicle rescue in case of accidents. Every year, millions of people lose their lives or suffer injuries due to car accidents. We wanted to develop a product that could help save the driver’s life by detecting and responding to these situations automatically and promptly. Our goal with this project is to make vehicle rescue more efficient and effective, while also reducing the risk of fatalities and injuries. 

## Device Functionality
Our device can be divided into two parts, sensors and actuators. The sensors we are using include 3 components. We use SHTC3 to read temperature and humidity data, corresponding to the detection of fire and wading accident. We use LSM6DSM to read acceleration and gyroscope data, corresponding to the detection of collision and overturning. At last, we have a gps sensor PA1616D to provide longitude and latitude information. Our actuators include a servo, connected to the trunk of our prototype car model, and a waterpump, connected to the MCU with a motor driver.
As the sensors read the data into the MCU, our embedded code will analyze it and determine if the accident happened or not. If the accident happened, the MCU will send command to the actuators and get them functioning. Also, as our device is connected to the cloud, our UI will display the real-time data when accident happens. Additionaly, we use Node-Red to process the data so that we can know the type and the severity of the accident.

## Project Links
### Link to our Node-RED demo URL
[link](https://urldefense.com/v3/__http://20.102.85.166:1880/ui/*!/2?socketid=2aQrE-XEIavbcpYjAAAB__;Iw!!IBzWLUs!SQBM2Ocf-4c6Tx-cR8XIjrAddaftF89aK1PXuFJ0L9vQYlaqKbhOuqs6xS7pKp9lN79EsX_AWTW2lYEGT9__uGYo$)
### Link to our final PCBA on Altium 365
[link](https://upenn-eselabs.365.altium.com/designs/62BF434C-BC62-4D87-9824-FC2D5E280976?OpenedFrom=AD&variant=[No+Variations]&activeDocumentId=Team3_VRSTeam_PCB.PcbDoc&activeView=3D&location=[3,19.84,60,0.29,19.84,60,-41.73,0,1,0]#design)

## Challenges
### Hardware:
- We assigned PA24 as the pin muxed to WO2 of TCC1 to generate PWM signal at the beginning according to the datasheet. However, it doesn't work on our board. We first tried to generate PWM signal on SAMW25 Xplain Pro dev board to ensure our program is fully correct. Then we experimented on our own board and found we can successfully generate PWM signal using pin PA17 and muxing it to WO2 of TCC2. Finally, we attached a jumper from the testpoint of PA17 to the connector and managed to control the servo.

### Software:
- The handler of accidents were repeatedly triggered when an accident was detected, resulting in redundant computation and server access. We added a flag to make the handler triggered only once in the case of an accident. The flag is set to block generating the request after the an semaphore is issued, and is reset when the accident is actually handled.

- The synchronization of our program didn't work fine in the beginning. As a result, the command line often got stuck, and mqtt broker cannot be connected sometimes. We carefully ajusted the priority of each thread, and tuned the suspension period of each task to solve this issue.

## Prototype Learnings
The process of building the prototype tells a lot about how to turn your ideas into a real product. One of the things we leared is that it is important to get your schematic and PCB right in the first place. Add backups and B-plans as much as possible in the first prototype, such as test points and jumpers. Moreover, it is better to begin doing casework earlier.

## Next Steps
- Improve the actuators, associated with PWM.
- Improve our casework and mechanical connections.
- Develop a control interface.
- Improve the gps accuracy and other performances.
- Test our system in real vehicles.

## Takeaways from ESE5160
- The process of having an idea to bringing the project to life ultimately and how to deal with every step of it.
- Designing PCBA and choosing parts according to power assumptions and functionality.
- How to build the communications using FreeRtos and CLI.
- How to connect our board to cloud and design our UI using Node-RED.
- Multiple communication protocols and how to implement them in our sensors and actuators.
- Techniques to display our project to the audience with pics and videos and emphasizing our highlights.
- The beauty of IoT.