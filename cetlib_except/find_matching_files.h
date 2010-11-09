#ifndef CETLIB_FIND_MATCHING_FILES_H
#define CETLIB_FIND_MATCHING_FILES_H

#include <string>
#include <algorithm>
#include <vector>

/*
	find_matching_files - go through all files in a directory and 
	return all the names that match pattern.  The names returned in
	file_list will be file names within that directory.

	If directory does not exist, it will just not attempt to scan it.
	The number of things placed in file_list from be returned.
	The file_list is added to, but not cleared.
*/

namespace cet 
{

namespace detail
{
size_t find_matching_internal(std::string const& pat,std::string const& dir,
	std::vector<std::string>& out);
}

template <class OutIter>
size_t find_matching_files(std::string const& pattern
	,std::string const& directory
	,OutIter dest)
{
	std::vector<std::string> files_out;
	size_t num=detail::find_matching_internal(pattern,directory,files_out);
	std::copy(files.out.begin(),files.out.end(),dest); 
	return num;
}

}

#endif