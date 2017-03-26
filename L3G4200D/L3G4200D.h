#define WHO_AM_I   0x0F
#define CTRL_REG1   0x20
#define CTRL_REG2   0x21
#define CTRL_REG3   0x22
#define CTRL_REG4   0x23
#define CTRL_REG5   0x24
#define CTRL_REG6   0x25
#define FIFO_CTRL_REG    0x2E
#define FIFO_SRC_REG     0x2F
#define OUT_X_L_INC      0xA8  // Çoklu okuma için gereken ilk adres
#define OUT_X_L     0x28
#define OUT_X_H     0x29
#define OUT_Y_L     0x2A
#define OUT_Y_H     0x2B
#define OUT_Z_L     0x2C
#define OUT_Z_H     0x2D
#define STATUS_REG  0x27
#define REFERENCE   0x25
#define INT1_CFG    0x30
#define INT1_SRC    0x31
#define INT1_THS_XH 0x32
#define INT1_THS_XL 0x33
#define INT1_THS_YH 0x34
#define INT1_THS_YL 0x35
#define INT1_THS_ZH 0x36
#define INT1_THS_ZL 0x37
#define INT1_DURATION 0x38
#define OUT_TEMP    0x26
//Adres bilgileri
#define _L3G4200D_I2C_Adress     0x69
#define L3G4200D_I2C_Adress	     _L3G4200D_I2C_Adress<<1
#define L3G4200D_deviceAdress_w  0xD2
#define L3G4200D_deviceAdress_r  0xD3

// Eksen tanýmlamalarý
#define x_eksen (uint8_t)0
#define y_eksen (uint8_t)1
#define z_eksen (uint8_t)2

unsigned char temp1[1],out1[6];
unsigned char L3G4200DSetup[1];

//Eþik ve ortalama deðerleri
#define RthX 12
#define RthY 9
#define RthZ 11
#define RoX  32
#define RoY  -73
#define RoZ  3

//########################################################################################################

void L3G4200D_Setup(I2C_HandleTypeDef *hi2c,GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void L3G4200D_Raw_Values(I2C_HandleTypeDef *hi2c, int16_t *GyroRaw);
uint8_t L3G4200D_Temperature(I2C_HandleTypeDef *hi2c);

//########################################################################################################



