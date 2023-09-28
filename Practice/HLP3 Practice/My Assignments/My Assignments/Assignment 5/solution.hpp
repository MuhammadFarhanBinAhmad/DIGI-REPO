/*!*****************************************************************************
\file solution.hpp
\author Nurul Dania Binte Mohd Rizal
\par DP email: nuruldania.b@digipen.edu
\par Course: CSD2125
\par Section: student   
\par Programming Assignment 5
\date 18/11/2021

\brief
Using STL containers to get file information to print file names and remove empty
files.

*******************************************************************************/


/*!*****************************************************************************
    \brief
    Print names of files.
    \param map
    takes in the map of a bunch of files.
*******************************************************************************/
void print_file_names(const file_records& map) {
    // create a file_name vector
    std::vector<file_name> names;
    // apply the split function on every element (file_record) of map and insert result (file_name) into names
    std::transform(std::begin(map), std::end(map), std::back_inserter(names), split);
    // for each element in names, do print_file_name(element)
    std::for_each(std::begin(names), std::end(names), print_file_name);
}

/*!*****************************************************************************
    \brief
    Print names of files that are not empty.
    \param map
    takes in the map of a bunch of files.
*******************************************************************************/
std::size_t print_non_empty_files(const file_records& map) {
    // create a map to hold non empty files
    file_records non_empty_files;
    // copy_if iterates through every element of map and insert it into non_empty_files if given predicate is true
    // we use bind to "transform" check_if_empty function from a 2-argument function into a 1-argument function so it can be used as a predicate in the copy_if function
    // check_if_empty(sample_record, true) returns true if sample_record is non-empty
    std::copy_if(std::begin(map), std::end(map), std::inserter(non_empty_files, std::begin(non_empty_files)), std::bind(check_if_empty, std::placeholders::_1, true));
    // print name of empty files (make use of a function previously defined)
    print_file_names(non_empty_files);
    return std::size(non_empty_files);
}

/*!*****************************************************************************
    \brief
    Print names of files that are empty.
    \param map
    takes in the map of a bunch of files.
*******************************************************************************/
std::size_t print_empty_files(const file_records& map) {
    file_records empty_files;
    // check_if_empty(sample_record, false) returns true if sample_record is empty
    std::copy_if(std::begin(map), std::end(map), std::inserter(empty_files, std::begin(empty_files)), std::bind(check_if_empty, std::placeholders::_1, false));
    print_file_names(empty_files);
    return std::size(empty_files);
}

/*!*****************************************************************************
    \brief
    Get the parameters of files in the map.
    \param map
    takes in the map of a bunch of files.
*******************************************************************************/
std::tuple<file_records &> get_parameters(file_records& map) {
    // return a tuple containing a std::ref(map)
    // this is necessary as the return value is used as a parameter for std::apply
    return std::forward_as_tuple(map);
}

/*!*****************************************************************************
    \brief
    Remove empty files from the map of files.
    \param map
    takes in the map of a bunch of files and returns back the bunch of modified
    files.
*******************************************************************************/
void remove_empty(file_records& map) {
    // c++20
    // std::erase_if(map,  std::bind(check_if_empty, std::placeholders::_1, true));
    file_records non_empty_files;
    std::copy_if(std::begin(map), std::end(map), std::inserter(non_empty_files, std::begin(non_empty_files)), std::bind(check_if_empty, std::placeholders::_1, true));
    map = non_empty_files;
}