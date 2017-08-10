#ifndef RSATEST_H
#define RSATEST_H

#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace  std;
//产生公钥和密钥
void CreateKey();
//解密
std::string DecryptData(string data);
//	加密
std::string EncryptData(string data);
//获取公钥的字符
std::string ReadPublicKey();



/* BASE64加密算法实现 */
int	Base64Encode(const char* pInputBuf, int nInputBufLen, char* pOutputBuf);
/* BASE64解密算法实现 */
int	Base64Decode(const char *pInputBuf, int nInputBufLen, char *pOutputBuf);

#endif // RSATEST_H
