//
//  PEFbxModel.cpp
//  Engine
//
//  Created by rocket99 on 14-9-18.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEFbxModel.h"

PEModelFBX *PEModelFBX::createWithFBX(const char *fileName)
{
    PEModelFBX *model = new PEModelFBX();
    if(model->initWithFBX(fileName)){
        return model;
    }
    delete model;
    return NULL;
}

bool PEModelFBX::initWithFBX(const char *fileName)
{
    if(!PERealNode::init()){
        return false;
    }
    
    
    return true;
}