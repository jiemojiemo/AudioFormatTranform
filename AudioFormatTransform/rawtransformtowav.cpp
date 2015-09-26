//
//  rawtransform.cpp
//  AudioFormatTransform
//
//  Created by meitu on 15/9/25.
//  Copyright © 2015年 meitu. All rights reserved.
//

#include "rawtransform.h"
#include "scopeguard.h"
#include <stdlib.h>
#include <assert.h>

typedef short WORD;
typedef unsigned int DWORD;


class RawTransformToWav::Impl
{
public:
    //Read data from the file to the memory
    //it will return a pointer which point the memory
    void* GetDataFromSourceFile(const string& sourceFile);
    
    //Open the file, the program will exit if it is failled
    FILE* OpenFile(const string& sourceFile, const string& mode);
    
    void  CloseFile(FILE* fd);
    
    //Get the total bytes of the file, for the memory alloc
    unsigned long GetFileSize(FILE* fd);
    
    //alloc memory, the program will exit if it is failed
    void* MemoryAlloc(unsigned long totalBytes);
    
    void WriteResultToFile(void* data, const string& resultFileName);
    //RIFF Chunk
    void WriteRIFFChunk();
    void WriteRIFFID();
    void WriteRIFFChunkSize();
    void WriteWAVEID();
    //FMT  Chunk
    void WriteFMTChunk();
    void WriteFMTID();
    void WriteFMTChunkSize();
    void WriteFormatTag();
    void WriteChannels();
    void WriteSampleRate();
    void WriteDataRate();
    void WriteBlockAlign();
    void WriteBitsPerSample();
    //Data Chunk
    void WriteDataChunk(void* data);
    void WriteDataID();
    void WriteDataSize();
    void WriteAudioData(void* data);
    
    void WriteSomeData( const void* data, unsigned int size );
public:
    Impl(const TransformParameter& params);
    unsigned long m_bufferSize;
    FILE* m_fd;
    unsigned long m_outFdIndex;
    TransformParameter m_params;
};

RawTransformToWav::Impl::Impl(const TransformParameter& params):m_params(params),
m_bufferSize(0), m_fd(nullptr),m_outFdIndex(0)
{
    
}

void* RawTransformToWav::Impl::GetDataFromSourceFile(const string& sourceFile)
{
    auto fd = OpenFile( sourceFile,"rb" );
    ON_SCOPE_EXIT([&](){CloseFile(fd);});
    
    auto totalBytes = GetFileSize(fd);
    auto buffer = MemoryAlloc(totalBytes);
    
    //get data from souce file to memory
    fread(buffer, 1, totalBytes, fd);
    
    return buffer;
    return nullptr;
}


FILE* RawTransformToWav::Impl::OpenFile(const string& sourceFile, const string& mode)
{
    auto fd = fopen(sourceFile.c_str(), mode.c_str());
    if(fd == nullptr)
    {
        fprintf(stderr, "Error:Cannot open the file.\n");
        _exit(-1);
    }
    return fd;
}

void  RawTransformToWav::Impl::CloseFile(FILE* fd)
{
    if( fd != nullptr )
    {
        fclose(fd);
    }
}

unsigned long RawTransformToWav::Impl::GetFileSize(FILE* fd)
{
    fseek(fd,0,SEEK_END);
    m_bufferSize = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    return m_bufferSize;
}

void* RawTransformToWav::Impl::MemoryAlloc(unsigned long totalBytes)
{
    auto buffer = malloc(totalBytes);
    
    if(buffer == nullptr)
    {
        fprintf(stderr, "Error:Cannot alloc enouth memory.\n");
        _exit(-1);
    }
    
    return buffer;
}


void RawTransformToWav::Impl::WriteResultToFile(void* data, const string& resultFileName)
{
    
    m_fd = OpenFile(resultFileName, "wb");
    ON_SCOPE_EXIT([&](){fclose(m_fd);});
    m_outFdIndex = 0;
    
    WriteRIFFChunk();
    WriteFMTChunk();
    WriteDataChunk( data );
}

//RIFF Chunk
void RawTransformToWav::Impl::WriteRIFFChunk()
{
    WriteRIFFID();
    WriteRIFFChunkSize();
    WriteWAVEID();
}
void RawTransformToWav::Impl::WriteRIFFID()
{
    const char *riffID = "RIFF";
    WriteSomeData(riffID, 4);
    
}
void RawTransformToWav::Impl::WriteRIFFChunkSize()
{
    DWORD chunkSize = m_bufferSize + 0x2c - 8;
    WriteSomeData(&chunkSize, sizeof(chunkSize));
}
void RawTransformToWav::Impl::WriteWAVEID()
{
    const char* waveID = "WAVE";
    WriteSomeData( waveID,4  );
}
//FMT  Chunk
void RawTransformToWav::Impl::WriteFMTChunk()
{
    WriteFMTID();
    WriteFMTChunkSize();
    WriteFormatTag();
    WriteChannels();
    WriteSampleRate();
    WriteDataRate();
    WriteBlockAlign();
    WriteBitsPerSample();
}
void RawTransformToWav::Impl::WriteFMTID()
{
    const char* fmt = "fmt ";
    WriteSomeData( fmt, 4);
}
void RawTransformToWav::Impl::WriteFMTChunkSize()
{
    DWORD chunkSize = 16;
    WriteSomeData( &chunkSize,sizeof(chunkSize) );
}
void RawTransformToWav::Impl::WriteFormatTag()
{
    WORD formatTag = m_params.formatTag;
    WriteSomeData(&formatTag, sizeof(formatTag));
}
void RawTransformToWav::Impl::WriteChannels()
{
    WORD channels = m_params.nChannels;
    WriteSomeData(&channels, sizeof(channels));
}
void RawTransformToWav::Impl::WriteSampleRate()
{
    DWORD sampleRate = m_params.sampleRate;
    WriteSomeData(&sampleRate, sizeof(sampleRate));
}
void RawTransformToWav::Impl::WriteDataRate()
{
    DWORD dataRate = m_params.sampleRate * m_params.nChannels * m_params.sampleBits / 8;
    WriteSomeData(&dataRate, sizeof(dataRate));
}
void RawTransformToWav::Impl::WriteBlockAlign()
{
    WORD blockAlign = m_params.nChannels * m_params.sampleBits / 8;
    WriteSomeData(&blockAlign, sizeof(blockAlign));
}
void RawTransformToWav::Impl::WriteBitsPerSample()
{
    WORD bits = m_params.sampleBits;
    WriteSomeData(&bits, sizeof(bits));
}
//Data Chunk
void RawTransformToWav::Impl::WriteDataChunk(void* data)
{
    assert(data != nullptr);
    WriteDataID();
    WriteDataSize();
    WriteAudioData( data );
}
void RawTransformToWav::Impl::WriteDataID()
{
    const char* data = "data";
    WriteSomeData(data, 4);
}
void RawTransformToWav::Impl::WriteDataSize()
{
    assert(m_bufferSize > 0);
    WriteSomeData(&m_bufferSize, sizeof(m_bufferSize));
}
void RawTransformToWav::Impl::WriteAudioData(void* data)
{
    assert(m_bufferSize > 0);
    WriteSomeData(data, m_bufferSize);
}

void RawTransformToWav::Impl::WriteSomeData( const void* data, unsigned int size )
{
    fseek(m_fd, m_outFdIndex, SEEK_SET);
    fwrite(data, 1, size, m_fd);
    m_outFdIndex += size;
}


RawTransformToWav::RawTransformToWav(const TransformParameter& params):m_Impl(new Impl(params))
{

}


void RawTransformToWav::doTransform(const string &sourceFileName, const string &resultFileName)
{
    assert(sourceFileName != "");
    assert(resultFileName != "");
    
    //open the source file and get data
    auto data = m_Impl->GetDataFromSourceFile(sourceFileName);
    ON_SCOPE_EXIT([&](){free(data);});
    
    //do transform
    //..raw to wav do not need transform
    
    //write the result to the file
    m_Impl->WriteResultToFile(data,resultFileName);
}

void RawTransformToWav::doTransform(const string &sourceFileNmae)
{
    assert(sourceFileNmae != "");
    
}



























