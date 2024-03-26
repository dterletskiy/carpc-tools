#pragma once

#include "carpc/tools/parameters/Base.hpp"



namespace carpc::tools::parameters {

   class Env: public Base
   {
      private:
         Env( const std::list< Parameter >& params );
      public:
         ~Env( ) = default;
         static tSptr create( char** envp );
   };

} // namespace carpc::tools::parameters
