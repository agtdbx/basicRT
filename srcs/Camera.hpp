#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <define.hpp>
# include <gmath.hpp>

/**
 * @brief Camera class.
 */
class Camera
{
public:
//**** PUBLIC ATTRIBUTS ********************************************************
	gm::Vec3f	position, front, up, right;
	float		pitch, yaw, roll, planeWidth, planeHeight, winRatio, fov;

//**** INITIALISION ************************************************************
//---- Constructors ------------------------------------------------------------
	/**
	 * @brief Default contructor of Camera class.
	 *
	 * @return The default Camera.
	 */
	Camera(void);
	/**
	 * @brief Copy constructor of Camera class.
	 *
	 * @param obj The Camera to copy.
	 *
	 * @return The Camera copied from parameter.
	 */
	Camera(const Camera &obj);

//---- Destructor --------------------------------------------------------------
	/**
	 * @brief Destructor of Camera class.
	 */
	~Camera();

//**** ACCESSORS ***************************************************************
//---- Getters -----------------------------------------------------------------
//---- Setters -----------------------------------------------------------------
	/**
	 * @brief Setter for position.
	 *
	 * @param position New position.
	 */
	void	setPosition(const gm::Vec3f &position);
	/**
	 * @brief Setter for rotation.
	 *
	 * @param pitch Pitch of rotation.
	 * @param yaw Yaw of rotation.
	 * @param roll Roll of rotation.
	 */
	void	setRotation(const float pitch, const float yaw, const float roll);
	/**
	 * @brief Setter for rotation.
	 *
	 * @param front Front unit vector. Must be normalize.
	 */
	void	setDirection(const gm::Vec3f &front);

//---- Operators ---------------------------------------------------------------
	/**
	 * @brief Copy operator of Camera class.
	 *
	 * @param obj The Camera to copy.
	 *
	 * @return The Camera copied from parameter.
	 */
	Camera	&operator=(const Camera &obj);

//**** PUBLIC METHODS **********************************************************
//---- move --------------------------------------------------------------------
	/**
	 * @brief Move camera with a vector.
	 *
	 * @param direction A vector to tell which direction to go. x for right, y for up, z for front.
	 * @param speed The distance to move.
	 */
	void	move(const gm::Vec3f &direction, const float speed);
	/**
	 * @brief Move camera in front direction.
	 *
	 * @param speed The distance to move.
	 */
	void	moveFront(const float speed);
	/**
	 * @brief Move camera in up direction.
	 *
	 * @param speed The distance to move.
	 */
	void	moveUp(const float speed);
	/**
	 * @brief Move camera in right direction.
	 *
	 * @param speed The distance to move.
	 */
	void	moveRight(const float speed);

//---- rotate ------------------------------------------------------------------
	/**
	 * @brief Rotate camera on x axis.
	 *
	 * @param degrees Angle of rotation in degrees.
	 */
	void	rotateX(const float degrees);
	/**
	 * @brief Rotate camera on y axis.
	 *
	 * @param degrees Angle of rotation in degrees.
	 */
	void	rotateY(const float degrees);
	/**
	 * @brief Rotate camera on z axis.
	 *
	 * @param degrees Angle of rotation in degrees.
	 */
	void	rotateZ(const float degrees);

//---- update ------------------------------------------------------------------
	/**
	 * @brief Update camera when window size change.
	 *
	 * @param windowWidth New width of window.
	 * @param windowHeight New height of window.
	 */
	void	updateFromWindow(const int windowWidth, const int windowHeight);
	/**
	 * @brief Update camera when fov change.
	 *
	 * @param fov New fov.
	 */
	void	updateFOV(const float fov);

//**** STATIC METHODS **********************************************************

private:
//**** PRIVATE ATTRIBUTS *******************************************************
//**** PRIVATE METHODS *********************************************************
	void	computeRotation(void);
};

//**** FUNCTIONS ***************************************************************

#endif
