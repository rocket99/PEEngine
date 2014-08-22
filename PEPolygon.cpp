//
//  PEPolygon.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEPolygon.h"

PEPolygon::PEPolygon():
m_data(NULL), m_num(0)
{
    
}

PEPolygon::~PEPolygon()
{
    delete [] m_data;
}

void PEPolygon::draw()
{
    if ( ) {
        
    }
    this->PENode::draw();
    if (glIsProgram(m_progam) == GL_FALSE) {
        return;
    }
}