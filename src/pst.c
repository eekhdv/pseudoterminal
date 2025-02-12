#include "pst.h"

#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>


int16_t setBaudRate(int32_t speed, int fd)
{
  return ioctl(fd, TIOCSBRK, &speed);
}

int16_t unlockpt(int fd)
{
  return ioctl(fd, TIOCSPTLCK, &(int){0});
}

int16_t setupUARTEmulation(int fd)
{
  struct termios tty;

  if (ioctl(fd, TCGETS, &tty) < 0) {
    perror("Error with ioctl TCGETS");
    close(fd);
    return -1;
  }

  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO;
  tty.c_lflag &= ~ECHOE;
  tty.c_lflag &= ~ECHONL;

  if (ioctl(fd, TCSETS, &tty) < 0) {
    perror("Error with ioctl TCSETS");
    close(fd);
    return -1;
  }
}

int16_t connectUARTDev(int br)
{
  int fd = open("/dev/ptmx", O_RDWR | O_NOCTTY);
  if (fd == -1) return fd;

  if (setBaudRate(br, fd) == -1)
    return -1;

  if (unlockpt(fd) == -1)
    return -1;

  if (setupUARTEmulation(fd) == -1)
    return -1;

  return fd;
}

int16_t disconnectUARTDev(int fd)
{
  return close(fd);
}

int16_t transmit(uint8_t data, int fd)
{
  return write(fd, &data, 1);
}

int16_t receive(uint8_t* buf, int bufSize, int fd)
{
  return read(fd, buf, bufSize - 1);
}

int16_t getPtsNum(/* in */ int fd)
{
  int n;
  if (ioctl(fd, TIOCGPTN, &n) == -1)
    return -1;

  return n;
}

void getPtsName(/* out */ char* name, /* */ int nameLen, /* in */ int fd)
{
  int ptsNum = getPtsNum(fd);

  if (ptsNum == -1)
    return;

  snprintf(name, nameLen, "/dev/pts/%d", ptsNum);
}

int16_t getSerialInfo(/* out */ struct serial_struct* serial, /* in */ int fd)
{
  return ioctl(fd, TIOCGSERIAL, serial);
}
