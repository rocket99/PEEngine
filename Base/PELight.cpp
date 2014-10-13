//
//  PELight.cpp
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PELight.h"

PELight::PELight()
{
    m_position = Point3D(0.0, 0.0, 0.0);
    m_direction = Point3D(0.0, -1.0, 0.0);
    m_world = Point3D(1.0, 1.0, 1.0);
    m_ambient = ColorRGBA(0.1, 0.1, 0.1, 0.1);
    m_diffuse = ColorRGBA(0.8, 0.8, 0.8, 0.8);
    m_specular = ColorRGBA(1.0, 1.0, 1.0, 1.0);
    m_fovy = 60.0;
    m_shininess = 1.0;
    m_camera = NULL;
}

PELight::~PELight()
{
    if(m_camera != NULL){
        delete m_camera;
    }
}

PELight * PELight::createWithWorld(const Size3D &world)
{
    PELight *light = new PELight;
    if(light->initWithWorld(world)) {
        return light;
    }
    delete light;
    return NULL;
}

bool PELight::initWithWorld(const Size3D &world)
{
    if(world.x*world.y*world.z == 0.0 ){
        return false;
    }
    m_world = world;
    return true;
}

Size3D &PELight::World()
{
    return m_world;
}

P3D &PELight::Position()
{
    return m_position;
}

V3D &PELight::Direction()
{
    return m_direction;
}

Color4F &PELight::Ambient()
{
    return m_ambient;
}

Color4F &PELight::Diffuse()
{
    return m_diffuse;
}

Color4F &PELight::Specular()
{
    return m_specular;
}

float &PELight::Fovy()
{
    return m_fovy;
}

float &PELight::Shininess()
{
    return m_shininess;
}

void PELight::setUniformBlock(GLuint program)
{
    if(glIsProgram(program) == GL_FALSE){
        return;
    }
    GLuint index = glGetUniformBlockIndex(program, UNIFORM_LIGHT);
    if(index == GL_INVALID_OPERATION || index == GL_INVALID_INDEX){
        return;
    }
    GLint size;
    glGetActiveUniformBlockiv(program, index, GL_UNIFORM_BLOCK_DATA_SIZE, &size);
    const char *name[] = {"l_ambient", "l_diffuse", "l_specular", "l_position", "l_direction", "l_fovy", "l_shininess"};
    GLuint indices[7]; GLint offset[7];
    glGetUniformIndices(program, 7, name, indices);
    glGetActiveUniformsiv(program, 7, indices, GL_UNIFORM_OFFSET, offset);
    GLfloat ambient[4];
    ambient[0] = m_ambient.r; ambient[1] = m_ambient.g;
    ambient[2] = m_ambient.b; ambient[3] = m_ambient.a;
    GLfloat diffuse[4];
    diffuse[0] = m_diffuse.r; diffuse[1] = m_diffuse.g;
    diffuse[2] = m_diffuse.b; diffuse[3] = m_diffuse.a;
    GLfloat specular[4];
    specular[0] = m_specular.r; specular[1] = m_specular.g;
    specular[2] = m_specular.b; specular[3] = m_specular.a;
    GLfloat pos[3];
    pos[0] = m_position.x/m_world.x;
    pos[1] = m_position.y/m_world.y;
    pos[2] = m_position.z/m_world.z;
    GLfloat direct[3];
    direct[0] = m_direction.x; direct[1] = m_direction.y; direct[2] = m_direction.z;
    GLfloat fovy = m_fovy/180.0*M_PI;
    fovy = fovy<0.0 ? -fovy : fovy;
    GLubyte *blockBuffer = new GLubyte[size];
    memcpy(blockBuffer+offset[0], ambient, sizeof(GLfloat)*4);
    memcpy(blockBuffer+offset[1], diffuse, sizeof(GLfloat)*4);
    memcpy(blockBuffer+offset[2], specular, sizeof(GLfloat)*4);
    memcpy(blockBuffer+offset[3], pos, sizeof(GLfloat)*3);
    memcpy(blockBuffer+offset[4], direct, sizeof(GLfloat)*3);
    memcpy(blockBuffer+offset[5], &fovy, sizeof(GLfloat));
    memcpy(blockBuffer+offset[6], &m_shininess, sizeof(GLfloat));
    
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, blockBuffer, GL_DYNAMIC_DRAW);
    free(blockBuffer);
    glUniformBlockBinding(program, index, UNIFORM_LIGHT_BIND);
    glBindBufferRange(GL_UNIFORM_BUFFER, UNIFORM_LIGHT_BIND, m_ubo, 0, size);
}

void PELight::removeUniformBlock()
{
    if(glIsBuffer(m_ubo) == GL_TRUE){
        glDeleteBuffers(1, &m_ubo);
    }
}

void PELight::setCamera(){
    P3D center = m_position + 1000*m_direction;
    V3D up;
    if(dot(m_direction, Point3D(1.0, 0.0, 0.0)) == 0){
        up = Point3D(1.0, 0.0, 0.0).normal();
    }else if(dot(m_direction, Point3D(0.0, 1.0, 0.0)) == 0){
        up = Point3D(0.0, 1.0, 0.0).normal();
    }else if(dot(m_direction, Point3D(0.0, 0.0, 1.0)) == 0){
        up = Point3D(0.0, 0.0, 1.0).normal();
    }
    
    if(m_camera != NULL ){
        m_camera->WorldPos() = m_position;
        m_camera->WorldFocus() = center;
        m_camera->upDirect() = up;
        return;
    }
    m_camera = PECamera::create(m_world, m_position, center, up);
    m_camera->setPerspect(2.0*m_fovy, 1.0, 0.01, 300.0);
}

PECamera *PELight::getCamera(){
    return m_camera;
}




