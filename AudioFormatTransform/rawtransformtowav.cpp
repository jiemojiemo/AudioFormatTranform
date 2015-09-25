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
typedef unsigned long DWORD;


class RawTransformToWav::Impl
{
public:
    unsigned long m_bufferSize;
public:
    //Read data from the file to the memory
    //it will return a pointer which point the memory
    void* GetDataFromSourceFile(const string& sourceFile);
    
    //Open the file, the program will exit if it is failled
    FILE* OpenFile(const string& sourceFile);
    
    void  CloseFile(FILE* fd);
    
    //Get the total bytes of the file, for the memory alloc
    unsigned long GetFileSize(FILE* fd);
    
    //alloc memory, the program will exit if it is failed
    void* MemoryAlloc(unsigned long totalBytes);
    
    void WriteResultToFile(const string& resultFileName);
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
    void WriteDataChunk();
    void WriteDataID();
    void WriteDataSize();
    void WriteAudioData();
    
    void WriteSomeData( const void* data, unsigned int size );
};

void* RawTransformToWav::Impl::GetDataFromSourceFile(const string& sourceFile)
{
    auto fd = OpenFile( sourceFile );
    ON_SCOPE_EXIT([&](){CloseFile(fd);});
    
    auto totalBytes = GetFileSize(fd);
    auto buffer = MemoryAlloc(totalBytes);
    
    //get data from souce file to memory
    fread(buffer, 1, totalBytes, fd);
    
    return buffer;
    return nullptr;
}


FILE* RawTransformToWav::Impl::OpenFile(const string& sourceFile)
{
    auto fd = fopen(sourceFile.c_str(), "rb");
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


void RawTransformToWav::Impl::WriteResultToFile(const string& resultFileName)
{
    auto fd = OpenFile(resultFileName);
    ON_SCOPE_EXIT([&](){fclose(fd);});
    
    WriteRIFFChunk();
    WriteFMTChunk();
    WriteDataChunk();
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
    WriteSomeData(&chunkSize, sizeof(DWORD));
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
    WriteSomeData( &chunkSize,sizeof(DWORD) );
}
void RawTransformToWav::Impl::WriteFormatTag()
{
    
}
void RawTransformToWav::Impl::WriteChannels()
{
    
}
void RawTransformToWav::Impl::WriteSampleRate()
{
    
}
void RawTransformToWav::Impl::WriteDataRate()
{
    
}
void RawTransformToWav::Impl::WriteBlockAlign()
{
    
}
void RawTransformToWav::Impl::WriteBitsPerSample()
{
    
}
//Data Chunk
void RawTransformToWav::Impl::WriteDataChunk()
{
    
}
void RawTransformToWav::Impl::WriteDataID()
{
    
}
void RawTransformToWav::Impl::WriteDataSize()
{
    
}
void RawTransformToWav::Impl::WriteAudioData()
{
    
}

void RawTransformToWav::Impl::WriteSomeData( const void* data, unsigned int size )
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
    m_Impl->WriteResultToFile(resultFileName);
}

void RawTransformToWav::doTransform(const string &sourceFileNmae)
{
    assert(sourceFileNmae != "");
    
}



























