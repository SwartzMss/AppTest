#include "RSATest.h"

const char  *_base64_encode_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const signed char _base64_decode_chars[] =
{
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, 62, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
	-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63, -1, 26,
	27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};


void CreateKey()
{
	/* 生成公钥 */
	RSA* rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	BIO *bp = BIO_new(BIO_s_file());
	BIO_write_filename(bp, "public.pem");
	PEM_write_bio_RSAPublicKey(bp, rsa);
	BIO_free_all(bp);

	/* 生成私钥 */
	char passwd[] = "1234";
	bp = BIO_new_file("private.pem", "w+");
	PEM_write_bio_RSAPrivateKey(bp, rsa, EVP_des_ede3_ofb(), (unsigned char*)passwd, 4, NULL, NULL);
	BIO_free_all(bp);
	RSA_free(rsa);
}

std::string DecryptData(string data)
{
	OpenSSL_add_all_algorithms();

	BIO* bp = BIO_new(BIO_s_file());

	long lRet = BIO_read_filename(bp, "private.pem");

	char passwd[] = "1234";
	RSA* rsaK = PEM_read_bio_RSAPrivateKey(bp, NULL, NULL, passwd);
	if (NULL == rsaK)
	{
		perror("read key file fail!");
	}
	else{
		printf("read success!\n");
	}
	int nLen = RSA_size(rsaK);
	char *pEncode = new char[2048];
	int len = data.length();
	int ret = RSA_private_decrypt(len, (const unsigned char*)data.c_str(), (unsigned char *)pEncode, rsaK, RSA_PKCS1_PADDING);
	std::string strRet;
	if (ret >= 0)
	{
		strRet = std::string(pEncode, ret);
	}

	delete[] pEncode;
	CRYPTO_cleanup_all_ex_data();
	BIO_free_all(bp);
	RSA_free(rsaK);
	return strRet;
}

std::string EncryptData(string data)
{
	OpenSSL_add_all_algorithms();
	BIO* bp = BIO_new(BIO_s_file());
	BIO_read_filename(bp, "public.pem");
	RSA* rsaK = PEM_read_bio_RSAPublicKey(bp, NULL, NULL, NULL);
	RSA_print_fp(stdout, rsaK, 0);

	if (NULL == rsaK)
	{
		perror("read key file fail!");
	}
	else
	{
		printf("read success!");
		int nLen = RSA_size(rsaK);
		printf("len:%d\n", nLen);
	}
	int nLen = RSA_size(rsaK);
	char *pEncode = new char[nLen + 1];
	memset(pEncode, 0, nLen + 1);
	int ret = RSA_public_encrypt(data.length(), (const unsigned char*)data.c_str(),
		(unsigned char *)pEncode, rsaK, RSA_PKCS1_PADDING);
	std::string strRet;
	if (ret >= 0)
	{
		strRet = std::string(pEncode, ret);
	}
	delete[] pEncode;
	CRYPTO_cleanup_all_ex_data();
	BIO_free_all(bp);
	RSA_free(rsaK);
	return strRet;

}

std::string ReadPublicKey()
{
	//尚未生成key
	if (-1 == access("public.pem", 0))
	{
		CreateKey();
	}
	ifstream file("public.pem");
	std::string tsum, ss;
	std::string keyb = "-----BEGIN RSA PUBLIC KEY-----";
	std::string keye = "-----END RSA PUBLIC KEY-----";
	while (getline(file, ss))
	{
		if (ss == keyb || ss == keye)
		{
			continue;
		}
		tsum.append(ss);
	}
	return tsum;
}


int Base64Encode(const char* pInputBuf, int nInputBufLen, char* pOutputBuf)
{
	unsigned char c1;
	unsigned char c2;
	unsigned char c3;
	int     i = 0;
	int     index = 0;

	if ((NULL == pInputBuf) || (NULL == pOutputBuf))
	{
		return -1;
	}

	while (i < nInputBufLen)
	{
		/* read the first byte */
		c1 = pInputBuf[i++];
		if (i == nInputBufLen)         ///< pad with "="
		{
			pOutputBuf[index++] = _base64_encode_chars[c1 >> 2];
			pOutputBuf[index++] = _base64_encode_chars[(c1 & 0x3) << 4];
			pOutputBuf[index++] = '=';
			pOutputBuf[index++] = '=';
			break;
		}

		/* read the second byte */
		c2 = pInputBuf[i++];
		if (i == nInputBufLen)        ///< pad with "="
		{
			pOutputBuf[index++] = _base64_encode_chars[c1 >> 2];
			pOutputBuf[index++] = _base64_encode_chars[((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4)];
			pOutputBuf[index++] = _base64_encode_chars[(c2 & 0xF) << 2];
			pOutputBuf[index++] = '=';
			break;
		}

		/* read the third byte */
		c3 = pInputBuf[i++];

		/* convert into four bytes string */
		pOutputBuf[index++] = _base64_encode_chars[c1 >> 2];
		pOutputBuf[index++] = _base64_encode_chars[((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4)];
		pOutputBuf[index++] = _base64_encode_chars[((c2 & 0xF) << 2) | ((c3 & 0xC0) >> 6)];
		pOutputBuf[index++] = _base64_encode_chars[c3 & 0x3F];
	}

	return index;
}


int Base64Decode(const char *pInputBuf, int nInputBufLen, char *pOutputBuf)
{
	signed char c1, c2, c3, c4;
	int     	i = 0;
	int     	index = 0;

	while (i < nInputBufLen)
	{
		// read the first byte
		do
		{
			c1 = _base64_decode_chars[(int)pInputBuf[i++]];
		} while ((i < nInputBufLen) && (c1 == -1));

		if (c1 == -1)
		{
			break;
		}

		// read the second byte
		do
		{
			c2 = _base64_decode_chars[(int)pInputBuf[i++]];
		} while ((i < nInputBufLen) && (c2 == -1));

		if (c2 == -1)
		{
			break;
		}

		// assamble the first byte
		pOutputBuf[index++] = (char)((c1 << 2) | ((c2 & 0x30) >> 4));

		// read the third byte
		do
		{
			c3 = pInputBuf[i++];
			if (c3 == 61)  // meet with "=", break
			{
				return index;
			}

			c3 = _base64_decode_chars[(int)c3];
		} while ((i < nInputBufLen) && (c3 == -1));

		if (c3 == -1)
		{
			break;
		}

		// assabmel the second byte
		pOutputBuf[index++] = (char)(((c2 & 0XF) << 4) | ((c3 & 0x3C) >> 2));

		// read the fourth byte
		do
		{
			c4 = pInputBuf[i++];
			if (c4 == 61)  // meet with "=", break
			{
				return index;
			}

			c4 = _base64_decode_chars[(int)c4];
		} while ((i < nInputBufLen) && (c4 == -1));

		if (c4 == -1)
		{
			break;
		}

		// assamble the third byte
		pOutputBuf[index++] = (char)(((c3 & 0x03) << 6) | c4);
	}

	return index;
}