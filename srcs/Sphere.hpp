#ifndef SPHERE_HPP
# define SPHERE_HPP

# include <gmath.hpp>
# include <SFML/Graphics.hpp>

/**
 * @brief Sphere class.
 */
class Sphere
{
public:
//**** PUBLIC ATTRIBUTS ********************************************************
	gm::Vec3f	pos;
	float		radius, radius2;
	sf::Color	color;

//**** INITIALISION ************************************************************
//---- Constructors ------------------------------------------------------------
	/**
	 * @brief Default contructor of Sphere class.
	 *
	 * @return The default Sphere.
	 */
	Sphere(void);
	/**
	 * @brief Copy constructor of Sphere class.
	 *
	 * @param obj The Sphere to copy.
	 *
	 * @return The Sphere copied from parameter.
	 */
	Sphere(const Sphere &obj);
	/**
	 * @brief Constructor of Sphere class.
	 *
	 * @param pos Sphere position.
	 * @param radius Sphere radius.
	 * @param color Sphere color.
	 *
	 * @return The Sphere create with parameters.
	 */
	Sphere(const gm::Vec3f &pos, float radius, const sf::Color &color);

//---- Destructor --------------------------------------------------------------
	/**
	 * @brief Destructor of Sphere class.
	 */
	~Sphere();

//**** ACCESSORS ***************************************************************
//---- Getters -----------------------------------------------------------------
//---- Setters -----------------------------------------------------------------
//---- Operators ---------------------------------------------------------------
	/**
	 * @brief Copy operator of Sphere class.
	 *
	 * @param obj The Sphere to copy.
	 *
	 * @return The Sphere copied from parameter.
	 */
	Sphere	&operator=(const Sphere &obj);

//**** PUBLIC METHODS **********************************************************
	/**
	 * @brief Made intersection beetween the sphere and a ray.
	 *
	 * @param rayPos The position of ray origin.
	 * @param rayDir The direction of ray.
	 *
	 * @return The distance of ray before hit the sphere, of MAX_RAY_DIST if not hit.
	 */
	float	intersectRay(const gm::Vec3f &rayPos, const gm::Vec3f &rayDir);
//**** STATIC METHODS **********************************************************

private:
//**** PRIVATE ATTRIBUTS *******************************************************
//**** PRIVATE METHODS *********************************************************
};

//**** FUNCTIONS ***************************************************************

#endif
