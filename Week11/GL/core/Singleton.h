#pragma once

#include <memory>

template <typename T>
class Singleton
{
private:
	static std::shared_ptr<T> _instance;
	
public:
	static std::shared_ptr<T> GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = std::make_shared<T>();
		}

		return _instance;
	}

	static void SetInstance(std::shared_ptr<T> instance)
	{	
		_instance = instance;
	}

	static void DestroyInstance()
	{
		if (_instance)
		{
			delete _instance;
		}
	}
};

template <typename T> std::shared_ptr<T> Singleton<T>::_instance = nullptr;