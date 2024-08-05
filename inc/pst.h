#pragma once

#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/serial.h>


int16_t connectUARTDev(/* in */ int baudrate);
int16_t disconnectUARTDev(/* in */ int fd);

int16_t transmit(/* in */ uint8_t data, /* in */ int fd);
int16_t receive(/* out */ uint8_t* buf, /* in */ int bufSize, /* in */ int fd);

void getPtsName(/* out */ char* name, /* */ int nameLen, /* in */ int fd);
int16_t getPtsNum(/* in */ int fd);

int16_t getSerialInfo(/* out */ struct serial_struct* serial, /* in */ int fd);

