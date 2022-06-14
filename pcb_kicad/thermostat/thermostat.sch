EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Smart Thermostat"
Date "2022-06-01"
Rev "1"
Comp "Enxor"
Comment1 "Designed by Matthew"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 6291B770
P 6900 4950
F 0 "A1" H 6350 3950 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 6350 3850 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6900 4950 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 6900 4950 50  0001 C CNN
	1    6900 4950
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U1
U 3 1 629200E8
P 1900 6450
F 0 "U1" H 1900 6767 50  0000 C CNN
F 1 "74HC14" H 1900 6676 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 1900 6450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 1900 6450 50  0001 C CNN
	3    1900 6450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U1
U 2 1 62922043
P 2800 4250
F 0 "U1" H 2800 4567 50  0000 C CNN
F 1 "74HC14" H 2800 4476 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 2800 4250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2800 4250 50  0001 C CNN
	2    2800 4250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U1
U 5 1 62923061
P 2800 4750
F 0 "U1" H 2800 5067 50  0000 C CNN
F 1 "74HC14" H 2800 4976 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 2800 4750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2800 4750 50  0001 C CNN
	5    2800 4750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U1
U 6 1 62923CF7
P 2800 5250
F 0 "U1" H 2800 5567 50  0000 C CNN
F 1 "74HC14" H 2800 5476 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 2800 5250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2800 5250 50  0001 C CNN
	6    2800 5250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U1
U 1 1 62924503
P 6000 7100
F 0 "U1" H 6000 7417 50  0000 C CNN
F 1 "74HC14" H 6000 7326 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6000 7100 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6000 7100 50  0001 C CNN
	1    6000 7100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 62925A55
P 1050 2200
F 0 "J3" H 1158 2481 50  0000 C CNN
F 1 "IR Motion" H 1158 2390 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1050 2200 50  0001 C CNN
F 3 "~" H 1050 2200 50  0001 C CNN
	1    1050 2200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 62926779
P 1050 1250
F 0 "J2" H 1158 1531 50  0000 C CNN
F 1 "HDC1080" H 1158 1440 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1050 1250 50  0001 C CNN
F 3 "~" H 1050 1250 50  0001 C CNN
	1    1050 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 6292732E
P 2250 1250
F 0 "J4" H 2358 1531 50  0000 C CNN
F 1 "OLED" H 2358 1440 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2250 1250 50  0001 C CNN
F 3 "~" H 2250 1250 50  0001 C CNN
	1    2250 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6292F240
P 1350 6800
F 0 "R1" H 1420 6846 50  0000 L CNN
F 1 "R" H 1420 6755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 1280 6800 50  0001 C CNN
F 3 "~" H 1350 6800 50  0001 C CNN
	1    1350 6800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6292FC01
P 950 6800
F 0 "C1" H 1065 6846 50  0000 L CNN
F 1 "C" H 1065 6755 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 988 6650 50  0001 C CNN
F 3 "~" H 950 6800 50  0001 C CNN
	1    950  6800
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U1
U 7 1 62984302
P 9900 4700
F 0 "U1" V 9533 4700 50  0000 C CNN
F 1 "74HC14" V 9624 4700 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 9900 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 9900 4700 50  0001 C CNN
	7    9900 4700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 62992227
P 1150 7150
F 0 "#PWR01" H 1150 6900 50  0001 C CNN
F 1 "GND" H 1155 6977 50  0000 C CNN
F 2 "" H 1150 7150 50  0001 C CNN
F 3 "" H 1150 7150 50  0001 C CNN
	1    1150 7150
	1    0    0    -1  
$EndComp
Text GLabel 1150 5700 1    50   Input ~ 0
3.3v
Text GLabel 2350 6450 2    50   Input ~ 0
BTN_A
Wire Wire Line
	1150 7150 1150 6950
Wire Wire Line
	1150 6950 1350 6950
Wire Wire Line
	1150 6950 950  6950
Connection ~ 1150 6950
Wire Wire Line
	950  6650 1150 6650
Connection ~ 1150 6650
Wire Wire Line
	1150 6650 1350 6650
Wire Wire Line
	1600 6450 1150 6450
Wire Wire Line
	1150 6450 1150 6650
Wire Wire Line
	2200 6450 2350 6450
$Comp
L 74xx:74HC14 U1
U 4 1 62999E84
P 3650 6450
F 0 "U1" H 3650 6767 50  0000 C CNN
F 1 "74HC14" H 3650 6676 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 3650 6450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 3650 6450 50  0001 C CNN
	4    3650 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 62999E8A
P 3100 6800
F 0 "R4" H 3170 6846 50  0000 L CNN
F 1 "R" H 3170 6755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3030 6800 50  0001 C CNN
F 3 "~" H 3100 6800 50  0001 C CNN
	1    3100 6800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 62999E90
P 2700 6800
F 0 "C4" H 2815 6846 50  0000 L CNN
F 1 "C" H 2815 6755 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2738 6650 50  0001 C CNN
F 3 "~" H 2700 6800 50  0001 C CNN
	1    2700 6800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x01 SW2
U 1 1 62999E96
P 2900 6100
F 0 "SW2" V 2854 6230 50  0000 L CNN
F 1 "SW_DPST" V 2945 6230 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 2900 6100 50  0001 C CNN
F 3 "~" H 2900 6100 50  0001 C CNN
	1    2900 6100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 62999E9C
P 2900 7150
F 0 "#PWR06" H 2900 6900 50  0001 C CNN
F 1 "GND" H 2905 6977 50  0000 C CNN
F 2 "" H 2900 7150 50  0001 C CNN
F 3 "" H 2900 7150 50  0001 C CNN
	1    2900 7150
	1    0    0    -1  
$EndComp
Text GLabel 2900 5700 1    50   Input ~ 0
3.3v
Text GLabel 4100 6450 2    50   Input ~ 0
BTN_B
Wire Wire Line
	2900 7150 2900 6950
Wire Wire Line
	2900 6950 3100 6950
Wire Wire Line
	2900 6950 2700 6950
Connection ~ 2900 6950
Wire Wire Line
	2700 6650 2900 6650
Connection ~ 2900 6650
Wire Wire Line
	2900 6650 3100 6650
Wire Wire Line
	3350 6450 2900 6450
Wire Wire Line
	2900 6450 2900 6650
Wire Wire Line
	3950 6450 4100 6450
Text GLabel 7000 3850 1    50   Input ~ 0
3.3v
Wire Wire Line
	7000 3950 7000 3900
Text GLabel 7100 3850 1    50   Input ~ 0
5.0v
Wire Wire Line
	7100 3850 7100 3900
$Comp
L power:GND #PWR08
U 1 1 6299BA7C
P 6950 6000
F 0 "#PWR08" H 6950 5750 50  0001 C CNN
F 1 "GND" H 6955 5827 50  0000 C CNN
F 2 "" H 6950 6000 50  0001 C CNN
F 3 "" H 6950 6000 50  0001 C CNN
	1    6950 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5950 6950 5950
Wire Wire Line
	6950 6000 6950 5950
Connection ~ 6950 5950
Wire Wire Line
	6950 5950 7000 5950
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 629A090C
P 1000 4650
F 0 "J1" H 1108 5031 50  0000 C CNN
F 1 "Rotary Encoder" H 1108 4940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 1000 4650 50  0001 C CNN
F 3 "~" H 1000 4650 50  0001 C CNN
	1    1000 4650
	1    0    0    -1  
$EndComp
Text GLabel 1200 4550 2    50   Input ~ 0
3.3v
$Comp
L power:GND #PWR02
U 1 1 629A3726
P 1200 4450
F 0 "#PWR02" H 1200 4200 50  0001 C CNN
F 1 "GND" V 1205 4322 50  0000 R CNN
F 2 "" H 1200 4450 50  0001 C CNN
F 3 "" H 1200 4450 50  0001 C CNN
	1    1200 4450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 629A393D
P 1850 4400
F 0 "R2" H 1780 4354 50  0000 R CNN
F 1 "R" H 1780 4445 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 1780 4400 50  0001 C CNN
F 3 "~" H 1850 4400 50  0001 C CNN
	1    1850 4400
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 629A4073
P 1850 5100
F 0 "R3" H 1780 5054 50  0000 R CNN
F 1 "R" H 1780 5145 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 1780 5100 50  0001 C CNN
F 3 "~" H 1850 5100 50  0001 C CNN
	1    1850 5100
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 629A42B5
P 2250 4400
F 0 "C2" H 2365 4446 50  0000 L CNN
F 1 "C" H 2365 4355 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2288 4250 50  0001 C CNN
F 3 "~" H 2250 4400 50  0001 C CNN
	1    2250 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 629A5278
P 2250 5100
F 0 "C3" H 2365 5146 50  0000 L CNN
F 1 "C" H 2365 5055 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2288 4950 50  0001 C CNN
F 3 "~" H 2250 5100 50  0001 C CNN
	1    2250 5100
	1    0    0    -1  
$EndComp
Text GLabel 2250 4650 2    50   Input ~ 0
3.3v
Text GLabel 2250 4850 2    50   Input ~ 0
3.3v
Text GLabel 3300 4250 2    50   Input ~ 0
ROT_SW
Text GLabel 3300 4750 2    50   Input ~ 0
ROT_B
Text GLabel 3300 5250 2    50   Input ~ 0
ROT_A
Connection ~ 2250 5250
Wire Wire Line
	2250 5250 2500 5250
Wire Wire Line
	1650 5250 1650 4850
Wire Wire Line
	1650 4850 1200 4850
Wire Wire Line
	1200 4750 2500 4750
Wire Wire Line
	3100 4750 3300 4750
Wire Wire Line
	3100 4250 3300 4250
Wire Wire Line
	3100 5250 3300 5250
Wire Wire Line
	2500 4250 2250 4250
Connection ~ 2250 4250
Wire Wire Line
	1650 4250 1650 4650
Wire Wire Line
	1650 4650 1200 4650
Text GLabel 1450 2200 2    50   Input ~ 0
3.3v
$Comp
L power:GND #PWR04
U 1 1 629BEC24
P 1450 2100
F 0 "#PWR04" H 1450 1850 50  0001 C CNN
F 1 "GND" V 1455 1972 50  0000 R CNN
F 2 "" H 1450 2100 50  0001 C CNN
F 3 "" H 1450 2100 50  0001 C CNN
	1    1450 2100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 629BF259
P 1450 1150
F 0 "#PWR03" H 1450 900 50  0001 C CNN
F 1 "GND" V 1455 1022 50  0000 R CNN
F 2 "" H 1450 1150 50  0001 C CNN
F 3 "" H 1450 1150 50  0001 C CNN
	1    1450 1150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 629BF70C
P 2650 1150
F 0 "#PWR05" H 2650 900 50  0001 C CNN
F 1 "GND" V 2655 1022 50  0000 R CNN
F 2 "" H 2650 1150 50  0001 C CNN
F 3 "" H 2650 1150 50  0001 C CNN
	1    2650 1150
	0    -1   -1   0   
$EndComp
Text GLabel 1450 1450 2    50   Input ~ 0
3.3v
Text GLabel 2650 1250 2    50   Input ~ 0
3.3v
Text GLabel 1450 1350 2    50   Input ~ 0
SDA
Text GLabel 2650 1450 2    50   Input ~ 0
SDA
Text GLabel 1450 1250 2    50   Input ~ 0
SCL
Text GLabel 2650 1350 2    50   Input ~ 0
SCL
Wire Wire Line
	1250 2200 1450 2200
Wire Wire Line
	1250 1450 1450 1450
Wire Wire Line
	1450 1350 1250 1350
Wire Wire Line
	1250 1250 1450 1250
Wire Wire Line
	1250 1150 1450 1150
Wire Wire Line
	2450 1150 2650 1150
Wire Wire Line
	2450 1250 2650 1250
Wire Wire Line
	2450 1350 2650 1350
Wire Wire Line
	2450 1450 2650 1450
Text GLabel 1450 2300 2    50   Input ~ 0
IR
Wire Notes Line
	4500 7450 4500 3800
Wire Notes Line
	4500 3800 800  3800
Wire Notes Line
	800  3800 800  7450
Wire Notes Line
	800  7450 4500 7450
Wire Notes Line
	850  800  3000 800 
Wire Notes Line
	3000 800  3000 2650
Wire Notes Line
	3000 2650 850  2650
Wire Notes Line
	850  2650 850  800 
Wire Wire Line
	3650 1700 3900 1700
Text GLabel 3650 1700 0    50   Input ~ 0
AC
$Comp
L Device:R R5
U 1 1 62A1886B
P 4050 1700
F 0 "R5" V 3843 1700 50  0000 C CNN
F 1 "R" V 3934 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3980 1700 50  0001 C CNN
F 3 "~" H 4050 1700 50  0001 C CNN
	1    4050 1700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 62A17AE8
P 4950 1300
F 0 "#PWR07" H 4950 1050 50  0001 C CNN
F 1 "GND" H 4955 1127 50  0000 C CNN
F 2 "" H 4950 1300 50  0001 C CNN
F 3 "" H 4950 1300 50  0001 C CNN
	1    4950 1300
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Female J5
U 1 1 62A045F3
P 6300 2150
F 0 "J5" H 6328 2126 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6328 2035 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 6300 2150 50  0001 C CNN
F 3 "~" H 6300 2150 50  0001 C CNN
	1    6300 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 629F6110
P 5850 2100
F 0 "C5" V 6102 2100 50  0000 C CNN
F 1 "C" V 6011 2100 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 5888 1950 50  0001 C CNN
F 3 "~" H 5850 2100 50  0001 C CNN
	1    5850 2100
	0    -1   -1   0   
$EndComp
Wire Notes Line
	3350 800  10500 800 
Wire Notes Line
	10500 800  10500 2900
Wire Notes Line
	10500 2900 3350 2900
Wire Notes Line
	3350 2900 3350 800 
Text Notes 950  3750 0    50   ~ 10
User Inputs
Text Notes 1000 2750 0    50   ~ 10
Sensors & Screen
Text Notes 3450 3000 0    50   ~ 10
Relays
Text GLabel 4150 2700 0    50   Input ~ 0
5.0v
Text GLabel 6300 5450 0    50   Input ~ 0
IR
Text GLabel 6300 5350 0    50   Input ~ 0
BTN_B
Text GLabel 6300 5250 0    50   Input ~ 0
BTN_A
Text GLabel 6300 4550 0    50   Input ~ 0
ROT_A
Text GLabel 6300 4650 0    50   Input ~ 0
ROT_SW
Text GLabel 6300 4750 0    50   Input ~ 0
ROT_B
Text GLabel 7500 5450 2    50   Input ~ 0
SCL
Text GLabel 7500 5350 2    50   Input ~ 0
SDA
Text GLabel 6300 4950 0    50   Input ~ 0
Heat
Text GLabel 6300 4850 0    50   Input ~ 0
AC
Wire Wire Line
	6300 5250 6400 5250
Wire Wire Line
	6300 5350 6400 5350
Wire Wire Line
	6300 5450 6400 5450
Wire Wire Line
	7400 5350 7500 5350
Wire Wire Line
	7400 5450 7500 5450
Wire Wire Line
	6300 4550 6400 4550
Wire Wire Line
	6300 4650 6400 4650
Wire Wire Line
	6300 4750 6400 4750
$Comp
L Device:CP C7
U 1 1 62ABAE2B
P 9500 5650
F 0 "C7" H 9618 5696 50  0000 L CNN
F 1 "CP" H 9618 5605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 9538 5500 50  0001 C CNN
F 3 "~" H 9500 5650 50  0001 C CNN
	1    9500 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C8
U 1 1 62ABB75E
P 10300 5650
F 0 "C8" H 10418 5696 50  0000 L CNN
F 1 "CP" H 10418 5605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 10338 5500 50  0001 C CNN
F 3 "~" H 10300 5650 50  0001 C CNN
	1    10300 5650
	1    0    0    -1  
$EndComp
Text GLabel 9500 5400 1    50   Input ~ 0
3.3v
Text GLabel 10500 4550 1    50   Input ~ 0
3.3v
Text GLabel 10300 5400 1    50   Input ~ 0
5.0v
$Comp
L power:GND #PWR010
U 1 1 62ABD4B0
P 9500 5900
F 0 "#PWR010" H 9500 5650 50  0001 C CNN
F 1 "GND" H 9505 5727 50  0000 C CNN
F 2 "" H 9500 5900 50  0001 C CNN
F 3 "" H 9500 5900 50  0001 C CNN
	1    9500 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 62ABD818
P 10300 5900
F 0 "#PWR011" H 10300 5650 50  0001 C CNN
F 1 "GND" H 10305 5727 50  0000 C CNN
F 2 "" H 10300 5900 50  0001 C CNN
F 3 "" H 10300 5900 50  0001 C CNN
	1    10300 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 62ABDBBB
P 9300 4800
F 0 "#PWR012" H 9300 4550 50  0001 C CNN
F 1 "GND" H 9305 4627 50  0000 C CNN
F 2 "" H 9300 4800 50  0001 C CNN
F 3 "" H 9300 4800 50  0001 C CNN
	1    9300 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 4700 10500 4700
Wire Wire Line
	10300 5500 10300 5400
Wire Wire Line
	10300 5900 10300 5800
Wire Wire Line
	9500 5900 9500 5800
Wire Wire Line
	9500 5500 9500 5400
Wire Wire Line
	9300 4700 9400 4700
Wire Notes Line
	9100 6250 10650 6250
Wire Notes Line
	10650 6250 10650 4050
Wire Notes Line
	10650 4050 9100 4050
Wire Notes Line
	9100 4050 9100 6250
Wire Notes Line
	7950 6350 5800 6350
Wire Notes Line
	5800 6350 5800 3550
Wire Notes Line
	5800 3550 7950 3550
Wire Notes Line
	7950 3550 7950 6350
Text Notes 9200 4000 0    50   ~ 10
Power
Text Notes 5850 3500 0    50   ~ 10
Arduino Nano 33 IoT
NoConn ~ 6400 5050
NoConn ~ 6400 5150
NoConn ~ 6400 4350
NoConn ~ 6400 4450
NoConn ~ 6800 3950
NoConn ~ 7400 4450
NoConn ~ 7400 4350
NoConn ~ 7400 4750
NoConn ~ 7400 4950
NoConn ~ 7400 5050
NoConn ~ 7400 5150
NoConn ~ 7400 5250
NoConn ~ 7400 5550
NoConn ~ 7400 5650
$Comp
L Relay_SolidState:34.81-8240 U2
U 1 1 62AEF2F8
P 5300 2250
F 0 "U2" H 5300 1933 50  0000 C CNN
F 1 "G3MB-202p" H 5300 2024 50  0000 C CNN
F 2 "Relay_THT:OMEON_G3MB-202P" H 5100 2050 50  0001 L CIN
F 3 "https://gfinder.findernet.com/public/attachments/34/EN/S34USAEN.pdf" H 5300 2250 50  0001 L CNN
	1    5300 2250
	1    0    0    1   
$EndComp
Wire Wire Line
	4200 1700 4650 1700
Wire Wire Line
	4950 1300 4950 1500
Wire Wire Line
	4950 2150 5000 2150
Wire Wire Line
	5000 2350 4950 2350
Wire Wire Line
	4950 2350 4950 2700
Wire Wire Line
	5600 2350 6100 2350
Wire Wire Line
	6100 2350 6100 2250
Wire Wire Line
	5600 2150 5650 2150
Wire Wire Line
	5650 2150 5650 2100
Wire Wire Line
	5650 2100 5700 2100
Wire Wire Line
	6000 2100 6100 2100
Wire Wire Line
	6100 2100 6100 2150
Wire Wire Line
	6800 1700 7050 1700
Text GLabel 6800 1700 0    50   Input ~ 0
Heat
$Comp
L Device:R R6
U 1 1 62B72ADD
P 7200 1700
F 0 "R6" V 6993 1700 50  0000 C CNN
F 1 "R" V 7084 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7130 1700 50  0001 C CNN
F 3 "~" H 7200 1700 50  0001 C CNN
	1    7200 1700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 62B72AE3
P 8100 1300
F 0 "#PWR09" H 8100 1050 50  0001 C CNN
F 1 "GND" H 8105 1127 50  0000 C CNN
F 2 "" H 8100 1300 50  0001 C CNN
F 3 "" H 8100 1300 50  0001 C CNN
	1    8100 1300
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Female J6
U 1 1 62B72AE9
P 9450 2150
F 0 "J6" H 9478 2126 50  0000 L CNN
F 1 "Conn_01x02_Female" H 9478 2035 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 9450 2150 50  0001 C CNN
F 3 "~" H 9450 2150 50  0001 C CNN
	1    9450 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 62B72AEF
P 9000 2100
F 0 "C6" V 9252 2100 50  0000 C CNN
F 1 "C" V 9161 2100 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 9038 1950 50  0001 C CNN
F 3 "~" H 9000 2100 50  0001 C CNN
	1    9000 2100
	0    -1   -1   0   
$EndComp
Text GLabel 7300 2700 0    50   Input ~ 0
5.0v
$Comp
L dk_Transistors-Bipolar-BJT-Single:PN2222A Q1
U 1 1 62B72B0B
P 4850 1700
F 0 "Q1" H 5038 1647 60  0000 L CNN
F 1 "PN2222A" H 5038 1753 60  0000 L CNN
F 2 "digikey-footprints:TO-92-3" H 5050 1900 60  0001 L CNN
F 3 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=PN2221-2222A.PDF" H 5050 2000 60  0001 L CNN
F 4 "PN2222ACS-ND" H 5050 2100 60  0001 L CNN "Digi-Key_PN"
F 5 "PN2222A" H 5050 2200 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 5050 2300 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 5050 2400 60  0001 L CNN "Family"
F 8 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=PN2221-2222A.PDF" H 5050 2500 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/central-semiconductor-corp/PN2222A/PN2222ACS-ND/4806937" H 5050 2600 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.8A TO-92" H 5050 2700 60  0001 L CNN "Description"
F 11 "Central Semiconductor Corp" H 5050 2800 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5050 2900 60  0001 L CNN "Status"
	1    4850 1700
	1    0    0    1   
$EndComp
$Comp
L Relay_SolidState:34.81-8240 U3
U 1 1 62B72B11
P 8450 2250
F 0 "U3" H 8450 1933 50  0000 C CNN
F 1 "G3MB-202p" H 8450 2024 50  0000 C CNN
F 2 "Relay_THT:OMEON_G3MB-202P" H 8250 2050 50  0001 L CIN
F 3 "https://gfinder.findernet.com/public/attachments/34/EN/S34USAEN.pdf" H 8450 2250 50  0001 L CNN
	1    8450 2250
	1    0    0    1   
$EndComp
Wire Wire Line
	7350 1700 7800 1700
Wire Wire Line
	8100 1300 8100 1500
Wire Wire Line
	8100 2150 8150 2150
Wire Wire Line
	8150 2350 8100 2350
Wire Wire Line
	8100 2350 8100 2700
Wire Wire Line
	8750 2350 9250 2350
Wire Wire Line
	9250 2350 9250 2250
Wire Wire Line
	8750 2150 8800 2150
Wire Wire Line
	8800 2150 8800 2100
Wire Wire Line
	8800 2100 8850 2100
Wire Wire Line
	9150 2100 9250 2100
Wire Wire Line
	9250 2100 9250 2150
Wire Wire Line
	1650 5250 1850 5250
Wire Wire Line
	1850 5250 2250 5250
Connection ~ 1850 5250
Wire Wire Line
	1850 4950 2250 4950
Wire Wire Line
	2250 4950 2250 4850
Connection ~ 2250 4950
Wire Wire Line
	2250 4650 2250 4550
Wire Wire Line
	2250 4550 1850 4550
Connection ~ 2250 4550
Wire Wire Line
	1650 4250 1850 4250
Wire Wire Line
	1850 4250 2250 4250
Connection ~ 1850 4250
$Comp
L power:PWR_FLAG #FLG03
U 1 1 62BCAC82
P 7100 3900
F 0 "#FLG03" H 7100 3975 50  0001 C CNN
F 1 "PWR_FLAG" V 7100 4028 50  0000 L CNN
F 2 "" H 7100 3900 50  0001 C CNN
F 3 "~" H 7100 3900 50  0001 C CNN
	1    7100 3900
	0    1    1    0   
$EndComp
Connection ~ 7100 3900
Wire Wire Line
	7100 3900 7100 3950
$Comp
L power:PWR_FLAG #FLG01
U 1 1 62BCBFBC
P 7000 3900
F 0 "#FLG01" H 7000 3975 50  0001 C CNN
F 1 "PWR_FLAG" V 7000 4027 50  0000 L CNN
F 2 "" H 7000 3900 50  0001 C CNN
F 3 "~" H 7000 3900 50  0001 C CNN
	1    7000 3900
	0    -1   -1   0   
$EndComp
Connection ~ 7000 3900
Wire Wire Line
	7000 3900 7000 3850
$Comp
L power:PWR_FLAG #FLG02
U 1 1 62BCC5B5
P 7000 5950
F 0 "#FLG02" H 7000 6025 50  0001 C CNN
F 1 "PWR_FLAG" V 7000 6078 50  0000 L CNN
F 2 "" H 7000 5950 50  0001 C CNN
F 3 "~" H 7000 5950 50  0001 C CNN
	1    7000 5950
	0    1    1    0   
$EndComp
Connection ~ 7000 5950
$Comp
L Switch:SW_DIP_x01 SW1
U 1 1 62BCE8AC
P 1150 6100
F 0 "SW1" V 1104 6230 50  0000 L CNN
F 1 "SW_DPST" V 1195 6230 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 1150 6100 50  0001 C CNN
F 3 "~" H 1150 6100 50  0001 C CNN
	1    1150 6100
	0    1    1    0   
$EndComp
Wire Wire Line
	1150 5800 1150 5700
Wire Wire Line
	1250 2100 1450 2100
Wire Wire Line
	1150 6450 1150 6400
Connection ~ 1150 6450
Wire Wire Line
	2900 6450 2900 6400
Connection ~ 2900 6450
Wire Wire Line
	2900 5800 2900 5700
$Comp
L dk_Transistors-Bipolar-BJT-Single:PN2222A Q2
U 1 1 62B29A55
P 8000 1700
F 0 "Q2" H 8188 1647 60  0000 L CNN
F 1 "PN2222A" H 8188 1753 60  0000 L CNN
F 2 "digikey-footprints:TO-92-3" H 8200 1900 60  0001 L CNN
F 3 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=PN2221-2222A.PDF" H 8200 2000 60  0001 L CNN
F 4 "PN2222ACS-ND" H 8200 2100 60  0001 L CNN "Digi-Key_PN"
F 5 "PN2222A" H 8200 2200 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8200 2300 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8200 2400 60  0001 L CNN "Family"
F 8 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=PN2221-2222A.PDF" H 8200 2500 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/central-semiconductor-corp/PN2222A/PN2222ACS-ND/4806937" H 8200 2600 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.8A TO-92" H 8200 2700 60  0001 L CNN "Description"
F 11 "Central Semiconductor Corp" H 8200 2800 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8200 2900 60  0001 L CNN "Status"
	1    8000 1700
	1    0    0    1   
$EndComp
Wire Wire Line
	4950 1900 4950 2150
Wire Wire Line
	4150 2700 4950 2700
Wire Wire Line
	8100 1900 8100 2150
Wire Wire Line
	7300 2700 8100 2700
NoConn ~ 6400 5550
NoConn ~ 6400 5650
Wire Wire Line
	6300 4850 6400 4850
Wire Wire Line
	6300 4950 6400 4950
Wire Wire Line
	10500 4700 10500 4550
Wire Wire Line
	9300 4800 9300 4700
NoConn ~ 6300 7100
NoConn ~ 5700 7100
Wire Wire Line
	1250 2300 1450 2300
$EndSCHEMATC
