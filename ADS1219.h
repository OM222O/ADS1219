#ifndef ADS1219_H
#define ADS1219_H

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Wire.h>

#define CONFIG_REGISTER_ADDRESS 0x40
#define STATUS_REGISTER_ADDRESS 0x24

#define MUX_MASK 				0x1F
#define MUX_DIFF_0_1			0x00
#define MUX_DIFF_2_3			0x20
#define MUX_DIFF_1_2			0x40
#define MUX_SINGLE_0			0x60
#define MUX_SINGLE_1			0x80
#define MUX_SINGLE_2			0xA0
#define MUX_SINGLE_3			0xC0
#define MUX_SHORTED				0xE0

#define GAIN_MASK 				0xEF
#define GAIN_ONE				0x00
#define GAIN_FOUR				0x10

#define DATA_RATE_MASK			0xF3
#define DATA_RATE_20			0x00
#define DATA_RATE_90			0x04
#define DATA_RATE_330			0x08
#define DATA_RATE_1000			0x0c

#define MODE_MASK				0xFD
#define MODE_SINGLE_SHOT		0x00
#define MODE_CONTINUOUS			0x02

#define VREF_MASK				0xFE
#define VREF_INTERNAL			0x00
#define VREF_EXTERNAL			0x01

typedef enum{
  ONE	= GAIN_ONE,
  FOUR	= GAIN_FOUR
}adsGain_t;

typedef enum{
  SINGLE_SHOT	= MODE_SINGLE_SHOT,
  CONTINUOUS	= MODE_CONTINUOUS
}adsMode_t;

typedef enum{
  REF_INTERNAL	= VREF_INTERNAL,
  REF_EXTERNAL	= VREF_EXTERNAL
}adsRef_t;

class ADS1219  {
  protected:
	uint8_t address;
  public:
    // Constructor 
    ADS1219(int drdy, uint8_t addr = 0x40);

    // Methods
    void begin();
	void resetConfig();
	long readSingleEnded(int channel);
	long readDifferential_0_1();
	long readDifferential_2_3();
	long readDifferential_1_2();
	long readShorted();
	void setGain(adsGain_t gain);
	void setDataRate(int rate);
	void setConversionMode(adsMode_t mode);
	void setVoltageReference(adsRef_t vref);
	void powerDown();
  private:
	void start();
	uint8_t readRegister(uint8_t reg);
	void writeRegister(uint8_t data);
	long readConversionResult();
	uint8_t config;
	boolean singleShot;
	int data_ready;
};
#endif
