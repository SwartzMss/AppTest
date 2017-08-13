#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <stdlib.h>
#include <iconv.h>		

using	 namespace std;
#define MAX_BUF_SIZE 1024

int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen,
	char *outbuf, size_t outlen) {
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
		return -1;
	iconv_close(cd);
	*pout = '\0';

	return 0;
}

int utf8_to_gbk(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("utf-8", "gbk", inbuf, inlen, outbuf, outlen);
}

int gbk_to_utf8(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("gbk", "utf-8", inbuf, inlen, outbuf, outlen);
}

void read_file(char buf[], const int32_t max_buf_size, const char *file_name)
{
	FILE* pFile;
	long lSize;
	size_t result;
	pFile =fopen(file_name, "rb");
	if (pFile == NULL) { fputs("File error\n", stderr); exit(1); }
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	if (lSize >= max_buf_size){ fputs("file too large\n", stderr); exit(1); }
	result = fread(buf, 1, lSize, pFile);
	if (result != lSize) { fputs("Reading error\n", stderr); exit(3); }
	fclose(pFile);
}

int main(int argc, char *argv[])
{
	char in_buf[MAX_BUF_SIZE] = { 0 }, out_buf[MAX_BUF_SIZE] = { 0 };
	read_file(in_buf, MAX_BUF_SIZE, "chinese_utf8.txt");
	printf("%s\n", in_buf);
	utf8_to_gbk(in_buf, strlen(in_buf), out_buf, MAX_BUF_SIZE);
	printf("%s\n", out_buf);
	read_file(in_buf, MAX_BUF_SIZE, "chinese_gbk.txt");
	printf("%s\n", in_buf);
	gbk_to_utf8(in_buf, strlen(in_buf), out_buf, MAX_BUF_SIZE);
	printf("%s\n", out_buf);
	return 0;
}

