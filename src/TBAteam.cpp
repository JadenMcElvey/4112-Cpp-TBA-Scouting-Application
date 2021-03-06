#include "TBAteam.hpp"
using namespace std;

bool teamDistrict(curlpp::Easy& request, const std::string& AuthKey, const std::string& teamKey, std::string& district)
{
	// gets the district of a team (requires teamKey)
	string url = "https://www.thebluealliance.com/api/v3/team/" + teamKey + "/districts";
	string response = performtostring(request, url, AuthKey);
	if (!parseError(response) && response != "")
	{
		parselast(response, "\"key\": \"", "\"", district);
		return true;
	}
	else
	{
		return false;
	}
}

bool teamEvents(curlpp::Easy& request, const std::string& AuthKey, const std::string& teamKey, std::vector<std::string>& events)
{
	// gets all event keys a team has or will compete at (requires teamKey)
  string url = "https://www.thebluealliance.com/api/v3/team/" + teamKey + "/events/keys";
	string response = performtostring(request, url, AuthKey);
	if (!parseError(response) && response != "")
	{
		parse(response, "\"", "\"", events);
		return true;
	}
	else
	{
		return false;
	}
}

bool yearTeamEvents(curlpp::Easy& request, const std::string& AuthKey, const std::string& teamKey, const std::string& year, std::vector<std::string>& events)
{
	// gets all event keys from a single FRC season (requires teamKey and year)
  string url = "https://www.thebluealliance.com/api/v3/team/" + teamKey + "/events/"+ year +"/keys";
	string response = performtostring(request, url, AuthKey);
	if (!parseError(response) && response != "")
	{
		parse(response, "\"", "\"", events);
		return true;
	}
	else
	{
		return false;
	}
}

bool teamMatchesAtEvent(curlpp::Easy& request, const std::string& AuthKey, const std::string& teamKey, const std::string& eventKey, std::vector<std::string>& matches)
{
	// get a teams match keys at an event (requires teamKey and eventKey)
	string url = "https://www.thebluealliance.com/api/v3/team/" + teamKey + "/event/"+ eventKey +"/matches/keys";
	string response = performtostring(request, url, AuthKey);
	if (!parseError(response) && response != "")
	{
		parse(response, "\"", "\"", matches);
		return true;
	}
	else
	{
		return false;
	}
}

bool teamQualsAtEvent(curlpp::Easy& request, const std::string& AuthKey, const std::string& teamKey, const std::string& eventKey, std::vector<std::string>& matches)
{
	// get a teams match keys at an event (requires teamKey and eventKey)
	string url = "https://www.thebluealliance.com/api/v3/team/" + teamKey + "/event/"+ eventKey +"/matches/keys";
	string response = performtostring(request, url, AuthKey);
	if (!parseError(response) && response != "")
	{
		parse(response, "\"", "\"", matches);
		std::vector<std::string>::iterator matchKey;
		for(matchKey = matches.begin(); matchKey != matches.end(); ++matchKey)
        {
            std::string qualifierMatch = "qm";
            if (search(matchKey->begin(), matchKey->end(), qualifierMatch.begin(), qualifierMatch.end()) == matchKey->end())
            {
                matches.erase(matchKey);
                --matchKey;
            }
        }
		return true;
	}
	else
	{
		return false;
	}
}

bool teamAwardsAtEvent(curlpp::Easy& request, const std::string& AuthKey, const std::string& teamKey, const std::string& eventKey, std::vector<std::string>& awards)
{
	// get a teams awards at an event (requires teamKey and eventKey)
	string url = "https://www.thebluealliance.com/api/v3/team/" + teamKey + "/event/"+ eventKey +"/awards";
	string response = performtostring(request, url, AuthKey);
	if (!parseError(response) && response != "")
	{
		parse(response, "\"name\": \"", "\"", awards);
		return true;
	}
	else
	{
		return false;
	}
}
