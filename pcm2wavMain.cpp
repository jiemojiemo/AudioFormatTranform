#include <string>
#include <stdio.h>
#include <assert.h>
#include <Windows.h>
#include "pcm2wav.h"

int main()
{
	//Pcm2WavParameter info;
	//CPcm2Wav pcm2wav( "2_32float_44100.raw", "233445453.wav" );
	//info.channels	= 2;
	//info.formatTag	= 3;
	//info.sampleRate = 44100;
	//info.sampleBits = 32;
	//pcm2wav.Pcm2Wav( info );



	unsigned long fileSize;
	FILE* file = fopen("2_32float_44100.raw", "rb");
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	float* buffer = (float*)malloc(fileSize);
	fread(buffer, 1, fileSize, file);

	Pcm2WavParameter info;
	CPcm2Wav pcm2wav(buffer, fileSize, "2333333.wav");
	info.channels = 2;
	info.formatTag = 3;
	info.sampleRate = 44100;
	info.sampleBits = 32;
	pcm2wav.Pcm2Wav(info);
	free(buffer);
}



////----------------以下定义一些地址
//
////RIFF,资源交换标志
//#define RIFFID			0x00
////从下一个地址开始到文件尾的总字节数
//#define CHUNKE_SIZE		0x04
////WAVE, 代表WAV文件格式
//#define WAVE			0x08
////FMT,波形格式标志
//#define FMT				0x0c
////16或者18，18表示有额外信息
//#define SIZE			0x10
////为1时表示线性PCM编码，大于1时表示有压缩的编码
////WAVE_FORMAT_IEEE_FLOAT为32bit float准备
//#define AUDIO_FORMAT	0x14
////声道数
//#define CHANNELS		0x16
////采样率
//#define SAMPLE_RATE		0x18
////BYTE率=采样频率*音频通道数*每次采样得到的样本位数/8
//#define BYTE_RATE		0x1c
////块对齐=通道数*每次采样得到的样本位数/8
//#define BLOCKALIGN		0x20
////样本数据位数
//#define BITS_PER_SAMPLE	0x22
////data, 一个标示而已
//#define DATAID			0x24
////Wav文件实际音频数据所占大小
//#define DATA_SIZE		0x28
////实际数据开始处
//#define DATA_BEGIN		0x2c
//
//void dothat()
//{
//	const char* source_pcm = "p_1_16int_44100";
//	const char* out_wav = "out_p_1_16int_44100.wav";
//	int channel = 1;
//	int sample_rate = 44100;
//	int sample_bits = 32;
//	int format_tag = 3;	//WAVE_FORMAT_IEEE_FLOAT(3)
//	//PCM(1)
//	char word[5];
//	DWORD DWORD_num;		
//	WORD WORD_num;
//	FILE *fpS;
//	FILE *fpD;
//	int dataSize = 0;
//	float* dataBuffer = NULL;
//
//	fpS = fopen(source_pcm,"rb");
//	fpD = fopen(out_wav,"wb+");
//
//
//	//将文件指针指向文件尾巴
//	fseek( fpS, 0, SEEK_END );
//	//获取音频数据的实际大小
//	dataSize = ftell( fpS );
//	//还原文件指针位置
//	fseek( fpS, 0, SEEK_SET );
//
//	//写RIFF
//	fseek( fpD,RIFFID ,SEEK_SET );
//	strcpy(word,"RIFF");
//	fwrite( word, 1, 4, fpD );
//
//	//.....写CHUNKE_SIZE = 音频实际大小 + 文件头（44个字节） - 8
//	DWORD_num = dataSize + 0x2c - 8;
//	fseek( fpD, CHUNKE_SIZE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//写WAVE
//	strcpy(word,"WAVE");
//	fseek( fpD, WAVE, SEEK_SET );
//	fwrite( word, 1, 4, fpD );
//
//	//写FMT
//	strcpy(word,"fmt ");
//	fseek( fpD, FMT, SEEK_SET );
//	fwrite( word, 1, 4, fpD );
//
//	//写size(16 or 18)通常16
//	DWORD_num = 16;
//	fseek( fpD, SIZE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//写AudioFormat
//	WORD_num = format_tag;	//pcm数据
//	fseek( fpD, AUDIO_FORMAT, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//写声道数
//	WORD_num = channel;
//	fseek( fpD, CHANNELS, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//写采样率
//	DWORD_num = sample_rate;
//	fseek( fpD, SAMPLE_RATE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//写byte率 = 采样频率*音频通道数*每次采样得到的样本位数/8
//	DWORD_num = sample_rate * channel * sample_bits / 8;
//	fseek( fpD, BYTE_RATE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//写块对齐 块对齐=通道数*每次采样得到的样本位数/8
//	WORD_num = channel * sample_bits / 8;
//	fseek( fpD, BLOCKALIGN, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//写样本数据位
//	WORD_num = sample_bits;
//	fseek( fpD, BITS_PER_SAMPLE, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//写"DATA"
//	strcpy( word, "data" );
//	fseek( fpD, DATAID, SEEK_SET );
//	fwrite( word, 1, 4, fpD );
//
//	//写实际音频数据大小
//	DWORD_num = dataSize;
//	fseek( fpD, DATA_SIZE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//写实际的音频数据
//
//	//从文件读取音频数据
//	dataBuffer = (float*)malloc( dataSize );
//	assert( dataBuffer != NULL );
//	fseek( fpS, 0, SEEK_SET );
//	fread( dataBuffer, 1, dataSize, fpS );
//
//	fseek( fpD, DATA_BEGIN, SEEK_SET );
//	fwrite( dataBuffer, 1, dataSize, fpD ); 
//
//	if( dataBuffer != NULL )
//	{
//		free( dataBuffer );
//		dataBuffer = NULL;
//	}
//
//	fclose( fpS );
//	fclose( fpD );
//}

