#include "utility.h"
#include "Token.h"
#include "Token_stream.h"
#include <string>

// discards input until the next print token.

void clean_up_mess()
{
	ts.ignore(print);
}


// reports an error by throwing a runtime_error.

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