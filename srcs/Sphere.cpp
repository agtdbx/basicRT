#include <Sphere.hpp>

#include <define.hpp>

//**** STATIC FUNCTIONS DEFINE *************************************************
//**** INITIALISION ************************************************************
//---- Constructors ------------------------------------------------------------

Sphere::Sphere(void)
{
	this->pos = gm::Vec3f(0, 0, 0);
	this->radius = 1;
	this->radius2 = this->radius * this->radius;
	this->color = sf::Color(255, 255, 255);
}


Sphere::Sphere(const Sphere &obj)
{
	this->pos = obj.pos;
	this->radius = obj.radius;
	this->radius2 = this->radius * this->radius;
	this->color = obj.color;
}


Sphere::Sphere(const gm::Vec3f &pos, float radius, const sf::Color &color)
{
	this->pos = pos;
	this->radius = radius;
	this->radius2 = this->radius * this->radius;
	this->color = color;
}

//---- Destructor --------------------------------------------------------------

Sphere::~Sphere()
{

}

//**** ACCESSORS ***************************************************************
//---- Getters -----------------------------------------------------------------
//---- Setters -----------------------------------------------------------------
//---- Operators ---------------------------------------------------------------

Sphere	&Sphere::operator=(const Sphere &obj)
{
	if (this == &obj)
		return (*this);

	this->pos = obj.pos;
	this->radius = obj.radius;
	this->radius2 = this->radius * this->radius;
	this->color = obj.color;

	return (*this);
}

//**** PUBLIC METHODS **********************************************************

float	Sphere::intersectRay(const gm::Vec3f &rayPos, const gm::Vec3f &rayDir)
{
	gm::Vec3f	vec = rayPos - this->pos;
	float		dot = gm::dot(rayDir, vec);
	float		nabla = (dot * dot) - gm::dot(vec, vec) + this->radius2;

	if (nabla < 0.0f)
		return (MAX_RAY_DIST);

	nabla = sqrtf(nabla);
	float	dist = -dot - nabla;
	if (dist >= 0.0f)
		return (dist);

	dist = -dot + nabla;
	if (dist >= 0.0f)
		return (dist);

	return (MAX_RAY_DIST);
}

//**** STATIC METHODS **********************************************************
//**** PRIVATE METHODS *********************************************************
//**** FUNCTIONS ***************************************************************
//**** STATIC FUNCTIONS ********************************************************
