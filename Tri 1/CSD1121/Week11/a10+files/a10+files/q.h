// TODO: File documentation block required

// TODO: DO NOT include any C standard library headers

#ifndef Q_H
#define Q_H

// TODO: declare anonymous enumeration type as described in the specs

// TODO: A function documentation block provides information that is crucial
// for clients to correctly use the function. Provide a documention block
// for each declared function that contains the following information:
// What does the function do?
// What are the (types) of the parameters?
// What is the (type) of value returned by function?
// Is there any particular input that will break the function?

// TODO: Now, declare the necessary function.

enum{TOT_GRADE =5};

double* read_data(char const *file_name, int *ptr_cnt);
double max(double const *begin, double const *end);
double min(double const *begin, double const *end);
double average(double const *begin, double const *end);
double variance(double const *begin, double const *end);
double std_dev(double const *begin, double const *end);
double median(double *base, int size);
void selection_sort(double *base, int size);
void ltr_grade_pctg(double const *begin, double const *end, double *ltr_grades);
// TODO: Repeat function documentation block plus function declaration for remaining functions

#endif // #ifndef Q_H
