#pragma once

#include <memory>

#ifdef RR_PLATFORM_WINDOWS
	
#else
	#error Unsupported platform!
#endif

#ifdef RR_ENABLE_ASSERTS
	#define RR_ASSERT(x, ...) { if(!(x)) { RR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RR_CORE_ASSERT(x, ...) { if(!(x)) { RR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RR_ASSERT(x, ...)
	#define RR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define RR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace RoseRoot {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}