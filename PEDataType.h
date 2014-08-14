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
}P3D, V3D;

P3D Point3D(float x, float y, float z);

#endif
