EESchema Schematic File Version 4
LIBS:design-cache
EELAYER 29 0
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
L design-rescue:HUZZAH32-my_custom_library U1
U 1 1 5D523388
P 7700 2650
F 0 "U1" H 7650 1261 50  0000 C CNN
F 1 "HUZZAH32" H 7650 1170 50  0000 C CNN
F 2 "MCU_Adafruit:Adafruit_HUZZAH_ESP32_3405" H 7150 4150 50  0001 C CNN
F 3 "https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/downloads" H 7150 4150 50  0001 C CNN
	1    7700 2650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5D529A5A
P 2650 1200
F 0 "J1" H 2758 1481 50  0000 C CNN
F 1 "Conn_USB_PWR" H 2758 1390 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 2650 1200 50  0001 C CNN
F 3 "~" H 2650 1200 50  0001 C CNN
	1    2650 1200
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5D52A236
P 2650 1850
F 0 "J2" H 2622 1732 50  0000 R CNN
F 1 "Conn_USB_HEATER" H 2622 1823 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 2650 1850 50  0001 C CNN
F 3 "~" H 2650 1850 50  0001 C CNN
	1    2650 1850
	-1   0    0    1   
$EndComp
NoConn ~ 2450 1200
NoConn ~ 2450 1100
$Comp
L power:GND #PWR03
U 1 1 5D5325D5
P 2450 1000
F 0 "#PWR03" H 2450 750 50  0001 C CNN
F 1 "GND" V 2455 872 50  0000 R CNN
F 2 "" H 2450 1000 50  0001 C CNN
F 3 "" H 2450 1000 50  0001 C CNN
	1    2450 1000
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5D532ABD
P 2450 1950
F 0 "#PWR05" H 2450 1800 50  0001 C CNN
F 1 "+5V" V 2465 2078 50  0000 L CNN
F 2 "" H 2450 1950 50  0001 C CNN
F 3 "" H 2450 1950 50  0001 C CNN
	1    2450 1950
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5D532F74
P 2450 1300
F 0 "#PWR02" H 2450 1150 50  0001 C CNN
F 1 "+5V" V 2465 1428 50  0000 L CNN
F 2 "" H 2450 1300 50  0001 C CNN
F 3 "" H 2450 1300 50  0001 C CNN
	1    2450 1300
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_NJFET_GDS Q1
U 1 1 5D536557
P 1800 2100
F 0 "Q1" H 1991 2146 50  0000 L CNN
F 1 "Q_NJFET_GDS" H 1991 2055 50  0000 L CNN
F 2 "" H 2000 2200 50  0001 C CNN
F 3 "~" H 1800 2100 50  0001 C CNN
	1    1800 2100
	1    0    0    -1  
$EndComp
NoConn ~ 2450 1750
NoConn ~ 2450 1850
Wire Wire Line
	1900 1900 1900 1650
Wire Wire Line
	1900 1650 2450 1650
$Comp
L power:GND #PWR04
U 1 1 5D541F6A
P 1900 2300
F 0 "#PWR04" H 1900 2050 50  0001 C CNN
F 1 "GND" H 1905 2127 50  0000 C CNN
F 2 "" H 1900 2300 50  0001 C CNN
F 3 "" H 1900 2300 50  0001 C CNN
	1    1900 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D5426A8
P 1450 2100
F 0 "R1" V 1243 2100 50  0000 C CNN
F 1 "100R" V 1334 2100 50  0000 C CNN
F 2 "" V 1380 2100 50  0001 C CNN
F 3 "~" H 1450 2100 50  0001 C CNN
	1    1450 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5D542CE8
P 1300 2100
F 0 "#PWR01" H 1300 1850 50  0001 C CNN
F 1 "GND" V 1305 1972 50  0000 R CNN
F 2 "" H 1300 2100 50  0001 C CNN
F 3 "" H 1300 2100 50  0001 C CNN
	1    1300 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	1600 2100 1600 2750
Connection ~ 1600 2100
Text Label 1600 2750 0    50   ~ 0
HeatGate
$Comp
L Connector:Conn_01x03_Female J3
U 1 1 5D54B88B
P 2800 3250
F 0 "J3" H 2828 3276 50  0000 L CNN
F 1 "Conn_Temp_Probe" H 2828 3185 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 2800 3250 50  0001 C CNN
F 3 "~" H 2800 3250 50  0001 C CNN
	1    2800 3250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR06
U 1 1 5D54C8B8
P 2250 3250
F 0 "#PWR06" H 2250 3100 50  0001 C CNN
F 1 "+3V3" V 2265 3378 50  0000 L CNN
F 2 "" H 2250 3250 50  0001 C CNN
F 3 "" H 2250 3250 50  0001 C CNN
	1    2250 3250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5D54E7BD
P 2600 3150
F 0 "#PWR07" H 2600 2900 50  0001 C CNN
F 1 "GND" V 2605 3022 50  0000 R CNN
F 2 "" H 2600 3150 50  0001 C CNN
F 3 "" H 2600 3150 50  0001 C CNN
	1    2600 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 3250 2600 3250
$Comp
L design-rescue:SparkFun_9Dof_Sensor_Stick-my_custom_library U2
U 1 1 5D55D4E0
P 5150 2150
F 0 "U2" H 5428 2246 50  0000 L CNN
F 1 "SparkFun_9Dof_Sensor_Stick" H 5428 2155 50  0000 L CNN
F 2 "Custom_Modules:SparkFun_9DoF_Sensor_Stick" H 4850 2550 50  0001 C CNN
F 3 "" H 4850 2550 50  0001 C CNN
	1    5150 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3650 2600 3900
$Comp
L Device:R R2
U 1 1 5D55312E
P 2600 3500
F 0 "R2" V 2393 3500 50  0000 C CNN
F 1 "4K7" V 2484 3500 50  0000 C CNN
F 2 "" V 2530 3500 50  0001 C CNN
F 3 "~" H 2600 3500 50  0001 C CNN
	1    2600 3500
	1    0    0    -1  
$EndComp
Connection ~ 2600 3650
Wire Wire Line
	2250 3650 2600 3650
Connection ~ 2250 3250
Wire Wire Line
	2250 3250 2250 3650
Text Label 2600 3900 0    50   ~ 0
TemperatureSensor
$Comp
L power:+3V3 #PWR0101
U 1 1 5D563AE9
P 5150 1700
F 0 "#PWR0101" H 5150 1550 50  0001 C CNN
F 1 "+3V3" H 5165 1873 50  0000 C CNN
F 2 "" H 5150 1700 50  0001 C CNN
F 3 "" H 5150 1700 50  0001 C CNN
	1    5150 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D5641C9
P 5150 2500
F 0 "#PWR0102" H 5150 2250 50  0001 C CNN
F 1 "GND" H 5155 2327 50  0000 C CNN
F 2 "" H 5150 2500 50  0001 C CNN
F 3 "" H 5150 2500 50  0001 C CNN
	1    5150 2500
	1    0    0    -1  
$EndComp
Text Label 4800 2050 2    50   ~ 0
i2cBus
Text Label 7000 3400 2    50   ~ 0
i2cBus
Text Label 4800 2150 2    50   ~ 0
i2cClock
Text Label 7000 3300 2    50   ~ 0
i2cClock
Text Notes 5300 2600 0    50   ~ 0
NOTE: Contains internal\n4k7 pullup resistor
$Comp
L Connector:Conn_01x05_Female J4
U 1 1 5D568BF1
P 4900 3450
F 0 "J4" H 4928 3476 50  0000 L CNN
F 1 "Conn_LED" H 4928 3385 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 4900 3450 50  0001 C CNN
F 3 "~" H 4900 3450 50  0001 C CNN
	1    4900 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5D569E77
P 4700 3250
F 0 "#PWR0103" H 4700 3100 50  0001 C CNN
F 1 "+5V" V 4715 3378 50  0000 L CNN
F 2 "" H 4700 3250 50  0001 C CNN
F 3 "" H 4700 3250 50  0001 C CNN
	1    4700 3250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5D56A9E5
P 4700 3350
F 0 "#PWR0104" H 4700 3100 50  0001 C CNN
F 1 "GND" V 4705 3222 50  0000 R CNN
F 2 "" H 4700 3350 50  0001 C CNN
F 3 "" H 4700 3350 50  0001 C CNN
	1    4700 3350
	0    1    1    0   
$EndComp
Text Label 4700 3450 2    50   ~ 0
MOSI_Bus
Text Label 4700 3650 2    50   ~ 0
SCK_Bus
Text Label 7000 3700 2    50   ~ 0
MOSI_Bus
Text Label 7000 3600 2    50   ~ 0
SCK_Bus
Text Label 4700 3550 2    50   ~ 0
LED_CS
$Comp
L Connector:Conn_01x03_Female J5
U 1 1 5D5372C8
P 5750 4800
F 0 "J5" H 5778 4826 50  0000 L CNN
F 1 "Conn_Shutter" H 5778 4735 50  0000 L CNN
F 2 "" H 5750 4800 50  0001 C CNN
F 3 "~" H 5750 4800 50  0001 C CNN
	1    5750 4800
	1    0    0    -1  
$EndComp
$Comp
L Isolator:ILD74 U3
U 1 1 5D53AFDD
P 3650 4600
F 0 "U3" H 3650 4925 50  0000 C CNN
F 1 "ILD74" H 3650 4834 50  0000 C CNN
F 2 "" H 3450 4400 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83640/ild74.pdf" H 3650 4600 50  0001 L CNN
	1    3650 4600
	1    0    0    -1  
$EndComp
$Comp
L Isolator:ILD74 U3
U 2 1 5D53FAAC
P 3650 5200
F 0 "U3" H 3650 5525 50  0000 C CNN
F 1 "ILD74" H 3650 5434 50  0000 C CNN
F 2 "" H 3450 5000 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83640/ild74.pdf" H 3650 5200 50  0001 L CNN
	2    3650 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D541297
P 3200 4500
F 0 "R3" V 2993 4500 50  0000 C CNN
F 1 "R" V 3084 4500 50  0000 C CNN
F 2 "" V 3130 4500 50  0001 C CNN
F 3 "~" H 3200 4500 50  0001 C CNN
	1    3200 4500
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5D541B6C
P 3200 5100
F 0 "R4" V 2993 5100 50  0000 C CNN
F 1 "R" V 3084 5100 50  0000 C CNN
F 2 "" V 3130 5100 50  0001 C CNN
F 3 "~" H 3200 5100 50  0001 C CNN
	1    3200 5100
	0    1    1    0   
$EndComp
Text Label 3050 4500 2    50   ~ 0
FocusSignal
Text Label 3050 5100 2    50   ~ 0
ShutterSignal
$Comp
L power:GND #PWR08
U 1 1 5D542D11
P 3350 4700
F 0 "#PWR08" H 3350 4450 50  0001 C CNN
F 1 "GND" V 3355 4572 50  0000 R CNN
F 2 "" H 3350 4700 50  0001 C CNN
F 3 "" H 3350 4700 50  0001 C CNN
	1    3350 4700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5D5433E6
P 3350 5300
F 0 "#PWR09" H 3350 5050 50  0001 C CNN
F 1 "GND" V 3355 5172 50  0000 R CNN
F 2 "" H 3350 5300 50  0001 C CNN
F 3 "" H 3350 5300 50  0001 C CNN
	1    3350 5300
	0    1    1    0   
$EndComp
Text Label 5550 4700 2    50   ~ 0
CameraGND
Text Label 3950 4700 0    50   ~ 0
CameraGND
Text Label 3950 5300 0    50   ~ 0
CameraGND
Text Label 5550 4800 2    50   ~ 0
CameraFocus
Text Label 3950 4500 0    50   ~ 0
CameraFocus
Text Label 5550 4900 2    50   ~ 0
CameraShutter
Text Label 3950 5100 0    50   ~ 0
CameraShutter
Text Notes 2650 5800 0    50   ~ 0
Note:\n1. Assume dual channel DIP8 Optocoupler\n2. Optocoupler yet to be chosen\n3. Resistor choice depends on max current of\n   optocoupler IR LED.
NoConn ~ 7000 1400
$EndSCHEMATC
