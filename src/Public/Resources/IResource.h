#pragma once

#include <Core/String.h>

class IResource
{
public:
	virtual ~IResource() = default;
protected:
	virtual IResource* LoadFromFile(String path) = 0;

	friend class ResourceManager;
};

