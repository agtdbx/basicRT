#include <Camera.hpp>

//**** STATIC FUNCTIONS DEFINE *************************************************
//**** INITIALISION ************************************************************
//---- Constructors ------------------------------------------------------------

Camera::Camera(void)
{
	this->winRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	this->fov = FOV;

	this->planeHeight = tan(gm::radians(this->fov * 0.5f)) * 2.0f;
	this->planeWidth = this->planeHeight * this->winRatio;

	this->position = gm::Vec3f(0.0f, 0.0f, 0.0f);
	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;

	this->computeRotation();
}


Camera::Camera(const Camera &obj)
{
	this->position = obj.position;
	this->front = obj.front;
	this->up = obj.up;
	this->right = obj.right;
	this->pitch = obj.pitch;
	this->yaw = obj.yaw;
	this->roll = obj.roll;
	this->planeWidth = obj.planeWidth;
	this->planeHeight = obj.planeHeight;
	this->winRatio = obj.winRatio;
}

//---- Destructor --------------------------------------------------------------

Camera::~Camera()
{

}

//**** ACCESSORS ***************************************************************
//---- Getters -----------------------------------------------------------------
//---- Setters -----------------------------------------------------------------

void	Camera::setPosition(const gm::Vec3f &position)
{
	this->position = position;
}


void	Camera::setRotation(const float pitch, const float yaw, const float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->computeRotation();
}


void	Camera::setDirection(const gm::Vec3f &front)
{
	this->pitch = gm::degrees(asin(front.y));
	this->yaw = gm::degrees(atan2(front.z, front.x));
	this->roll = 0.0f;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->computeRotation();
}

//---- Operators ---------------------------------------------------------------

Camera	&Camera::operator=(const Camera &obj)
{
	if (this == &obj)
		return (*this);

	this->front = obj.front;
	this->up = obj.up;
	this->right = obj.right;
	this->pitch = obj.pitch;
	this->yaw = obj.yaw;
	this->roll = obj.roll;
	this->planeWidth = obj.planeWidth;
	this->planeHeight = obj.planeHeight;
	this->winRatio = obj.winRatio;

	return (*this);
}

//**** PUBLIC METHODS **********************************************************
//---- move --------------------------------------------------------------------

void	Camera::move(const gm::Vec3f &direction, const float speed)
{
	this->position += this->right * direction.x * speed
						+ this->up * direction.y * speed
						+ this->front * direction.z * speed;
}


void	Camera::moveFront(const float speed)
{
	this->position += this->front * speed;
}


void	Camera::moveUp(const float speed)
{
	this->position += this->up * speed;
}


void	Camera::moveRight(const float speed)
{
	this->position += this->right * speed;
}

//---- rotate ------------------------------------------------------------------

void	Camera::rotateX(const float degrees)
{
	this->pitch += degrees;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->computeRotation();
}


void	Camera::rotateY(const float degrees)
{
	this->yaw += degrees;
	this->computeRotation();
}


void	Camera::rotateZ(const float degrees)
{
	this->roll += degrees;
	this->computeRotation();
}

//---- update ------------------------------------------------------------------

void	Camera::updateFromWindow(const int windowWidth, const int windowHeight)
{
	this->winRatio = (float)windowWidth / (float)windowHeight;

	this->planeHeight = tan(gm::radians(this->fov * 0.5f)) * 2.0f;
	this->planeWidth = this->planeHeight * this->winRatio;

	this->computeRotation();
}


void	Camera::updateFOV(const float fov)
{
	this->fov = fov;

	if (this->fov < 0.0f)
		this->fov = 0.0f;
	if (this->fov > 360.0f)
		this->fov = 360.0f;

	this->planeHeight = tan(gm::radians(this->fov * 0.5f)) * 2.0f;
	this->planeWidth = this->planeHeight * this->winRatio;

	this->computeRotation();
}

//**** STATIC METHODS **********************************************************
//**** PRIVATE METHODS *********************************************************

void	Camera::computeRotation(void)
{
	this->front.x = cos(gm::radians(this->pitch)) * cos(gm::radians(this->yaw));
	this->front.y = sin(gm::radians(this->pitch));
	this->front.z = cos(gm::radians(this->pitch)) * sin(gm::radians(this->yaw));
	this->front = gm::normalize(this->front);

	this->right = gm::normalize(gm::cross(this->front,gm::Vec3f(0.0f, 1.0f, 0.0f)));
	this->up = gm::normalize(gm::cross(this->right, this->front));
}

//**** FUNCTIONS ***************************************************************
//**** STATIC FUNCTIONS ********************************************************
