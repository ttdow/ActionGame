#include "Entity.h"

Entity::Entity(std::string name) : name(name) {}

bool Entity::attachComponent(Component& component, std::string name)
{
	/*
	if (this->components.emplace(name, component).second)
	{
		component.owner = *this;
		return true;
	}
	else
		return false;
	*/

	return false;
}

Component* Entity::getComponent(std::string name)
{
	auto result = components.find(name);

	if (result != components.end())
		return &result->second;
	else
		return nullptr;
}