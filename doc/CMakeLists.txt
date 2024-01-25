find_package(Doxygen COMPONENTS dot)

if (NOT Doxygen_FOUND)
  message(WARNING "BUILD_DOCS set but Doxygen missing: no docs generated for ${CETMODULES_CURRENT_PROJECT_NAME}")
  return()
endif()

include(CetGenerateSphinxDocs)

set(cetlib_except_DOXYGEN_SOURCES
  ../cetlib_except/coded_exception.h
  ../cetlib_except/demangle.cc
  ../cetlib_except/demangle.h
  ../cetlib_except/exception.cc
  ../cetlib_except/exception.h
  ../cetlib_except/exception_category_matcher.h
  ../cetlib_except/exception_collector.cc
  ../cetlib_except/exception_collector.h
  ../cetlib_except/exception_message_matcher.h
)

set(DOXYGEN_ALLOW_UNICODE_NAMES YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_DOT_GRAPH_MAX_NODES 500)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)
set(DOXYGEN_DOT_UML_DETAILS YES)
set(DOXYGEN_DOT_WRAP_THRESHOLD 23)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_GENERATE_HTML NO)
set(DOXYGEN_GENERATE_XML YES)
set(DOXYGEN_INTERACTIVE_SVG YES)
set(DOXYGEN_INTERNAL_DOCS NO)
set(DOXYGEN_MARKDOWN_ID_STYLE "GITHUB")
set(DOXYGEN_PROJECT_BRIEF "C++ Classes and utilities related to handling exceptions.")
set(DOXYGEN_TEMPLATE_RELATIONS YES)
set(DOXYGEN_UML_LOOK YES)

doxygen_add_docs(${CETMODULES_CURRENT_PROJECT_NAME}_doxygen_xml
  ${${CETMODULES_CURRENT_PROJECT_NAME}_DOXYGEN_SOURCES}
  ALL
  USE_STAMP_FILE
  COMMENT "Generate XML reference documentation with Doxygen"
)
