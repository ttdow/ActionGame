#pragma once

#include <string>
#include <unordered_map>

#include "Component.h"

class Entity
{
public:

	Entity(std::string name);

	std::string name;

	bool attachComponent(Component& component, std::string name);
	Component* getComponent(std::string name);

private:

	std::unordered_map<std::string, Component&> components;
};