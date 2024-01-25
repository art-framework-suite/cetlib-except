find_package(Doxygen COMPONENTS dot)

if (NOT Doxygen_FOUND)
  message(WARNING "BUILD_DOCS set but Doxygen missing: no docs generated for ${CETMODULES_CURRENT_PROJECT_NAME}")
  return()
endif()

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

include(CetGenerateSphinxDocs)

if(NOT DEFINED SPHINX_THEME)
    set(SPHINX_THEME default)
endif()

if(NOT DEFINED SPHINX_THEME_DIR)
    set(SPHINX_THEME_DIR)
endif()

# configured documentation tools and intermediate build results
#set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")

# Sphinx cache with pickled ReST documents
set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")

# HTML output directory
# --- doing a bit of extra work here. Why?
#        + we want to see what directory are people putting their docs
#          do we want them to make and environement variable for that?
#        + once we know that this dir exists, we want to check does the
#          product dir exist there (e.g. all_docs/cetlib_except exists)
#          if not then we should probably make it ourselves
#        + and then we do the same for the version being developed
#          the goal is for the all_docs dir to look similar to scisoft
#          in directory structure.

#set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/html")
#set(SPHINX_HTML_DIR "$ENV{MRB_TOP}/all_docs/cetlib_except")
#set(SPHINX_HTML_DIR "$ENV{MRB_TOP}/all_docs/${PROJECT_NAME}/$ENV{}")
#message("\n\n\n\n\n\n")

set(TOP_DOCS_DIR "$ENV{MRB_TOP}/all_docs")

# looking for top level dir
if(EXISTS "${TOP_DOCS_DIR}")
  #message("I can use exists this way. all_docs is there.")
  set(PROJ_DOCS_DIR "${TOP_DOCS_DIR}/${PROJECT_NAME}")


  # looking for project dir
  if(EXISTS "${PROJ_DOCS_DIR}")
    #message("cetlib_except dir is here")
    string(TOUPPER ${PROJECT_NAME} ENV_PROJ_NAME)
    set(VERSION_DOCS_DIR "${PROJ_DOCS_DIR}/$ENV{${ENV_PROJ_NAME}_VERSION}")
    set(VERSION_NUMBER $ENV{${ENV_PROJ_NAME}_VERSION})
    #message("looking for.. ${DUMB_TEMP_VAR}")
    #if(EXISTS "$ENV{MRB_TOP}/all_docs/${PROJECT_NAME}/$ENV{${ENV_PROJ_NAME}_VERSION}")

    if(EXISTS "${VERSION_DOCS_DIR}")
      #set(DUMB_TEMP_VAR "$ENV{MRB_TOP}/all_docs/${PROJECT_NAME}/$ENV{${ENV_PROJ_NAME}_VERSION}")
      #message("version dir is here")
    else()
      #message("You don't have a version dir")
      add_custom_target(build_cetlib_except_version_dir ALL COMMAND
                        ${CMAKE_COMMAND} -E make_directory
                        ${VERSION_DOCS_DIR})
    endif()
  else()
    #message("You don't have a cetlib_except dir")
    add_custom_target(build_cetlib_except_proj_dir ALL COMMAND
                      ${CMAKE_COMMAND} -E make_directory
                      ${PROJ_DOCS_DIR})

    # Going back through now assuming it exists !
    #message("cetlib_except dir is here")
    string(TOUPPER ${PROJECT_NAME} ENV_PROJ_NAME)
    set(VERSION_DOCS_DIR "${PROJ_DOCS_DIR}/$ENV{${ENV_PROJ_NAME}_VERSION}")
    #message("looking for.. ${DUMB_TEMP_VAR}")
    #if(EXISTS "$ENV{MRB_TOP}/all_docs/${PROJECT_NAME}/$ENV{${ENV_PROJ_NAME}_VERSION}")

    if(EXISTS "${VERSION_DOCS_DIR}")
      #set(DUMB_TEMP_VAR "$ENV{MRB_TOP}/all_docs/${PROJECT_NAME}/$ENV{${ENV_PROJ_NAME}_VERSION}")
      #message("version dir is here")
    else()
      #message("You don't have a version dir")
      add_custom_target(build_cetlib_except_version_dir ALL COMMAND
                        ${CMAKE_COMMAND} -E make_directory
                        ${VERSION_DOCS_DIR})
    endif()
  endif()
else()
  message("You don't a spot to put your docs!")
endif()



#message("\n\n\n\n\n\n")

set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${VERSION_NUMBER}")
message("BINARY_BUILD_DIR: ${BINARY_BUILD_DIR}")
set(SPHINX_HTML_DIR "${BINARY_BUILD_DIR}")




file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/_static/ DESTINATION ${BINARY_BUILD_DIR}/_static)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/_templates/ DESTINATION ${BINARY_BUILD_DIR}/_templates)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/_extensions/ DESTINATION ${BINARY_BUILD_DIR}/_extensions)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in"
    "${BINARY_BUILD_DIR}/conf.py"
    @ONLY)

add_custom_target(cetlib_except_docs ALL
  sphinx-doc::sphinx-build
  -q -b html
  -c "${BINARY_BUILD_DIR}"
  -d "${SPHINX_CACHE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${SPHINX_HTML_DIR}"
  COMMENT "Building HTML documentation with Sphinx"
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/_extensions/redmineRoles.py)

# Install the built html files to an instal dir (HTML DIR)

install(DIRECTORY "${BINARY_BUILD_DIR}"
        #DESTINATION "${VERSION_DOCS_DIR}"
        DESTINATION "${PROJ_DOCS_DIR}"
        PATTERN "${BINARY_BUILD_DIR}/*")
