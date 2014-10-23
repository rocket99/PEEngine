#ifndef __PEDataType_H__
#define __PEDataType_H__

#include "../PEPrefix.h"

typedef struct PEPoint2D
{
	float x, y;
	void operator = (const struct PEPoint2D &P);
    void operator += (const struct PEPoint2D &P);
    void operator -= (const struct PEPoint2D &P);
    void operator *= (float scalar);
    void operator /= (float scalar);
    
	friend struct PEPoint2D operator + (const struct PEPoint2D &A, const struct PEPoint2D &B);
	friend struct PEPoint2D operator - (const struct PEPoint2D &A, const struct PEPoint2D &B);
	friend struct PEPoint2D operator * (const struct PEPoint2D &A, const struct PEPoint2D &B);
	friend struct PEPoint2D operator * (const struct PEPoint2D &A, float scalar);
    friend struct PEPoint2D operator * (float scalar, const struct PEPoint2D &A);
	friend struct PEPoint2D operator / (const struct PEPoint2D &A, float scalar);
	friend struct PEPoint2D operator / (const struct PEPoint2D &A, const struct PEPoint2D &B);//复述除法

	friend float dot(struct PEPoint2D &A, const PEPoint2D &B); //点积
	friend struct PEPoint2D cross(struct PEPoint2D &A, struct PEPoint2D &B);
    
	float morel() const;
	float arg() const;
	float degree() const;

    float morel();
	float arg();
	float degree();
	friend bool operator == (const struct PEPoint2D &A, const struct PEPoint2D &B);
	friend bool operator != (const struct PEPoint2D &A, const struct PEPoint2D &B);

	void normalized();
	struct PEPoint2D normal() const;
    struct PEPoint2D normal();
    
    void display();
    
    friend float areaOfTriangle(const struct PEPoint2D &A, const struct PEPoint2D &B, const struct PEPoint2D &C);
    friend struct PEPoint2D gravityCenterOfTriangle(const struct PEPoint2D &A, const struct PEPoint2D &B, const struct PEPoint2D &C);
} P2D, V2D, Size2D;
P2D Point2D(float x, float y);


typedef struct PEPoint3D
{		
	float x, y, z;
	void operator = (const struct PEPoint3D &P);
	friend struct PEPoint3D operator + (const struct PEPoint3D &A, const struct PEPoint3D &B);
	friend struct PEPoint3D operator - (const struct PEPoint3D &A, const struct PEPoint3D &B);
	friend struct PEPoint3D operator * (const struct PEPoint3D &A, const struct PEPoint3D &B);
	friend struct PEPoint3D operator * (const struct PEPoint3D &A, float scalar);
    friend struct PEPoint3D operator * (float scalar, const struct PEPoint3D &A);
	friend struct PEPoint3D operator / (const struct PEPoint3D &A, float scalar);
    friend struct PEPoint3D operator / (const struct PEPoint3D &A, const struct PEPoint3D &B);
    
    void operator += (const struct PEPoint3D &P);
    void operator -= (const struct PEPoint3D &P);
    void operator *= (float scalar);
    void operator /= (float scalar);
    
    friend struct PEPoint3D cross (const struct PEPoint3D &A, const struct PEPoint3D &B);
	friend float dot(const struct PEPoint3D &A, const struct PEPoint3D &B);
	
	float morel();	
	void normalized();
	struct PEPoint3D normal();	

    float morel() const;
	struct PEPoint3D normal() const;
	//笛卡尔坐标变换球坐标,返回的 PEPoint3D的 (x-radius), 
	//(y-theta(与球坐标Z轴的角度)), (z-alpha(在XY平面上的相位角))
	struct PEPoint3D sphericalCoord(struct PEPoint3D &P);
    
    friend bool isParallel(const struct PEPoint3D &A, const struct PEPoint3D &B);
    friend bool operator == (const struct PEPoint3D &A, const PEPoint3D &B);
    
    void display();
}P3D, V3D, Size3D;
P3D Point3D(float x, float y, float z);
#define P3DZERO Point3D(0.0, 0.0, 0.0)
   

typedef struct PEColor
{
    float r, g, b, a;
    void operator = (const struct PEColor &color);
}Color4F;
Color4F ColorRGBA(float red, float green, float blue, float alpha);
#endif
