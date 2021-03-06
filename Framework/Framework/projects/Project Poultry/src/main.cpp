#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <filesystem>
#include <fstream>

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "MainMenu.h"
#include "Application.h"

using namespace freebird; //referencing the module's includes/src's

using namespace std;

GLFWwindow* window;

//The main register for our ECS
entt::registry* ECS = nullptr;

//Scenes
Scene* currentScene = nullptr;
std::vector<Scene*> scenes;

int level = 0;

//Need to figure out how to load objects better for faster scene swtiching and loading
void SetActiveScene(int sceneNum)
{
	if (currentScene != nullptr)
	{
		currentScene->Unload();
	}

	scenes[sceneNum]->InitScene();
	ECS = scenes[sceneNum]->GetScene();
	currentScene = scenes[sceneNum];
	level = sceneNum + 1;

	if (level > 3)
		level = 1;
}

int main()
{

	if (!(window = Application::Init("Project Poultry", 1200, 1000)))
	{
		return 1;
	}

	Application::SetClearColor(glm::vec4(0.08f, 0.17f, 0.31f, 1.0f));

	scenes.push_back(new MainMenu("Main Menu", window));
	scenes.push_back(new Level1("Level 1", window));
	scenes.push_back(new Level2("Level 2", window));
	scenes.push_back(new Level3("Level 3", window));

	SetActiveScene(1);
	
	//Calculates our timer
	Application::Tick();

	//Main Loop//
	while (!Application::IsClosing()) {

		//Close the window
		Application::ProcessInput(window);

		//Updates the window
		Application::Update();

		//Grabs the time
		float dt = Application::GetDT();

		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			SetActiveScene(3);
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			SetActiveScene(2);
		}
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			SetActiveScene(1);
		}
		if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		{
			SetActiveScene(0);
		}

		if (currentScene->GetComplete())
		{
			currentScene->SetComplete(false);
			SetActiveScene(level);
		}

		currentScene->Update(dt);

		Application::SwapBuffers();
	}

	//Cleans up the window and glfw
	Application::Cleanup();

	Logger::Uninitialize();
	return 0;
}