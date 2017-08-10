#include "RSATest.h"

int main()
{
	CreateKey();	
	string strdata = "swartz";
	char    pBufKey[1024] = { 0 };
	int nlen = Base64Encode(strdata.c_str(), strdata.length(), pBufKey);
	strdata = string(pBufKey, nlen);
	string m_strdata = EncryptData(strdata);
	nlen = Base64Encode(m_strdata.c_str(), m_strdata.length(), pBufKey);
	m_strdata = string(pBufKey, nlen);
	
	nlen = Base64Decode(m_strdata.c_str(), m_strdata.length(), pBufKey);
	m_strdata = string(pBufKey, nlen);
	strdata = DecryptData(m_strdata);
	nlen = Base64Decode(strdata.c_str(), strdata.length(), pBufKey);
	strdata = string(pBufKey, nlen);
	cout<<strdata<<endl;
}
