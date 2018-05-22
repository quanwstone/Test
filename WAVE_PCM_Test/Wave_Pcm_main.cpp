#include<stdio.h>
#include<Windows.h>
#include"WAVEData.h"
/*
通过解析wave文件，获取PCM文件，并且正常播放
播放48kHz 单声道 16bit的xxx.pcm的PCM文件为例
$ ffplay -ar 48000 -channels 1 -f s16le -i xxx.pcm
*/
uint16_t LittleByteConvShort(char *in_Data)
{
	uint16_t ulSize = 0;
	
	if (!in_Data)
		printf("LittleByteConvShort faile\n");

	ulSize = uint16_t((*(in_Data + 1) & 0xFF )<<8 |
					  (*(in_Data + 0) & 0xFF )<<0);

	return ulSize;
}
uint32_t LittleByteConvlong(char *in_Data)
{
	uint32_t ulSize = 0;

	if (!in_Data)
		printf("LittleByteConvlong faile\n");

	ulSize = uint32_t((*(in_Data + 3) & 0xFF ) << 24 |
					  (*(in_Data + 2) & 0xFF ) << 16 | 
					  (*(in_Data + 1) & 0xFF ) << 8  |
					  (*(in_Data + 0) & 0xFF ) << 0);
	
	return ulSize;
}
void ParseBuf(char *in_chData)
{
	if (!in_chData)
		printf("in_chData faile\n");
	
	SWAVE_HEADER sWAVE_HEADER;
	SWAVE_FMT sWAVE_FMT;

	//Header Chunk
	//riff
	if (*in_chData == 0x52 && *(in_chData + 1) == 0x49 &&
		*(in_chData + 2) == 0x46 && *(in_chData + 3) == 0x46)
	{
		memcpy_s(sWAVE_HEADER.chRIFF,4,in_chData,4);
		in_chData += 4;
	}
	
	sWAVE_HEADER.ui32Size = LittleByteConvlong(in_chData);
	in_chData += 4;
	
	//wave
	if (*(in_chData)==0x57 &&*(in_chData + 1)==0x41&&
		*(in_chData + 2)==0x56 &&*(in_chData +3)==0x45)
	{
		memcpy_s(sWAVE_HEADER.chWave, 4,in_chData, 4);
		in_chData += 4;
	}
	printf("chIFF = %s\r\n \
			chunksize = %ld\r\n \
			chWAVE = %s\r\n",
		sWAVE_HEADER.chRIFF, 
		sWAVE_HEADER.ui32Size,
		sWAVE_HEADER.chWave);
	//Format Chunk
	//fmt
	if (*(in_chData)==0x66 && *(in_chData + 1)==0x6d 
		&& *(in_chData + 2)==0x74 && *(in_chData + 3)==0x20)
	{
		memcpy_s(sWAVE_FMT.chFMT,4, in_chData, 4);
		in_chData += 4;
	}
	//Chunk Size
	sWAVE_FMT.ui32Size = LittleByteConvlong(in_chData);
	in_chData += 4;

	//Audio Format
	sWAVE_FMT.ui16AudioFormat = LittleByteConvShort(in_chData);
	in_chData += 2;

	//Audio Channel
	sWAVE_FMT.ui16AudioChannel = LittleByteConvShort(in_chData);
	in_chData += 2;

	//Audio Rate
	sWAVE_FMT.ui32AudioRate = LittleByteConvlong(in_chData);
	in_chData += 4;

	//Audio Bytes
	sWAVE_FMT.ui32AudioByte = LittleByteConvlong(in_chData);
	in_chData += 4;

	//Block Algin
	sWAVE_FMT.ui16BlockAlign = LittleByteConvShort(in_chData);
	in_chData += 2;

	//Bit 
	sWAVE_FMT.ui16BitAudio = LittleByteConvShort(in_chData);
	in_chData += 2;
	printf("Fmt = %s\r\n\
			ChunkSize = %ld\r\n\
			AudioFormat = %d\r\n\
			Audio Channel =%d\r\n\
			Audio Rate = %ld\r\n\
			Audio Bytes = %ld\r\n\
			Block Algin = %d\r\n\
			Bit = %d\r\n",
		sWAVE_FMT.chFMT,
		sWAVE_FMT.ui32Size,
		sWAVE_FMT.ui16AudioFormat,
		sWAVE_FMT.ui16AudioChannel,
		sWAVE_FMT.ui32AudioRate,
		sWAVE_FMT.ui32AudioByte,
		sWAVE_FMT.ui16BlockAlign,
		sWAVE_FMT.ui16BitAudio);
}
int main(int argc, char*argv[])
{
	FILE *pIn = nullptr;
	FILE *pLeft = nullptr;

	errno_t er = fopen_s(&pIn, "Test.wav", "rb+");
	er = fopen_s(&pLeft, "Left.pcm", "wb+");

	char chbuf[36] = {0};
	
	size_t sre = fread_s(chbuf, 36, 1, 36, pIn);
	if (sre != 36)
	{
		printf("fread faile\n");
	}
	
	ParseBuf(chbuf);

	_fseeki64(pIn, 4096, SEEK_SET);

	char ch_Readbuf[4] = {0};
	while (!feof(pIn))
	{
		fread_s(ch_Readbuf, 4, 1, 4, pIn);
		fwrite(ch_Readbuf, 2, 1, pLeft);
	}
	fclose(pIn);
	fclose(pLeft);
	
	pIn = nullptr;
	pLeft = nullptr;

	return 0;
}