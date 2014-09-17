//
//  PERect.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PERect.h"

PERect::PERect():m_width(1.0f),m_height(1.0f){}
PERect::~PERect(){}

PERect *PERect::create(float width, float height)
{
    PERect *rect = new PERect();
    if(rect->initWithSize(width, height)){
        return rect;
    }
    delete rect;
    return NULL;
}

bool PERect::initWithSize(float width, float height)
{
    if (!PENode::init()) {
        return false;
    }
    m_width = width;
    m_height = height;
    m_data = (float *)malloc(sizeof(float)*(12+8+12));
    //coord
    m_data[0] = -0.5*m_width; m_data[1] = -0.5*m_height; m_data[2] = 0.0;
    m_data[3] = -0.5*m_width; m_data[4] =  0.5*m_height; m_data[5] = 0.0;
    m_data[6] =  0.5*m_width; m_data[7] =  0.5*m_height; m_data[8] = 0.0;
    m_data[9] =  0.5*m_width; m_data[10] = -0.5*m_height; m_data[11] = 0.0;
    //texCoord
    m_data[12] = 0.0; m_data[13] = 0.0;
    m_data[14] = 0.0; m_data[15] = 1.0;
    m_data[16] = 1.0; m_data[17] = 1.0;
    m_data[18] = 1.0; m_data[19] = 0.0;
    //normal
    m_data[20] = 0.0; m_data[21] = 0.0; m_data[22] = 1.0;
    m_data[23] = 0.0; m_data[24] = 0.0; m_data[25] = 1.0;
    m_data[26] = 0.0; m_data[27] = 0.0; m_data[28] = 1.0;
    m_data[29] = 0.0; m_data[30] = 0.0; m_data[31] = 1.0;
    //material
    m_material.ambient = ColorRGBA(0.2, 0.2, 0.2, 0.1);
    m_material.diffuse = ColorRGBA(0.7, 0.7, 0.7, 0.7);
    m_material.specular = ColorRGBA(0.95, 0.95, 1.0, 1.0);
    m_material.emission = ColorRGBA(0.0, 0.0, 0.0, 0.0);
    return true;
}


void PERect::draw()
{
    if(m_isVisible == false){
        return;
    }
    m_program = m_program1;
    if(glIsProgram(m_program) == GL_FALSE){
        return;
    }
    glUseProgram(m_program);
    this->setModelViewProjectUniform();
    this->setLightProjectViewUniform();
    this->setDepthTexUnifrom();
    this->setTextureUniform();
    this->drawFunc();
}

void PERect::drawFBO()
{
    if(m_isVisible == false){
        return;
    }
    m_program = m_program0;
    if(glIsProgram(m_program) == GL_FALSE){
        return;
    }
    glUseProgram(m_program);
    this->setLightProjectViewUniform(UNIFORM_MODELPROJECT);
    this->drawFunc();
}

void PERect::drawFunc()
{
    this->setSpaceUniform();
    this->setWorldMatUniform();
    this->setColorUniform();
    
    GLint loc = glGetUniformLocation(m_program, UNIFORM_ROTATE);
    if(loc >= 0){
        PEMatrix mat = m_worldMat.complement(3, 3);
        glUniformMatrix3fv(loc, 1, GL_FALSE, mat.getData());
    }
    
    this->setMaterialUniformBlock();
    this->setLightUniformBlock();
    glEnableVertexAttribArray(ATTRIB_POINT_LOC);
    glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 0, m_data);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glVertexAttribPointer(ATTRIB_TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, &m_data[12]);
    glEnableVertexAttribArray(ATTRIB_NORMAL_LOC);
    glVertexAttribPointer(ATTRIB_NORMAL_LOC, 3, GL_FLOAT, GL_TRUE, 0, &m_data[20]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(ATTRIB_POINT_LOC);
    glDisableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glDisableVertexAttribArray(ATTRIB_NORMAL_LOC);
    this->deleteMaterialUbo();
    this->deleteLightUbo();
}




