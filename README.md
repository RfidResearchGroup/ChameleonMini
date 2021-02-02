Chameleon-Mini
==============
This is NOT the official repository of ChameleonMini, a freely programmable, portable tool for NFC security analysis that can emulate and clone contactless cards, read RFID tags and sniff/log RF data. 

Chameleon BLE API
[**Codes.RAR**](https://github.com/RfidResearchGroup/ChameleonBLEAPI/blob/master/code.rar)

Our Project is based on the open-source project by ChameleonMini RevG by Kasper & Oswald [Webshop](https://shop.kasper.it/). 

Our ChameleonMini / ChameleonTiny by ProxGrind is available on Indiegogo now. 
**[Done](https://www.indiegogo.com/campaigns/chameleonmini-rev-g-chameleontiny-by-proxgrind/)**

Our Asia & Oceania Reseller
**[Here](https://sneaktechnology.com/)**

Our Europe Reseller
**[Here](https://lab401.com/)**

Our US Reseller
**[Here](https://hackerwarehouse.com/)**

Most information can be found on **[Here](http://chameleontiny.com/)**

Our APP can be found here: **[Here](https://play.google.com/store/apps/details?id=com.proxgrind.chameleon)**

Dropbox download for all relevant files: [Link-Broken]
----------------------------------------
**[Here](https://www.dropbox.com/s/xt2o9ugalaam4xu/REV.G%20User%20Manual%2020200309.zip?dl=0)** **Dropbox**

**[Here](https://drive.google.com/open?id=1nU6r8VS4HwFRkp9hhhIlAmfU49p4cbn6)** **Google Drive**

A.Upgrade to the latest firmware
==============================

1.Upgrade Chameleon AVR Firmware
-----------------------------

(1) Prepare your Windows computer. Linux or MAC please refer to GITHUB.

(2) Prepare the firmware. Go to GITHUB to compile the latest firmware:
**[Here](https://github.com/RfidResearchGroup/ChameleonMini)**

Or use the firmware in attachment.

(3) Install the DFU driver. The DFU driver comes from ATMEL's official LIBUSB driver library. You can download it yourself or find it in attachment.

(4) Enter the chameleon DFU mode. When the device is off, press and hold the yellow button near the USB (TINY is the B button), insert the USB, and then you can enter the DFU upgrade mode. Or send the command "UPGRADE" in the connected state, and it can also enter the DFU upgrade mode.

(5) Start to upgrade the firmware. Run the "ChameleonFirmwareUpgrade.bat" file in the attachment to automatically start the firmware upgrade. It usually takes 2-5 seconds. After the progress bar is complete, the firmware upgrade is complete!

(6) A description of the firmware. The chameleon REV.G version uses the same firmware for both the MINI with Bluetooth version and ITNY. The hardware design of the RF part is exactly the same.
The hardware is also compatible with the official firmware of the KAOS brothers: **[Here](https://github.com/emsec/ChameleonMini)**

It should be noted that the Android APP is currently not compatible with the official firmware.

2. Upgrade (OTA) Bluetooth firmware for Chameleon MINI

(1) Prepare Android phone and install APP.

Google Store: **[Here](https://play.google.com/store/apps/details?id=com.proxgrind.chameleon)**

**Password: e4g1**

(2) Open the app and connect the device using Bluetooth. Press any button on the MINI, and the white battery light is on, and Bluetooth is connectable. At this time, open the app again and click Connect to automatically connect the chameleon.

(3) Start upgrade (OTA) Bluetooth firmware. In the “Device Information” column, press “BLE CMD Version” 5 times.
It will pop up the OTA upgrade page, click "Auto Upgrade", and the APP will immediately start to upgrade the latest Bluetooth firmware that comes with it. Automatically exit after the upgrade is complete.

-----------------------

B. Quick Crash Course
====================

**1.Detect keys and upload card files**

(1) Prepare the computer GUI or Android APP.
 
Computer GUI download address: **[Here](http://www.icesql.se/download/ChameleonMiniGUI/publish.htm)**

Source: **[Here](https://github.com/iceman1001/ChameleonMini-rebootedGUI)**

 Android APP download address:

Google Store:**[Here](https://play.google.com/store/apps/details?id=com.proxgrind.chameleon)**

**Password: e4g1**

(2) Connect the Chameleon MINI or TINY using the Android APP.

USB port direct connection: Both the Chameleon MINI and TINY support direct connection to the mobile phone USB port. For the MINI, an additional OTG adapter needs to be purchased. TINY uses its own dual-headed TYPE-C data cable to connect directly to TYPE-C mobile phones.
Bluetooth connection: Chameleon MINI has built-in Bluetooth BLE4.0. Press any button first to wake up Bluetooth. Turn on Bluetooth on your Android phone and the app will automatically connect.

(3) Use Android APP to enable detection mode.

   After connecting, click on a single card slot and select DETECTION_1K or 4K in the "card slot mode". This card slot has the detection mode turned on. Write the original card number in the "UID Card Number" column. Click "Write." If you don't know the UID number, you can fill in it at will. Then click the "Clear" button below to clear the last detection record.

(4) Use Android APP to get keys.

At this time, take the chameleon to the access control reader and swipe. The key and access traces when the chaser reads the chameleon will be recorded by the chameleon.
. At this time, connect back to the mobile phone and click the "crack" button. After few seconds, the app will automatically solve and list the results, as shown in the figure below:

<a href="https://ibb.co/Q6xcVkW"><img src="https://i.ibb.co/Q6xcVkW/Untitled-1.png" alt="Untitled-1" border="0"></a>

The list shows which blocks the read head just visited, and what password was used for each access.
At this point, click the "History" button, the APP will automatically list the keys separately and copy it automatically for easy copying to other software for next use.
If your mobile phone comes with NFC function, you can directly put the original card on the mobile phone NFC at this time, the APP will automatically use the key in the list to read the entire card, and after successful, it will automatically save the entire card data file on the mobile phone. .
Note: Multiple red LEDs are on at the same time during detection, which means the memory is full, just clear the memory.

(5) Use Android APP to import existing card data files in batches.

 Use QQ to send the card data file to the mobile phone QQ, or connect the mobile phone to the computer and transfer the file to any directory on the mobile phone.
Open the app, click the "DUMP" column below, click the "Scanner" in the "plus sign" in the upper right corner, click the three horizontal line buttons in the upper left corner, and select this phone. Then select the root directory of the QQ receiving file or the previously copied directory, and click Allow Access. All card data files will be automatically scanned into the "DUMP file" interface, which can be uploaded or edited at will. 

Click the card data file in the “DUMP” column below, and click “Upload” below to upload to the card slot corresponding to the chameleon.

**2. Introduction to UID mode and SAK mode**

(1) UID mode

After the UID mode is turned on, the card simulated by Chameleon will become a GEN1a card, commonly known as a UID card, Chinese magic card.
Global card slot takes effect.
How to open: Click the button "UID Changeable (GEN1a)" in the APP or directly send the command "UIDMODE = 1" to turn it on, and "UIDMODE = 0" to turn it off.

(2) SAK mode

After the SAK mode is turned on, the card will feedback the real SAK value when it is being found. The SAK value is determined by the 0 sector and 0 block, and the position is the position of the sixth byte immediately after the UID number. If the SAK mode is not turned on, the SAK is a fixed value of 08, and 0 blocks of data are ignored.
This function is used to meet the situation that some cards with special SAK values cannot be used normally after being copied, and can achieve better compatibility.
The current card slot takes effect.
How to open: Click the "SAK Mode" button in the APP or directly send the command "SAKMODE = 1" to turn it on, and "SAKMODE = 0" to turn it off.

**3. Card slot function introduction**

UID Card Function Class

|Option     | Type     | Length of UID | Memory Size    |
| ------------------- |:-------------------:| -------------------:| -------------------:|
MF_classic_1K 4B/7B|M1 S50 |4 Byte / 7 Byte|1024 byte
MF_classic_4K 4B/7B | M1 S70|4 Byte / 7 Byte|4096 byte|
MF_classic_mini_4B|M1 mini S20|4 Byte / 7 Byte|320 byte|
MF_ultralight_C|M0 ultralight|7 Byte|192 byte|
MF_ultralight_EV1_80B|M0 ultralight|7 Byte|80 byte|
MF_ultralight_EV1_164B|M0 ultralight|7 Byte|164 byte|
Vicinity|-|8 Byte|8192  byte|
SL2S2002|-|8 Byte|8192 byte|
TITAGITSTANDARD|-|8 Byte|44  byte|
EM4233|-|8 Byte|208 byte|

**Cracking and card reading functions**
 
|Option     | Ability    | Cracking Type | APP Supported    |
| ------------------- |:-------------------:| -------------------:| -------------------:|
MF_DETECTION_1K|Detecting reader to obtain keys|MFKEY32V2|List results directly|
MF_DETECTION_4K|Detecting reader to obtain keys|MFKEY32V2|List results directly|
ISO14443A_READER|Reader Mode|-|Display UID|
ISO14443A_SNIFF|Sniffing|-|Not supported|
ISO15693_SNIFF|Sniffing|-|Not supported|

**4. Button Custom Function Introduction**

|Option names    | Description    | 
| ------------------- |:-------------------:| 
NONE|Set this button to have no function|
UID_RANDOM|Randomly generated UID number in the current card slot after pressing|
UID_LEFT_INCREMENT|After pressing, the highest byte of the UID number plus one (hexadecimal)|
UID_RIGHT_INCREMENT|After pressing the lowest byte of the UID number plus one (hexadecimal)|
UID_LEFT_DECREMENT|After pressing, the highest byte of the UID number is reduced by one (hexadecimal)
UID_RIGHT_DECREMENT|After pressing, the lowest byte of the UID number is reduced by one (hexadecimal)|
CYCLE_SETTINGS|Card slot number sequence will increase after pressing|
CYCLE_SETTINGS_DEC|Card slot number sequence decreases after pressing|
STORE_MEM|Immediately after pressing, the current card data in the temporary buffer is overwritten into the memory|
RECALL_MEM|Immediately after pressing, the current card data in the memory is overwritten into the temporary buffer (Can be used to quickly restore card data)|
TOGGLE_FIELD|Click once to turn off the antenna and click again to turn on the antenna function|
STORE_LOG|Write the log data in the temporary cache to the memory, which can be saved even when power is off|
CLEAR_LOG|Clear log data immediately after pressing|
CLONE|Read the UID card number immediately after pressing, continue searching, and simulate immediately after reading the card|

Button Usage
-----------
When the power is off, press any button once to turn on the Bluetooth power, and at the same time, display the current power with a white LED.
In the Bluetooth 'ON' state, click any button to turn off the Bluetooth power, the power LED goes out, and the system sleeps.
Bluetooth will sleep automatically 15 seconds after no operation.
Press any button for a long time, you can quickly check the power, and immediately sleep when you release.
Click the button three times to turn on the power of chameleon. Sleep automatically after 5 seconds without operation.
When shutting down, press and hold the button next to USB and then connect USB. You can enter DFU mode.
Charging: Any time you connect USB, it will automatically start charging. Stop automatically after filling. The white LED indicates the power level.
Detect memory full: If the memory is full during dense flow detection, multiple red LEDs will be abnormally lit.

C.Hardware Introduction
=======================

**1.Button function introduction**

(1)ChameleonMini Rev G

Turn on Bluetooth and check the battery:
In the off state, press any button once to turn on the Bluetooth power and light up the white LED to show the current power. After 15 seconds, it will automatically shut down after no operation. Bluetooth is on. Press any button once to sleep and shut down immediately. Can be used to quickly check the battery level.
Turn on the chameleon:
When the Bluetooth is on, press any button twice (double-click), or in the off state, press any button three times (three-click) to turn on the chameleon. The red LED lights up to indicate the slot number. After 5 seconds without operation, it will automatically sleep and shut down.
DFU firmware upgrade status:
In the closed state, press and hold the yellow button near the USB, and then let go after inserting the USB, the chameleon enters the DFU firmware upgrade mode.

(2 ) ChameleonTiny

Turn on the chameleon:
In the off/standby state, press the A button once to turn on the chameleon power. The red LED lights up to indicate the slot number. After 5 seconds without operation, it will automatically sleep and shut down. This can be adjusted in Android Application.
DFU firmware upgrade status:
In the off state, hold down the B button and connect the USB. You can enter the DFU mode to flash new firmware .

 **Appendix**
 =================

**1.Feature comparison table for each version**

|-     | Rev.G Official by KAOS    | Rev.E Old Rdv2.0 by ProxGrind | Rev.G by ProxGrind    |Rev.G  Tiny by ProxGrind |
| ------------------- |:-------------------:| -------------------:| -------------------:|-------------------:
**Simulation**|Good performance, has blind area|Poor compatibility|Perfect performance|no blind area|Perfect performance|no blind area|
**As a reader**|1-2cm for white tag|0cm for keyfob|×|5-6cm for white tag|3-4cm for keyfob|3-5cm for white tag|2-3cm for keyfob|
**Read current**|170mA|×|65mA|60mA|
**BLE nrf52832**|×|×|√|×|
**Li-ion battery**|√|×|√|√|
**Battery indicator**|×|×|√|×|
**Low power sleep**|×|×|√|√|
**RF field wakeup**|×|√|√|√|
**Button wakeup**|×|√|√|√|
**Auto power off**|×|√|√|√|
**Official firmware compatible**|√|√|√|√|
**Replaceable Antenna**|×|×|√|×|
**MFKEY32 crack**|×|√|√|√|
**8 LED for slot**|×|√|√|√|
**Android APP**|×|×|√|√|
**Firmware anti lost**|×|×|√|×|

**2.Comparison Table Analog Card Characteristic**

||**Rev.G Official By KAOS**|**Rev.E old RDV2.0 By PROXGRIND**|**Rev.G new RDV2.0 By PROXGRIND** |**M1 white tag**|
| ------------------- |:-------------------:| -------------------:| ------------------- |-------------------:|
**122U r/w full data**|1-2 sector only|Smooth|Smooth|Smooth|
**122U Range**|61mm|41mm|73mm|71mm|
**PM3 r/w full data**|1-2 sector only|Smooth|Smooth|Smooth
**PM3 Range**|57mm|74mm|88mm|89mm|
**Phone NFC r/w full data**|No|Smooth|Smooth|Smooth
**Phone NFC Range**|25mm|18mm|33mm|32mm
**Magic back door** |By default|No|Dual mode|No
**SAK ATQA Support**|No|No|Modifiable|No|

**3.List of new commands**

| Command    | Effect Range    | Description | 
| ------------------- |:-------------------:| -------------------:|
**UIDMODE?**|All slot|Returns the configuration of the all slot|
**UIDMODE=?**|All slot|Returns a list of all supported configurations|
**UIDMODE=[0;1]**|All slot|Activates(1)，deactivates(0)，the magic card mode(It will has Chinese magic card back door)|
**SAKMODE?**|Current slot|Returns the configuration of the current slot|
**SAKMODE=?**|Current slot|Returns a list of all supported configurations|
**SAKMODE=[0;1]**|Current slot|Activates(1)，deactivates(0)，the real SAK ATQA mode (the SAK ATQA will be mapped from block 0)|
**CONFIG=MF_DETECTION_1K**|Current slot|Set current slot to detection 1K mode.|(It will record the key information as log in flash)|
**CONFIG=MF_DETECTION_****4****K**|Current slot|Set current slot to detection 4K mode.|(It will record the key information as log in flash)|
**DETECTION=0**|Device|Clears the detection log memory|
**DETECTION？**|Device|Wait for an XModem connection and then downloads the binary detection log data.|

4.Complete Instruction List
-----------------------

From the official:
**[Here](https://rawgit.com/emsec/ChameleonMini/master/Doc/Doxygen/html/_page__command_line.html)**

Or see the instruction sheet in the attached files.

（1）Simulation Support

5.Supported Cards & Encoding Types
-------------------------------

From the official:
**[Here](https://github.com/emsec/ChameleonMini/wiki/Supported-Cards-and--Codecs)**

（1）Simulation Support

|Card Type|Encoding Type|Whether the hardware supports|Does the software support|Whether the application layer supports|Note|
| ------------------- |:-------------------:| -------------------:| ------------------- |:-------------------:| -------------------:|
Non13.56MHz|No|No|No| |
Mifare Ultralight|ISO14443A/106 kbit/s|Support|Support|Support|
Mifare Ultralight Ev1|ISO14443A/106 kbit/s|Support|Support|Support|
MifareClassic1K/4K 4B/7B|ISO14443A/106 kbit/s|Support|Support|Support|
Mifare DESFire|ISO14443A High Rate|Supports low rates, or possibly higher rates|Only supported Low rate|No|
Mifare DESFire EV1|ISO14443A High rate|Supports low rates, or possibly higher rates|Only supported Low rate|No|Backward compatible|
Mifare DESFire EV2|ISO14443A High rate| Supports low rates, or possibly higher rates|Only supported|Low rate|No|Backward compatible|
Mifare PLUS|ISO14443A High rate|Supports low rates, or possibly higher rates|Only supported Low rate|No
Sniff Mode NTAG|ISO14443A 106 kbit/s|Support|Support| No
LEGIC prime|LEGICprime/ ISO14443A/ ISO15693|Possible but not supported|Possible but not supported|No|
HID iCLASS|125kHz/ISO15693/ISO14443B|Possible but not supported|Possible but not supported|No|
Epass|ISO14443A/B|Supported / Supported|Low rate only / not supported|No|
ISO15693|ISO15693|Support|Support|No|


（2）Sniff Mode Support Type


|Encoding type|Whether the hardware supports|Does the software support| Whether the application layer supports|Note|
| ------------------- |:-------------------:| -------------------:| ------------------- |-------------------:|
Non-13.56MHz|Not Supported|Not Supported|Not Supported|
ISO 14443 A 106 kbit/s|Reader -> card Direction sniffing|Maybe support the other direction|Currently only supported Reader -> card Direction sniffing |Support|


（3） Card Type Supported via Reading


Card type |Encoding type|  Whether the hardware stand by|Whether the software stand by|Whether the application layer supports|Note
| ------------------- |:-------------------:| -------------------:| ------------------- |-------------------:|-------------------:|
Non13.56MHz|Not Supported|Not Supported|Not Supported|
Mifare Ultralight|ISO14443A 106 kbit/s|Support|Support|SupportCommand: dump_mfu
MifareClassic1K/4K 4B/7B|ISO14443A 106 kbit/s|Support|Support|Not Supported|No card reading instruction, encryption function has been implemented|MIFARE DESFIRE|ISO14443A High rate|Supports low rates, or possibly higher rates|  Only supported Low rate|Not Supported|No card reading instruction, encryption function is being supported|

2.Charging and Standby Mode
-----------------------

Charging method: Plug in the USB at any time and start charging immediately.
Battery type: LIR2032H replaceable lithium-ion rechargeable battery
Charging time: 2 hours @ 0-100%
Charging current: 40mA
Start-up current: 38mA
Card reading current: 65mA
Sleep current: 5uA (9uA-MAX)
Battery capacity: 70mAh
Duration: Swipe the card 3 times a day for 5 seconds each time, and it can be used for one year on a single charge.
Sleeping time: Fully charged, it can be left for two years when it is turned off and sleeping.
Port type: 
MINI: MicroUSB 
TINY: Type-C

Parameter
------------------------
Battery Type: LIR2032h rechargeable lithium ion battery  
Charging Time: 2 hours @ 0-100%  
Charging Current: 40mA  
Standby Current: 38ma  
Sleep Current: 4uA  
Card Reading Current: 65mA  
Battery Capacity: 70mah  
Usage Time: Use the tag 3 times a day, power on for 5 seconds each time, can use up to one year.  
Port Type: Micro USB (ChameleonMini) / Type-C (ChameleonTiny)  

Repository Structure
--------------------
The code repository contains
* Doc: A doxygen documentation 
* Drivers: Chameleon drivers for Windows and Linux
* Dumps: Dumps of different smartcards
* Hardware: The layout and schematics of the PCB
* Firmware: The complete firmware including a modified Atmel DFU bootloader and LUFA
* Software: Contains a python tool for an easy configuration (and more) of the ChameleonMini, Note that this is currently under construction
* RevE: Contains the whole contents of the discontinued RevE repository.
* RevE-light: Contains our development files for the RevE-light - **WARNING:** currently not supported / not functional

Schematics for ChameleonMini
--------------------------

**[Here](http://chameleontiny.com/downloads/)**

Usage Guide for new function
---------------------------
<a href="https://ibb.co/VvcGbg9"><img src="https://i.ibb.co/K9pgB2h/EUd-Gl7w-Uw-AAg-Cf6.jpg" alt="EUd-Gl7w-Uw-AAg-Cf6" border="0"></a><br />

External Contributions
----------------------
Iceman  
Philippe Teuwen  
Willok  
DXL  
ProxGrind aka Olaf 
