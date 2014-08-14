#ifndef __PEDataType_H__
#define __PEDataType_H__

#include "PEPrefix.h"

typedef struct PEPoint2D
{
	float x, y;
	void operator = (struct PEPoint2D &P);
	struct PEPoint2D operator + (struct PEPoint2D &P);
	struct PEPoint2D operator - (struct PEPoint2D &P);
	struct PEPoint2D operator * (struct PEPoint2D &P);
	struct PEPoint2D operator * (float scalar);
	struct PEPoint2D operator / (float scalar);
	struct PEPoint2D operator / (struct PEPoint2D &P);//复述除法
	float dot(struct PEPoint2D &P); //点积
	struct PEPoint2D cross(struct PEPoint2D &P);
	float morel();
	float arg();
	float degree();

	bool operator == (struct PEPoint2D &P);
	bool operator != (struct PEPoint2D &P);

	void normalized();
	struct PEPoint2D normal();
} P2D, V2D;
P2D Point2D(float x, float y);


typedef struct PEPoint3D
{		
	float x, y, z;
	void operator = (struct PEPoint3D &P);	
	struct PEPoint3D operator + (struct PEPoint3D &P);	
	struct PEPoint3D operator - (struct PEPoint3D &P);	
	struct PEPoint3D operator * (struct PEPoint3D &P);
	struct PEPoint3D operator * (float scalar);
	struct PEPoint3D operator / (float scalar);
	
	struct PEPoint3D cross (struct PEPoint3D &P);

	float dot(struct PEPoint3D &P);
	
	float morel();	
	void normalized();
	struct PEPoint3D normal();	

	//笛卡尔坐标变换球坐标,返回的 PEPoint3D的 (x-radius), 
	//(y-theta(与球坐标Z轴的角度)), (z-alpha(在XY平面上的相位角))
	struct PEPoint3D sphericalCoord(struct PEPoint3D &P);
}P3D, V3D;

P3D Point3D(float x, float y, float z);

#endif
