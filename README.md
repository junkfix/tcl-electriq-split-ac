# electriq-split-ac

TCL Air Conditioner
iQool-3MS9K9K9K
iQool-3MS9K9K9KB
iQool-2MS9K9K
iQool-2MS9K9KB
iQool-2MS12K12K
iQool-2MS12K12KB

Converted from Tuya Smartlife app to generic esp8266 arduino
Serial 9600, SERIAL_8E1
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
|[ 7] | 60 | eco, display, power (32+ power on = +4, display on = +64, eco on = +128  		0x60 = power off 	0xE4= power on eco on  0x64=power on  eco off 
|[ 8] | 03 | mode 01 heat, 02 dry, 03 cool, 07 fan,  08 auto,    41=turbo-heat   43=turbo-cool (turbo = 0x40+ 0x01..0x08)
|[ 9] | 06 | settemp 31 - x
|[10] | 02 | fan+swing modes 
|[11] | 00 | 
|[12] | 00 | cf 80=f 0=c
|[13] | 00 | 
|[14] | 00 | 
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
|[ 7] | 32 | turbo, eco, display, power
|[ 8] | 9A | fan modes (0x80=auto 0x90=low 0xA0=med 0xB0=high) +    byte set_temp=(value & 0x0F) + 16 ;
|[ 9] | 00 | 40=timer active + 04 = health
|[10] | 40 | swing on v =40, swing on h=20
|[11] | 00 | timer hour
|[12] | 00 | timer mins
|[13] | 00 | 
|[14] | 00 | 
|[15] | 00 | 
|[16] | 00 | 
|[17] | 69 | curr temp
|[18] | 2b | curr temp
|[19] | 88 | 
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
|[35] | 00 | compressor?
|[36] | 00 | compressor?
|[37] | 00 | compressor?
|[38] | 00 | compressor?
|[39] | 00 | compressor?
|[40] | 00 | compressor?
|[41] | 00 | 
|[42] | 00 | 
|[43] | 00 | 
|[44] | 00 | 
|[45] | 00 | 
|[46] | 00 | compressor?
|[47] | 00 | 
|[48] | 00 | 
|[49] | 44 | 
|[50] | 40 | 
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
