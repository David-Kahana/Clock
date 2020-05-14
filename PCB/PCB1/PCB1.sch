EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x10_Female ESP32_4
U 1 1 5E9E032D
P 3600 1900
F 0 "ESP32_4" H 3492 2393 50  0000 C CNN
F 1 "Conn_01x10_Female" V 3300 1900 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 3600 1900 50  0001 C CNN
F 3 "~" H 3600 1900 50  0001 C CNN
	1    3600 1900
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10_Female ESP32_3
U 1 1 5E9E0333
P 3500 1900
F 0 "ESP32_3" H 3200 2400 50  0000 L CNN
F 1 "Conn_01x10_Female" V 3200 1500 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 3500 1900 50  0001 C CNN
F 3 "~" H 3500 1900 50  0001 C CNN
	1    3500 1900
	1    0    0    -1  
$EndComp
Text Label 3800 1500 0    50   ~ 0
CMD
Text Label 3800 1600 0    50   ~ 0
SD2
Text Label 3800 1700 0    50   ~ 0
NC1
Text Label 3800 1800 0    50   ~ 0
TMS
Text Label 3800 1900 0    50   ~ 0
IO34
Text Label 3800 2100 0    50   ~ 0
IO35
Text Label 3800 2200 0    50   ~ 0
SVN
Text Label 3800 2300 0    50   ~ 0
NC
Text Label 3800 2400 0    50   ~ 0
GND
Text Label 3300 2400 2    50   ~ 0
RST
Text Label 3300 2300 2    50   ~ 0
SVP
Text Label 3300 2200 2    50   ~ 0
IO26
Text Label 3300 2100 2    50   ~ 0
IO18
Text Label 3300 2000 2    50   ~ 0
IO19
Text Label 3300 1900 2    50   ~ 0
IO23
Text Label 3300 1800 2    50   ~ 0
IO5
Text Label 3300 1700 2    50   ~ 0
3V3
Text Label 3300 1600 2    50   ~ 0
TCK
Text Label 3300 1500 2    50   ~ 0
SD3
Text Label 2700 1500 0    50   ~ 0
SD0
Text Label 2700 1600 0    50   ~ 0
TD0
Text Label 2700 1800 0    50   ~ 0
GND
Text Label 2700 1900 0    50   ~ 0
IO16
Text Label 2700 2000 0    50   ~ 0
IO17
Text Label 2700 2100 0    50   ~ 0
IO21
Text Label 2700 2200 0    50   ~ 0
IO22
Text Label 2700 2300 0    50   ~ 0
RXD
Text Label 2700 2400 0    50   ~ 0
TXD
Text Label 2200 2400 2    50   ~ 0
GND
Text Label 2200 2300 2    50   ~ 0
IO27
Text Label 2200 2200 2    50   ~ 0
IO25
Text Label 2200 2100 2    50   ~ 0
IO32
Text Label 2200 2000 2    50   ~ 0
TDI
Text Label 2200 1900 2    50   ~ 0
IO4
Text Label 2200 1800 2    50   ~ 0
IO0
Text Label 2200 1600 2    50   ~ 0
SD1
Text Label 2200 1500 2    50   ~ 0
CLK
Text Label 2200 1700 2    50   ~ 0
IO2
$Comp
L Connector:Conn_01x10_Female ESP32_1
U 1 1 5E9C058A
P 2400 1900
F 0 "ESP32_1" H 2100 2400 50  0000 L CNN
F 1 "Conn_01x10_Female" V 1800 1500 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 2400 1900 50  0001 C CNN
F 3 "~" H 2400 1900 50  0001 C CNN
	1    2400 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10_Female ESP32_2
U 1 1 5E9C4262
P 2500 1900
F 0 "ESP32_2" H 2200 2400 50  0000 L CNN
F 1 "Conn_01x10_Female" V 2200 1900 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 2500 1900 50  0001 C CNN
F 3 "~" H 2500 1900 50  0001 C CNN
	1    2500 1900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5EA0AE3B
P 800 2500
F 0 "R4" H 870 2546 50  0000 L CNN
F 1 "2K" H 870 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 730 2500 50  0001 C CNN
F 3 "~" H 800 2500 50  0001 C CNN
	1    800  2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5EA0D680
P 1150 2500
F 0 "R3" H 1220 2546 50  0000 L CNN
F 1 "2K" H 1220 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1080 2500 50  0001 C CNN
F 3 "~" H 1150 2500 50  0001 C CNN
	1    1150 2500
	1    0    0    -1  
$EndComp
Text Label 3800 2000 0    50   ~ 0
IO33
$Comp
L Device:R R2
U 1 1 5E9C77DE
P 1450 2500
F 0 "R2" H 1380 2454 50  0000 R CNN
F 1 "120" H 1380 2545 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1380 2500 50  0001 C CNN
F 3 "~" H 1450 2500 50  0001 C CNN
	1    1450 2500
	-1   0    0    1   
$EndComp
Text Label 1200 1600 3    50   ~ 0
USB_D-
Text Label 1300 1600 3    50   ~ 0
USB_D+
Text Label 1150 2350 1    50   ~ 0
USB_D+
Text Label 800  2350 1    50   ~ 0
USB_D-
Text Label 1150 2650 3    50   ~ 0
VCC
Text Label 800  2650 3    50   ~ 0
VCC
Text Label 1450 2350 1    50   ~ 0
USB_D-
Text Label 1450 2650 3    50   ~ 0
IO4
Text Label 900  1200 2    50   ~ 0
GND
Text Label 1800 2650 3    50   ~ 0
IO32
Text Label 1800 2350 1    50   ~ 0
USB_D+
$Comp
L Device:R R1
U 1 1 5EA0BCD1
P 1800 2500
F 0 "R1" H 1730 2454 50  0000 R CNN
F 1 "120" H 1730 2545 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1730 2500 50  0001 C CNN
F 3 "~" H 1800 2500 50  0001 C CNN
	1    1800 2500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x09_Male DISPALY1
U 1 1 5EA18DDD
P 2050 3750
F 0 "DISPALY1" H 2158 4421 50  0000 C CNN
F 1 "Conn_01x09_Male" H 2158 4330 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x09_P2.54mm_Vertical" H 2150 3150 50  0000 C CNN
F 3 "~" H 2050 3750 50  0001 C CNN
	1    2050 3750
	1    0    0    -1  
$EndComp
Text Notes 1950 4200 2    60   ~ 0
VCC(1)\nGND\nCS\nRESET\nDC/RS\nSDI/MOSI\nSCK\nLED\nSDO/MISO(9)
Text Label 2250 3350 0    50   ~ 0
3V3
Text Label 2250 3450 0    50   ~ 0
GND
Text Label 2250 3550 0    50   ~ 0
IO5
Text Label 2250 3650 0    50   ~ 0
TCK
Text Label 2250 3750 0    50   ~ 0
IO26
Text Label 2250 3850 0    50   ~ 0
IO23
Text Label 2250 3950 0    50   ~ 0
IO18
Text Label 2250 4050 0    50   ~ 0
TMS
Text Label 2250 4150 0    50   ~ 0
IO19
Text Label 2700 1700 0    50   ~ 0
VCC
$Comp
L Connector:USB_A USB_K1
U 1 1 5E9EC64F
P 1300 1300
F 0 "USB_K1" V 1311 1630 50  0000 L CNN
F 1 "USB_A" V 1402 1630 50  0000 L CNN
F 2 "Connector_USB:USB_A_Stewart_SS-52100-001_Horizontal" H 1450 1250 50  0001 C CNN
F 3 " ~" H 1450 1250 50  0001 C CNN
	1    1300 1300
	0    1    1    0   
$EndComp
Text Label 900  1300 2    50   ~ 0
GND
Text Label 1500 1600 3    50   ~ 0
VCC
$Comp
L Connector:Conn_01x05_Male ENC1
U 1 1 5EB359DF
P 3400 3500
F 0 "ENC1" V 3300 3500 50  0000 C CNN
F 1 "Conn_01x05_Male" V 3200 3500 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 3400 3500 50  0001 C CNN
F 3 "~" H 3400 3500 50  0001 C CNN
	1    3400 3500
	0    -1   -1   0   
$EndComp
Text Label 3200 3300 1    50   ~ 0
3V3
Text Label 3300 3300 1    50   ~ 0
GND
Text Label 3400 3300 1    50   ~ 0
IO33
Text Label 3500 3300 1    50   ~ 0
IO35
Text Label 3600 3300 1    50   ~ 0
IO34
$Comp
L Connector:Conn_01x01_Male H1
U 1 1 5EB686C0
P 750 700
F 0 "H1" H 858 881 50  0000 C CNN
F 1 "Conn_01x01_Male" H 858 790 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill2mm" H 750 700 50  0001 C CNN
F 3 "~" H 750 700 50  0001 C CNN
	1    750  700 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male H2
U 1 1 5EB6C557
P 1500 750
F 0 "H2" H 1608 931 50  0000 C CNN
F 1 "Conn_01x01_Male" H 1608 840 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill2mm" H 1500 750 50  0001 C CNN
F 3 "~" H 1500 750 50  0001 C CNN
	1    1500 750 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male H3
U 1 1 5EB6CA09
P 2400 750
F 0 "H3" H 2508 931 50  0000 C CNN
F 1 "Conn_01x01_Male" H 2508 840 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill2mm" H 2400 750 50  0001 C CNN
F 3 "~" H 2400 750 50  0001 C CNN
	1    2400 750 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male H4
U 1 1 5EB6CA3F
P 3250 750
F 0 "H4" H 3358 931 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3358 840 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill2mm" H 3250 750 50  0001 C CNN
F 3 "~" H 3250 750 50  0001 C CNN
	1    3250 750 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male STAND1
U 1 1 5EB7B31D
P 4250 3450
F 0 "STAND1" V 4150 3450 50  0000 C CNN
F 1 "Conn_01x05_Male" V 4050 3450 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 4250 3450 50  0001 C CNN
F 3 "~" H 4250 3450 50  0001 C CNN
	1    4250 3450
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
