#include "Parser.h"

//internal
#include "rapidjson\reader.h"
#include "rapidjson\prettywriter.h"
using namespace rapidjson;

struct JsonHandler {
	std::vector<Router::Order> _orders;
	int flags = 0;
	enum {
		PUSH_ORDER,
		PUSH_LAT,
		PUSH_LNG,
		PUSH_TIME
	};

	std::vector<Router::Order> GetOrders()
	{
		return this->_orders;
	}

	bool Null()
	{

		return true;
	}
	bool Bool(bool b)
	{
		return true;
	}
	bool Int(int i)
	{
		return true;
	}
	bool Uint(unsigned u)
	{
		return true;
	}
	bool Int64(int64_t i)
	{
		return true;
	}
	bool Uint64(uint64_t u)
	{
		return true;
	}
	bool Double(double d)
	{
		switch (flags)
		{
		case PUSH_LAT: _orders.back().location.lat = d; break;
		case PUSH_LNG: _orders.back().location.lng = d; break;

		default:
			break;
		}
		return true;
	}
	bool RawNumber(const char* str, SizeType length, bool copy) 
	{
		return true;
	}
	bool String(const char* str, SizeType length, bool copy) 
	{
		return true;
	}
	bool StartObject()
	{
		return true;
	}
	bool Key(const char* str, SizeType length, bool copy)
	{
		if (strcmp(str, "location") == 0)
		{
			_orders.push_back(Router::Order());
			flags = PUSH_ORDER;
		}
		else if (strcmp(str, "lat") == 0)
			flags = PUSH_LAT;
		else if (strcmp(str, "lng") == 0)
			flags = PUSH_LNG;
		else if (strcmp(str, "time") == 0)
			flags = PUSH_TIME;
		return true;
	}
	bool EndObject(SizeType memberCount)
	{

		return true;
	}
	bool StartArray()
	{

		return true;
	}
	bool EndArray(SizeType elementCount)
	{
		return true;
	}
};



namespace Router
{

	std::vector<Order> JSONParser::Parse(const std::string& str)
	{

		JsonHandler handler;
		Reader reader;
		StringStream ss(str.c_str());
		reader.Parse(ss, handler);
		return handler.GetOrders();
	}

	std::string JSONParser::ToString(const std::vector<Order>& orders)
	{
		StringBuffer sb;
		PrettyWriter<StringBuffer> out(sb);

		out.StartArray();
		for (auto order : orders)
		{
			out.StartObject();
				out.String("location");
					out.StartObject();
						out.String("lat");
							out.Double(order.location.lat);
						out.String("lng");
							out.Double(order.location.lng);
					out.EndObject();
				out.String("time");
				out.Uint64(order.time);
			out.EndObject();
		}
		out.EndArray();
		return sb.GetString();
	}

}