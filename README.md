# uSDX-EX-SDR RADIO

This project are in attempt to integrate USDX HF transceiver version from WB2CBA with the following features:

01 - Automatic 6 bands pre and final LPF selection.

02 - RF power amplifier (RF PA) controlling process, since it is crucial for the proper RF transition sequence.

03 - SWR measurements, with a simplified LED indicator - 1->1.5 (BEST), 1.5->1.9 (BETTER), 1.9->3 (GOOD), >3 (POOR).

04 - 30W SSB RF linear power amplifier. 

05 - RF spectrum display experimentation. For future developments, I will use Raspberry PI PICO with Micro Python scripting language. 

Below are the first prototype image:

![WhatsApp Image 2023-08-20 at 12 53 13 AM](https://github.com/bahari/USDX-CNTRL-MCU/assets/3076739/5cad0087-fde6-4f5a-9aa8-bb502913f045)

# Brief Information - SDR Radio

The uSDX-EX SDR radio (EX means EXTRA/EXPERIMENTATION) was adopted from the well known projects known as micro SDX (uSDX) - Micro Software Defined Transceiver, 
which you can get the information via the following link:

https://github.com/threeme3/usdx

The base radio firmware was taken from expand/additions version made by Rob Colclough GW8RDI, hence you can see the copyright term written in the code itself.
But STILL the concept of copyright are still open source as stated below:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

In the spirit of maintaining the open source concepts, all can copy, modified and sell the code but are still subjected to the above term and conditions. NO ONE can disclose the code.  

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

01 - Maintaining using Si5351 signal generator module as been suggested by WB2CBA for signal debugging and verification process.

02 - Replacing FST3253 and LM4562 for Tayloe Quadrature Sampling detector with 74HC4053 and NE5532 which can be purchased from local store as suggested
from the following link:

https://hf5l.pl/en/transceiver-usdx-with-arduino-nano/

03 - Using existing PTX - PB3 (External PTT trigger) and PD5 I/O port for I2C communication with the control MCU. All the triggering process will
be implemented via I2C communication and process via external control MCU (Arduino NANO board).

# Brief Information - Low Pass Filter (LPF)

This protype are consists of two stages LPF:

01 - Pre 6 bands (80,60,40,30,20,17 meters) 7 elements Butterworth LPF with self wind and self constructed design which is copy from the following link:

http://qrp-labs.com/images/lpfkit/gqrplpf.pdf - For the design

http://qrp-labs.com/images/lpfkit/assembly_A4.pdf - For detail constructions

02 - Final 5 elements Butterworth LPF bare board brand XF-LPF-HF which is cater for all HF bands low pass filtering. This board you can purchased online.

The above filter was simulated using ELSIE application which you can download it from the following link:

http://tonnesoftware.com/elsie.html

Further practical test for the LPF section was checked and tested by using NanoVNA. My 7 elements LPF are not very sharp in suppressing the harmonics because of 
the low quality capacitor and toroid used, but the characteristics as predicted from simulation software are still in accepted level. 

Furthermore the final LPF stage will further suppressed the harmonics after the RF PA stage. RF harmonics was test and measured by using spectrum analyzer.
I used the TinySA as a main spectrum analyzer with a 100W 30dB attenuator.

## 80m Bands LPF S21 Test Results

![80m-S21-23T-27T-23T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/4c1e00c7-423a-4cec-becf-341d0f94652f)

## 80m Bands LPF S11 Test Results

![80m-S11-23T-27T-23T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/1b8efe1d-cffc-4240-835f-1a6a3a2a21fc)

# Brief Information - Control MCU

The control MCU was constructed using Arduino NANO as a main controller which will have the following features in minds:

01 - Automatic 6 bands pre and final LPF and RF PA LPF selection.

02 - RF power amplifier (RFPA) controlling process, since it is crucial for the proper RF transition sequence.

03 - SWR measurements, with a simplified LED indicator - 1->1.5 (BEST), 1.5->1.9 (BETTER), 1.9->3 (GOOD), >3 (POOR).

Feature no. 01 and 02 already tested. For no. 03 need to purchase Stockton/SWR bridge module.

With the implementation of the external MCU, I can expand the radio functionalities according to my needs since the current uSDX code already consumes 
a lot of program memory.

# Brief Information - Relay

This design was used a normal relay that you can find from the local store. There is two type of relay used for this design, which is:

01 - Double Pole Double Throw (DPDT) relay for pre LPF selection for each bands.

02 - Single Pole Double Throw (SPDT) relay for RF PA control.

# Brief Information - RF Power Amplifier

The RF Power Amplifier used for this projects are a linear type of Push Pull RF amplifier which used a normal power MOSFET (IRF 530N) as an amplifier
elements. The further information you can get from the following links:

https://pa0fri.home.xs4all.nl/Lineairs/RF-AMP-2078/RF-AMP-2078.htm

Bear in minds that, this amplifier are HARD to adjust and calibrate. I already blown a lot of this power amplifier MOSFET in order to get a better
amplified signal waveform. You will learn a lot if you constructed and test this type of amplifier, but STILL its WORKS.

Please watch the following link (4 Parts of video) for further details in construction and testing process:

https://www.youtube.com/watch?v=d4Vtk0D06S8&t=7s

You needs an oscilloscope in order to test and measured the signal purity of the amplification process. But this is an optional, you can used bulb if you
dare as stated from the following link:

https://www.rfcafe.com/references/qst/neon-bulbs-qst-july-1953.htm

You can buy this kits online.

# Brief Information - Constructions

The construction of this radio was adopted from the 'Manhattan' style construction which gives an easy construction techniques and easy for
hardware debugging purposes. Further information are from following links:

https://hackaday.com/2016/05/04/getting-ugly-dead-bugs-and-going-to-manhattan/

# Last Words

I will update this page from time to time along with progress of the projects. Please inform me if there is a misinformation regarding the above knowledge and
facts - I'm still in a limited knowledge mode.

Ahmad Bahari - 9M2GRC

73



