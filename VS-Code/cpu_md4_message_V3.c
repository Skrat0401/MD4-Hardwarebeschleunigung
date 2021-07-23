/*
 *      The MD4 hash algorithm, as described in https://tools.ietf.org/html/rfc1320
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct string {
  char* c;
  int len;
  char sign;
} string;

char* MD4(char* str, int len);

static uint32_t* MD4Digest(uint32_t* w, int len);
static void setMD4Registers(uint32_t AA, uint32_t BB, uint32_t CC, uint32_t DD);
static uint32_t changeEndianness(uint32_t x);
static void resetMD4Registers(void);
static string stringCat(string first, string second);
static string uint32ToString(uint32_t l);
static uint32_t stringToUint32(string s);

static const char* BASE16 = "0123456789abcdef=";

#define F(X, Y, Z) (((X) & (Y)) | ((~(X)) & (Z)))
#define G(X, Y, Z) (((X) & (Y)) | ((X) & (Z)) | ((Y) & (Z)))
#define H(X, Y, Z) ((X) ^ (Y) ^ (Z))

#define LEFTROTATE(A, N) ((A) << (N)) | ((A) >> (32 - (N)))

#define MD4ROUND1(a, b, c, d, x, s) \
  a += F(b, c, d) + x;              \
  a = LEFTROTATE(a, s);
#define MD4ROUND2(a, b, c, d, x, s)           \
  a += G(b, c, d) + x + (uint32_t)0x5A827999; \
  a = LEFTROTATE(a, s);
#define MD4ROUND3(a, b, c, d, x, s)           \
  a += H(b, c, d) + x + (uint32_t)0x6ED9EBA1; \
  a = LEFTROTATE(a, s);

static uint32_t A = 0x67452301;
static uint32_t B = 0xefcdab89;
static uint32_t C = 0x98badcfe;
static uint32_t D = 0x10325476;
int main() {
  clock_t start, end;
  uint32_t* hash;
  long counter = 0;
  int len = 16;
  char s[64] = "EinekleineTestnachrichtumeinenwunderbarenMD4hashzugenerieren    ";
  uint32_t arr[32];
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
  arr[16] = 0x00008061;
  arr[17] = 0x00000000;
  arr[18] = 0x00000000;
  arr[19] = 0x00000000;
  arr[20] = 0x00000000;
  arr[21] = 0x00000000;
  arr[22] = 0x00000000;
  arr[23] = 0x00000000;
  arr[24] = 0x00000000;
  arr[25] = 0x00000000;
  arr[26] = 0x00000000;
  arr[27] = 0x00000000;
  arr[28] = 0x00000000;
  arr[29] = 0x00000000;
  arr[30] = 0x00000008;
  arr[31] = 0x00000000;
  arr[32] = 0x00008061;
  arr[33] = 0x00000000;
  arr[34] = 0x00000000;
  arr[35] = 0x00000000;
  arr[36] = 0x00000000;
  arr[37] = 0x00000000;
  arr[38] = 0x00000000;
  arr[39] = 0x00000000;
  arr[40] = 0x00000000;
  arr[41] = 0x00000000;
  arr[42] = 0x00000000;
  arr[43] = 0x00000000;
  arr[44] = 0x00000000;
  arr[45] = 0x00000000;
  arr[46] = 0x00000008;
  arr[47] = 0x00000000;

  // printf("char* s = %s \n", s);
  start = clock();
  while (counter < 60000) {
    // MD4(s, 64); // Testing for char* and timing
    hash = MD4Digest(arr, len);
    counter++;
  }

  end = clock();
  // MD4 hash : 9c8ad26e6a8fd819e5aee07cac2baedc
  printf("\nMd4-hash for testing: %s\n\n", MD4(s, 64));
  double runningTime = ((double)(end - start) / CLOCKS_PER_SEC);
  printf("elapsed time for program : %f seconds.\n", runningTime);
  printf("start :                    %ld clock cycles.\nend   :                    %ld clock cycles.\n%ld runs with %d bit\n\nCPU : \n", start, end, counter, len * 32);
  hash = MD4Digest(arr, 16);
  printf("uint32_t hash (hex)  512 bit: %x , %x, %x, %x\n", hash[3], hash[2], hash[1], hash[0]);
  hash = MD4Digest(arr, 32);
  printf("uint32_t hash (hex) 1024 bit: %x , %x, %x, %x\n", hash[3], hash[2], hash[1], hash[0]);
};
string newString(char* c, int t) {
  string r;
  int i;
  if (c != NULL) {
    r.len = (t <= 0) ? strlen(c) : t;
    r.c = (char*)malloc(sizeof(char) * (r.len + 1));
    for (i = 0; i < r.len; i++)
      r.c[i] = c[i];
    r.c[r.len] = '\0';
    return r;
  }
  r.len = t;
  r.c = (char*)malloc(sizeof(char) * (r.len + 1));
  memset(r.c, (char)0, sizeof(char) * (t + 1));
  r.sign = 1;
  return r;
}

string stringCat(string first, string second) {
  string str = newString(NULL, first.len + second.len);
  int i;

  for (i = 0; i < first.len; i++) {
    str.c[i] = first.c[i];
  }
  for (i = first.len; i < str.len; i++) {
    str.c[i] = second.c[i - first.len];
  }
  return str;
}

string base16Encode(string in) {
  string out = newString(NULL, in.len * 2);
  int i, j;

  j = 0;
  for (i = 0; i < in.len; i++) {
    out.c[j++] = BASE16[((in.c[i] & 0xF0) >> 4)];
    out.c[j++] = BASE16[(in.c[i] & 0x0F)];
  }
  out.c[j] = '\0';
  return out;
}

string uint32ToString(uint32_t l) {
  string s = newString(NULL, 4);
  int i;
  for (i = 0; i < 4; i++) {
    s.c[i] = (l >> (8 * (3 - i))) & 0xFF;
  }
  return s;
}

uint32_t stringToUint32(string s) {
  uint32_t l;
  int i;
  l = 0;
  for (i = 0; i < 4; i++) {
    l = l | (((uint32_t)((unsigned char)s.c[i])) << (8 * (3 - i)));
  }
  return l;
}

char* MD4(char* str, int len) {
  string m = newString(str, len);
  string digest;
  uint32_t* w;
  uint32_t* hash;
  uint64_t mlen = m.len;
  unsigned char oneBit = 0x80;
  int i, wlen;

  m = stringCat(m, newString((char*)&oneBit, 1));

  // append 0 ≤ k < 512 bits '0', such that the resulting message length in bits
  //	is congruent to −64 ≡ 448 (mod 512)4
  i = ((56 - m.len) % 64);
  if (i < 0)
    i += 64;
  m = stringCat(m, newString(NULL, i));

  w = (uint32_t*)malloc(sizeof(uint32_t) * (m.len / 4 + 2));

  // append length, in bits (hence <<3), least significant word first
  for (i = 0; i < m.len / 4; i++) {
    w[i] = stringToUint32(newString(&(m.c[4 * i]), 4));
  }
  w[i++] = (mlen << 3) & 0xFFFFFFFF;
  w[i++] = (mlen >> 29) & 0xFFFFFFFF;

  wlen = i;

  // change endianness, but not for the appended message length, for some reason?
  for (i = 0; i < wlen - 2; i++) {
    w[i] = changeEndianness(w[i]);
  }

  hash = MD4Digest(w, wlen);

  digest = newString(NULL, 0);
  for (i = 0; i < 4; i++) {
    hash[i] = changeEndianness(hash[i]);
    digest = stringCat(digest, uint32ToString(hash[i]));
  }

  return base16Encode(digest).c;
}

uint32_t* MD4Digest(uint32_t* w, int len) {
  // assumes message.len is a multiple of 64 bytes.
  int i, j;
  uint32_t X[16];
  uint32_t* digest = (uint32_t*)malloc(sizeof(uint32_t) * 4);
  uint32_t AA, BB, CC, DD;

  for (i = 0; i < len / 16; i++) {
    for (j = 0; j < 16; j++) {
      X[j] = w[i * 16 + j];
    }

    AA = A;
    BB = B;
    CC = C;
    DD = D;

    MD4ROUND1(A, B, C, D, X[0], 3);
    MD4ROUND1(D, A, B, C, X[1], 7);
    MD4ROUND1(C, D, A, B, X[2], 11);
    MD4ROUND1(B, C, D, A, X[3], 19);
    MD4ROUND1(A, B, C, D, X[4], 3);
    MD4ROUND1(D, A, B, C, X[5], 7);
    MD4ROUND1(C, D, A, B, X[6], 11);
    MD4ROUND1(B, C, D, A, X[7], 19);
    MD4ROUND1(A, B, C, D, X[8], 3);
    MD4ROUND1(D, A, B, C, X[9], 7);
    MD4ROUND1(C, D, A, B, X[10], 11);
    MD4ROUND1(B, C, D, A, X[11], 19);
    MD4ROUND1(A, B, C, D, X[12], 3);
    MD4ROUND1(D, A, B, C, X[13], 7);
    MD4ROUND1(C, D, A, B, X[14], 11);
    MD4ROUND1(B, C, D, A, X[15], 19);

    MD4ROUND2(A, B, C, D, X[0], 3);
    MD4ROUND2(D, A, B, C, X[4], 5);
    MD4ROUND2(C, D, A, B, X[8], 9);
    MD4ROUND2(B, C, D, A, X[12], 13);
    MD4ROUND2(A, B, C, D, X[1], 3);
    MD4ROUND2(D, A, B, C, X[5], 5);
    MD4ROUND2(C, D, A, B, X[9], 9);
    MD4ROUND2(B, C, D, A, X[13], 13);
    MD4ROUND2(A, B, C, D, X[2], 3);
    MD4ROUND2(D, A, B, C, X[6], 5);
    MD4ROUND2(C, D, A, B, X[10], 9);
    MD4ROUND2(B, C, D, A, X[14], 13);
    MD4ROUND2(A, B, C, D, X[3], 3);
    MD4ROUND2(D, A, B, C, X[7], 5);
    MD4ROUND2(C, D, A, B, X[11], 9);
    MD4ROUND2(B, C, D, A, X[15], 13);

    MD4ROUND3(A, B, C, D, X[0], 3);
    MD4ROUND3(D, A, B, C, X[8], 9);
    MD4ROUND3(C, D, A, B, X[4], 11);
    MD4ROUND3(B, C, D, A, X[12], 15);
    MD4ROUND3(A, B, C, D, X[2], 3);
    MD4ROUND3(D, A, B, C, X[10], 9);
    MD4ROUND3(C, D, A, B, X[6], 11);
    MD4ROUND3(B, C, D, A, X[14], 15);
    MD4ROUND3(A, B, C, D, X[1], 3);
    MD4ROUND3(D, A, B, C, X[9], 9);
    MD4ROUND3(C, D, A, B, X[5], 11);
    MD4ROUND3(B, C, D, A, X[13], 15);
    MD4ROUND3(A, B, C, D, X[3], 3);
    MD4ROUND3(D, A, B, C, X[11], 9);
    MD4ROUND3(C, D, A, B, X[7], 11);
    MD4ROUND3(B, C, D, A, X[15], 15);

    A += AA;
    B += BB;
    C += CC;
    D += DD;
  }

  digest[0] = A;
  digest[1] = B;
  digest[2] = C;
  digest[3] = D;
  resetMD4Registers();
  return digest;
}

uint32_t changeEndianness(uint32_t x) {
  return ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x & 0xFF0000) >> 8) | ((x & 0xFF000000) >> 24);
}

void setMD4Registers(uint32_t AA, uint32_t BB, uint32_t CC, uint32_t DD) {
  A = AA;
  B = BB;
  C = CC;
  D = DD;
}

void resetMD4Registers(void) {
  setMD4Registers(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476);
}