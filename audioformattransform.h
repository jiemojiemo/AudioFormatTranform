//
//  audioformattransform.h
//  AudioFormatTransform
//
//  Created by meitu on 15/9/25.
//  Copyright © 2015年 meitu. All rights reserved.
//

#ifndef audioformattransform_h
#define audioformattransform_h

#include <string>
using std::string;

#define    DISALLOW_COPY_AND_ASSIGN(ClassName) \
ClassName(const ClassName&);                \
ClassName& operator=(const ClassName&)

//more information about wave http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html

typedef unsigned long AUDIO_FORMAT;
static const AUDIO_FORMAT RAW   =0x0001;
static const AUDIO_FORMAT WAVE  =0x0003;

typedef unsigned long FORMAT_CODE;
static const FORMAT_CODE WAVE_FORMAT_PCM        = 0x0001;
static const FORMAT_CODE WAVE_FORMAT_IEEE_FLOAT = 0x0003;

struct TransformParameter{
    AUDIO_FORMAT destFmt;
    AUDIO_FORMAT sourFmt;
    FORMAT_CODE  formatTag;
    unsigned int nChannels;
    unsigned int sampleRate;
    unsigned int sampleBits;    //每个采样的bit数
};

//Interface about Audio Transform
class AudioTransformer{
public:
    //create a new file to storage the result
    virtual void doTransform(const string& sourceFileName, const string& resultFileName)=0;
    //the result file will covers the source file
    virtual void doTransform(const string& sourceFileNmae)=0;
    //
    virtual void doTransform(const void* data, unsigned long totalBytes, const string& resultFileName)=0;
private:
    
};

//
class TransformFactory{
public:
    static AudioTransformer* GetTransformer(const TransformParameter& params);
private:
    static TransformFactory* m_pInstance;
    TransformFactory(){}
    DISALLOW_COPY_AND_ASSIGN(TransformFactory);
};


#endif /* audioformattransform_h */
