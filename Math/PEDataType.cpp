#include "PEDataType.h"

#pragma mark PEPoint2D implementation
void P2D::operator = (const P2D &P){
	x = P.x;
	y = P.y;
}

void P2D::operator += (const struct PEPoint2D &P)
{
    x += P.x; y += P.y;
}
void P2D::operator -= (const struct PEPoint2D &P)
{
    x -= P.x; y -= P.y;
}
void P2D::operator *= (float scalar)
{
    x *= scalar; y *= scalar;
}
void P2D::operator /= (float scalar)
{
    x /= scalar; y/= scalar;
}

P2D operator + (const P2D &A, const P2D &B)
{
	P2D result;
	result.x = A.x + B.x;
	result.y = A.y + B.y;
	return result;
}

P2D operator - (const P2D &A, const P2D &B)
{
	P2D result;
	result.x = A.x - B.x;
	result.y = A.y - B.y;
	return result;
}

P2D operator * (const P2D &A, const P2D &B)
{	
	P2D result;
	result.x = A.x * B.x;
	result.y = A.y * B.y;
	return result;
}

P2D operator * (const P2D &A, float scalar)
{
	P2D result;
	result.x = A.x*scalar;
	result.y = A.y*scalar;
	return result;
}

P2D operator * (float scalar, const P2D &A)
{
	P2D result;
	result.x = A.x*scalar;
	result.y = A.y*scalar;
	return result;
}

P2D operator / (const P2D &A, const P2D &B)
{
	P2D result;
	float m = B.morel();
	result.x = (A.x*B.x + A.y*B.y)/m;
	result.y = (A.y*B.x - A.x*B.y)/m;
	return result;	
}

P2D operator / (const P2D &A, float scalar)
{
	P2D result;
	result.x = A.x/scalar;
	result.y = A.y/scalar;
	return result;
}

bool P2D::operator == (const P2D &P)
{
	return (x==P.x && y==P.y);
}

bool P2D::operator != (const P2D &P)
{
	return (x!=P.x || y!=P.y);
}

float dot(P2D &A, P2D &B)
{
	return A.x*B.x + A.y*B.y;
}

P2D cross (P2D &A, P2D &B)
{
	P2D result;
	result.x = A.x*B.x - A.y*B.y;
	result.y = A.x*B.y + A.y*B.x;
	return result;
}

float P2D::morel() const
{
	return x*x + y*y;
}

float P2D::arg() const
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

float P2D::degree() const{
	return this->arg()/M_PI*180.0;
}

float P2D::morel(){
	return x*x + y*y;
}

float P2D::arg(){
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
float P2D::degree(){
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

P2D P2D::normal() const
{
	float m = morel();
	P2D result;
	result.x = x/m;
	result.y = y/m;
	return result;
}

P2D P2D::normal(){
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

void P2D::display()
{
    printf("(%.3f, %.3f)\n", x, y);
}

float areaOfTriangle(P2D &A, P2D &B, P2D &C)
{
    V2D AB = B-A;
    V2D AC = C-A;
    return AB.x*AC.y - AB.y*AC.x;
}

P2D gravityCenterOfTriangle(const P2D &A, const P2D &B, const P2D &C)
{
    return A+2.0*(0.5*(B+C)-A)/3.0;
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

void P3D::operator = (const P3D &P)
{
	x = P.x;
	y = P.y;
	z = P.z;
}

P3D operator + (const P3D &A, const P3D &B)
{	
	return Point3D(A.x+B.x, A.y+B.y, A.z+B.z);
}

P3D operator - (const P3D &A, const P3D &B)
{
	return Point3D(A.x-B.x, A.y-B.y, A.z-B.z);
}

P3D operator * (const P3D &A, const P3D &B)
{
	return Point3D(A.x*B.x, A.y*B.y, A.z*B.z);
}

P3D operator *(float scalar, const P3D &A)
{
	return Point3D(A.x*scalar, A.y*scalar, A.z*scalar);
}

P3D operator *(const P3D &A, float scalar)
{
    return Point3D(A.x*scalar, A.y*scalar, A.z*scalar);
}

P3D operator / (const P3D &A, float scalar)
{
	return Point3D(A.x/scalar, A.y/scalar, A.z/scalar);
}

P3D operator / (const P3D &A, const P3D &B)
{
    return Point3D(A.x/B.x, A.y/B.y, A.z/B.z);
}

void P3D::operator += (const P3D &P)
{
    x += P.x; y += P.y; z += P.z;
}

void P3D::operator -= (const P3D &P)
{
    x -= P.x; y -= P.y; z -= P.z;
}

void P3D::operator *= (float scalar)
{
    x *= scalar; y *= scalar; z*= scalar;
}

void P3D::operator /= (float scalar)
{
    x /= scalar; y /= scalar; z/= scalar;
}

P3D cross(const P3D &A, const P3D &B)
{
	return Point3D(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);
}

float dot(const P3D &A, const P3D &B)
{
	return (A.x*B.x + A.y*B.y + A.z*B.z);
}

float P3D::morel()
{
	return sqrt(x*x + y*y + z*z);
}

void P3D::normalized()
{
	float len = this->morel();
	x /= len; y /= len; z /= len;
}

P3D P3D::normal()
{
	float len = this->morel();
	return Point3D(x/len, y/len, z/len);
}

float P3D::morel() const
{
	return sqrt(x*x+y*y+z*z);
}

P3D P3D::normal() const
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

bool isParallel(const P3D &A, const P3D &B)
{
    return  (cross(A, B).morel() == 0.0);
}

bool operator == (const P3D &A, const P3D &B)
{
    return (A.x==B.x) && (A.y==B.y) && (A.z==B.z);
}

void P3D::display()
{
    PELog("(%.3f, %.3f, %.3f)", x, y, z);
}

#pragma mark PEColor

void Color4F::operator = (const Color4F &color)
{
    r = color.r; g = color.g;
    b = color.b; a = color.a;
}

Color4F ColorRGBA(float red, float green, float blue, float alpha)
{
    Color4F color;
    color.r = red;  color.g = green;
    color.b = blue; color.a = alpha;
    return color;
}




