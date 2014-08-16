#include "PEDataType.h"

#pragma mark PEPoint2D implementation
void P2D::operator = (P2D &P)
{
	x = P.x;
	y = P.y;
}

P2D P2D::operator + (P2D &P)
{
	P2D result;
	result.x = x + P.x;
	result.y = y + P.y;
	return result;
}

P2D P2D::operator - (P2D &P)
{
	P2D result;
	result.x = x - P.x;
	result.y = y - P.y;
	return result;
}

P2D::P2D::operator * (P2D &P)
{	
	P2D result;
	result.x = x * P.x;
	result.y = y * P.y;
	return result;
}

P2D P2D::cross (P2D &P)
{
	P2D result;
	result.x = x*P.x - y*P.y;
	result.y = x*P.y + y*P.x;
	return result;
}

P2D P2D::operator * (float scalar)
{
	P2D result;
	result.x = x*scalar;
	result.y = y*scalar;
	return result;
}

P2D P2D::operator / (P2D &P)
{
	P2D result;
	float m = P.morel();
	result.x = (x*P.x + y*P.y)/m;
	result.y = (y*P.x - x*P.y)/m;
	return result;	
}

P2D P2D::operator / (float scalar)
{
	P2D result;
	result.x = x/scalar;
	result.y = x/scalar;
	return result;
}

bool P2D::operator == (P2D &P)
{
	return (x==P.x && y==P.y);
}

bool P2D::operator != (P2D &P)
{
	return (x!=P.x || y!=P.y);
}

float P2D::dot(P2D &P)
{
	return x*P.x + y*P.y;
}

float P2D::morel()
{
	return x*x + y*y;
}

float P2D::arg()
{
	float m = morel();
	if(m == 0.0){
		return 0.0;
	}
	float angle;
	if(x==0){
		if(y > 0){
			angle = 0.5*M_PI;
		}else if(y < 0){
			angle = -0.5*M_PI;
		}else{
			angle = 0.0;
		}
	}else{
		if(x > 0){
			angle = asin(y/m);
		}else{
			angle = asin(y/m) + M_PI;
			angle = (angle>M_PI) ? (angle-2.0*M_PI) : angle;
		}
	}
	return angle;
}
float P2D::degree()
{
	return this->arg()/M_PI*180.0;
}

void P2D::normalized()
{
	float m = this->morel();
	if(m == 0){
		x = y = 0.0;
	}else{
		x /= m;
		y /= m;
	}
}

P2D P2D::normal()
{
	float m = morel();
	P2D result;
	result.x = x/m;
	result.y = y/m;
	return result;
}

P2D Point2D(float x, float y)
{
	P2D point; 
	point.x = x; 
	point.y = y;
	return point;
}

#pragma mark PEPoint3D implementation

P3D Point3D(float x , float y, float z)
{
	P3D point;
	point.x = x;
	point.y = y;
	point.z = z;
	return point;
}

void P3D::operator = (P3D &P)
{
	x = P.x;
	y = P.y;
	z = P.z;
}

P3D P3D::operator + (P3D &P)
{	
	return Point3D(x+P.x, y+P.y, z+P.z);
}

P3D P3D::operator - (P3D &P)
{
	return Point3D(x-P.x, y-P.y, z-P.z);
}

P3D P3D::operator * (P3D &P)
{
	return Point3D(x*P.x, y*P.y, z*P.z);
}

P3D P3D::operator *(float scalar)
{
	return Point3D(x*scalr, y*scalar, z*scalar);
}

P3D P3D::operator / (float scalar)
{
	return (x/scalar, y/scalar, z/scalar);
}

P3D P3D::cross(P3D &P)
{
	return Point3D(y*P.z-z*P.y, z*P.x-x*P.z, x*P.y-y*P.x);
}

float P3D::dot(P3D &P)
{
	return (x*P.x + y*P.y + z*P.z);
}

float P3D::morel()
{
	return sqrt(x*x+y*y+z*z);
}

void P3D::normalized()
{
	float len = this->morel();
	x /= len;
	y /= len;
	z /= len;
}

P3D P3D::normal()
{
	float len = this->morel();
	return Point3D(x/len, y/len, z/len);
}

P3D P3D::sphericalCoord(P3D &P)
{
	float radius = P.morel();
	P2D pxy = Point2D(x/radius, y/radius);
	float alpha = pxy.degree();
	float theta = acos(z/radius);
	return Point3D(radius, theta, alpha);
}




