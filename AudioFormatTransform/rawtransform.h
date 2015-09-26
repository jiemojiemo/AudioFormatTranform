//
//  rawtransform.h
//  AudioFormatTransform
//
//  Created by meitu on 15/9/25.
//  Copyright © 2015年 meitu. All rights reserved.
//

#ifndef rawtransform_h
#define rawtransform_h
#include "audioformattransform.h"
#include <memory>

class RawTransformer : public AudioTransformer
{
public:
    virtual void doTransform(const string& sourceFileName, const string& resultFileName)=0;
    virtual void doTransform(const string& sourceFileNmae)=0;
private:
    
};


class RawTransformToWav : public RawTransformer
{
public:
    RawTransformToWav(const TransformParameter& params);
    virtual void doTransform(const string& sourceFileName, const string& resultFileName);
    virtual void doTransform(const string& sourceFileNmae);
private:
    class Impl;
    std::unique_ptr<Impl> m_Impl;
};


#endif /* rawtransform_h */
