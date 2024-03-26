#include "carpc/base/helpers/functions/pointer.hpp"
#include "carpc/tools/parameters/CmdLine.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "CMDLINE"



using namespace carpc::tools::parameters;



const char* const wrong_param_prefix = "---";
const size_t wrong_param_prefix_size = strlen( wrong_param_prefix );
const char* const short_param_prefix = "-";
const size_t short_param_prefix_size = strlen( short_param_prefix );
const char* const long_param_prefix = "--";
const size_t long_param_prefix_size = strlen( long_param_prefix );
const char* const delimiter = "=";
const size_t delimiter_size = strlen( delimiter );



CmdLine::CmdLine( const std::list< Parameter >& params )
   : Base( params, "CMDLINE" )
{
}

CmdLine::tSptr CmdLine::create( int argc, char** argv )
{
   if( nullptr == argv )
      return nullptr;

   std::list< Parameter > params;

   char* p_argument = nullptr;
   char* p_value = nullptr;

   for( int i = 1; i < argc; ++i )
   {
      char* item = argv[i];
      // SYS_WRN( "processing: %s", item );
      if( 0 == strncmp( item, wrong_param_prefix, wrong_param_prefix_size ) )
      {
         SYS_ERR( "processing wrong parameter" );
         return nullptr;
      }
      else if( 0 == strncmp( item, long_param_prefix, long_param_prefix_size ) )
      {
         // --
         SYS_DBG( "processing long parameter" );
         if( char* p_delimiter = strchr( item, (int)*delimiter ) )
         {
            // --argument=value
            char* argument_ptr = item + long_param_prefix_size;
            size_t argument_size = (size_t)carpc::diff( p_delimiter, argument_ptr );
            p_argument = (char*)malloc( argument_size + 1 );
            strncpy( p_argument, argument_ptr, argument_size );
            p_argument[ argument_size ] = 0;

            char* value_ptr = p_delimiter + 1;
            size_t value_size = strlen( p_delimiter );
            p_value = (char*)malloc( value_size + 1 );
            strncpy( p_value, value_ptr, value_size );
            p_value[ value_size ] = 0;
         }
         else
         {
            // --option
            char* option_ptr = item + long_param_prefix_size;
            size_t option_size = strlen( option_ptr );
            p_argument = (char*)malloc( option_size + 1 );
            strncpy( p_argument, option_ptr, option_size );
            p_argument[ option_size ] = 0;
         }
      }
      else if( 0 == strncmp( item, short_param_prefix, short_param_prefix_size ) )
      {
         // -
         SYS_DBG( "processing short parameter" );
         char* argument_ptr = item + short_param_prefix_size;
         size_t argument_size = strlen( argument_ptr );
         p_argument = (char*)malloc( argument_size + 1 );
         strncpy( p_argument, argument_ptr, argument_size );
         p_argument[ argument_size ] = 0;

         if( argc > i + 1 )
         {
            char* next_item = argv[i + 1];
            if( 0 != strncmp( next_item, short_param_prefix, short_param_prefix_size ) )
            {
               // 
               SYS_DBG( "processing short parameter value" );
               char* value_ptr = next_item;
               size_t value_size = strlen( value_ptr );
               p_value = (char*)malloc( value_size + 1 );
               strncpy( p_value, value_ptr, value_size );
               p_value[ argument_size ] = 0;
               ++i;
            }
         }
      }
      else
      {
         // 
         SYS_ERR( "unexpected short parameter value" );
         // return nullptr;
      }

      params.push_back( Parameter{ p_argument, p_value } );
      p_argument = nullptr;
      p_value = nullptr;
   }

   struct make_shared_enabler : public CmdLine
   {
      make_shared_enabler( const std::list< Parameter >& params )
         : CmdLine( params )
      { }
   };

   return std::make_shared< make_shared_enabler >( params );
}
