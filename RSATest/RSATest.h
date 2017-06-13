#ifndef RSATEST_H
#define RSATEST_H

#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace  std;
//������Կ����Կ
void CreateKey();
//����
std::string DecryptData(string data);
//	����
std::string EncryptData(string data);
//��ȡ��Կ���ַ�
std::string ReadPublicKey();



/* BASE64�����㷨ʵ�� */
int	Base64Encode(const char* pInputBuf, int nInputBufLen, char* pOutputBuf);
/* BASE64�����㷨ʵ�� */
int	Base64Decode(const char *pInputBuf, int nInputBufLen, char *pOutputBuf);

#endif // RSATEST_H
