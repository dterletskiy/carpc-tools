#include "carpc/tools/parameters/Base.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "PARAMS"



using namespace carpc::tools::parameters;



Base::Base( const std::list< Parameter >& params, const char* const dump_message )
   : m_params( params )
   , m_dump_message( dump_message)
{
}

const Parameter* const Base::find( const char* const name ) const
{
   for( auto& param: m_params )
   {
      if( 0 == strcmp( name, param.name ) )
      {
         return &param;
      }
   }

   return nullptr;
}

void Base::print( ) const
{
   const char* line = "----------------------------------------------";
   MSG_WRN( "%s BEGIN: %s %s", line, m_dump_message, line );
   for( auto param: m_params )
   {
      if( param.value )
      {
         SYS_DBG( "argument: %s", param.name );
         SYS_DBG( "value: %s", param.value );
      }
      else
      {
         SYS_DBG( "option: %s", param.name );
      }
      SYS_DBG( );
   }
   MSG_WRN( "%s  END:  %s %s", line, m_dump_message, line );
}
