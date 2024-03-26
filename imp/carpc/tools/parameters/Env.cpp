#include "carpc/base/helpers/functions/pointer.hpp"
#include "carpc/tools/parameters/Env.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "ENV"



using namespace carpc::tools::parameters;



const char* const delimiter = "=";
const size_t delimiter_size = strlen( delimiter );



Env::Env( const std::list< Parameter >& params )
   : Base( params, "ENV" )
{
}

Env::tSptr Env::create( char** envp )
{
   if( nullptr == envp )
      return nullptr;

   std::list< Parameter > params;

   char* p_argument = nullptr;
   char* p_value = nullptr;

   for( int count = 0; nullptr != envp[ count ]; ++count )
   {
      char* item = envp[ count ];

      // SYS_WRN( "processing: %s", item );
      char* p_delimiter = strchr( item, (int)*delimiter );
      if( nullptr == p_delimiter )
      {
         SYS_ERR( "wrong environment variable format: '%s'", item );
         return nullptr;
      }

      // argument=value
      char* argument_ptr = item;
      size_t argument_size = (size_t)carpc::diff( p_delimiter, argument_ptr );
      p_argument = (char*)malloc( argument_size + 1 );
      strncpy( p_argument, argument_ptr, argument_size );
      p_argument[ argument_size ] = 0;

      char* value_ptr = p_delimiter + 1;
      size_t value_size = strlen( p_delimiter );
      p_value = (char*)malloc( value_size + 1 );
      strncpy( p_value, value_ptr, value_size );
      p_value[ value_size ] = 0;

      params.push_back( Parameter{ p_argument, p_value } );
      p_argument = nullptr;
      p_value = nullptr;
   }

   struct make_shared_enabler : public Env
   {
      make_shared_enabler( const std::list< Parameter >& params )
         : Env( params )
      { }
   };

   return std::make_shared< make_shared_enabler >( params );
}
