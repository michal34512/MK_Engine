#pragma once

namespace mk
{
	class Object;
	class Component
	{
	public:
		Object* gameObject;
		virtual ~Component();
		virtual void Update();
	};
}
