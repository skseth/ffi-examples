#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

#include "aes_whitebox.h"


static void err_quit(const char *fmt, ...) {
  va_list ap;
  char buf[1024];

  va_start(ap, fmt);
  vsprintf(buf, fmt, ap);
  strcat(buf, "\n");
  fputs(buf, stderr);
  fflush(stderr);
  va_end(ap);

  exit(1);
}

void tallymarker_hextobin(const char * str, uint8_t * bytes, size_t blen)
{
   uint8_t  pos;
   uint8_t  idx0;
   uint8_t  idx1;

   // mapping of ASCII characters to hex values
   const uint8_t hashmap[] =
   {
     0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 01234567
     0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89:;<=>?
     0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, // @ABCDEFG
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // HIJKLMNO
   };

   memset(bytes, 0, blen);
   for (pos = 0; ((pos < (blen*2)) && (pos < strlen(str))); pos += 2)
   {
      idx0 = ((uint8_t)str[pos+0] & 0x1F) ^ 0x10;
      idx1 = ((uint8_t)str[pos+1] & 0x1F) ^ 0x10;
      bytes[pos/2] = (uint8_t)(hashmap[idx0] << 4) | hashmap[idx1];
   };
}

static void read_hex(const char *in, uint8_t* v, size_t size, const char* param_name) {
  if (strlen(in) != size << 1) {
    err_quit("Invalid param %s (got %d, expected %d)",
        param_name, strlen(in), size << 1);
  }

  tallymarker_hextobin(in, v, size);

/*
  for (size_t i = 0; i < size; i++) {
    sscanf(in + i * 2, "%2hhx", v + i);
  }*/
}


static void write_hex(const char *title, uint8_t* v, size_t size) {
  printf("%s\n\n", title);

  for (int i = 0; i < size; i++)
  {
      if (i > 0) printf(":");
      printf("%02X", v[i]);
  }
  printf("\n");
}

void syntax(const char* program_name) {
  err_quit("Syntax: %s <cfb|ofb|ctr>"
      " <hex-plain>"
      " <hex-ir-or-nonce>"
      " <hex-cipher>", program_name);
}

#define BUF_SIZE 1024
static const char CFB_IV[] = "000102030405060708090a0b0c0d0e0f";
static const char CFB_PLAIN[] = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710";
static const char CFB_CIPHER[] = "dc7e84bfda79164b7ecd8486985d386039ffed143b28b1c832113c6331e5407bdf10132415e54b92a13ed0a8267ae2f975a385741ab9cef82031623d55b1e471";

/* AEAD_AES_256_GCM */

int main() {
  uint8_t plain[4*16], iv_or_nonce[16], cipher[4*16], output[4*16];

  printf("%s\n", CFB_PLAIN);

  read_hex(CFB_PLAIN, plain, 4*16, "plain");
  read_hex(CFB_IV, iv_or_nonce, 16, "iv-or-nonce");
  read_hex(CFB_CIPHER, cipher, 4*16, "cipher");
  
  write_hex("Plain:", plain, 64);
  aes_whitebox_encrypt_cfb(iv_or_nonce, plain, sizeof(plain), output);

  write_hex("Encrypted:", output, 64);

  aes_whitebox_decrypt_cfb(iv_or_nonce, cipher, sizeof(cipher), output);
  write_hex("Decrypted:", output, 64);

  return 0;
}

int read_string() {
  char buffer[BUF_SIZE];
  size_t contentSize = 1; // includes NULL

  /* Preallocate space.  We could just allocate one char here, 
  but that wouldn't be efficient. */
  char *content = malloc(sizeof(char) * BUF_SIZE);
  if(content == NULL)
  {
      perror("Failed to allocate content");
      exit(1);
  }
  content[0] = '\0'; // make null-terminated
  while(fgets(buffer, BUF_SIZE, stdin))
  {
      char *old = content;
      contentSize += strlen(buffer);
      content = realloc(content, contentSize);
      if(content == NULL)
      {
          perror("Failed to reallocate content");
          free(old);
          exit(2);
      }
      strcat(content, buffer);
  }

  if(ferror(stdin))
  {
      free(content);
      perror("Error reading from stdin.");
      exit(3);
  }

  printf("Content : %s\n", content);

  return 0;
}