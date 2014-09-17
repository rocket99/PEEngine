//
//  PETextureMananger.h
//  Engine
//
//  Created by rocket99 on 14-9-10.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PETextureMananger__
#define __Engine__PETextureMananger__

#include <iostream>
#include "PETexture.h"

class PETextureManager
{
public:
    static PETextureManager *Instance();
    static void purge();
    
    GLuint &ColorTex();
    GLuint &DepthTex();
private:
    GLuint m_depthTex;
    GLuint m_colorTex;

};
#endif 
/* defined(__Engine__PETextureMananger__) */

