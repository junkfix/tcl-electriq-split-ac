//For electriq split ac TYWE1S on a TYJW2 v2.0.0 ESP8266 2MB

//will need to add wifi and mqtt codes.

uint8_t ac_state[11]={0};
uint8_t ac_mqtt[11]={0};

byte pendingCommand=0;

#define AC_ECO		0
#define AC_DISPLAY	1
#define AC_POWER	2
#define AC_TURBO	3
#define AC_MODE		4
#define AC_STMP		5
#define AC_FAN		6
#define AC_SWING	7
#define AC_SLEEP	8
#define AC_HEALTH	9
#define AC_MUTE		10

float currTemp = 0;

uint8_t rx_pos = 0;
uint8_t rx_line [70];

unsigned long minidelay = 0;
unsigned long hbeat = 0;
byte hasStatus=0;
byte lastCommandType=0;

void setup() {
	Serial.begin(9600,SERIAL_8E1);
	Serial.swap();
	//GPIO15 (TX) and GPIO13 (RX)
}

void loop() {
	byte i = 0;
	
	while( Serial.available () > 0){
		if (rx_pos < 69){rx_line [rx_pos++] = Serial.read();}else{rx_pos = 0;}
		minidelay = millis();
	}
	

	if(millis() - minidelay > 100 ){
		minidelay = millis();
		byte pos=0;
		byte checksum = 0;
		if (rx_pos>1){
			pos=rx_pos - 1 ;
			for ( i = 0; i < pos ; i++) {
				checksum ^= rx_line[i];
			}
			if (rx_line[0] ==  0xBB && pos>9 && checksum == rx_line[pos] ) {
				if(pos == 60 ){
					lastCommandType=rx_line[3]; //3 for command, 4 for heartbeat status
					hasStatus=1;
					ac_state[AC_TURBO]=rx_line[7] >> 7 & 1;
					ac_state[AC_ECO]=rx_line[7] >> 6 & 1;
					ac_state[AC_DISPLAY]=rx_line[7] >> 5 & 1;
					ac_state[AC_POWER]=rx_line[7] >> 4 & 1;
					
					//0=cool 1=fan  2=dry 3=heat 4=auto 
					ac_state[AC_MODE]=(rx_line[7] & 0x0F) - 1;
					if(ac_state[AC_MODE]>4){ac_state[AC_MODE]=4;}
					
					//0=auto 1=low 2=med 3=high
					ac_state[AC_FAN]=(rx_line[8] >> 4) - 8; 					
					ac_state[AC_STMP]=( rx_line[8] & 0x0F ) + 16;
					ac_state[AC_HEALTH]=rx_line[9] >> 2 & 1;
					ac_state[AC_SWING]=rx_line[10] >> 6 & 1;
					ac_state[AC_SLEEP]=rx_line[19] & 1;
					
					currTemp = (( (rx_line[17] << 8) | rx_line[18] ) / 374 - 32)/1.8;
					
					ac_state[AC_MUTE]=rx_line[33] >> 7 & 1;
					//ac_state[AC_TIMERON]=rx_line[9] >> 6 & 1;
					//ac_state[AC_TIMERHH]=rx_line[11];
					//ac_state[AC_TIMERMM]=rx_line[12];
					//ac_state[AC_INT_FAN_RPM]=rx_line[34]; //65-100, 0 when off
				}				
			}
			
			checksum = 0;

			rx_pos = 0;
		}

		if(hasStatus && pendingCommand){
			pendingCommand = 0;hasStatus = 0;
			byte AcCmd[] = {0};
			AcCmd[0] = 0xBB; AcCmd[2] = 0x1; AcCmd[3] = 0x3; AcCmd[4] = 0x19; AcCmd[5] = 0x1;
			const byte modeMap[] = {3,7,2,1,8};
			const byte fanMap[] = {0,2,3,5,0};

			AcCmd[7] = 32;
			
			if(ac_mqtt[AC_POWER]){AcCmd[7] += 4;}
			
			if(ac_mqtt[AC_DISPLAY]){AcCmd[7] +=  64;}
			
			if(ac_mqtt[AC_ECO]){AcCmd[7] += 128;}
			
			// 0=cool 1=fan  2=dry 3=heat 4=auto
			AcCmd[8] = modeMap[ ac_mqtt[AC_MODE] ];
			
			if(ac_mqtt[AC_HEALTH] && ac_mqtt[AC_POWER]){AcCmd[8] += 16;}
			
			if(ac_mqtt[AC_TURBO]){AcCmd[8] += 64;}
			
			//16-30
			AcCmd[9] = 31 - ac_mqtt[AC_STMP];
			
			//0=auto 1=low 2=med 3=high
			AcCmd[10] = fanMap[ ac_mqtt[AC_FAN] ];
			
			if(ac_mqtt[AC_SWING]){AcCmd[10] += 56;}
			
			AcCmd[19] = (ac_mqtt[AC_SLEEP])? 1 : 0;
			
			checksum = 0;
			for ( i = 0; i < 30 ; i++) {
				checksum ^= AcCmd[i];
			}

			AcCmd[30] = checksum;
			
			Serial.write(AcCmd, 31);
			hbeat = millis();
		}
		
		if (millis() - hbeat > 2000) {hbeat = millis();
			const byte heartbeat[] = {0xBB, 0x00, 0x01, 0x04, 0x02, 0x01, 0x00, 0xBD};
			Serial.write(heartbeat, 8);
		}
	}
}


