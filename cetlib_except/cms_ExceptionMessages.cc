#include "art/Utilities/ExceptionMessages.h"

#include "art/Utilities/Exception.h"

#include "MessageFacility/MessageLogger.h"
  using mf::LogSystem;

#include <string>
#include <sstream>


namespace edm {
  void
  printCmsException(cms::Exception& e, char const* prog)
  try {
    std::string programName(prog ? prog : "program");
    std::string shortDesc("CMSException");
    std::ostringstream longDesc;
    longDesc << "cms::Exception caught in " << programName << "\n"
             << e.explainSelf();
    LogSystem(shortDesc) << longDesc.str() << "\n";
  }
  catch(...) {
  }

  void printBadAllocException(char const *prog)
  try {
    std::string programName(prog ? prog : "program");
    std::string shortDesc("std::bad_allocException");
    std::ostringstream longDesc;
    longDesc << "std::bad_alloc exception caught in " << programName << "\n"
             << "The job has probably exhausted the virtual memory available to the process.\n";
    LogSystem(shortDesc) << longDesc.str() << "\n";
  }
  catch(...) {
  }

  void printStdException(std::exception& e, char const*prog)
  try {
    std::string programName(prog ? prog : "program");
    std::string shortDesc("StdLibException");
    std::ostringstream longDesc;
    longDesc << "Standard library exception caught in " << programName << "\n"
             << e.what();
    LogSystem(shortDesc) << longDesc.str() << "\n";
  }
  catch(...) {
  }

  void printUnknownException(char const *prog)
  try {
    std::string programName(prog ? prog : "program");
    std::string shortDesc("UnknownException");
    std::ostringstream longDesc;
    longDesc << "Unknown exception caught in " << programName << "\n";
    LogSystem(shortDesc) << longDesc.str() << "\n";
  }
  catch(...) {
  }

}  // namespace edm
