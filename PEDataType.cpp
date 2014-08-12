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

P2D P2D::operator * (P2D &P)
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

P2D P2D::operator / (float scalar)
{
	P2D result;
	result.x = x/scalar;
	result.y = x/scalar;
	return result;
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

#pragma mark PEPoint3D implementation

