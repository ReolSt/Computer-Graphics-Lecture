#pragma once

#include <memory>
template <typename T>
using GLWeakPtr = std::weak_ptr<T>;

template <typename T>
using GLSharedPtr = std::shared_ptr<T>;

template <typename T, typename... Args>
std::shared_ptr<T> GLCreateShared(Args... args)
{
	return std::make_shared<T>(args...);
}

template <typename T, typename... Args>
std::shared_ptr<T> GLCreate(Args... args)
{
	return std::make_shared<T>(args...);
}

template <typename T>
using GLUniquePtr = std::unique_ptr<T>;

template <typename T, typename... Args>
std::unique_ptr<T> GLCreateUnique(Args... args)
{
	return std::make_unique<T>(args...);
}