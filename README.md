# Firmware_for_Transmitter

 ZJUNlict Transmitter's Firmware for the Robocup Soccer Small-Size League https://zjunlict.cn/

The firmware for [transmitter](https://github.com/ZJUNlict/Transmitter)'s corresponding core board is designed using Altera (now Intel) [Quartus II 9.1](https://www.intel.com/content/www/us/en/programmable/downloads/software/quartus-ii-se/91.html) and [Nios II 9.1 IDE](https://www.intel.com/content/altera-www/global/en_us/index/downloads/software/nios-ii/91.html). 

The features are:

* Verilog design of UART interface. 
* [Nios® II embedded processor](https://www.intel.com/content/www/us/en/products/programmable/processor/nios-ii.html) (set the running frequency at 50MHz) is built in the Cyclone III FPGA through Quartus II software. 
* Nios® II embedded firmware is designed in C language handling more complex logical calculation and hardware configuration. 
* The C project for the firmware is in Trans_V2.3\trans_3 folder. 
* Radio communication configuration (nRF2401A modules) and communication test procedure is designed in the firmware.