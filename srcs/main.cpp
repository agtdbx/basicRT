#include <define.hpp>
#include <InputManager.hpp>
#include <Camera.hpp>
#include <Sphere.hpp>

#include <iostream>
#include <SFML/Graphics.hpp>

struct Scene
{
	Camera							camera;
	std::vector<Sphere>				spheres;
	gm::Vec3f						lightPos = {0, 0, 0};
	int								renderPrecision = 10;
	bool							needRender = true;
};


static void	update(sf::RenderWindow *window, InputManager *inputManager);
static void	tick(sf::RenderWindow *window, const InputManager *inputManager, Scene &scene);
static void	draw(sf::RenderWindow *window, Scene &scene);

int main(void)
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML game base");
	window.setFramerateLimit(FPS_CAP);

	InputManager	inputManager;
	Scene	scene;

	scene.camera.setPosition(gm::Vec3f(0, 0, -10));
	scene.camera.setDirection(gm::Vec3f(0, 0, 1));
	scene.lightPos = gm::Vec3f(0, 10, -10);

	scene.spheres = {
		{{0, 0, 0}, 3, {255, 0, 0}},
		{{0, -103, 0}, 100, {0, 255, 0}},
		{{5, 0, 0}, 3, {0, 0, 255}},
	};

	sf::Clock	clock;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		update(&window, &inputManager);
		if (inputManager.keyPressed(sf::Keyboard::Escape))
			break;
		tick(&window, &inputManager, scene);
		draw(&window, scene);
	}

	return (0);
}


static void	update(sf::RenderWindow *window, InputManager *inputManager)
{
	sf::Event event;

	inputManager->update();
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else
			inputManager->listenEvent(&event);
	}
}


static void	tick(sf::RenderWindow *window, const InputManager *inputManager, Scene &scene)
{
	static sf::Clock	clock;
	static int			nbCall = 0;
	static float		totalDelta = 0.0f;

	// Compute delta time
	float delta = clock.restart().asSeconds();

	// Display fps in title
	totalDelta += delta;
	nbCall++;
	if (totalDelta >= FPS_DISPLAY_UPDATE)
	{
		float avgDelta = totalDelta / (float)nbCall;
		window->setTitle(std::to_string(1.0f / avgDelta));
		totalDelta = 0.0f;
		nbCall = 0;
	}

	// Scene precision
	if (inputManager->keyPressed(sf::Keyboard::Num1))
	{
		scene.renderPrecision = 1;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num2))
	{
		scene.renderPrecision = 2;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num3))
	{
		scene.renderPrecision = 3;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num4))
	{
		scene.renderPrecision = 4;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num5))
	{
		scene.renderPrecision = 5;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num6))
	{
		scene.renderPrecision = 6;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num7))
	{
		scene.renderPrecision = 7;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num8))
	{
		scene.renderPrecision = 8;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num9))
	{
		scene.renderPrecision = 9;
		scene.needRender = true;
	}
	else if (inputManager->keyPressed(sf::Keyboard::Num0))
	{
		scene.renderPrecision = 10;
		scene.needRender = true;
	}

	float	camMovSpeed = CAMERA_MOV_SPEED * delta;
	float	camRotSpeed = CAMERA_ROT_SPEED * delta;

	if (inputManager->keyDown(sf::Keyboard::LControl))
	{
		camMovSpeed *= CAMERA_SPRINT;
		camRotSpeed *= CAMERA_SPRINT;
	}

	// Camera movement
	if (inputManager->keyDown(sf::Keyboard::A))
	{
		scene.camera.moveRight(-camMovSpeed);
		scene.needRender = true;
	}
	else if (inputManager->keyDown(sf::Keyboard::D))
	{
		scene.camera.moveRight(camMovSpeed);
		scene.needRender = true;
	}
	if (inputManager->keyDown(sf::Keyboard::Space))
	{
		scene.camera.moveUp(camMovSpeed);
		scene.needRender = true;
	}
	else if (inputManager->keyDown(sf::Keyboard::LShift))
	{
		scene.camera.moveUp(-camMovSpeed);
		scene.needRender = true;
	}
	if (inputManager->keyDown(sf::Keyboard::W))
	{
		scene.camera.moveFront(camMovSpeed);
		scene.needRender = true;
	}
	else if (inputManager->keyDown(sf::Keyboard::S))
	{
		scene.camera.moveFront(-camMovSpeed);
		scene.needRender = true;
	}

	// Camera rotation
	if (inputManager->keyDown(sf::Keyboard::Left))
	{
		scene.camera.rotateY(-camRotSpeed);
		scene.needRender = true;
	}
	else if (inputManager->keyDown(sf::Keyboard::Right))
	{
		scene.camera.rotateY(camRotSpeed);
		scene.needRender = true;
	}
	if (inputManager->keyDown(sf::Keyboard::Up))
	{
		scene.camera.rotateX(camRotSpeed);
		scene.needRender = true;
	}
	else if (inputManager->keyDown(sf::Keyboard::Down))
	{
		scene.camera.rotateX(-camRotSpeed);
		scene.needRender = true;
	}
}


static void	draw(sf::RenderWindow *window, Scene &scene)
{
	if (!scene.needRender)
		return ;

	// clear the window with black color
	window->clear(sf::Color::Black);

	scene.needRender = false;

	Camera	&camera  = scene.camera;

	float	invWinW = 1.0f / (float)WINDOW_WIDTH;
	float	invWinH = 1.0f / (float)WINDOW_HEIGHT;
	gm::Vec3f	camW = camera.right * camera.planeWidth;
	gm::Vec3f	camH = camera.up * camera.planeHeight;
	gm::Vec3f	fakeCamPos = camera.position - (camera.front * 2.0f);

	int	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		float	rayY = y * invWinH - 0.5f;

		int	x = 0;
		while (x < WINDOW_WIDTH)
		{
			float	rayX = x * invWinW - 0.5f;

			gm::Vec3f	rayPos = camera.position + camW * rayX - camH * rayY;
			gm::Vec3f	rayDir = gm::normalize(rayPos - fakeCamPos);

			int		closestId = -1;
			float	closestDist = MAX_RAY_DIST;

			for (int i = 0; i < (int)scene.spheres.size(); i++)
			{
				float	dist = scene.spheres[i].intersectRay(rayPos, rayDir);

				if (dist < closestDist)
				{
					closestDist = dist;
					closestId = i;
				}
			}

			if (closestId == -1)
			{
				x += scene.renderPrecision;
				continue;
			}

			gm::Vec3f	hitPoint = rayPos + rayDir * closestDist;
			gm::Vec3f	normal = gm::normalize(hitPoint - scene.spheres[closestId].pos);
			gm::Vec3f	toLight = gm::normalize(scene.lightPos - hitPoint);
			float		lightStrength = gm::max(gm::dot(normal, toLight), 0.0f);

			if (lightStrength > 0.0f)
			{
				// Shadow
				for (int i = 0; i < (int)scene.spheres.size(); i++)
				{
					if (i == closestId)
						continue;

					float	dist = scene.spheres[i].intersectRay(hitPoint, toLight);

					if (dist < closestDist)
					{
						lightStrength = 0.0f;
						break;
					}
				}
			}

			if (lightStrength == 0.0f)
			{
				x += scene.renderPrecision;
				continue;
			}

			sf::RectangleShape	pixel;
			sf::Color	color = scene.spheres[closestId].color;

			pixel.setPosition(sf::Vector2f(x, y));
			pixel.setSize(sf::Vector2f(scene.renderPrecision, scene.renderPrecision));
			pixel.setFillColor({color.r * lightStrength, color.g * lightStrength, color.b * lightStrength});

			window->draw(pixel);

			x += scene.renderPrecision;
		}
		y += scene.renderPrecision;
	}

	// end the current frame
	window->display();
}
