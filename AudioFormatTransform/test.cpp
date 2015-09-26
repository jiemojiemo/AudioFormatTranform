//
//  test.cpp
//  AudioFormatTransform
//
//  Created by meitu on 15/9/25.
//  Copyright © 2015年 meitu. All rights reserved.
//

#include "audioformattransform.h"
#include <iostream>

using namespace std;

int main()
{
    TransformParameter params;
    params.formatTag = WAVE_FORMAT_PCM;
    params.destFmt = WAVE;
    params.sourFmt = RAW;
    params.nChannels = 1;
    params.sampleRate = 44100;
    params.sampleBits = 16;

    auto audioTransformer = TransformFactory::GetTransformer(params);
    string sourseFile = "/Users/zj-dt0095/Music/1_16_44100.raw";
    string destFile = "/Users/zj-dt0095/Music/sourceFile.wav";
    audioTransformer->doTransform( sourseFile, destFile );
    
    return 0;
}