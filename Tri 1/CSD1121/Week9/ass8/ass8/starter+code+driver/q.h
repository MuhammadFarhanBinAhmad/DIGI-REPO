char const* find(char const *begin, char const *end, char val);
char const* find_any(char const *begin, char const *end,
char const *vals, int len);
int count(char const *begin, char const *end, char val);
int count_any(char const *begin, char const *end, char const *vals, int len);
int compare(char const *begin1, char const *begin2, int len);
void exchange(char *begin1, char *begin2, int len);
void copy(char *dst, char *src, int len);
