#ifndef TRPROTOCOL_H
#define TRPROTOCOL_H

/**
* @brief  Sadece bir 16 bitlik deger okur
* @param 	rData :Gelen veriler.
* @param  buffer :Ilk ve son isaretçilerin çikarilmis hali.
* @param  rDataDim :rData dizi boyutu
*/
HAL_StatusTypeDef TR_Receive(char *rData,char *buffer,int8_t rDataDim);
/**
* @brief  16 bitlik birden fazla deger okur
* @param 	rData :Gelen veriler.
* @param  buffer :Ilk ve son isaretçilerin çikarilmis hali.
* @param  rDataDim :rData dizi boyutu
*/
HAL_StatusTypeDef TR_Receive_Multi(char *rData,char *buffer,int8_t rDataDim);
/**
* @brief  Veri gönderme
* @param 	data :Gönderilecek veri.
* @param  buffer :Gönderilecek verinin karakterlere ayrilmis biçimi.
* @param  bufferDim :buffer dizi boyutu
*/
void TR_Transmit(int16_t data,char *buffer,int8_t bufferDim);
/**
* @brief  Veri gönderme
* @param 	data :Gönderilecek veriler.
* @param  buffer :Gönderilecek verinin karakterlere ayrilmis biçimi.
* @param  bufferDim :buffer dizi boyutu
* @param  dataDim :data dizi boyutu
*/
void TR_Transmit_Multi(int16_t *data,char *buffer,int8_t bufferDim,int8_t dataDim);

#endif
