#ifndef KMP_H
#define KMP_H

#include <string>


class kmpSearcher
{
public:
    
    kmpSearcher(const std::string &pattern);
    ~kmpSearcher();

    void searchLine(const std::string &line);
      
private:
    
    int ptrnLen;
    int lineLen;
    int *lookup;

    std::string ptrn;

    void ptrnPreprocess();
    int kmpSearch(const std::string &line);
};

#endif
