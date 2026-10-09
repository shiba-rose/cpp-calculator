#include "utility.h"
#include "Token.h"
#include "Token_stream.h"
#include <string>
void clean_up_mess()
{
	ts.ignore(print);
}


// error() simply disguises throws:
[[noreturn]]  void error (const std::string& s)
{
  throw std::runtime_error(s);
}

[[noreturn]] void error (const std::string& s, const std::string& s2)
{
  error (s + s2);
}

[[noreturn]] void error (const std::string& s, int i)
{
  std::ostringstream os;
  os << s << ": " << i;
  error (os.str());
}