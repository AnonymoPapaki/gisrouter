#pragma once

#include "Order.h"
#include <vector>
#include <string>

namespace Router
{
	class JSONParser
	{
	public:
		std::vector<Order> Parse(const std::string& str);
		std::string ToString(const std::vector<Order>& orders); 
	};
}
