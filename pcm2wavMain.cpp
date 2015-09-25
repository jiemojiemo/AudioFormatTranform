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



////----------------���¶���һЩ��ַ
//
////RIFF,��Դ������־
//#define RIFFID			0x00
////����һ����ַ��ʼ���ļ�β�����ֽ���
//#define CHUNKE_SIZE		0x04
////WAVE, ����WAV�ļ���ʽ
//#define WAVE			0x08
////FMT,���θ�ʽ��־
//#define FMT				0x0c
////16����18��18��ʾ�ж�����Ϣ
//#define SIZE			0x10
////Ϊ1ʱ��ʾ����PCM���룬����1ʱ��ʾ��ѹ���ı���
////WAVE_FORMAT_IEEE_FLOATΪ32bit float׼��
//#define AUDIO_FORMAT	0x14
////������
//#define CHANNELS		0x16
////������
//#define SAMPLE_RATE		0x18
////BYTE��=����Ƶ��*��Ƶͨ����*ÿ�β����õ�������λ��/8
//#define BYTE_RATE		0x1c
////�����=ͨ����*ÿ�β����õ�������λ��/8
//#define BLOCKALIGN		0x20
////��������λ��
//#define BITS_PER_SAMPLE	0x22
////data, һ����ʾ����
//#define DATAID			0x24
////Wav�ļ�ʵ����Ƶ������ռ��С
//#define DATA_SIZE		0x28
////ʵ�����ݿ�ʼ��
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
//	//���ļ�ָ��ָ���ļ�β��
//	fseek( fpS, 0, SEEK_END );
//	//��ȡ��Ƶ���ݵ�ʵ�ʴ�С
//	dataSize = ftell( fpS );
//	//��ԭ�ļ�ָ��λ��
//	fseek( fpS, 0, SEEK_SET );
//
//	//дRIFF
//	fseek( fpD,RIFFID ,SEEK_SET );
//	strcpy(word,"RIFF");
//	fwrite( word, 1, 4, fpD );
//
//	//.....дCHUNKE_SIZE = ��Ƶʵ�ʴ�С + �ļ�ͷ��44���ֽڣ� - 8
//	DWORD_num = dataSize + 0x2c - 8;
//	fseek( fpD, CHUNKE_SIZE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//дWAVE
//	strcpy(word,"WAVE");
//	fseek( fpD, WAVE, SEEK_SET );
//	fwrite( word, 1, 4, fpD );
//
//	//дFMT
//	strcpy(word,"fmt ");
//	fseek( fpD, FMT, SEEK_SET );
//	fwrite( word, 1, 4, fpD );
//
//	//дsize(16 or 18)ͨ��16
//	DWORD_num = 16;
//	fseek( fpD, SIZE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//дAudioFormat
//	WORD_num = format_tag;	//pcm����
//	fseek( fpD, AUDIO_FORMAT, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//д������
//	WORD_num = channel;
//	fseek( fpD, CHANNELS, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//д������
//	DWORD_num = sample_rate;
//	fseek( fpD, SAMPLE_RATE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//дbyte�� = ����Ƶ��*��Ƶͨ����*ÿ�β����õ�������λ��/8
//	DWORD_num = sample_rate * channel * sample_bits / 8;
//	fseek( fpD, BYTE_RATE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//д����� �����=ͨ����*ÿ�β����õ�������λ��/8
//	WORD_num = channel * sample_bits / 8;
//	fseek( fpD, BLOCKALIGN, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//д��������λ
//	WORD_num = sample_bits;
//	fseek( fpD, BITS_PER_SAMPLE, SEEK_SET );
//	fwrite( &WORD_num, 1, sizeof(WORD), fpD );
//
//	//д"DATA"
//	strcpy( word, "data" );
//	fseek( fpD, DATAID, SEEK_SET );
//	fwrite( word, 1, 4, fpD );
//
//	//дʵ����Ƶ���ݴ�С
//	DWORD_num = dataSize;
//	fseek( fpD, DATA_SIZE, SEEK_SET );
//	fwrite( &DWORD_num, 1, sizeof(DWORD), fpD );
//
//	//дʵ�ʵ���Ƶ����
//
//	//���ļ���ȡ��Ƶ����
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

