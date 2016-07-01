#include <iostream>
using namespace std;

#include "Fraction.h"
#include "Stack.h"

  bool err      = false;
   int errNum   =    -1;
string errMsg[] = { /*0*/ "infix error: [提示] 系統錯誤",
                    /*1*/ "infix error: [格式錯誤] 不存在的字元",
                    /*2*/ "infix error: [格式錯誤] 括號不正確",
                    /*3*/ "infix error: [格式錯誤] 雙零",
                    /*4*/ "infix error: [格式錯誤] 雙小數點",
                    /*5*/ "infix error: [格式錯誤] 空小數點",
                    /*6*/ "postfix error: [提示] 系統錯誤",
                    /*7*/ "postfix error: [格式錯誤] 分母為 0",
                    /*8*/ "postfix error: [警告] 尚未支援的運算"
                  };

void error(int errNum) {
    if ( 0>errNum || errNum>8 )
       { cout << "error" << endl;
         return;
       }
    err    = true;
  ::errNum = errNum;
    return;
}

const double sim = -1.0,  // 符號: * /
             sia = -2.0,  // 符號: + -
             sip = -3.0,  // 符號: ( )
             erc = -4.0,  // 錯誤: 不存在的字元
             erz = -5.0,  // 錯誤: 雙零
             erp = -6.0,  // 錯誤: 雙小數點
             ern = -7.0;  // 錯誤: 空小數點

void evalPostfix(string &infix);
void evalAnswer (string* postfix, const int n);

double iden(string x);

int main()
{
    string infix("3*(1+2.1)+100");
  //string infix("(3*(1+2.1)");  // error
  //string infix("1+010");  // error
  //string infix("2/0");  // error

    evalPostfix(infix);
    if ( err )
       { cout << errMsg[errNum] << endl;
         return 0;
       }

    return 0;
}

void evalPostfix(string &infixOri)
{
    Stack<string> box;

    const int len = infixOri.size();
    for ( int i=0 ; i<len ; ++i )
        { string token(1, infixOri[i]);

          if ( iden(token)==erc )
             { error(1);
               return;
             }
          if ( iden(token)==erz )
             { error(3);
               return;
             }
          if ( iden(token)==erp )
             { error(4);
               return;
             }
          if ( iden(token)==ern )
             { error(5);
               return;
             }

          if ( token=="+" ||
               token=="-" ||
               token=="*" ||
               token=="/" ||
               token=="(" ||
               token==")" )
             { box.push(token);
               continue;
             }

          string test( token );
          for ( int j=i+1 ; j<len ; ++j )
              { test += infixOri[j];

                if ( iden(test)==erc )
                   { break;
                   }
                if ( iden(test)==erz )
                   { error(3);
                     return;
                   }
                if ( iden(test)==erp )
                   { error(4);
                     return;
                   }
                if ( iden(test)==ern )
                   { error(5);
                     return;
                   }

                token += infixOri[++i];
              }
          box.push(token);
        }


    const  int   numI = box.size();
    string infix[numI];              int cnt = numI;
    for ( int i=numI-1 ; i>=0 ; --i )
        { infix[i] = box.top();  box.pop();
          if ( infix[i]=="(" ||
               infix[i]==")" )         --cnt;
        }


    const  int     numP = cnt;
    string postfix[numP];                cnt = 0;
    for ( int i=0 ; i<numI ; ++i )
        { string token( infix[i] );

          if ( token=="(" )
             { box.push(token);
               continue;
             }
          if ( token==")" )
             { for ( ; true ; )
                   { if ( box.empty() )
                        { error(2);
                          return;
                        }
                     if ( box.top()=="(" )
                        { box.pop();
                          break;
                        }
                     postfix[cnt++] = box.top();
                     box.pop();
                   }
               continue;
             }
          if ( token=="+" ||
               token=="-" ||
               token=="*" ||
               token=="/" )
             { for ( ; true ; )
                   { if ( box.empty() )
                        { box.push(token);
                          break;
                        }
                     if ( iden(token)>iden(box.top()) )
                        { box.push(token);
                          break;
                        }
                     postfix[cnt++] = box.top();
                     box.pop();
                   }
               continue;
             }
          postfix[cnt++] = token;
        }
    for ( ; !box.empty() ; )
        { if ( box.top()=="(" )
             { error(2);
               return;
             }
          postfix[cnt++] = box.top();
          box.pop();
        }


    cout << "postfix: ";
    for ( int i=0 ; i<numP ; ++i )
        { cout << postfix[i] << " ";
        }
    cout << endl << endl;


    evalAnswer(postfix, numP);
    if ( err )
       { return;
       }

    return;
}

void evalAnswer(string* postfix, const int n)
{
    Stack<Frac> box;

    for ( int i=0 ; i<n ; ++i )
        { string token( postfix[i] );

          if ( token=="+" ||
               token=="-" ||
               token=="*" ||
               token=="/" )
             { if ( box.size()<2 )
                  { error(8);
                    return;
                  }
               Frac y = box.top();  box.pop();
               Frac x = box.top();  box.pop();
               if ( token=="+" )
                  { box.push(x+y);
                    continue;
                  }
               if ( token=="-" )
                  { box.push(x-y);
                    continue;
                  }
               if ( token=="*" )
                  { box.push(x*y);
                    continue;
                  }
               if ( token=="/" )
                  { if ( y.empty() )
                       { error(7);
                         return;
                       }
                    box.push(x/y);
                    continue;
                  }
             }

          Frac x( iden(token) );
          box.push(x);
        }
    if  ( box.size()!=1 )
        { error(6);
          return;
        }


    Frac x( box.top() );
    cout << "answer: " << x
         << endl << endl;
    return;
}

double iden(string x)
{
    double idenNum(string x);

    if ( x=="*" || x=="/" )  return sim;
    if ( x=="+" || x=="-" )  return sia;
    if ( x=="(" || x==")" )  return sip;
    return idenNum(x);
}

double idenNum(string x)
{
    int idenNum(char x);

    const int len = x.size();
    double sum = 0.0;  int exp;

    // 判定
        // 雙零
        bool zo = ( idenNum(x[0])==0 )?true:false;
        bool zp = true;

        // 雙小數點
        int pn = 0;

        // 空小數點
        if ( idenNum(x[0])==-1 )
            return ern;

    for ( int i=0 ; i<len ; ++i )
        { char token = x[i];

          if ( idenNum(token)==-2 )
             { return erc;
             }
          if ( idenNum(token)==-1 )
             { if ( ++pn > 1 )
                  { return erp;
                  }
               zp  = false;
               exp =     i;
               continue;
             }
          if ( zo && zp && i!=0 )
             { return erz;
             }

          sum *= 10;
          sum += idenNum(token);
        }
    exp = len - exp - 1;
    for ( int i=1 ; i<=exp ; ++i )
        { sum /= 10;
        }
    return sum;
}

int idenNum(char x)
{
    if ( '0'<=x && x<='9' )
        return x - '0';

    if ( x=='.' )
        return -1;

    return -2;
}
