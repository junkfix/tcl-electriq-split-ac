# electriq-split-ac

TCL Air Conditioner

iQool-3MS9K9K9K

iQool-3MS9K9K9KB

iQool-2MS9K9K

iQool-2MS9K9KB

iQool-2MS12K12K

iQool-2MS12K12KB

Converted from Tuya Smartlife app to generic esp8266 arduino TYWE1S on a TYJW2 v2.0.0 ESP8266EX 2MB, no soldering required.

Serial 9600, SERIAL_8E1, 5V logic
```
TX
BB000104020100BD request status
BB00010319010024080F000000000000000000000000000000000000000082  on
BB00010319010020080F000000000000000000000000000000000000000086  off
```
| TX | Data | Description
| --- | -- | ------- 
|[ 0] | BB | 
|[ 1] | 00 | version
|[ 2] | 01 | version
|[ 3] | 03 | cmd or 04 heartbeat
|[ 4] | 19 | data length from here
|[ 5] | 01 | 
|[ 6] | 00 | 
|[ 7] | 60 | [eco,display,beep,ontimerenable?, offtimerenable?,power,0,0]
|[ 8] | 03 | [mute,0,turbo,health, mode(4)]  mode 01 heat, 02 dry, 03 cool, 07 fan,  08 auto,  health(+16),    41=turbo-heat   43=turbo-cool (turbo = 0x40+ 0x01..0x08)
|[ 9] | 06 | 0,0,0,0, temp(4)   settemp 31 - x
|[10] | 02 | [0,timerindicator?,swingv(3),fan(3)]		fan+swing modes 
|[11] | 00 | [0,offtimer?(6),0]
|[12] | 00 | [fahrenheit,ontimer?(6),0]	cf 80=f 0=c
|[13] | 00 | 
|[14] | 00 | [0,0,halfdegree?,0, swingh,0,0,0]
|[15] | 00 | 
|[16] | 00 | 
|[17] | 00 | 
|[18] | 00 | 
|[19] | 00 | sleep on = 1  off=0
|[20] | 00 | 
|[21] | 00 | 
|[22] | 00 | 
|[23] | 00 | 
|[24] | 00 | 
|[25] | 00 | 
|[26] | 00 | 
|[27] | 00 | 
|[28] | 00 | 
|[29] | 00 | 
|[30] | 00 | checksum


```
RX
	command		pwr	settemp	health	swing			curtemp					mute	
BB0100	03	370400	32	9A	00	40	000000000000	6903	080000000000000000000069FF4000	00	38367700008000000000000000004440004000001A0000000071
```

| RX | Data | Description
| --- | -- | ------- 
|[ 0] | BB | 
|[ 1] | 01 | version
|[ 2] | 00 | version
|[ 3] | 03 | cmd, 04 heartbeat
|[ 4] | 37 | data length from here
|[ 5] | 04 | 
|[ 6] | 00 | 
|[ 7] | 32 | [turbo, eco, display, power, mode(4) ]
|[ 8] | 9A | [fanspeed(4), settemp(4)] fan modes (0x80=auto 0x90=low 0xA0=med 0xB0=high) +    byte set_temp=(value & 0x0F) + 16 ;
|[ 9] | 00 | [0,timeractive,0,0, 0,health,0,0] 40=timer active + 04 = health
|[10] | 40 | [0,swingV,0,0, 0,0,swingH,0] swing on v =40, swing on h=20
|[11] | 00 | timer hour
|[12] | 00 | timer mins
|[13] | 00 | 
|[14] | 00 | 
|[15] | 00 | 
|[16] | 00 | 
|[17] | 69 | curr temp
|[18] | 2b | curr temp
|[19] | 88 | 88 sleep off, 89 sleep on, 08(compressor off/deepsleep?),88(compressor on/waiting?)
|[20] | 00 | 
|[21] | 00 | 
|[22] | 00 | 
|[23] | 00 | 
|[24] | 00 | 
|[25] | 00 | 
|[26] | 00 | 
|[27] | 00 | 
|[28] | 00 | 
|[29] | 00 | 
|[30] | 00 | temp or humidity
|[31] | FF | 
|[32] | 40 | 
|[33] | 80 | mute on, 0=off
|[34] | 00 | internal fan speed 
|[35] | 00 | temp pipe out  -32
|[36] | 00 | temp pipe in   -32
|[37] | 00 | compressor?
|[38] | 00 | compressor?
|[39] | 00 | compressor fan?
|[40] | 80 | 0x80 -> 8A cool mode,  0xC0  -> 0xCA heat mode  C0/80 idle
|[41] | 00 | 
|[42] | 00 | 
|[43] | 00 | 
|[44] | 00 | fault
|[45] | 00 | 
|[46] | 00 | outside motor?
|[47] | 00 | 
|[48] | 00 | 
|[49] | 44 | 
|[50] | 40 | [0,0,0,0, 0,0,cleanfilter,0]
|[51] | 00 | swing v pos?
|[52] | 00 | swing h pos?
|[53] | 00 | 
|[54] | 00 | 
|[55] | 1A | 
|[56] | 00 | 
|[57] | 00 | 
|[58] | 00 | 
|[59] | 00 | 
|[60] | 00 | checksum
