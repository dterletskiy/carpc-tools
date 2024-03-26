#include <fstream>
#include <filesystem>
#include <algorithm>

#include "carpc/base/helpers/functions/format.hpp"
#include "carpc/tools/parameters/Params.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "PARAMS"



using namespace carpc::tools::parameters;



Params::Params( int argc, char** argv, char** envp )
{
   mp_cmdline = carpc::tools::parameters::CmdLine::create( argc, argv );
   // mp_cmdline->print( );

   mp_env = carpc::tools::parameters::Env::create( envp );
   // mp_env->print( );

   if( mp_cmdline )
   {
      if( auto param = mp_cmdline->find( "config" ) )
      {
         mp_config = carpc::tools::parameters::Config::create( param->value );
         // mp_config->print( );
      }
   }

   if( mp_cmdline )
      m_params.push_back( mp_cmdline );

   if( mp_config )
      m_params.push_back( mp_config );

   if( mp_env )
      m_params.push_back( mp_env );



   // m_params.push_back( CmdLine::create( argc, argv ) );
   // m_params.push_back( Env::create( envp ) );

   // std::string file_name = std::filesystem::path( *argv ).filename( );
   // file_name += std::string( ".cfg" );
   // file_name = m_params[0]->value_or( "config", file_name ).first;
   // m_params.push_back( Config::create( file_name ) );
}

const Parameter* const Params::find( const char* const name ) const
{
   for( auto item: m_params )
   {
      if( const Parameter* const param = item->find( name ) )
      {
         return param;
      }
   }

   return nullptr;
}

const char* const Params::value( const char* const name ) const
{
   if( const Parameter* const param = find( name ) )
      return param->value;

   return nullptr;
}

const char* const Params::value_or( const char* const name, const char* const default_value ) const
{
   if( const char* const v = value( name ) )
      return v;

   return default_value;
}

void Params::print( ) const
{
   for( auto item: m_params )
      if( item )
         item->print( );
}
