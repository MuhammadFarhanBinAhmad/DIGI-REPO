//SMART POINTER
/*unique_ptr
* shared_ptr
* weak_ptr
*/

#include <iostream>
#include <string>
#include <memory>

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

			//Since its a share pointer, it can copy one another and every copy make increases the amount of references
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			e0 = sharedEntity;

			//Its like share pointer except this will not increase the reference count
			//weak pointer can be use to check is shared pointer is still alive;
			std::weak_ptr<Entity> weakEntity = sharedEntity;

			//when this scope ends, sharedEntity will be deleted but shared_ptr will not be deleted as there is still one more reference to a pointer still(e0);
			//entity->Print();
		}

	}
	std::cin.get();
}
