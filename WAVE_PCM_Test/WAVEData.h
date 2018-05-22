#pragma once

typedef unsigned long uint32_t;
typedef unsigned short uint16_t;

#pragma pack(1)

struct SWAVE_HEADER
{
	char chRIFF[4];//RIFF
	uint32_t ui32Size;//chunk Size
	char chWave[4];//Wave
};
struct SWAVE_FMT
{
	char chFMT[4];//FMT
	uint32_t ui32Size;//chunk size
	uint16_t ui16AudioFormat;//Audio Format
	uint16_t ui16AudioChannel;//Audio Channel
	uint32_t ui32AudioRate;//Audio Rate
	uint32_t ui32AudioByte;//per second Audio Byte
	uint16_t ui16BlockAlign;//Block Align
	uint16_t ui16BitAudio;//Bit per Audio
};
struct SWAVE_DATA
{
	char chData[4];
	uint32_t ui32Size;
};