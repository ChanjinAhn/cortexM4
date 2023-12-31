#ifndef AES_H
#define AES_H

#ifndef WINAPI
#define WINAPI
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef unsigned char* LPBYTE;
typedef const unsigned char* LPCBYTE;
#define VOID void
#define CONST const
#endif // WINAPI

#define LOCAL(type) static type

#define CBC     1
#define ECB     1
#define AES128  1
//#define AES192 1
//#define AES256 1

#if ECB
VOID AES_ECB_Encrypt(LPCBYTE Input, LPCBYTE Key, LPBYTE Output, int Length);
VOID AES_ECB_Decrypt(LPCBYTE Input, LPCBYTE Key, LPBYTE Output, int Length);
#endif

#if CBC
VOID AES_CBC_Encrypt(LPBYTE Output, LPBYTE Input, int Length, LPCBYTE Key, LPCBYTE Iv);
VOID AES_CBC_Decrypt(LPBYTE Output, LPCBYTE Input, int Length, LPCBYTE Key, LPCBYTE Iv);
#endif

#endif // AES_H
