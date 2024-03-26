#pragma once

#include <cstdlib>
#include <cstdint>
#include <string>
#include <list>




// value --------------------------------+
// delimiter -------------------------+  |
// parameter --------------------+    |  |
// prefix ------------------+    |    |  |
//                          |    |    |  |
//                         --parameter=value
//                         |                |
//                         +----------------+
//                                  |
// argument ------------------------+

namespace carpc::tools::parameters {

   struct Parameter
   {
      // const char* const short_name = nullptr;
      // const char* const long_name = nullptr;
      const char* const name = nullptr;
      const char* const value = nullptr;
   };

} // namespace carpc::tools::parameters
