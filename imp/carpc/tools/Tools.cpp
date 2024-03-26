#include <algorithm>

#include "carpc/tools/Tools.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "TOOLS"



namespace carpc::tools::cmd {

   char* get_option( int argc, char** begin, const std::string & option )
   {
      char** end = begin + argc;
      char** itr = std::find( begin, end, option );
      if( itr != end && ++itr != end )
         return *itr;

      return nullptr;
   }

   bool is_option_exists( int argc, char** begin, const std::string& option )
   {
      char** end = begin + argc;
      return std::find( begin, end, option ) != end;
   }

} // namespace carpc::tools::cmd
