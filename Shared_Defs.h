////////////////////////////////////////////////////
// ifdef�� DEFINE ������ stdafx���� ���� �ʿ�

#ifdef USING_QTLIB
    #include <QString>
#endif

////////////////////////////////////////////////////

#define NULLPTR nullptr

#define IF_FALSE_BREAK(x) if( (x) == false ) break;
#define IF_TRUE_BREAK(x) if( (x) == true ) break;

#define IF_FALSE_CONTINUE(x) if( (x) == false ) continue;
#define IF_TRUE_CONTINUE(x) if( (x) == true ) continue;