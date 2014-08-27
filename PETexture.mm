//
//  PETexture.m
//  Engine
//
//  Created by rocket99 on 14-8-27.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#import "PETexture.h"

PETexture::PETexture():
m_width(0), m_height(0), m_Id(GL_FALSE)
{}

PETexture::~PETexture()
{
    glDeleteTextures(1, &m_Id);
}

PETexture *PETexture::create(const char *fileName)
{
    PETexture *texture = new PETexture;
    if(texture->initWithPic(fileName)){
        return texture;
    }
    delete texture;
    return NULL;
    
}

bool PETexture::initWithPic(const char *fileName)
{
    UIImage *img = [[UIImage alloc] initWithContentsOfFile:
                    [[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"%s",fileName]
                                                    ofType:nil]];
    if(img == nil){
        return false;
    }
    CGImageRef imgRef = img.CGImage;
    size_t width = CGImageGetWidth(imgRef);
    size_t height = CGImageGetHeight(imgRef);
    GLubyte *data = (GLubyte *)malloc(sizeof(GLubyte)*width*height*4);
    CGContextRef context = CGBitmapContextCreate(data, width, height, 8, width*4,
                                                 CGImageGetColorSpace(imgRef),
                                                 kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), imgRef);
    CGContextRelease(context);
    
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    free(data);
    [img release];
    return true;
}

int PETexture::getWidth()
{
    return m_width;
}

int PETexture::getHeight()
{
    return m_height;
}

GLuint PETexture::getTexture()
{
    return m_Id;
}