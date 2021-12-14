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
L My_Arduino:ESP-01 U1
U 1 1 61A66C7B
P 4650 3550
F 0 "U1" H 5425 3775 50  0000 C CNN
F 1 "ESP-01" H 5425 3684 50  0000 C CNN
F 2 "My_Arduino:ESP-01_large" H 5350 3400 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 5350 3400 50  0001 C CNN
	1    4650 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 61A67CA8
P 4750 2300
F 0 "BT1" H 4868 2396 50  0000 L CNN
F 1 "3.6V" H 4868 2305 50  0000 L CNN
F 2 "My_Headers:2-pin_power_input_header_larger_pads" V 4750 2360 50  0001 C CNN
F 3 "~" V 4750 2360 50  0001 C CNN
	1    4750 2300
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U2
U 1 1 61A79A2B
P 6050 1900
F 0 "U2" H 6050 2142 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 6050 2051 50  0000 C CNN
F 2 "My_Misc:TO-220F-3_Horizontal_TabDown_large" H 6050 2100 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 6150 1650 50  0001 C CNN
	1    6050 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61A7A731
P 5550 2250
F 0 "C1" H 5665 2296 50  0000 L CNN
F 1 "100n" H 5665 2205 50  0000 L CNN
F 2 "My_Misc:C_Disc_D3.0mm_W1.6mm_P2.50mm_larg" H 5588 2100 50  0001 C CNN
F 3 "~" H 5550 2250 50  0001 C CNN
	1    5550 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 61A7AF7D
P 6550 2250
F 0 "C2" H 6668 2296 50  0000 L CNN
F 1 "10u" H 6668 2205 50  0000 L CNN
F 2 "My_Misc:CP_Radial_D5.0mm_P2.50mm_larger_pads" H 6588 2100 50  0001 C CNN
F 3 "~" H 6550 2250 50  0001 C CNN
	1    6550 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2100 5550 1900
Wire Wire Line
	5550 1900 5750 1900
Wire Wire Line
	6350 1900 6550 1900
Wire Wire Line
	6550 1900 6550 2100
Wire Wire Line
	5550 2400 5550 2500
Wire Wire Line
	5550 2500 6050 2500
Wire Wire Line
	6550 2500 6550 2400
Wire Wire Line
	6050 2200 6050 2500
Connection ~ 6050 2500
Wire Wire Line
	6050 2500 6550 2500
Wire Wire Line
	4750 2100 4750 1900
Wire Wire Line
	4750 1900 5550 1900
Connection ~ 5550 1900
Wire Wire Line
	4750 2400 4750 2500
Wire Wire Line
	4750 2500 5550 2500
Connection ~ 5550 2500
$Comp
L power:GND #PWR0101
U 1 1 61A80383
P 4750 2600
F 0 "#PWR0101" H 4750 2350 50  0001 C CNN
F 1 "GND" H 4755 2427 50  0000 C CNN
F 2 "" H 4750 2600 50  0001 C CNN
F 3 "" H 4750 2600 50  0001 C CNN
	1    4750 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 61A80804
P 6750 1700
F 0 "#PWR0102" H 6750 1550 50  0001 C CNN
F 1 "+3.3V" H 6765 1873 50  0000 C CNN
F 2 "" H 6750 1700 50  0001 C CNN
F 3 "" H 6750 1700 50  0001 C CNN
	1    6750 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1900 6750 1900
Wire Wire Line
	6750 1900 6750 1700
Connection ~ 6550 1900
Wire Wire Line
	4750 2500 4750 2600
Connection ~ 4750 2500
$Comp
L power:+3.3V #PWR0103
U 1 1 61A8757B
P 7950 2450
F 0 "#PWR0103" H 7950 2300 50  0001 C CNN
F 1 "+3.3V" H 7965 2623 50  0000 C CNN
F 2 "" H 7950 2450 50  0001 C CNN
F 3 "" H 7950 2450 50  0001 C CNN
	1    7950 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 61A87802
P 7950 3550
F 0 "#PWR0104" H 7950 3300 50  0001 C CNN
F 1 "GND" H 7955 3377 50  0000 C CNN
F 2 "" H 7950 3550 50  0001 C CNN
F 3 "" H 7950 3550 50  0001 C CNN
	1    7950 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 61A88CA5
P 8450 2800
F 0 "R1" H 8520 2846 50  0000 L CNN
F 1 "4.7k" H 8520 2755 50  0000 L CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 8380 2800 50  0001 C CNN
F 3 "~" H 8450 2800 50  0001 C CNN
	1    8450 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2850 7950 2550
Wire Wire Line
	8450 2650 8450 2550
Wire Wire Line
	8450 2550 7950 2550
Connection ~ 7950 2550
Wire Wire Line
	7950 2550 7950 2450
Wire Wire Line
	8250 3150 8450 3150
Wire Wire Line
	8450 3150 8450 2950
Wire Wire Line
	7950 3550 7950 3450
$Comp
L power:GND #PWR0105
U 1 1 61A926AA
P 3950 4050
F 0 "#PWR0105" H 3950 3800 50  0001 C CNN
F 1 "GND" H 3955 3877 50  0000 C CNN
F 2 "" H 3950 4050 50  0001 C CNN
F 3 "" H 3950 4050 50  0001 C CNN
	1    3950 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0106
U 1 1 61A92963
P 6850 3350
F 0 "#PWR0106" H 6850 3200 50  0001 C CNN
F 1 "+3.3V" H 6865 3523 50  0000 C CNN
F 2 "" H 6850 3350 50  0001 C CNN
F 3 "" H 6850 3350 50  0001 C CNN
	1    6850 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3550 3950 4050
Wire Wire Line
	6200 3850 6850 3850
Wire Wire Line
	6850 3350 6850 3650
Wire Wire Line
	6200 3650 6850 3650
Connection ~ 6850 3650
Wire Wire Line
	6850 3650 6850 3850
Text GLabel 8650 3150 2    50   Input ~ 0
GPIO2
Text GLabel 4450 3650 0    50   Input ~ 0
GPIO2
Wire Wire Line
	8650 3150 8450 3150
Connection ~ 8450 3150
$Comp
L My_Parts:DHT22,CM2303 U3
U 1 1 61B915F0
P 7950 3150
F 0 "U3" H 7707 3196 50  0000 R CNN
F 1 "DHT22,CM2303" H 7707 3105 50  0000 R CNN
F 2 "My_Misc:DHT22,RHT03,CM2303_large" H 7950 2750 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 8100 3400 50  0001 C CNN
	1    7950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3550 4650 3550
Wire Wire Line
	4650 3650 4450 3650
$EndSCHEMATC
