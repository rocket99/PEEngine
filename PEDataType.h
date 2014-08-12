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
	float dot(struct PEPoint2D &P);
	float morel();
	float arg();
	float degree();

	void normalized();
	struct PEPoint2D normal();
} P2D, V2D;
P2D Point2D(float x, float y);


typedef struct PEPoint3D
{		
	float x, y, z;

}P3D, V3D;

P3D Point3D(float x, float y, float z);

#endif
