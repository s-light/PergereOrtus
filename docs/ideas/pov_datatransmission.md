<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
# POV infrared data transmission
idea here is to have a IR led directly pulsing the raw data out and an receiver converting it back to signal..
so this could be transmitted over the rotation contact-less.
challenge here is the bit time - we need some very very fast photo detectors...

![pov concept overview](pov_concept_overview.svg)


## ToDo:
- find / decide which parts to test
- add schematics for
  - led control
  - photodiode / phototransistor handling


## bitrate / update-rate calculations

### 130mm Needle, 3mm Pixel Pitch

| calculation step   | APA102                | TLC5971             | formula               |
| :----------------- | :-------------------- | :------------------ | --------------------: |
| bytes_per_update   | 166 (4 + 40*4 + 2)    | 280 (28 * (40 / 4)) |                       |
| bits_per_update    | 1328                  | 2240                | bytes_per_update * 8  |
| bits_per_second    | 5418240               | 9139200             | bits_per_update * pixel_updates_per_second |
| kbit_per_second    | 5418                  | 9139                |                       |
| Mbit_per_second    | 5,41                  | 9,14                |                       |
| bit_time_max       | 184ns (= 0,184us)     | 109 ns (= 0,109us)  | `1s / (5,41*10^6) ==` |


#### reminders/ helper

1 second == 1.000 ms == 1.000.000 us == 1.000.000.000 ns  
10 bit pro second == 1s/10 per bit == 100ms per bit
10kbit pro second == 1s/10k per bit == 100us per bit
10Mbit pro second == 1/10.000.000s per bit == 0,0000001s == 100 ns  


## information collection (research)
- [Photo Detectors - Phototransistor Output](https://www.vishay.com/photo-detectors/phototrans-out/)
- [Photo Detectors - Photodiode Output](https://www.vishay.com/photo-detectors/photodie-out/)
- [Photo Detectors - Surface Mount Devices](https://www.vishay.com/photo-detectors/surface-mount-devices/)

[Optical Sensors - Transmissive](https://www.vishay.com/optical-sensors/transmissive-sensors/)

- [digikey: Vishay TEFD4300F High-Speed Photodiodes](https://www.digikey.com/en/product-highlight/v/vishay-semi-opto/tefd4300-and-tefd4300f-high-speed-pin-photodiodes)
- [Why are most IR phototransistors slow?](https://electronics.stackexchange.com/questions/347665/why-are-most-ir-phototransistors-slow)
- [example with explanation to drive a phototransistors (optoisolators)](https://electronics.stackexchange.com/a/136944/13800)
- [Phototransistor Switching Time Analysis (app note)](http://www.cel.com/pdf/appnotes/an3009.pdf)

- [Anschluß Phototransistor für high-speed? (with schematics)](https://www.mikrocontroller.net/topic/198315#2101045)

- Analog Devices
    - [LT1328 (4Mbps IrDA Infrared Receiver)](http://www.analog.com/en/products/interface-isolation/multiprotocol-transceivers/lt1328.html)
    - [ir photodiode used in demo board: BPV22NF](http://www.vishay.com/docs/81509/bpv22nf.pdf)

- [Ronja project](http://ronja.twibright.com/irrx/material.php)
  - [SFH 203 P](https://www.digikey.com/product-detail/en/osram-opto-semiconductors-inc/SFH-203-P/475-2649-ND/1893875)

- [OPA380	High Speed Precision Transimpedance Amplifier (also as dual variant)](http://www.ti.com/product/opa380)
- [OPT101 Monolithic Photodiode and Single-Supply Transimpedance Amplifier](http://www.ti.com/lit/ds/symlink/opt101.pdf)

- [some ideas and research to optical transmission with leds](https://electronics.stackexchange.com/questions/24214/using-a-led-to-transmit-data)
    - [photodiode OPF430 by Optek Inc](https://www.digikey.com/product-detail/en/tt-electronics-optek-technology/OPF430/365-1839-ND/1637898)
    - [TI OPA657 1.6GHz, Low Noise, FET-Input Operational Amplifier](http://www.ti.com/product/OPA657)

- [mikrocontroller.net basics](https://www.mikrocontroller.net/articles/Lichtsensor_/_Helligkeitssensor)


## Parts

| part                                                         | type       | wavelength | housing    | capacitance  | rise/fall time  |
| :----------------------------------------------------------- | :--------: | :--------- | :--------- | -----------: | --------------: |
| [VEMT2020X01](http://www.vishay.com/docs/81595/vemt2000.pdf) | photodiode | 860nm      | SMD GW     |  25pF        | 2ns             |
| [VSMY1850X01](http://www.vishay.com/docs/83317/vsmy1850.pdf) | led        | 850nm      | SMD 0805   | 125pF        | 10ns            |
| [VSMF4720](http://www.vishay.com/docs/81923/vsmf4720.pdf)    | led        | 870nm      | SMD PLCC-2 | 125pF        | 15ns            |
| [TEMT7100X01](http://www.vishay.com/docs/81770/temt7100.pdf) | photodiode | 870nm      | SMD 0805   |  25pF        | 2ns             |
[Vishay source for rise/fall times for photodiodes](https://www.vishay.com/docs/49071/_sg2166.pdf)
