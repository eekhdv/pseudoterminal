#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>
#include <poll.h>

#include "pst.h"


/*** clean after end of a scope ***/
static void freep(void* te) { free(*(void**)te); }
#define _cleanup_(x) __attribute__((cleanup(x)))
#define _cleanup_free_ _cleanup_(freep)


int main(int argc, char *argv[])
{
  struct pollfd pfd;
  _cleanup_free_ char* ptsName = malloc(50);

  int baudRate = 115200;

  int fd = connectUARTDev(baudRate); ///< Create PST char device

  pfd.fd = fd;
  pfd.events = POLLIN;

  getPtsName(ptsName, 50, fd);

  printf("pts num : %d\n", getPtsNum(fd));
  printf("pts name: %s\n", ptsName);

  for (;;) { 
    int poll_result = poll(&pfd, 1, 1000); ///< Wait 1 sec

    if (poll_result > 0) {
      uint8_t buffer[1024];
      ssize_t bytesRead = receive(buffer, 1024, fd); ///< Receive data from a slave

      if (bytesRead > 0) {
        for (uint16_t i = 0; i < bytesRead; i++) {
          transmit(buffer[i], fd); ///< Send data to a slave
        }
      } 
    } else if (poll_result == -1) {
        perror("Error with polling");
    } 
    sleep(9);
  }

  return EXIT_SUCCESS;
}
