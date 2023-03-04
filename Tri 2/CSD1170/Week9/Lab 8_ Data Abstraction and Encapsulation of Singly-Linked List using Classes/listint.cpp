// File header documentation is required!!!

// Other than listint.hpp, you really don't have to include any other files except when testing your code.
// When you're ready to submit, don't include either of the following two headers: <forward_list> and <list>

// Private functions must be declared and defined in an anonymous namespace!!!

// This function definition is provided:
////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
//  Purpose: Output the list into an ostream object
//   Inputs: os - ostream object
//           list - the List to output
//  Outputs: Returns an ostream object.
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const ListInt& rhs) {
  // Start at the first node
  ListInt::Node *pnode = rhs.head;

  // Until we reach the end of the list
  while (pnode != 0) {
    os << std::setw(4) << pnode->data; // print the data in this node
    pnode = pnode->next;               // move to the next node
  }
  
  os << std::endl; // extra newline for readability
  return os;
}