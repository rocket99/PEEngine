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

PETexture *PETexture::create(const char *fileName, PicType type)
{
    PETexture *texture = new PETexture;
    if(texture->initWithPic(fileName, type)){
        return texture;
    }
    delete texture;
    return NULL;
    
}

bool PETexture::initWithPic(const char *fileName, PicType type)
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    free(data);
    [img release];
    return true;
}

int PETexture::Width() {
    return m_width;
}

int PETexture::Height() {
    return m_height;
}

GLuint PETexture::Texture() {
    return m_Id;
}

bool PETexture::readJPGFile(const char *fileName) {
    return true;
}

bool PETexture::readPNGFile(const char *fileName) {
    return true;
}


PETexture *PETexture::createCubeTex(const char *fileName)
{
    PETexture *tex = new PETexture();
    if(tex->initWithCubeMap(fileName)){
        return tex;
    }
    delete tex;
    return NULL;
}

bool PETexture::initWithCubeMap(const char *fileName)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
   
    const char *suffixes[] = {
      "posx", "negx", "posy", "negy", "posz", "negz",
    };
    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };
    
    for (int i=0; i<6; ++i) {
        string file = fileName;
        file.append(suffixes[i]);
        file.append(".png");
        UIImage *img = [[UIImage alloc] initWithContentsOfFile:
                        [[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"%s",file.c_str()]
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
        
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(targets[i], 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
        delete [] data;
        [img release];
    }
    
    return true;
}


