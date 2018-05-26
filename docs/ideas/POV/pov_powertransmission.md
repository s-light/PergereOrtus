# POV power transmission
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
power transmission should be possible with slip-rings.
as Jürgen pointed out in chat - if you get the diameter of the slide-ring smaller you get lower surface speed -
so less wear...

this is in contrast to the data ir transmission - as i need to get these wires or fibers through the shaft..
but i think i will find a good compromise..

---
# Contents
{:.no_toc}

* Will be replaced with the ToC, excluding the "Contents" header
{:toc}
---

## use slip-rings
- [slip-rings with ball-bearings](http://web.archive.org/web/20101005013331/http://maybevideodoes.de/howto/slipring.html)
    - [images](http://web.archive.org/web/20101010045648/http://www.maybevideodoes.de:80/howto/newSlipring/index.html)
- [slip-ring car alternator (to big)](https://www.lima-shop.de/en/product_info.php/info/p297_Slip-ring-univ--d-14-90mm-for-Valeo-Alternator.html)
- [slip-ring small but only 250rpm](http://www.slipring.com/miniature-slip-rings.html)
- [slip-ring small but only 250rpm](http://www.slipring.com/miniature-slip-rings.html)
- [exp / sparkfun - slip-ring 22mm 12x2A <250rpm](https://www.exp-tech.de/motoren/schleifring/8494/slip-ring-12-wire-2a)
- [exp / Adafruit - slip-ring 12mm 6x2A <250rpm](https://www.exp-tech.de/module/sonstige/5583/miniature-slip-ring-12mm-diameter-6-wires-max-240v-at-2a)
- [SRS022-12 - slip-ring 12x2A <3000rpm](http://slipring.com.cn/product_detaile.php?id=116)
- [LTN Servotechnik GmbH - schleifring](https://www.ltn-servotechnik.com/de/produkte/schleifringe/signaluebertragung/)
- [element14 community: DIY Slip Rings: 5 Go-To Guides That Detail How To Make A Slip Ring](https://www.element14.com/community/groups/power-management/blog/2016/09/12/diy-slip-rings-5-go-to-guides-that-detail-how-to-make-a-slip-ring)


## use coils
- [Royer Converter](https://www.mikrocontroller.net/articles/Royer_Converter)
- [technology overview (TI)](https://www.wirelesspowerconsortium.com/technology/why-not-a-wire-the-case-for-wireless-power.html)
- [more background info: Wireless Electricity Transmission](https://www.wirelesspowerconsortium.com/technology/how-it-works.html)
- [POV Display With Wireless Power!](http://www.instructables.com/id/POV-Display-With-Wireless-Power/)
- [Arduino Wireless Power POV Display](http://www.instructables.com/id/Arduino-Wireless-Power-POV-Display/)
- [rotating air transformer](http://www.oocities.org/tjacodesign/propclock/propclock.html)
- [PCB-Winding - Version 4 (August 2014)](http://electronixandmore.com/projects/propclock/index.html)
- [3D POV Display with 10W wireless power](http://www.instructables.com/id/PropHelix-3D-POV-Display/)
    - [wireless module](https://www.banggood.com/12V-Wireless-Charger-Module-5V-Power-Supply-Charging-Coil-Transmitter-Receiver-For-Phone-p-1122411.html?rmmds=myorder)
- [Rotary Transformer (for Persistence of Vision displays)](https://www.youtube.com/watch?v=7rGtyMUr_Vc)

GreatScott! (video)
- [How Does Wireless Charging Work? || Crude Wireless Energy Transfer Circuit (video)](https://www.youtube.com/watch?v=ExU32UyGX6w)
- [DIY Wireless Energy Transfer System (good starting point)](https://www.youtube.com/watch?v=3E5PUnYlaTM)
    - [same as instructables write down](http://www.instructables.com/id/DIY-Wireless-Energy-Transfer-System/)

- [WE REDexpert Workbench](https://www.we-online.com/redexpert/#/module/15/selecteditems/760308100110,760308100143/productdata/=760308101302/kf/asc/size/+or+%C3%98_50+5353/applicationbar/WPCCMatcher/on/wp/760308100110/options/true)
- [WE 760308100141](http://katalog.we-online.com/de/pbs/WE-WPCC-TRANSMITTER/760308100141) [(PDF)](http://katalog.we-online.com/pbs/datasheet/760308101141.pdf)
- [WE 760308100143](http://katalog.we-online.com/de/pbs/WE-WPCC-TRANSMITTER/760308100143) [(PDF)](http://katalog.we-online.com/pbs/datasheet/760308100143.pdf)
- [WE 760308100110](http://katalog.we-online.com/de/pbs/WE-WPCC-TRANSMITTER/760308100110) [mouser 11,60€](https://www.mouser.de/ProductDetail/Wurth-Electronics/760308100110?qs=%2fha2pyFadui4G5%2f1MFX1HUUrVCJModGZAm4rKxr1lSo0EM1Ygx79Gw==) [(PDF)](http://katalog.we-online.com/pbs/datasheet/760308100110.pdf)

self-made with Ferrite cores
- [Ferrite Pot Cores for Inductors and Power Supplies](http://www.cwsbytemark.com/index.php?main_page=index&cPath=206_231)
- [TDK pmpp cores halves](https://de.tdk.eu/tdk-de/193526/produkte/produktkatalog/ferrites/epcos-ferrite-und-zubehoer/pmppcoreshalves)
- [TDK Core P 36 x 22](https://de.tdk.eu/inf/80/db/fer/p_36_22.pdf)
- [Ferroxcube P 22 x13](https://www.ferroxcube.com/upload/media/product/file/Pr_ds/P22_13.pdf)

### Phone wireless charging technology
- receiver
    - [bq51013b	WPC 1.1 Compatible Fully Integrated Wireless Power Receiver IC (20VQFN)](http://www.ti.com/product/bq51013b)
    - [bq51050b	Qi (WPC) Compliant Highly Integrated Secondary-Side Direct Lithium Ion Charger (20VQFN)](http://www.ti.com/product/bq51050b)
- transmitter
    - [bq500212a	(NRND) Qi Compliant 5V Wireless Power Transmitter Manager](www.ti.com/product/bq500212a)
    - [5W WPC (Qi) Compliant Wireless Power Transmitter for 5V Applications Reference Design (bq500212A)](http://www.ti.com/tool/tida-00259)
    - [Small 5W Wireless Power Transmitter Reference Design (bq500511 & bq50002)](http://www.ti.com/tool/tida-00623)

- würth electronic
    - [WE-WPCC Wireless Power Transfer Transmitter Spule](http://katalog.we-online.de/de/pbs/WE-WPCC-TRANSMITTER?sid=e05308da79)
    - [high power designs industrial](http://www.we-online.de/web/de/electronic_components/produkte_pb/application_notes/anp032.php)
    - [reference design / kits](http://www.we-online.de/web/de/electronic_components/produkte_pb/demoboards/wireless_power/referencedesigns/referencedesigns.php)


- [Qi-Universalempfänger: Micro-USB “unten”](http://inbay.systems/de/qi-handyzubehoer/)
- [Inbay® Universal Lüftungshalter mit induktiver Ladefunktion](http://inbay.systems/de/inbay-universal-lueftungshalter-2/)
- [acv ist Spezialist für Wireless Charging](https://www.acvgmbh.de/produkte/induktive-lademoeglichkeiten/)

- [modules uway-qi](http://www.uway-qi.com/e/Products/qi_modules/index.html)
    - [Qi RX Receiver Module Model NO: UNIQT-0108 (15W)](http://www.uway-qi.com/e/Products/qi_modules/p32.html)
    - [(SEMICO) Qi 5W Wireless Charging TX Module A11/5V (WPC 1.2.1 certified) (Round Type) Model NO: UNIQT-0004 (1W)](http://www.uway-qi.com/e/Products/qi_modules/p39.html)
    - [Qi 15W Medium power wireless charging TX module Model NO: UNIQT-0014 (15W)](http://www.uway-qi.com/e/Products/qi_modules/p31.html)
    - [Fast-Charge Qi 10W Wireless Charging TX Module Model NO: SAMQT-0011 (10W)](http://www.uway-qi.com/e/Products/qi_modules/p33.html)
    - [(SEMICO) Qi 5W Wireless Charging TX Module A11/5V (WPC 1.2.0 certified) (Square Type) (5W)](http://www.uway-qi.com/e/Products/qi_modules/p40.html)

- [Wireless Power Receiver - Futura Group Srl - 7100-FT1236M (9,9€)](https://store.open-electronics.org/FT1236M?search=ft123)
- [Wireless Power Trasmitter FT1235M - Futura Group Srl- 7100-FT1235M (19,70€)](https://store.open-electronics.org/FT1235M)



### ToDo:
- research parts and schematics
- source for small brushes?!
- use some small motors?!
- [exp-tech DC 130-Size, 6V, 11.5kRPM; 1,7€](https://www.exp-tech.de/motoren/dc-motoren/4858/dc-buerstenmotor-130-size-6v-11.5krpm-800ma-stall?c=1199)
- [exp-tech DC M260, 1V, 6.6kRPM; 2,0€](https://www.exp-tech.de/motoren/dc-motoren/5204/hobby-motor-gear?c=1199)
