# uSDX-EX-SDR RADIO

This project are in attempt to integrate USDX HF transceiver version from WB2CBA with the following features:

01 - Automatic 6 bands LPF and RF PA LPF selection.

02 - RF power amplifier (RFPA) controlling process, since it is crucial for the proper RF transition sequence.

03 - SWR measurements, with a simplified LED indicator - 1->1.5 (BEST), 1.5->1.9 (BETTER), 1.9->3 (GOOD), >3 (POOR).

04 - 30W SSB RF linear power amplifier. 

05 - RF spectrum display experimentation.

Below are the first prototype image:

![WhatsApp Image 2023-08-20 at 12 53 13 AM](https://github.com/bahari/USDX-CNTRL-MCU/assets/3076739/5cad0087-fde6-4f5a-9aa8-bb502913f045)

# Brief Information - SDR Radio

The uSDX-EX SDR radio (EX means EXTRA/EXPERIMENTATION) was adopted from the well known projects known as micro SDX (uSDX) - Micro Software Defined Transceiver, 
which you can get the information via the following link:

https://github.com/threeme3/usdx

The base radio firmware was taken from expand/additions version made by Rob Colclough GW8RDI, hence you can see the copyright term written in the code itself.
But STILL the concept of copyright are still open source as stated below:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

In the spirit of maintaining the open source concepts, all can copy, modified and sell the code but are still subjected to above term and conditions. NO ONE can disclose the code.  

There is some additions of the code in order to integrate it with above stated features. You can search it by using one of the following keyword:

//////////////////////////////////////////////////////////////////////////////////

// Code Patch/Changes

// Author : Bahari

// Date   : 18/08/2023

// REMARKS: My firmware version number

#define VERSION   "1.02E01"  

//////////////////////////////////////////////////////////////////////////////////

Above are my own programming style - different programmer with a different commenting style.

The main board for SDR radio was a self assembled board develop by WB2CBA and the kit can be purchased online. The further information
regarding this developments you can get via the following link:

https://antrak.org.tr/blog/usdx-an-arduino-based-sdr-all-mode-hf-transceiver-pcb-iteration-v1-02/

The modification was been done as following:

01 - Maintaining using Si5351 signal genarator module as been suggested by WB2CBA for signal debugging and verification process.

02 - Replacing FST3253 and LM4562 for Tayloe Quadrature Sampling detector with 74HC4053 and NE5532 which can be purchased from local stored as suggested
from the following link:

https://hf5l.pl/en/transceiver-usdx-with-arduino-nano/

03 - Using existing PTX - PB3 (External PTT trigger) and PD5 I/O port for I2C communication with the control MCU. So all the triggering process with
be implemented via I2C communication and process via external control MCU (Arduino NANO board).

# Brief Information - Low Pass Filter (LPF)

This protype are consists of two stages LPF:

01 - Pre 6 bands (80,60,40,30,20,17 meters) 7 elements Butterworth LPF with self wind and self constructed design copy from a following link:

http://qrp-labs.com/images/lpfkit/gqrplpf.pdf - For the design

http://qrp-labs.com/images/lpfkit/assembly_A4.pdf - For detail constructions

02 - Final 5 elements Butterworth LPF bare board brand XF-LPF-HF which cater low pass filtering for all HF bands. This board you can purchased online.

The above filter was simulated using ELSIE application which you can download it from the following link:

http://tonnesoftware.com/elsie.html

Further practical test for the LPF section are check and tested by using NanoVNA. My 7 elements LPF are not very sharp in suppressing the harmonics because of 
the low quality capacitor and toroid used, but the characteristics as predicted from simulation software are still in accepted level. 
