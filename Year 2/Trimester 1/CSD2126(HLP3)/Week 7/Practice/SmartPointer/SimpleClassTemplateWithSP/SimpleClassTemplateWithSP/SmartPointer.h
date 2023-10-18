#pragma once
#include <memory>
#include <iostream>
#include <string>

//template<typename T>
//class smrt_pointer
//{
//public:
//	smrt_pointer() = default;
//	explicit smrt_pointer(const T& val) : value(std::make_unique<T>(val)) {}
//	smrt_pointer(smrt_pointer const& rhs) : value(std::make_unique<T>(*(rhs.value))){}
//	smrt_pointer(smrt_pointer&& rhs) noexcept
//	{
//		value = std::move(rhs.value);
//	}
//	smrt_pointer& operator=(smrt_pointer const& rhs)
//	{
//		if (this != &rhs)
//		{
//			value = std::make_unique<T>(*(rhs.value));
//		}
//		return *this;
//	}
//	smrt_pointer& operator=(smrt_pointer && rhs) noexcept
//	{
//		if (this != &rhs)
//		{
//			value = std::move(rhs.value);
//			rhs.value = nullptr;
//		}
//		return *this;
//	}
//	~smrt_pointer()
//	{
//		std::cout << "Smart pointer deleted\n";
//	}
//	T& operator* () const
//	{
//		return *(value);
//	}
//	T* operator->() const
//	{
//		return value.get();
//	}
//	T* get() const
//	{
//		return value.get();
//	}
//	void print() const
//	{
//		if (value)
//		{
//			std::cout << "value: " << *value << std::endl;
//		}
//		else
//		{
//			std::cout << "No value"<< std::endl;
//		}
//	}
//private:
//	std::unique_ptr<T> value;
//};
template<typename T>
class smrt_pointer 
{
public:
	smrt_pointer() = default;
	explicit smrt_pointer(const T& value) : value(std::make_unique<T>(value)) {}
	smrt_pointer(const smrt_pointer& other) : value(std::make_unique<T>(*other.value)) {}
	smrt_pointer(smrt_pointer&& rhs) noexcept
	{
		value = std::move(rhs.value);
	}
	smrt_pointer& operator=(const smrt_pointer& other) {
		if (this != &other) 
		{
			value = std::make_unique<T>(*other.value);
		}
		return *this;
	}
	smrt_pointer& operator=(smrt_pointer&& rhs) noexcept
	{
		if (this != &rhs)
		{
			value = std::move(rhs.value);
		}
		return *this;
	}
	T& operator* () const
	{
		return *(value);
	}
	T* operator->() const
	{
		return value.get();
	}
	T* get() const
	{
		return value.get();
	}
	void print() const 
	{
		if (value)
		{
			std::cout << *(value) << "\n";
		}
		else
		{
			std::cout << "No value found\n";
		}
	}
private:
	std::unique_ptr<T> value;
};
