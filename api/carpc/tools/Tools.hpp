#pragma once

#include <string>



namespace carpc::tools::cmd {

   char* get_option( int, char**, const std::string& );
   bool is_option_exists( int, char**, const std::string&  );

} // namespace carpc::tools::cmd
