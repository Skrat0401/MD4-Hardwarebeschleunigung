#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int fdr, fdw;
  int rc, rb;
  unsigned char* buf;
  uint32_t arr[16];

  char tologic[64] = "EinekleineTestnachrichtumeinenwunderbarenMD4hashzugenerierenhehe";

  struct {
    unsigned int v1;
    unsigned int v2;
    unsigned int v3;
    unsigned int v4;
    unsigned int v5;
  } fromlogic;
  clock_t start, end;

  arr[0] = 0x00008061;
  arr[1] = 0x00000000;
  arr[2] = 0x00000000;
  arr[3] = 0x00000000;
  arr[4] = 0x00000000;
  arr[5] = 0x00000000;
  arr[6] = 0x00000000;
  arr[7] = 0x00000000;
  arr[8] = 0x00000000;
  arr[9] = 0x00000000;
  arr[10] = 0x00000000;
  arr[11] = 0x00000000;
  arr[12] = 0x00000000;
  arr[13] = 0x00000000;
  arr[14] = 0x00000008;
  arr[15] = 0x00000000;

  for (int i = 0; i < 16; i++) {
    printf(" In array on slot %d is %x \n", i, arr[i]);
  };
  start = clock();
  // for (int ii = 0; ii < 10; ii++) {
  fdr = open("/dev/xillybus_read_32", O_RDONLY);
  fdw = open("/dev/xillybus_write_32", O_WRONLY);
  if ((fdr < 0) || (fdw < 0)) {
    perror("Failed to open Xillybus device file(s)");
    exit(1);
  }
  rc = write(fdw, (void*)&arr, sizeof(arr));
  // rc = write(fdw, (void*)&tologic, sizeof(tologic));
  rb = read(fdr, (void*)&fromlogic, sizeof(fromlogic));
  close(fdr);
  close(fdw);
  //};
  end = clock();

  printf("number of bytes wrote : %d \n ", rc);
  printf("size of unsigned is %d byte \n ", sizeof(unsigned int));
  // printf("%d \n", sizeof(tologic));

  printf("FPGA said: %x and  %x and %x and %x \n number of bytes read: %d \n in %d clock cycles: \n ", fromlogic.v1, fromlogic.v2, fromlogic.v3, fromlogic.v4, rb, fromlogic.v5);
  double runningTime = ((double)(end - start) / CLOCKS_PER_SEC);
  printf("elapsed time for program: %f seconds.\n", runningTime);
  printf("start: %ld clock cycles.\n", start);
  printf("end: %ld clock cycles.\n", end);
  // for (int i = 0; i < 17; i++) {
  //  printf("now singel: %d : %c \n", i, buf[i]);
  //};
  // memcpy(tologic.v2, "HalloHalloHalloHalloHalloHalloHalloHalloHalloHalloHalloHalloaaaa", 65);  // ~ pi/4

  // Not checking return values of write() and read(). This must be done
  // in a real-life program to ensure reliability.
  // tologic.v1 = 123;
  // memcpy(tologic.v2, "HalloHalloHalloHalloHalloHalloHalloHalloHalloHalloHalloHalloaaaa", 65);  // ~ pi/4

  // char string[65];
  // char string2[16];
  // memcpy(string, "HalloHalloHalloHalloHalloHalloHalloHalloHalloHalloHalloHalloaaaa", 65);
  // Not checking return values of write() and read(). This must be done
  // in a real-life program to ensure reliability.

  // write(fdw, (void*)&tologic, sizeof(tologic));
  // read(fdr, (void*)&fromlogic, sizeof(fromlogic));

  // write(fdw, (void*)&string, sizeof(string));
  // read(fdr, (void*)&string2, sizeof(string2));

  // printf(
  //    "FPGA said: %d + 1 = %d and also "
  //    "sin(%s) = %s\n",
  //    tologic.v1, fromlogic.v1, tologic.v2, fromlogic.v2);
  // "FPGA said: %d + 1 = %d and also "
  // "sin(%s) = %s\n",
  // string, string2, string, string2);

  close(fdr);
  close(fdw);

  return 0;
}