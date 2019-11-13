#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

/* BoringSSL - slow
#include "openssl/poly1305.h"
static inline void bssl_poly1305(uint8_t mac[16],const uint8_t* in, size_t in_len, const uint8_t key[32]) {
  poly1305_state st;
  CRYPTO_poly1305_init(&st,key);
  CRYPTO_poly1305_update(&st,in,in_len);
  CRYPTO_poly1305_finish(&st,mac);
}
*/

#include "poly1305.h"

void ossl_poly1305(uint8_t* mac, uint8_t* plain, int len, uint8_t* key){
  POLY1305 state;
  Poly1305_Init(&state,key);
  Poly1305_Update(&state,plain,len);
  Poly1305_Final(&state,mac);
}

#include "impl.h"

extern void poly1305_impl(
  unsigned char *out,
  const unsigned char *in,
  unsigned long long inlen,
  const unsigned char *k
);


typedef uint64_t cycles;

static __inline__ cycles cpucycles_begin(void)
{
  uint64_t rax,rdx,aux;
  asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
  return (rdx << 32) + rax;
  //  unsigned hi, lo;
  //__asm__ __volatile__ ("CPUID\n\t"  "RDTSC\n\t"  "mov %%edx, %0\n\t"  "mov %%eax, %1\n\t": "=r" (hi), "=r" (lo):: "%rax", "%rbx", "%rcx", "%rdx");
  //return ( (uint64_t)lo)|( ((uint64_t)hi)<<32 );
}

static __inline__ cycles cpucycles_end(void)
{
  uint64_t rax,rdx,aux;
  asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
  return (rdx << 32) + rax;
  //  unsigned hi, lo;
  //__asm__ __volatile__ ("RDTSCP\n\t"  "mov %%edx, %0\n\t"  "mov %%eax, %1\n\t"  "CPUID\n\t": "=r" (hi), "=r" (lo)::     "%rax", "%rbx", "%rcx", "%rdx");
  //return ( (uint64_t)lo)|( ((uint64_t)hi)<<32 );
}

//extern void Hacl_Poly1305_64_poly1305_mac(uint8_t* out, uint8_t* in, int in_len, uint8_t* k);
extern void Hacl_Poly1305_32_poly1305_mac(uint8_t* out, int in_len, uint8_t* in, uint8_t* k);
extern void Hacl_Poly1305_128_poly1305_mac(uint8_t* out, int in_len, uint8_t* in, uint8_t* k);
extern void Hacl_Poly1305_256_poly1305_mac(uint8_t* out, int in_len, uint8_t* in, uint8_t* k);

/*
extern void
Hacl_Poly1305_64_crypto_onetimeauth(
  uint8_t *output,
  uint8_t *input,
  uint64_t len1,
  uint8_t *k1
				    );

extern void
Hacl_Poly1305_32_crypto_onetimeauth(
  uint8_t *output,
  uint8_t *input,
  uint64_t len1,
  uint8_t *k1
				    );
*/

#define ROUNDS 100000
#define SIZE   16384

int main() {
  int in_len = 34;
  uint8_t in[34] = {
    0x43, 0x72, 0x79, 0x70, 0x74, 0x6f, 0x67, 0x72,
    0x61, 0x70, 0x68, 0x69, 0x63, 0x20, 0x46, 0x6f,
    0x72, 0x75, 0x6d, 0x20, 0x52, 0x65, 0x73, 0x65,
    0x61, 0x72, 0x63, 0x68, 0x20, 0x47, 0x72, 0x6f,
    0x75, 0x70};
  uint8_t key[32] = {
    0x85, 0xd6, 0xbe, 0x78, 0x57, 0x55, 0x6d, 0x33,
    0x7f, 0x44, 0x52, 0xfe, 0x42, 0xd5, 0x06, 0xa8,
    0x01, 0x03, 0x80, 0x8a, 0xfb, 0x0d, 0xb2, 0xfd,
    0x4a, 0xbf, 0xf6, 0xaf, 0x41, 0x49, 0xf5, 0x1b
  };
  uint8_t exp[16] = {
    0xa8, 0x06, 0x1d, 0xc1, 0x30, 0x51, 0x36, 0xc6,
    0xc2, 0x2b, 0x8b, 0xaf, 0x0c, 0x01, 0x27, 0xa9
  };

  int in_len2 = 16;
  uint8_t in2[16] = {
		     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
  };
  uint8_t key2[32] = {
		    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  uint8_t exp2[16] = {
		    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };



  int in_len3 = 528;
  uint8_t in3[528] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x17,0x03,0x03,0x02,0x00,0x00,0x00,0x00,0x06,0xdb,0x1f,0x1f,0x36,0x8d,0x69,0x6a,0x81,0x0a,0x34,0x9c,0x0c,0x71,0x4c,0x9a,0x5e,0x78,0x50,0xc2,0x40,0x7d,0x72,0x1a,0xcd,0xed,0x95,0xe0,0x18,0xd7,0xa8,0x52,0x66,0xa6,0xe1,0x28,0x9c,0xdb,0x4a,0xeb,0x18,0xda,0x5a,0xc8,0xa2,0xb0,0x02,0x6d,0x24,0xa5,0x9a,0xd4,0x85,0x22,0x7f,0x3e,0xae,0xdb,0xb2,0xe7,0xe3,0x5e,0x1c,0x66,0xcd,0x60,0xf9,0xab,0xf7,0x16,0xdc,0xc9,0xac,0x42,0x68,0x2d,0xd7,0xda,0xb2,0x87,0xa7,0x02,0x4c,0x4e,0xef,0xc3,0x21,0xcc,0x05,0x74,0xe1,0x67,0x93,0xe3,0x7c,0xec,0x03,0xc5,0xbd,0xa4,0x2b,0x54,0xc1,0x14,0xa8,0x0b,0x57,0xaf,0x26,0x41,0x6c,0x7b,0xe7,0x42,0x00,0x5e,0x20,0x85,0x5c,0x73,0xe2,0x1d,0xc8,0xe2,0xed,0xc9,0xd4,0x35,0xcb,0x6f,0x60,0x59,0x28,0x00,0x11,0xc2,0x70,0xb7,0x15,0x70,0x05,0x1c,0x1c,0x9b,0x30,0x52,0x12,0x66,0x20,0xbc,0x1e,0x27,0x30,0xfa,0x06,0x6c,0x7a,0x50,0x9d,0x53,0xc6,0x0e,0x5a,0xe1,0xb4,0x0a,0xa6,0xe3,0x9e,0x49,0x66,0x92,0x28,0xc9,0x0e,0xec,0xb4,0xa5,0x0d,0xb3,0x2a,0x50,0xbc,0x49,0xe9,0x0b,0x4f,0x4b,0x35,0x9a,0x1d,0xfd,0x11,0x74,0x9c,0xd3,0x86,0x7f,0xcf,0x2f,0xb7,0xbb,0x6c,0xd4,0x73,0x8f,0x6a,0x4a,0xd6,0xf7,0xca,0x50,0x58,0xf7,0x61,0x88,0x45,0xaf,0x9f,0x02,0x0f,0x6c,0x3b,0x96,0x7b,0x8f,0x4c,0xd4,0xa9,0x1e,0x28,0x13,0xb5,0x07,0xae,0x66,0xf2,0xd3,0x5c,0x18,0x28,0x4f,0x72,0x92,0x18,0x60,0x62,0xe1,0x0f,0xd5,0x51,0x0d,0x18,0x77,0x53,0x51,0xef,0x33,0x4e,0x76,0x34,0xab,0x47,0x43,0xf5,0xb6,0x8f,0x49,0xad,0xca,0xb3,0x84,0xd3,0xfd,0x75,0xf7,0x39,0x0f,0x40,0x06,0xef,0x2a,0x29,0x5c,0x8c,0x7a,0x07,0x6a,0xd5,0x45,0x46,0xcd,0x25,0xd2,0x10,0x7f,0xbe,0x14,0x36,0xc8,0x40,0x92,0x4a,0xae,0xbe,0x5b,0x37,0x08,0x93,0xcd,0x63,0xd1,0x32,0x5b,0x86,0x16,0xfc,0x48,0x10,0x88,0x6b,0xc1,0x52,0xc5,0x32,0x21,0xb6,0xdf,0x37,0x31,0x19,0x39,0x32,0x55,0xee,0x72,0xbc,0xaa,0x88,0x01,0x74,0xf1,0x71,0x7f,0x91,0x84,0xfa,0x91,0x64,0x6f,0x17,0xa2,0x4a,0xc5,0x5d,0x16,0xbf,0xdd,0xca,0x95,0x81,0xa9,0x2e,0xda,0x47,0x92,0x01,0xf0,0xed,0xbf,0x63,0x36,0x00,0xd6,0x06,0x6d,0x1a,0xb3,0x6d,0x5d,0x24,0x15,0xd7,0x13,0x51,0xbb,0xcd,0x60,0x8a,0x25,0x10,0x8d,0x25,0x64,0x19,0x92,0xc1,0xf2,0x6c,0x53,0x1c,0xf9,0xf9,0x02,0x03,0xbc,0x4c,0xc1,0x9f,0x59,0x27,0xd8,0x34,0xb0,0xa4,0x71,0x16,0xd3,0x88,0x4b,0xbb,0x16,0x4b,0x8e,0xc8,0x83,0xd1,0xac,0x83,0x2e,0x56,0xb3,0x91,0x8a,0x98,0x60,0x1a,0x08,0xd1,0x71,0x88,0x15,0x41,0xd5,0x94,0xdb,0x39,0x9c,0x6a,0xe6,0x15,0x12,0x21,0x74,0x5a,0xec,0x81,0x4c,0x45,0xb0,0xb0,0x5b,0x56,0x54,0x36,0xfd,0x6f,0x13,0x7a,0xa1,0x0a,0x0c,0x0b,0x64,0x37,0x61,0xdb,0xd6,0xf9,0xa9,0xdc,0xb9,0x9b,0x1a,0x6e,0x69,0x08,0x54,0xce,0x07,0x69,0xcd,0xe3,0x97,0x61,0xd8,0x2f,0xcd,0xec,0x15,0xf0,0xd9,0x2d,0x7d,0x8e,0x94,0xad,0xe8,0xeb,0x83,0xfb,0xe0
  };
  uint8_t key3[32] = {
/*		      0x01,0x00,0x00,0x00,
		      0x00,0x00,0x00,0x00,
		      0x00,0x00,0x00,0x00,
		      0x00,0x00,0x00,0x00,
		      0x00,0x00,0x00,0x00,
		      0x00,0x00,0x00,0x00,
		      0x00,0x00,0x00,0x00,
		      0x00,0x00,0x00,0x00 */
0x99,0xe5,0x82,0x2d,0xd4,0x17,0x3c,0x99,0x5e,0x3d,0xae,0x0d,0xde,0xfb,0x97,0x74,0x3f,0xde,0x3b,0x08,0x01,0x34,0xb3,0x9f,0x76,0xe9,0xbf,0x8d,0x0e,0x88,0xd5,0x46
  };
  uint8_t exp3[16] = {
0x26,0x37,0x40,0x8f,0xe1,0x30,0x86,0xea,0x73,0xf9,0x71,0xe3,0x42,0x5e,0x28,0x20
  };

  uint8_t comp[16] = {0};
  bool ok = true;

  /*Hacl_Poly1305_64_poly1305_mac(comp,in,34,key);
  printf("Poly1305 (64-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n"); */

  Hacl_Poly1305_32_poly1305_mac(comp,in_len,in,key);
  printf("Poly1305 (32-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  Hacl_Poly1305_128_poly1305_mac(comp,in_len,in,key);
  printf("Poly1305 (128-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  Hacl_Poly1305_256_poly1305_mac(comp,in_len,in,key);
  printf("Poly1305 (256-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  /*Hacl_Poly1305_64_poly1305_mac(comp,in2,in_len2,key2);
  Hacl_Poly1305_64_crypto_onetimeauth(comp,in,in_len,key);
  printf("Master Poly1305 (64-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n"); */

/*  Hacl_Poly1305_32_crypto_onetimeauth(comp,in,in_len,key);
  printf("Master Poly1305 (32-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n"); */


  ossl_poly1305(comp,in,in_len,key);
  printf("OpenSSL Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  poly1305_impl(comp, in, in_len, key);
  printf("Jasmin Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");


  /*Hacl_Poly1305_64_poly1305_mac(comp,in2,in_len2,key2);
  printf("Poly1305 (64-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp2[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp2[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n"); */
  
  Hacl_Poly1305_32_poly1305_mac(comp,in_len2,in2,key2);
  printf("Poly1305 (32-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp2[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp2[i] == comp[i]);
  if (ok) printf("Success!\n");

  Hacl_Poly1305_128_poly1305_mac(comp,in_len2,in2,key2);
  printf("Poly1305 (128-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp2[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp2[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  Hacl_Poly1305_256_poly1305_mac(comp,in_len2,in2,key2);
  printf("Poly1305 (256-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp2[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp2[i] == comp[i]);
  if (ok) printf("Success!\n");

  ossl_poly1305(comp,in2,in_len2,key2);
  printf("OpenSSL Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp2[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp2[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  poly1305_impl(comp, in2, in_len2, key2);
  printf("Jasmin Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp2[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp2[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");
  
  /*Hacl_Poly1305_64_poly1305_mac(comp,in3,in_len3,key3);
  printf("Poly1305 (64-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp3[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp3[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n"); */
  
  Hacl_Poly1305_32_poly1305_mac(comp,in_len3,in3,key3);
  printf("Poly1305 (32-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp3[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp3[i] == comp[i]);
  if (ok) printf("Success!\n");

  Hacl_Poly1305_128_poly1305_mac(comp,in_len3,in3,key3);
  printf("Poly1305 (128-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp3[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp3[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  Hacl_Poly1305_256_poly1305_mac(comp,in_len3,in3,key3);
  printf("Poly1305 (256-bit) Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp3[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp3[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  ossl_poly1305(comp,in3,in_len3,key3);
  printf("OpenSSL Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp3[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp3[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");

  poly1305_impl(comp, in3, in_len3, key3);
  printf("Jasmin Result:\n");
  printf("computed:");
  for (int i = 0; i < 16; i++)
    printf("%02x",comp[i]);
  printf("\n");
  printf("expected:");
  for (int i = 0; i < 16; i++)
    printf("%02x",exp3[i]);
  printf("\n");
  ok = true;
  for (int i = 0; i < 16; i++)
    ok = ok & (exp3[i] == comp[i]);
  if (ok) printf("Success!\n");
  else printf("**FAILED**\n");
  
  uint8_t plain[SIZE];
  uint64_t res = 0;
  uint8_t tag[16];
  cycles a,b;
  clock_t t1,t2;
  uint64_t count = ROUNDS * SIZE;

  /*memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_64_poly1305_mac(plain,plain,SIZE,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_64_poly1305_mac(tag,plain,SIZE,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff1 = t2 - t1;
  cycles cdiff1 = b - a; */

  memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_32_poly1305_mac(plain,SIZE,plain,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_32_poly1305_mac(tag,SIZE,plain,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff2 = t2 - t1;
  cycles cdiff2 = b - a;

  memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_128_poly1305_mac(plain,SIZE,plain,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_128_poly1305_mac(tag,SIZE,plain,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff3 = t2 - t1;
  cycles cdiff3 = b - a;

  memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_256_poly1305_mac(plain,SIZE,plain,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_256_poly1305_mac(tag,SIZE,plain,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff4 = t2 - t1;
  cycles cdiff4 = b - a;


  /*memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_64_crypto_onetimeauth(plain,plain,SIZE,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_64_crypto_onetimeauth(tag,plain,SIZE,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff5 = t2 - t1;
  cycles cdiff5 = b - a; 


  memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_32_crypto_onetimeauth(tag,plain,SIZE,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    Hacl_Poly1305_32_crypto_onetimeauth(tag,plain,SIZE,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff6 = t2 - t1;
  cycles cdiff6 = b - a;
*/
  memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    ossl_poly1305(tag,plain,SIZE,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    ossl_poly1305(tag,plain,SIZE,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff7 = t2 - t1;
  cycles cdiff7 = b - a;

  
  memset(plain,'P',SIZE);
  memset(key,'K',16);
  for (int j = 0; j < ROUNDS; j++) {
    poly1305_impl(tag,plain,SIZE,key);
  }

  t1 = clock();
  a = cpucycles_begin();
  for (int j = 0; j < ROUNDS; j++) {
    poly1305_impl(tag,plain,SIZE,key);
    res ^= tag[0] ^ tag[15];
  }
  b = cpucycles_end();
  t2 = clock();
  clock_t tdiff8 = t2 - t1;
  cycles cdiff8 = b - a;
  

  
  /*printf("Poly1305 (64-bit) PERF:\n");
  printf("cycles for %" PRIu64 " bytes: %" PRIu64 " (%.2fcycles/byte)\n",count,(uint64_t)cdiff1,(double)cdiff1/count);
  printf("time for %" PRIu64 " bytes: %" PRIu64 " (%.2fus/byte)\n",count,(uint64_t)tdiff1,(double)tdiff1/count);
  printf("bw %8.2f MB/s\n",(double)count/(((double)tdiff1 / CLOCKS_PER_SEC) * 1000000.0)); */

  printf("Poly1305 (32-bit) PERF: %d\n",(int)res);
  printf("cycles for %" PRIu64 " bytes: %" PRIu64 " (%.2fcycles/byte)\n",count,(uint64_t)cdiff2,(double)cdiff2/count);
  printf("time for %" PRIu64 " bytes: %" PRIu64 " (%.2fus/byte)\n",count,(uint64_t)tdiff2,(double)tdiff2/count);
  printf("bw %8.2f MB/s\n",(double)count/(((double)tdiff2 / CLOCKS_PER_SEC) * 1000000.0));

  printf("Poly1305 (128-bit) PERF:\n");
  printf("cycles for %" PRIu64 " bytes: %" PRIu64 " (%.2fcycles/byte)\n",count,(uint64_t)cdiff3,(double)cdiff3/count);
  printf("time for %" PRIu64 " bytes: %" PRIu64 " (%.2fus/byte)\n",count,(uint64_t)tdiff3,(double)tdiff3/count);
  printf("bw %8.2f MB/s\n",(double)count/(((double)tdiff3 / CLOCKS_PER_SEC) * 1000000.0));

  printf("Poly1305 (256-bit) PERF:\n");
  printf("cycles for %" PRIu64 " bytes: %" PRIu64 " (%.2fcycles/byte)\n",count,(uint64_t)cdiff4,(double)cdiff4/count);
  printf("time for %" PRIu64 " bytes: %" PRIu64 " (%.2fus/byte)\n",count,(uint64_t)tdiff4,(double)tdiff4/count);
  printf("bw %8.2f MB/s\n",(double)count/(((double)tdiff4 / CLOCKS_PER_SEC) * 1000000.0));


  printf("OpenSSL Poly1305 (vec) PERF:\n");
  printf("cycles for %" PRIu64 " bytes: %" PRIu64 " (%.2fcycles/byte)\n",count,(uint64_t)cdiff7,(double)cdiff7/count);
  printf("time for %" PRIu64 " bytes: %" PRIu64 " (%.2fus/byte)\n",count,(uint64_t)tdiff7,(double)tdiff7/count);
  printf("bw %8.2f MB/s\n",(double)count/(((double)tdiff7 / CLOCKS_PER_SEC) * 1000000.0));

  printf("Jasmin Poly1305 (vec) PERF:\n");
  printf("cycles for %" PRIu64 " bytes: %" PRIu64 " (%.2fcycles/byte)\n",count,(uint64_t)cdiff8,(double)cdiff8/count);
  printf("time for %" PRIu64 " bytes: %" PRIu64 " (%.2fus/byte)\n",count,(uint64_t)tdiff8,(double)tdiff8/count);
  printf("bw %8.2f MB/s\n",(double)count/(((double)tdiff7 / CLOCKS_PER_SEC) * 1000000.0));

/*
  printf("Master Poly1305 (32-bit) PERF:\n");
  printf("cycles for %" PRIu64 " bytes: %" PRIu64 " (%.2fcycles/byte)\n",count,(uint64_t)cdiff6,(double)cdiff6/count);
  printf("time for %" PRIu64 " bytes: %" PRIu64 " (%.2fus/byte)\n",count,(uint64_t)tdiff6,(double)tdiff6/count);
  printf("bw %8.2f MB/s\n",(double)count/(((double)tdiff6 / CLOCKS_PER_SEC) * 1000000.0)); */

}
