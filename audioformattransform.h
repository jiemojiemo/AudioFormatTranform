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


typedef unsigned long AUDIO_FORMAT;

static const AUDIO_FORMAT RAW   =0x0001;
static const AUDIO_FORMAT WAVE  =0x0002;


class AudioTransformer{
public:
    //create a new file to storage the result
    virtual void doTransform(const string& sourceFileName, const string& resultFileName)=0;
    //the result file will covers the source file
    virtual void doTransform(const string& sourceFileNmae)=0;
private:
    
};


struct TransformParameter{
    AUDIO_FORMAT destFmt;
    AUDIO_FORMAT sourFmt;
    unsigned int nChannels;
    unsigned int sampleRate;
    unsigned int sampleBits;    //每个采样的bit数
};

class TransformFactory{
public:
    static AudioTransformer* GetTransformer(const TransformParameter& params);
private:
    static TransformFactory* m_pInstance;
    TransformFactory(){}
    DISALLOW_COPY_AND_ASSIGN(TransformFactory);
};





#endif /* audioformattransform_h */
