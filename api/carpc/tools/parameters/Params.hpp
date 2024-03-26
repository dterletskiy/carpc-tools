#pragma once

#include <vector>

#include "carpc/tools/parameters/CmdLine.hpp"
#include "carpc/tools/parameters/Env.hpp"
#include "carpc/tools/parameters/Config.hpp"



namespace carpc::tools::parameters {

   class Params
   {
      public:
         enum class eType : std::uint8_t { CMD, ENV, CFG, ANY };

      public:
         Params( int argc, char** argv, char** envp );
         ~Params( ) = default;

      public:
         void print( ) const;
         bool exists( const char* const name, const eType& type = eType::ANY ) const;
         const Parameter* const find( const char* const name, const eType& type = eType::ANY ) const;
         const char* const value( const char* const name, const eType& type = eType::ANY ) const;
         const char* const value_or( const char* const name, const char* const default_value, const eType& type = eType::ANY ) const;

      protected:
         CmdLine::tSptr    mp_cmdline  = nullptr;
         Env::tSptr        mp_env      = nullptr;
         Config::tSptr     mp_config   = nullptr;
         std::vector< Base::tSptr >    m_params;
   };

} // namespace carpc::tools::parameters
