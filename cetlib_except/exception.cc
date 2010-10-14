// ======================================================================
//
// exception
//
// ======================================================================


#include "cetlib/exception.h"
#include <cctype>

using cet::exception;

typedef  exception::Category      Category;
typedef  exception::CategoryList  CategoryList;


// ======================================================================
// helpers:

bool
  ends_with_whitespace( std::string const & s )
{
  return s.empty() || std::isspace( *(s.end()-1) );
}

bool
  ends_with_newline( std::string const & s )
{
  return s.empty() || *(s.end()-1) == '\n';
}


std::exception *
  exception::clone() const
{
  return new exception(*this);
}


void
  exception::rethrow()
{
  throw *this;
}


// ======================================================================
// c'tors, d'tors:

exception::exception( Category const & c )
  : std::exception( )
  , ost_          ( )
  , category_     ( 1, c )
{ }


exception::exception( Category    const & c
                    , std::string const & m )
  : std::exception( )
  , ost_          ( )
  , category_     ( 1, c )
{
  ost_ << m;
  if( ! ends_with_whitespace(m) )
    ost_ << ' ';
}


exception::exception( Category    const & c
                    , std::string const & m
                    , exception   const & e )
  : std::exception( )
  , ost_          ( )
  , category_     ( 1, c )
{
  ost_ << m;
  if( ! ends_with_whitespace(m) )
    ost_ << ' ';
  category_.push_back( e.category() );
  append( e );
}


exception::~exception( ) throw()
{ }


// ======================================================================
// copy c'tor:

exception::exception( exception const & other )
  : std::exception( )
  , ost_          ( )
  , category_     ( other.category_ )
{
  ost_ << other.ost_.str();
}


// ======================================================================
// inspectors:

char const *
  exception::what( ) const throw()
{
  return explain_self().c_str();
}


std::string
  exception::explain_self( ) const
{
  std::ostringstream ost;

  ost << "---- " << category() << " BEGIN\n";

  std::string part( ost_.str() );
  ost << part;
  if( ! ends_with_newline(part) )
    ost << "\n";

  ost << "---- " << category() << " END\n";

  return ost.str();
}


std::string
  exception::category( ) const
{
  return category_.front();
}


CategoryList const &
  exception::history( ) const
{
  return category_;
}


std::string
  exception::root_cause( ) const
{
  return category_.back();
}


// ======================================================================
// mutators:

void
  exception::append( exception const & e ) const
{
  ost_ << e.explain_self();
}


void
  exception::append( std::string const & more_information ) const
{
  ost_ << more_information;
}


void
  exception::append( char const more_information[] ) const
{
  ost_ << more_information;
}


void
  exception::append( std::ostream& f(std::ostream&) ) const
{
  f(ost_);
}


void
  exception::append( std::ios_base& f(std::ios_base&) ) const
{
  f(ost_);
}


// ======================================================================


std::ostream &
  cet::operator << ( std::ostream & os, exception const & e )
{
  return os << e.explain_self();
}



