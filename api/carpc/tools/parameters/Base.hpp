#pragma once

#include <memory>

#include "carpc/tools/parameters/Types.hpp"



namespace carpc::tools::parameters {

   class Base
   {
      public:
         using tSptr = std::shared_ptr< Base >;

      public:
         Base( const std::list< Parameter >& params, const char* const dump_message );
         ~Base( ) = default;

      public:
         void print( ) const;
         const Parameter* const find( const char* const name ) const;

      protected:
         std::list< Parameter >  m_params;
         const char* const       m_dump_message{ "DUMP" };
   };

} // namespace carpc::tools::parameters
