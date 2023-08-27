# uSDX-EX HF SDR RADIO

![Simple-HF-SDR](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/e6f314c2-deaf-4adc-bd41-a61063fc0bd1)

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
But the concept of copyright are STILL open source as stated below:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

In the spirit of maintaining the open source concepts, all can copy, modified and sell the code but are still subjected to the above term and conditions.  

There is some additions of the code in order to integrate it with above stated features. You can search it by using one of the following keyword:

//////////////////////////////////////////////////////////////////////////////////

// Code Patch/Changes

// Author : Bahari

// Date   : 18/08/2023

// REMARKS: My firmware version number

#define VERSION   "1.01EX"  

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

Adjustments and fine tuning process for the LPF was done with a minimum efforts since I required only at approximately -10dBm RF input to RF PA.

## 80m Bands LPF Simulation

![elsie](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/160d0ce6-1231-4608-abf0-caec6f869192)

## 80m Bands LPF S21 Test Results

![80m-S21-23T-27T-23T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/4c1e00c7-423a-4cec-becf-341d0f94652f)

## 80m Bands LPF S11 Test Results

![80m-S11-23T-27T-23T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/1b8efe1d-cffc-4240-835f-1a6a3a2a21fc)

## 80m Bands Harmonics Test Results - 13.3dBm

![harmonics-01](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/c84c4073-8eb4-4ff2-8be3-3480ed8d574e)

Frequency used: 3.8MHz - Power (dBm): 13.3dBm - Power (mW): 20mW

2'nd harmonic: -45.3dB - 3'nd harmonic: -70.3dB - 4'th harmonic: -73dB

Attenuator: 30dB

## 80m Bands Harmonics Test Results - 31.8dBm

![harmonics-02](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/670a9b3f-16f5-47eb-bc8d-3fca6bee7aa2)

Frequency used: 3.8MHz - Power (dBm): 31.8dBm - Power (W): 1.5W

2'nd harmonic: -61.4dB - 3'nd harmonic: -87.2dB - 4'th harmonic: -105.2dB

Attenuator: 30dB

## 60m Bands LPF Simulation

![elsie](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/170e6d70-2a9d-498d-9916-8b5d6f2012e7)

## 60m Bands LPF S21 Test Results

![60m-S21-21T-24T-21T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/8ef39597-dac8-4a17-85bf-3d41ec1e5cfa)

## 60m Bands LPF S11 Test Results

![60m-S11-21T-24T-21T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/0482881f-9c14-4e62-af6e-c1db39c781ed)

## 60m Bands Harmonics Test Results - 12.3dBm

![harmonics-01](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/9a94302f-3dc7-4cb5-a0e6-fea0e5288cde)

Frequency used: 5.3MHz - Power (dBm): 12.3dBm - Power (W): 16mW

2'nd harmonic: -61.1dB - 3'nd harmonic: -67.6dB - 4'th harmonic: -61.2dB

Attenuator: 30dB

## 60m Bands Harmonics Test Results - 31dBm

![harmonics-02](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/352d5b6c-4aca-4a8f-b949-5a36ea42616b)

Frequency used: 5.3MHz - Power (dBm): 31dBm - Power (W): 1.25W

2'nd harmonic: -78.3dB - 3'nd harmonic: -73.9dB - 4'th harmonic: -81.1dB

Attenuator: 30dB

## 40m Bands LPF Simulation

![elsie](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/0b3bda19-bb8f-4b30-81e8-2f825dd901d0)

## 40m Bands LPF S21 Test Results

![40m-S21-18T-22T-18T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/e3904339-e956-4b59-b3f0-710703c5dce2)

## 40m Bands LPF S11 Test Results

![40m-S11-18T-22T-18T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/ccbfe3a4-15e1-4b8a-aa21-7cd32e7ea368)

## 40m Bands Harmonics Test Results - 12.8dBm

![harmonics-01](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/b6839b5b-ebde-4b28-baa5-60396ba5398f)

Frequency used: 7.13MHz - Power (dBm): 12.8dBm - Power (W): 20mW

2'nd harmonic: -47.2dB - 3'nd harmonic: -68.4dB - 4'th harmonic: -56.2dB

Attenuator: 30dB

## 40m Bands Harmonics Test Results - 30.8dBm

![harmonics-02](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/c374fa32-4d5e-45d7-9c7b-7731450390a0)

Frequency used: 7.13MHz - Power (dBm): 30.8dBm - Power (W): 1.25W

2'nd harmonic: -68.2dB - 3'nd harmonic: -75.2dB - 4'th harmonic: -82dB

Attenuator: 30dB

## 30m Bands LPF Simulation

![elsie](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/b0034fc4-214f-459e-96b7-6a4145868f1b)

## 30m Bands LPF S21 Test Results

![30m-S21-17T-20T-17T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/174ddcd1-6231-4cfc-8e2d-dde8508a202d)

## 30m Bands LPF S11 Test Results

![30m-S11-17T-20T-17T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/780f3a16-3b93-43c8-a2c5-f7996ec5a744)

## 30m Bands Harmonics Test Results - 9.8dBm

![Harmonics-01](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/04488528-1b1e-4648-8c51-0867346c8c09)

Frequency used: 10.1MHz - Power (dBm): 9.8dBm - Power (W): 10mW

2'nd harmonic: -54.6dB - 3'nd harmonic: -58.5dB - 4'th harmonic: -50.1dB

Attenuator: 30dB

## 30m Bands Harmonics Test Results - 29.3dBm

![Harmonics-02](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/ac16931d-ca15-44ab-bad9-db17e7a291dc)

Frequency used: 10.1MHz - Power (dBm): 29.3dBm - Power (W): 1W

2'nd harmonic: -80.1dB - 3'nd harmonic: -83.8dB - 4'th harmonic: -80dB

Attenuator: 30dB

## 20m Bands LPF Simulation

![elsie](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/48ca8ca1-7e5d-4ae2-97b4-69f1efe91b39)

## 20m Bands LPF S21 Test Results

![20m-S21-16T-17T-16T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/0637c35d-e361-493d-9ac3-6212d0f4e197)

## 20m Bands LPF S11 Test Results

![20m-S11-16T-17T-16T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/9e870a9e-7c5c-4084-9114-9c7b81b41a04)

## 20m Bands Harmonics Test Results - 9dBm

![harmonics-01](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/ffef3004-8dac-4425-930d-4accff08ee34)

Frequency used: 14.1MHz - Power (dBm): 9dBm - Power (W): 8mW

2'nd harmonic: -67.3dB - 3'nd harmonic: -46.3dB - 4'th harmonic: -68.4dB

Attenuator: 30dB

## 20m Bands Harmonics Test Results - 26dBm

![harmonics-02](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/4d7ba173-0608-4c24-806f-bc56c0df4d14)

Frequency used: 14.1MHz - Power (dBm): 26dBm - Power (W): 0.4W

2'nd harmonic: -83.9dB - 3'nd harmonic: -76.8dB - 4'th harmonic: -87dB

Attenuator: 30dB

## 17m Bands LPF Simulation

![elsie](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/1ef32b87-3822-4120-a082-ff1cf11815fd)

## 17m Bands LPF S21 Test Results

![17m-S21-13T-15T-13T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/d3708ff5-aced-4c65-9323-16b0730d0dc5)

## 17m Bands LPF S11 Test Results

![17m-S11-13T-15T-13T-LPF](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/61602b97-0279-4eef-a7d8-34e9b1149abf)

## 17m Bands Harmonics Test Results - 6dBm

Frequency used: 18.1MHz - Power (dBm): 6dBm - Power (W): 4mW

2'nd harmonic: -40.9dB - 3'nd harmonic: -48.9dB - 4'th harmonic: -53.5dB

Attenuator: 30dB

## 17m Bands Harmonics Test Results - 23.5dBm

![harmonics-02](https://github.com/bahari/USDX-EX-RADIO/assets/3076739/2cc1f32f-b0f1-469f-a91f-9b78866fe03f)

Frequency used: 18.1MHz - Power (dBm): 6dBm - Power (W): 0.2W

2'nd harmonic: -73.7dB - 3'nd harmonic: -80.7dB - 4'th harmonic: -81.7dB

Attenuator: 30dB

## Emission Standards

Emission standards are according to the following link:

https://www.law.cornell.edu/cfr/text/47/97.307

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



