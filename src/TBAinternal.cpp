#include "TBAinternal.hpp"
using namespace std;

string performtostring(curlpp::Easy& request, string& url)
{
  //returns TBA response as string to be parsed
  try {
    request.setOpt(new curlpp::options::Url(url));
    ostringstream requeststream;
    request.setOpt(new curlpp::options::WriteStream(&requeststream));
    request.perform();
    return requeststream.str();
  }
  catch ( curlpp::LogicError & e ) {
  cout << e.what() << endl;
    return "";
  }
  catch ( curlpp::RuntimeError & e ) {
  cout << e.what() << endl;
    return "";
  }
}

bool parse(std::string& response, std::string seperator, std::string& value)
{
  //use to parse for value after FIRST occurence of seperator
  string::iterator start, end;
  start = search(response.begin(), response.end(), seperator.begin(), seperator.end());
  advance(start, seperator.length());
  end = start;
  advance(end, value.length());
  copy(start, end, value.begin());
  return true;
}

bool parse(std::string& response, std::string seperator1, std::string seperator2, std::string& value)
{
  //use to parse for value between first occurence of two seperators
  string::iterator start, end;
  start = response.begin();
  start = search(start, response.end(), seperator1.begin(), seperator1.end());
  advance(start, seperator1.length());
  end = search(start, response.end(), seperator2.begin(), seperator2.end());
  value.resize(std::distance(start, end));
  copy(start, end, value.begin());
  return true;
}

bool parse(std::string& response, std::string seperator1, std::string seperator2, std::vector<std::string>& values)
{
  //use to parse for values between first occurence of two seperators
  std::string value;
  string::iterator start, end;
  start = response.begin();
  while (start != response.end())
  {
    start = search(start, response.end(), seperator1.begin(), seperator1.end());
    advance(start, seperator1.length());
    end = search(start, response.end(), seperator2.begin(), seperator2.end());
    value.resize(std::distance(start, end));
    copy(start, end, value.begin());
    values.push_back(value);
    start = end;
    start++;
    value.clear();
    start = search(start, response.end(), seperator1.begin(), seperator1.end());
  }
  return true;
}

bool parselast(std::string& response, std::string seperator, std::string& value)
{
  //finds value within TBA response after LAST occurence of seperator
  string::iterator start, end;
  start = find_end(response.begin(), response.end(), seperator.begin(), seperator.end());
  advance(start, seperator.length());
  end = start;
  advance(end, value.length());
  copy(start, end, value.begin());
  return true;
}

bool parselast(std::string& response, std::string seperator1, std::string seperator2, std::string& value)
{
  //use to parse for value between last occurence of two seperators
  string::iterator start, end;
  start = response.begin();
  start = find_end(start, response.end(), seperator1.begin(), seperator1.end());
  advance(start, seperator1.length());
  end = search(start, response.end(), seperator2.begin(), seperator2.end());
  value.resize(std::distance(start, end));
  copy(start, end, value.begin());
  return true;
}