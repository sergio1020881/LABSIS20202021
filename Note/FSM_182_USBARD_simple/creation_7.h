/*creation_7.h*/
#ifdef _CREATION_7_H_
#else
#define _CREATION_7_H_
//PROTOTYPE
/**sergio manuel salazar dos santos 934805603**/
/***Libraries***/
// fopen perror fread fwrite feof fseek ferror fclose rewind scanf sscanf getchar scanf fscanf
// strncpy sscanf
#include <stdio.h>
// calloc free realloc
#include <stdlib.h>
// strcpy strcmp strcat memcmp
#include <string.h>
// termios tcflush
#include <termios.h>
// nanosleep sleep
#include <time.h>
// tcflsuh read write close
#include <unistd.h>
// perror
#include <errno.h>
// open
#include <sys/types.h>
#include <sys/stat.h>
//#include <sys/dir.h>
//#include <syscalls.h>
#include <fcntl.h>
//assert
#include <assert.h>
//offsetof
#include <stddef.h>
//__fpurge 
//#include <stdio_ext.h>
//#include <netdb.h>
//#include <netinet/in.h> 
//#include <stdbool.h>
//#include <ctype.h>
//#include <limits.h>
//#include <semaphore.h>
//#include <pthread.h>
//#include <math.h>
//#include <signal.h>
//#include <sys/mman.h>
//#include <sys/wait.h>
//#include <sys/time.h>
//#include <sys/resource.h>
#include <sys/dir.h>
//#include <sys/socket.h>
//#include <sys/un.h>
/***MACROS***/
#define TRUE 1
#define FALSE 0
#define BAUDRATE B9600
//arduino MEGA
#define DEVICE_1 "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A600aiS5-if00-port0"
//arduino DUEMILANOVE
#define DEVICE_2 "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A9007Qwg-if00-port0"
//arduino uno
#define DEVICE_3 "/dev/serial/by-id/usb-Arduino__www.arduino.cc__Arduino_Uno_649353431333512121A0-if00"
//open free tty
#define DEVICE_4 "/home/sergio/fd"
#define _POSIX_SOURCE 1
#define buf_size 16
#define SEND 16
#define Double(x) (2*(x))
/***Gloabal Variables***/
int LEARN;
char* DEVICE;
/***PROTO***/
typedef struct {
  char registry[2][buf_size];
  
}pastx;
typedef struct {
  char key[2][buf_size];
  char who[2][buf_size];
  
}buildingx;
#endif
/***FUNCTION TITLES***/
#include "creation_7_func.h"
