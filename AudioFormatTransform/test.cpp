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
    params.destFmt = WAVE;
    params.sourFmt = RAW;
    params.nChannels = 1;
    params.sampleRate = 44100;
    params.sampleBits = 16;

    auto audioTransformer = TransformFactory::GetTransformer(params);
    string sourseFile = "/Users/zj-dt0095/Music/sourceFile.raw";
    audioTransformer->doTransform( sourseFile );
    
    return 0;
}