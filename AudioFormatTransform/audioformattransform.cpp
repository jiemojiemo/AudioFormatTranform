//
//  audioformattransform.cpp
//  AudioFormatTransform
//
//  Created by meitu on 15/9/25.
//  Copyright © 2015年 meitu. All rights reserved.
//


#include "rawtransform.h"
TransformFactory* TransformFactory::m_pInstance=nullptr;

//TransformFactory

//
AudioTransformer* TransformFactory::GetTransformer(const TransformParameter &params)
{
    switch (params.sourFmt) {
        case RAW:
            switch (params.destFmt)
            {
                case WAVE:
                    return new RawTransformToWav(params);
                    break;
                    
                default:
                    break;
            }
            return nullptr;
            break;
        default:
            break;
    }
    return nullptr;
}




