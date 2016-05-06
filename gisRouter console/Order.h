#pragma once
#include "LatLng.h"
#include <time.h>
namespace Router
{
	struct Order
	{
		LatLng location;
		time_t time;
		Order()
			: location(0, 0), time(0)
		{

		}
	};
}