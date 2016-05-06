
#include "HttpServer.h"
#include "LatLng.h"
#include <iostream>
#include <vector>
#include "Parser.h"


int main(int argc, char** argv)
{
	Router::IO::HttpServer http(8081);
	Router::JSONParser parser;
	while (http.WaitRequest())
	{
		auto orders = parser.Parse(http.GetRequest());
	
		http.SendResponse(parser.ToString(orders));
	}
	return 0;
}