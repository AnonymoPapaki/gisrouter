#include "LatLng.h"
namespace Router
{
	__inline
		float d2r(const float& val)
	{
		return val * PI / 180.0f;
	}

	LatLng::LatLng(const float & lat, const float & lng)
		: lat(lat), lng(lng)
	{
	}

	LatLng::~LatLng()
	{
	}

	float LatLng::Distance(const LatLng & a, const LatLng & b)
	{
		float
			latA = d2r(a.lat),
			lngA = d2r(a.lng),
			latB = d2r(b.lat),
			lngB = d2r(b.lng);
		float
			u = sin((latB - latA) / 2.0f),
			v = sin((lngB - lngA) / 2.0f);
		return
			2.0f * EARTH_RADIUS_KM
			* asinf(sqrtf(u * u + cosf(latA)* cosf(latB) * v * v));
	}
}