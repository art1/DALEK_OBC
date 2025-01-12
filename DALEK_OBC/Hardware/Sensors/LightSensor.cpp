/*
 * lightSensor.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: arthur
 */

#include "LightSensor.h"

#include "inttypes.h"

static Application senderName("Lux_Data_Publisher",500);



lightSensor::lightSensor() : Thread("Light Sensor",108, 1000){

	activated = false;
}

lightSensor::~lightSensor() {

}

void lightSensor::init(){
	pub_data.activated = true;
}

void lightSensor::initSensor(){

	int k=0;
	lux = 0.0f;
	activated =false;
	memset(transBuf,0,sizeof(transBuf));
	memset(recBuf,0,sizeof(recBuf));
	pub_data.LUX = 0;
	pub_data.activated = true;

	//turn on the light sensor
	transBuf[0] = REG_CONTROL;
	transBuf[1] = TURN_ON;
	k = i2c1.writeRead(DEVICE_ADRESS,transBuf,2,recBuf,1);
	while(k < 0){
		PRINTF("turn on return: %d with i2c-k %d\n",recBuf[0],k);
		i2c1.reset();
		suspendCallerUntil(NOW()+200*MILLISECONDS);
		i2c1.init(400000);
		suspendCallerUntil(NOW()+200*MILLISECONDS);
		k = i2c1.writeRead(DEVICE_ADRESS,transBuf,2,recBuf,1);
		PRINTF("turn on return: %d with i2c-k %d\n",recBuf[0],k);

	}
//	k = i2c1.writeRead(0x39,transBuf,2,recBuf,1);
//	PRINTF("turn on return: %d with i2c-k %d\n",recBuf[0],k);
	PRINTF("turn on return: %d with i2c-k %d\n",recBuf[0],k);

	if(recBuf[0] != TURN_ON){
		PRINTF("error turning on the light sensor! please check connections!\n");
		activated =false;
	} else activated = true;

	// setting gain
	if(activated){
		transBuf[0] = LIGHT_INTEGRATION_ADRESS;
		switch (LIGHT_INTEGRATION_TIME) {
		case 13:
			if(LIGHT_GAIN == 1){
				transBuf[1] = 0x10;
			} else transBuf[1] = 0x00;
			break;
		case 101:
			if(LIGHT_GAIN == 1){
				transBuf[1] = 0x11;
			} else transBuf[1] = 0x01;
			break;
		case 420:
			if(LIGHT_GAIN == 1){
				transBuf[1] = 0x12;
			} else transBuf[1] = 0x02;
			break;
		default:
			break;
		}
		k = i2c1.write(DEVICE_ADRESS,transBuf,2);
	}
}

bool lightSensor::isActive(){
	return activated;
}

void lightSensor::setActive(LUX_DATA val){
	pub_data = val;
}

void lightSensor::run(){
	suspendCallerUntil(NOW()+2000*MILLISECONDS);
	INTERCOMM tmp;
	tmp.changedVal = LUX_CHANGED;
	if(!isActive())initSensor();

	while(1){

		suspendCallerUntil(NOW()+LIGHT_SAMPLERATE*MILLISECONDS);

		if(pub_data.activated){
			readRawData();
			calculateLux();
			tmp.luxData = pub_data;
			interThreadComm.publish(tmp);
		} else suspendCallerUntil(END_OF_TIME);

	}
}

// lux equation approximation without floating point calculations
uint32_t lightSensor::calculateLux(){
	//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
	// first, scale the channel values depending on the gain and integration time
	// 16X, 402mS is nominal.
	// scale if integration time is NOT 402 msec
	unsigned long chScale;
	unsigned long channel1;
	unsigned long channel0;

	switch(LIGHT_INTEGRATION_TIME){
	case 13: // 13.7 msec
		chScale = CHSCALE_TINT0;
		break;
	case 101: // 101 msec
		chScale = CHSCALE_TINT1;
		break;
	default: // assume no scaling
		chScale = (1 << CH_SCALE);
		break;
	}

	// scale if gain is NOT 16X
	if (!LIGHT_GAIN) chScale = chScale << 4;    	// scale 1X to 16X
	// scale the channel values
	channel0 = (ch0 * chScale) >> CH_SCALE;
	channel1 = (ch1 * chScale) >> CH_SCALE;
	//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
	// find the ratio of the channel values (Channel1/Channel0)
	// protect against divide by zero
	unsigned long ratio1 = 0;
	if (channel0 != 0) ratio1 = (channel1 << (RATIO_SCALE+1)) / channel0;
	// round the ratio value
	unsigned long ratio = (ratio1 + 1) >> 1;
	// is ratio <= eachBreak ?
	unsigned int b, m;


	if ((ratio >= 0) && (ratio <= K1C))
	{b=B1C; m=M1C;}
	else if (ratio <= K2C)
	{b=B2C; m=M2C;}
	else if (ratio <= K3C)
	{b=B3C; m=M3C;}
	else if (ratio <= K4C)
	{b=B4C; m=M4C;}
	else if (ratio <= K5C)
	{b=B5C; m=M5C;}
	else if (ratio <= K6C)
	{b=B6C; m=M6C;}
	else if (ratio <= K7C)
	{b=B7C; m=M7C;}
	else if (ratio > K8C)
	{b=B8C; m=M8C;}
	unsigned long temp;
	temp = ((channel0 * b) - (channel1*m));
	// do not allow negative lux value
	if (temp < 0) temp = 0;
	// round lsb (2^(LUX_SCALE−1))
	temp += (1 << (LUX_SCALE -1 ));
	// strip off fractional portion
	uint32_t lux = temp >> LUX_SCALE;
	pub_data.LUX = lux;
	return lux;
}

void lightSensor::readRawData(){
	// read channel 0 -> visible & IR
	transBuf[0] = ((REG_DATA0_LOW & 0x0F )| 0x90); //
	i2c1.writeRead(DEVICE_ADRESS,transBuf,1,recBuf,2);
	ch0 = (uint16_t)(recBuf[0] | (recBuf[1] << 8));

	transBuf[0] = ((REG_DATA1_LOW & 0x0F)| 0x90);
	i2c1.writeRead(DEVICE_ADRESS,transBuf,1,recBuf,2);
	ch1 = (uint16_t)(recBuf[0] | (recBuf[1] << 8));
//	PRINTF("raw data %d %d\n",ch0,ch1);
}
