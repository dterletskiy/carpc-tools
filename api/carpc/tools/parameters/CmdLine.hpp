#pragma once

#include "carpc/tools/parameters/Base.hpp"



namespace carpc::tools::parameters {

   class CmdLine: public Base
   {
      private:
         CmdLine( const std::list< Parameter >& params );
      public:
         ~CmdLine( ) = default;
         static tSptr create( int argc, char** argv );
   };

} // namespace carpc::tools::parameters
