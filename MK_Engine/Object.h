#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <typeindex>
#include "Component.h"

namespace mk
{
	class Physic;
	class Object
	{
		static std::vector<Object*> allObjects;

		std::map<std::type_index, Component*> allComponents;
		std::vector<Component*> allComponentsVector;
		void UpdateComponents();
	public:
		Object();
		template<typename comType> comType& addComponent()
		{
			comType* a = new comType(this);
			if (allComponents.find(typeid(a)) == allComponents.end())
				allComponents[typeid(a)] = a;
			allComponentsVector.emplace_back(a);
			return *a;
		}
		template<typename comType> comType* getComponent()
		{
			if (allComponents.find(typeid(comType*)) == allComponents.end()) {

				for (const std::pair< std::type_index, Component*> a : allComponents)
				{
					if (dynamic_cast<comType*>(a.second) != 0)
					{
						allComponents[typeid(comType*)] = a.second;
						return dynamic_cast<comType*>(a.second);
					}
				}
			}
			else {
				return dynamic_cast<comType*>(allComponents[typeid(comType*)]);
			}
			return nullptr;
		}
		template<typename comType> bool removeComponent()
		{
			allComponentsVector.erase(std::remove_if(allComponentsVector.begin(), allComponentsVector.end(), [](Component* a) 
				{ 
					return dynamic_cast<comType*>(a) != 0; 
				}), allComponentsVector.end());
			
			for (auto it = allComponents.begin(); it != allComponents.end(); ) {
				if (dynamic_cast<comType*>((*it).second) != 0) {
					it = allComponents.erase(it);
				}
				else ++it;
			}
			return true;
		}
		~Object();
		void removeAllComponents();
		friend Physic;
	};
}
