#pragma once

#include "IVisitor.h"

class IElement
{
public:
	virtual void accept(IVisitor & visitor) = 0;
	virtual ~IElement() = default;
};

