#include "PCH/PCH.h"
#include "VMLEntry.h"

namespace Volund
{
	void VMLEntry::PushBack(const std::string& Value)
	{
		this->_Values.push_back(Value);
	}

	uint32_t VMLEntry::Size() const
	{
		return (uint32_t)this->_Values.size();
	}

	VMLValue& VMLEntry::operator[](uint32_t Index)
	{
		if (Index < this->_Values.size())
		{
			return this->_Values[Index];
		}
		else
		{
			VOLUND_ERROR("Index exceeds boundary of VML entry (%d)!", Index);
		}
	}
}