#define DATA_FORMAT 0x31 // 3.bit Full_Res 1 ise tam çözünürlük. 2. bit justify 0 ise saða yaslanmýþ mod
#define BW_RATE     0x2C
#define POWER_CTL   0x2D
#define FIFO_CTL    0x38
#define DATAXL_INC  0xB2  // çoklu okuma için gereken ilk adres
#define DATAXL      0x32
#define DATAXH      0x33
#define DATAYL      0x34
#define DATAYH      0x35
#define DATAZL      0x36
#define DATAZH      0x37
#define OFSX        0x1E
#define OFSY        0x1F
#define OFSZ        0x20
#define INT_ENABLE  0x2E  //7.bit Data_Ready enable
#define INT_SOURCE  0x30  //7.bit Data_Ready control
//I2C cihaz adres bilgileri
#define _ADXL345_I2C_Adress		 0x53
#define ADXL345_I2C_Adress  	 _ADXL345_I2C_Adress<<1
#define ADXL345_I2C_Adress_w   0xA6
#define ADXL345_I2C_Adress_r   0xA7

// Eksen tanýmlamalarý
#define x_eksen (uint8_t)0
#define y_eksen (uint8_t)1
#define z_eksen (uint8_t)2

unsigned char temp[1],out[6],ADXL345Setup[1];

//########################################################################################################

void ADXL345_Setup(I2C_HandleTypeDef *hi2c,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void ADXL345_Raw_Values(I2C_HandleTypeDef *hi2c, int16_t* AccRaw);

//########################################################################################################
