#include "carpc/base/helpers/functions/pointer.hpp"
#include "carpc/tools/parameters/Config.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "CONFIG"



using namespace carpc::tools::parameters;



const char* const delimiter = "=";
const size_t delimiter_size = strlen( delimiter );



Config::Config( const std::list< Parameter >& params )
   : Base( params, "CONFIG" )
{
}

Config::tSptr Config::create( const char* const filename )
{
   if( nullptr == filename )
      return nullptr;

   std::list< Parameter > params;

   char line[1000];

   FILE* file = fopen( filename, "r" );

   if( nullptr == file )
   {
      SYS_ERR( "Can't opern file: '%s'", filename );
      return nullptr;
   }

   char* p_argument = nullptr;
   char* p_value = nullptr;

   while( nullptr != fgets( line, sizeof( line ), file ) )
   {
      int len = strlen( line );
      if( len > 0 && line[len - 1] == '\n' )
      {
         line[len - 1] = '\0';
      }

      // SYS_WRN( "processing: %s", line );
      if( char* p_delimiter = strchr( line, (int)*delimiter ) )
      {
         // argument=value
         char* argument_ptr = line;
         size_t argument_size = (size_t)carpc::diff( p_delimiter, argument_ptr );
         p_argument = (char*)malloc( argument_size + 1 );
         strncpy( p_argument, argument_ptr, argument_size );
         p_argument[ argument_size ] = 0;

         char* value_ptr = p_delimiter + 1;
         size_t value_size = strlen( value_ptr );
         p_value = (char*)malloc( value_size + 1 );
         strncpy( p_value, value_ptr, value_size );
         p_value[ value_size ] = 0;
      }
      else
      {
         // option
         char* option_ptr = line;
         size_t option_size = strlen( option_ptr );
         p_argument = (char*)malloc( option_size + 1 );
         strncpy( p_argument, option_ptr, option_size );
         p_argument[ option_size ] = 0;
      }

      params.push_back( Parameter{ p_argument, p_value } );
      p_argument = nullptr;
      p_value = nullptr;
   }

   fclose( file );

   struct make_shared_enabler : public Config
   {
      make_shared_enabler( const std::list< Parameter >& params )
         : Config( params )
      { }
   };

   return std::make_shared< make_shared_enabler >( params );
}
