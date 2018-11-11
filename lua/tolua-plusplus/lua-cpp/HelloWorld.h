#ifndef _TESTCLASS_H
#define _TESTCLASS_H
#include <string.h>
extern int g_Arr[10];

class CNumber {
    //tolua_export
public:
    //tolua_begin
    CNumber():m_nNum(0){ }
    CNumber(int num):m_nNum(num){ }
    ~CNumber() { }
    void SetNumber(int num) { m_nNum = num; }
    int GetNumber()     { return m_nNum; }
    int Add(int num)
    {
        m_nNum += num;
        return m_nNum;
    }

    //tolua_end
protected:

    int m_nNum;
};

class CMessage
{
public:
    CMessage()
    {
        strcpy(m_buff,"init message!");
    }
    ~CMessage()
    {

    }
    void SetMessage(char *msg)
    {
        strcpy(m_buff,msg);
    }

    char *GetMessage()
    {
        return m_buff;
    }

    void ShowMessage()
    {
        printf("%s\n",m_buff);
    }
protected:
    char m_buff[256];
};

//tolua_export  //tolua_begin  class

#endif
