#pragma once

#include "carpc/tools/parameters/Base.hpp"



namespace carpc::tools::parameters {

   class Config: public Base
   {
      private:
         Config( const std::list< Parameter >& params );
      public:
         ~Config( ) = default;
         static tSptr create( const char* const );
   };


} // namespace carpc::tools::parameters
