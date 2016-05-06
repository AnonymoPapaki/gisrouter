#pragma once
#include <cmath>
namespace Router 
{
	constexpr float PI = 3.14159265358979f;
	constexpr float EARTH_RADIUS_KM = 6371.0f;
	struct LatLng
	{
		LatLng(const float& lat, const float& lng);
		~LatLng();

		static float Distance(const LatLng& a, const LatLng& b);
		float lat, lng;

	};
}