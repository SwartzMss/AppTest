#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "turbojpeg.h"

using namespace std;

int tjpeg_header(unsigned char* jpeg_buffer, int jpeg_size, int* width, int* height, int* subsample, int* colorspace)
{
	tjhandle handle = NULL;

	handle = tjInitDecompress();
	tjDecompressHeader3(handle, jpeg_buffer, jpeg_size, width, height, subsample, colorspace);

	tjDestroy(handle);

	return 0;
}

int tjpeg2rgb(unsigned char* jpeg_buffer, int jpeg_size,  unsigned char* rgb_buffer, int* size)
{
	tjhandle handle = NULL;
	int width, height, subsample, colorspace;
	int flags = 0;
	int pixelfmt = TJPF_RGB;

	handle = tjInitDecompress();
	tjDecompressHeader3(handle, jpeg_buffer, jpeg_size, &width, &height, &subsample, &colorspace);

	flags |= 0;
	tjDecompress2(handle, jpeg_buffer, jpeg_size, rgb_buffer, width, 0,
		height, pixelfmt, flags);

	tjDestroy(handle);

	return 0;
}

int trgb2jpeg(unsigned char* rgb_buffer, int width, int height, int quality, unsigned char** jpeg_buffer, unsigned long* jpeg_size)
{
	tjhandle handle = NULL;
	//unsigned long size=0;
	int flags = 0;
	int subsamp = TJSAMP_422;
	int pixelfmt = TJPF_RGB;

	handle = tjInitCompress();
	//size=tjBufSize(width, height, subsamp);
	tjCompress2(handle, rgb_buffer, width, 0, height, pixelfmt, jpeg_buffer, jpeg_size, subsamp,
		quality, flags);

	tjDestroy(handle);

	return 0;
}

int tjpeg2yuv(unsigned char* jpeg_buffer, int jpeg_size, unsigned char** yuv_buffer, int* yuv_size, int* yuv_type, int& width, int &height)
{
	tjhandle handle = NULL;
	int  subsample, colorspace;
	int flags = 0;
	int padding = 1; // 1或4均可，但不能是0
	int ret = 0;

	handle = tjInitDecompress();
	tjDecompressHeader3(handle, jpeg_buffer, jpeg_size, &width, &height, &subsample, &colorspace);

	printf("w: %d h: %d subsample: %d color: %d\n", width, height, subsample, colorspace);

	flags |= 0;

	*yuv_type = subsample;
	// 注：经测试，指定的yuv采样格式只对YUV缓冲区大小有影响，实际上还是按JPEG本身的YUV格式来转换的
	*yuv_size = tjBufSizeYUV2(width, padding, height, subsample);
	*yuv_buffer = (unsigned char *)malloc(*yuv_size);
	if (*yuv_buffer == NULL)
	{
		printf("malloc buffer for rgb failed.\n");
		return -1;
	}

	ret = tjDecompressToYUV2(handle, jpeg_buffer, jpeg_size, *yuv_buffer, width,
		padding, height, flags);
	if (ret < 0)
	{
		printf("compress to jpeg failed: %s\n", tjGetErrorStr());
	}
	tjDestroy(handle);

	return ret;
}

int tyuv2jpeg(unsigned char* yuv_buffer, int yuv_size, int width, int height, int subsample, unsigned char** jpeg_buffer, unsigned long* jpeg_size, int quality)
{
	tjhandle handle = NULL;
	int flags = 0;
	int padding = 1; // 1或4均可，但不能是0
	int need_size = 0;
	int ret = 0;

	handle = tjInitCompress();

	flags |= 0;

	need_size = tjBufSizeYUV2(width, padding, height, subsample);
	if (need_size != yuv_size)
	{
		printf("we detect yuv size: %d, but you give: %d, check again.\n", need_size, yuv_size);
		return 0;
	}

	ret = tjCompressFromYUV(handle, yuv_buffer, width, padding, height, subsample, jpeg_buffer, jpeg_size, quality, flags);
	if (ret < 0)
	{
		printf("compress to jpeg failed: %s\n", tjGetErrorStr());
	}

	tjDestroy(handle);

	return ret;
}

int main(int argc, char* argv[])
{

	FILE* fp;
	fp = fopen("1.jpeg", "rb");
	fseek(fp, 0, SEEK_END);
	int nlength = ftell(fp);
	unsigned char*szbuf = new unsigned char[nlength + 1];
	fseek(fp, 0, SEEK_SET);
	fread(szbuf, nlength, 1, fp);
	fclose(fp);

	unsigned char* szbuf1=NULL;
	int nsize = 0;
	int yuv_type = 0;
	int nwidth = 0;
	int nheight = 0;
	tjpeg2yuv(szbuf, nlength, &szbuf1, &nsize, &yuv_type, nwidth, nheight);
	delete[]szbuf;

	fp = fopen("2.yuv", "wb");
	fwrite(szbuf1, 1, nsize, fp);
	fclose(fp);

	unsigned char* szbuf2=NULL /*= new unsigned char[nsize + 1]*/;
	unsigned long ulsize = 0;
	tyuv2jpeg(szbuf1, nsize, nwidth, nheight, yuv_type, &szbuf2, &ulsize, 100);

	fp = fopen("3.jpeg", "wb");
	fwrite(szbuf2, 1, ulsize, fp);
	fclose(fp);
	delete[] szbuf2;
	delete[] szbuf1;
	return 0;
}

