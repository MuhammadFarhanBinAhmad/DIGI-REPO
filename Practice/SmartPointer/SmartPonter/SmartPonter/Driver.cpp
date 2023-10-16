//SMART POINTER
/*unique_ptr
* shared_ptr
* weak_ptr
*/

#include <iostream>
#include <string>
#include <memory>


//The idea of smart pointer is all about ownership and more safety and security than calling new

class Entity
{
public:
	Entity()
	{
		std::cout << "CreatedEntity!\n";
	}
	~Entity()
	{
		std::cout << "DestroyedEntity\n";
	}
	void Print()
	{

	}
};

int main()
{

	{
		//First scope
		std::shared_ptr<Entity> e0;
		{
			//2nd scope
			//std::unique_ptr<Entity> = new Entity();// Cant use new cause unique_ptr is explicit. Must call its constructor
			//std::unique_ptr<Entity> entity(new Entity()); // Not recommend to use this due to possible exception error

			//std::unique_ptr<Entity> entity = std::make_unique<Entity>();//safer if constructor throw exception and help avoid dangling pointer, causing mem leak

			//std::unique_ptr<Entity> e0 = entity;//Unique pointer cant be copy/shared.Thats because when the unique pointer dies, those copying will be pointing to nothing which can cause error. If like to share, use shared_ptr

			/*Reference counting : Basically count how many reference are there to that pointer.By default its 1(the original) and you could create another share pointer that copies the original.
			*Thus leading to 2. When the 1st one die, there is still one more. But the moment its goes to 0, it will automatically delete itself
			*/
			Entity* test = new Entity;

			//Since its a share pointer, it can copy one another and every copy make increases the amount of references
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			std::shared_ptr<Entity> sharedEntity2(test);//See this. Dont do this because if multiple object point to this, double deletion will occur

			e0 = sharedEntity;
			//Its like share pointer except this will not increase the reference count
			//weak pointer can be use to check is shared pointer is still alive;
			std::weak_ptr<Entity> weakEntity = sharedEntity;

			//when this scope ends, sharedEntity will be deleted but shared_ptr will not be deleted as there is still one more reference to a pointer still(e0);
			//entity->Print();

		}
		std::cin.get();
	}

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}
/*****************************************************************//**
 * \file	Main.cpp
 * \brief	Entry point of the program, contains main()
 *
 * \author	Jun Rong
 * \date	05-SEP-2023
***********************************************************************/

#include "Pch.h"
#include "Engine/Engine.h"

#include "Engine/ANC.h"
#include "DataSerialize/DataCenter.h"
#include "Timer/TimerThreadManager.h"

static void Initialize_Engine();
static void CleanUp();

void TempAutoSave()
{
	TimerThreadManager timerManager;
	timerManager.StartTimerThread();
	while (true)
	{
		// Check for an exit condition and stop the timer thread if needed
		if (!timerManager.timerRunning)
		{
			MainDataCenter.SerializeData(GAMEOBJECT, "Data/DefaultEnemyData.json");
			break;
		}
	}
}

/*!***********************************************************************
* \brief
*	Entry point to the program.
*
* \return
*	0 if exit is good. Else returns the error exit code.
*************************************************************************/

int WinMain() {
	Initialize_Engine();


	//std::thread anotherThread(TempAutoSave);
	while (ANC::Core.Run()) {
		try {
			// Start profiling.
			ANC_Debug::ANC_Debug_Profiler::ProfileSystem(ANC_Debug::ANC_Debug_Profiler::MAIN_LOOP);
			// Update input system.
			ANC::Input.Update();
			// Update engine.
			ANC::Core.Update();
			// Tick engine's time.
			ANC::Time.Update();
			// Update game.
			//ANC::Game.Update();
			ECS::SceneMgr.Update();
			// Render graphics.
			ANC::Graphics.Update();
			// Update engine editor. (ImGui interface)
			ANC::Editor.Update();
			// DataCenter update
			MainDataCenter.DataCenterUpdate();

			ANC_Debug::ANC_Debug_Profiler::ProfileSystem("Swap Buffers");
			// Swap buffers: front <-> back
			glfwSwapBuffers(ANC::Core.Window());
			ANC_Debug::ANC_Debug_Profiler::ProfileSystem("Swap Buffers", false);

			// Stop profiling.
			ANC_Debug::ANC_Debug_Profiler::ProfileSystem(ANC_Debug::ANC_Debug_Profiler::MAIN_LOOP, false);
		}
		catch (const std::exception& e) {
			ANC_Debug::ANC_Crash_Logger crash(e);
			break;
		}
		catch (const std::string& e) {
			ANC_Debug::ANC_Crash_Logger crash(e.c_str());
			break;
		}
		catch (const char* e) {
			ANC_Debug::ANC_Crash_Logger crash(e);
			break;
		}
		catch (...) {
			ANC_Debug::ANC_Crash_Logger crash("Unknown exception caught.");
			break;
		}
	}
	//Need find better way to end program cause, if not handle properly, may cause mem leak
	//So far no need worry cause other thread not handling mem allocation
	//std::exit(0);//Enable program to end to without having to wait for other thread to end
	//anotherThread.join();
	CleanUp();

	// Terminate program.
	return EXIT_SUCCESS;
}

//========================================================
//\brief
//	Initializes the game engine and its associated engine
//	functions.
//========================================================
static void Initialize_Engine() {
	// Load saved config for engine.
	ANC_Configs configs;
	configs.Load();

	if (!configs.Status()) {
		std::cerr << "CONFIG ERROR: Unable to load configs for engine.";
		std::exit(EXIT_FAILURE);
	}
	MainDataCenter.DeserializeData();
	// Load main engine functionalities.
	ANC::Core.Initialize();

	ANC::Resource.Load();

	ANC::Input.Initialize();
	ANC::Editor.Initialize();
	ANC::Graphics.Initialize();
	ECS::SceneMgr.Initialize();

}

//========================================================
//\brief
//	Terminates running resources to ensure application
//	ends correctly.
//========================================================
void CleanUp() {
	//Output Json File
	MainDataCenter.SerializeData(GAMEOBJECT, "Data/DefaultEnemyData.json");
	//Free Gameobject
	MainDataCenter.FreeData();
	// Stop game first before engine.
	// Stop input system.
	ANC::Input.Quit();
	// Stop engine editor.
	ANC::Editor.Quit();
	// Stop core last.
	ANC::Core.Quit();
}
