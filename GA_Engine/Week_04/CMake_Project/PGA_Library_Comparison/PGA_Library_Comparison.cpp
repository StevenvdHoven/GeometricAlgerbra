#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <klein/klein.hpp>
using namespace kln;

//#include "pga3d.h"

void Print(const plane& p)
{
	std::cout << "plane:[ scale:" << p.d() << " e1:" << p.e1() << " e2:" << p.e2() << " e3:" << p.e3() << "]" << std::endl;
}

void Print(const line& p)
{
	std::cout << "line:[ e12:" << p.e12() << " e23 : " << p.e23() << " e31 : " << p.e31() << "]" << std::endl;
}

void Print(const point& p)
{
	std::cout << "point:[ e123:" << p.e123() << " e021:" << p.e021() << " e032 : " << p.e032() << " e013 : " << p.e013() << "]" << std::endl;
}

int main()
{
	
	plane e1{ 1,0,0,0 };
	plane e2{ 0,1,0,0 };
	plane e3{ 0,0,1,0 };
	plane e0{ 0,0,0,0 };

	line e01{ e0 ^ e1 };
	line e02{ e0 ^ e2 };
	line e03{ e0 ^ e3 };
	line e12{ e1 ^ e2 };
	line e23{ e2 ^ e3 };
	line e31{ e3 ^ e1 };

	point e123{ e12 ^ e3 };
	point e012{ e0 ^ e12 };
	point e023{ e0 ^ e23 };
	point e031{ e0 ^ e31 };
	

	Print(e1);
	Print(e2);
	Print(e3);

	Print(e01);
	Print(e02);
	Print(e03);
	Print(e12);
	Print(e23);
	Print(e31);

	Print(e123);
	Print(e012);
	Print(e023);
	Print(e031);
	
	//// Elements of the even subalgebra (scalar + bivector + pss) of unit length are motors
	//kln::rotor rot = kln::rotor{ kln::plane(1,0,0,0) ^ kln::plane(0,0,0,2) };

	//// The outer product ^ is the MEET. Here we intersect the yz (x=0) and xz (y=0) planes.
	//PGA3D ax_z = e1 ^ e2;

	//// line and plane meet in point. We intersect the line along the z-axis (x=0,y=0) with the xy (z=0) plane.
	//PGA3D orig = ax_z ^ e3;

	//// We can also easily create points and join them into a line using the regressive (vee, &) product.
	//PGA3D px = point(1.0, 0.0, 0.0);
	//PGA3D line = orig & px;

	//// Lets also create the plane with equation 2x + z - 3 = 0
	//PGA3D p = plane(2, 0, 1, -3);

	//// rotations work on all elements
	//PGA3D rotated_plane = rot * p * ~rot;
	//PGA3D rotated_line = rot * line * ~rot;
	//PGA3D rotated_point = rot * px * ~rot;

	//// See the 3D PGA Cheat sheet for a huge collection of useful formulas
	//PGA3D point_on_plane = (p | px) * p;

	//// Some output.
	//printf("a point       : "); px.log();
	//printf("a line        : "); line.log();
	//printf("a plane       : "); p.log();
	//printf("a rotor       : "); rot.log();
	//printf("rotated line  : "); rotated_line.log();
	//printf("rotated point : "); rotated_point.log();
	//printf("rotated plane : "); rotated_plane.log();
	//printf("point on plane: "); point_on_plane.normalized().log();
	//printf("point on torus: "); point_on_torus(0.0f, 0.0f).log();
	//(e0 - 1.0f).log();
	//(1.0f - e0).log();

	return 0;
}


