#include "MemoryTracker.h"
#include <iostream>
#include <new>     // Para std::bad_alloc
#include <cstdlib> // Para malloc y free

namespace Engine::Debug
{
#ifdef _DEBUG
	// Usamos size_t porque es el estándar para contar bytes en memoria (evita números negativos por error)
	static int printAmount = 0;

	static size_t allocCount = 0;
	static size_t deleteCount = 0;
	static size_t sizeAllocCount = 0;
	static size_t sizeDeleteCount = 0;

#endif // _DEBUG

	void print()
	{
#ifdef _DEBUG
		// Calculamos las diferencias en el momento
		size_t totalCount = allocCount - deleteCount;
		size_t sizeDifference = sizeAllocCount - sizeDeleteCount;

		std::cout << "\n=== [ " << "Memoty track calls: " <<printAmount << " ] ===\n";
		std::cout << "Difference (Leaks): " << totalCount << '\n';
		std::cout << "MemAllocCounter: " << allocCount << '\n';
		std::cout << "SizeAllocCounter: " << sizeAllocCount << " bytes\n";
		std::cout << "MemDeleteCounter: " << deleteCount << '\n';
		std::cout << "SizeDeleteCounter: " << sizeDeleteCount << " bytes\n";
		std::cout << "SizeDifferenceCounter: " << sizeDifference << " bytes\n";
		std::cout << "===========================\n\n";

		printAmount++;
#endif // _DEBUG
	}
}

// =============================================================================
// SOBRECARGAS GLOBALES
// =============================================================================

#ifdef _DEBUG

#pragma warning(push)
#pragma warning(disable: 28251)

[[nodiscard]] void* operator new(size_t size)
{
	Engine::Debug::sizeAllocCount += size;
	Engine::Debug::allocCount++;

	void* ptr = malloc(size);
	if (!ptr) throw std::bad_alloc{};
	return ptr;
}

void operator delete(void* memory, size_t size) noexcept
{
	Engine::Debug::sizeDeleteCount += size;
	Engine::Debug::deleteCount++;
	free(memory);
}

[[nodiscard]] void* operator new[](size_t size)
{
	Engine::Debug::sizeAllocCount += size;
	Engine::Debug::allocCount++;

	void* ptr = malloc(size);
	if (!ptr) throw std::bad_alloc{};
	return ptr;
}

void operator delete[](void* memory, size_t size) noexcept
{
	Engine::Debug::sizeDeleteCount += size;
	Engine::Debug::deleteCount++;
	free(memory);
}

#pragma warning(pop)

#endif // _DEBUG