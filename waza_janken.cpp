// g++ でコンパイルしてね
#include <iostream>
#include <string>



// 名前空間の解決
using namespace std;

// クラスの前方宣言
class CMonster;

// 関数プロトタイプ宣言
int judge(const string &_cstrJ1, const string &_cstrJ2);



struct State {
    State(int _nHp, int _nAtk, int _nDef)
    : m_nHp(_nHp),m_nAtk(_nAtk),m_nDef(_nDef) {}
    int m_nHp;
    int m_nAtk;
    int m_nDef;
};

// 各モンスターと技が持つタイプのインターフェース
typedef
class IType {
public:
    virtual ~IType() {}
    virtual State _do(int _nHp, int _nAtk, int _nDefence) = 0;
    string m_strName;
}*LPTYPE;

class CGu : public IType {
public:
    CGu() {m_strName = "gu";}
    State _do(int _nHp, int _nAtk, int _nDefence) {
        return State(_nHp,_nAtk/2,_nDefence*2);
    }
};

class CCho : public IType {
public:
    CCho() {m_strName = "cho";}
    State _do(int _nHp, int _nAtk, int _nDefence) {
        return State(_nHp,_nAtk*2,_nDefence/2);
    }
};

class CPa : public IType {
public:
    CPa() {m_strName = "pa";}
    State _do(int _nHp, int _nAtk, int _nDefence) {
        return State(_nHp*4,_nAtk/2,_nDefence/2);
    }
};

// 各モンスターが持つ技
class CWaza {
public:
    CWaza(const string &_cstrName)
    :m_strName(_cstrName), m_lpType(NULL) {}
    ~CWaza() {if(m_lpType) {delete m_lpType;m_lpType = NULL;}}
    
    int _do(CMonster &_m, CMonster &_e) /* クラス宣言のタイミングの関係上ここに_do()の実装書けなかった... */
#if 1
    ;
#else
    {
        cout << _m.m_strName.c_str() << "の" << m_strName.c_str() << "!" << endl;
        
        string wazatype = _m.m_lpType->m_strName;
        string entype = _e.m_lpType->m_strName;
        int result = judge(_m.m_lpType->m_strName,_e.m_lpType->m_strName);
        switch(result) {
            case 1:
            cout << "勝ち" << endl;
            cout << "攻撃力×2!" << endl;
            _e.damage(_m.m_nAtk*2);
            break;
            case -1:
            cout << "負け" << endl;
            _e.damage(_m.m_nAtk/2);
            break;
            default:
            cout << "あいこ" << endl;
        }
        return result;
    }
#endif
        
        
    string m_strName;
    LPTYPE m_lpType;
};

class CKirisaku : public CWaza {
public:
    CKirisaku()
    : CWaza("きりさく")
    {
        m_lpType = new CCho();
    }
};

class CKnuckle : public CWaza {
public:
    CKnuckle()
    : CWaza("ナックルパンチ")
    {
        m_lpType = new CGu();
    }
};

class CHenka : public CWaza {
public:
    CHenka()
    : CWaza("")
    {
        
    }
};

class CMonster {
public:
    CMonster()
    : m_strName("default"),
    m_nHp(0L),m_nAtk(0L),m_nDef(0L),
    m_lpType(NULL),m_lpType2(NULL),
    m_lpWaza1(NULL),
    m_strStatus("") {}
    
    CMonster(const string &_cstrName,
             int _nHp, int _nAtk, int _nDefence,
             LPTYPE _lpType, LPTYPE _lpType2,
             CWaza *_lpWaza1,
             const string _cstrStatus)
    : m_strName(_cstrName),
    m_nHp(_nHp),m_nAtk(_nAtk),m_nDef(_nDefence),
    m_lpType(_lpType),m_lpType2(_lpType2),
    m_lpWaza1(_lpWaza1),
    m_strStatus(_cstrStatus) {}
    
    ~CMonster() {
        if(m_lpType) {delete m_lpType;m_lpType = NULL;}
        if(m_lpType2) {delete m_lpType2;m_lpType2 = NULL;}
        if(m_lpWaza1) {delete m_lpWaza1;m_lpWaza1 = NULL;}
    }
    
    int damage(int _nHpDamage) {
        int damage = _nHpDamage-m_nDef;
        if (damage>0L) {
            cout << m_strName.c_str() << "に" << damage << "のダメージ" << endl;
            if(m_nHp<damage) {
                cout << "死" << endl;
                m_strStatus = "死";
                m_nHp = 0L;
                return 0L;
            }
            
            m_nHp -= damage;
        } else {
            cout << m_strName.c_str() << "に0のダメージ" << endl;
        }
        
        return m_nHp;
    }
    
    void show_status() {
        cout << "-------" << endl <<
        "name:" << m_strName.c_str() << endl <<
        "hp:" << m_nHp << endl <<
        "atk:" << m_nAtk << endl <<
        "def:" << m_nDef << endl <<
        "type:" << m_lpType->m_strName.c_str() << endl <<
        "status:" << m_strStatus.c_str() << endl <<
        "-------" <<endl;
    }
    
    string m_strName;
    int m_nHp;
    int m_nAtk;
    int m_nDef;
    LPTYPE m_lpType;
    LPTYPE m_lpType2;
    CWaza *m_lpWaza1;
    string m_strStatus;
};

class CSlime : public CMonster {
public:
    CSlime() {
        m_strName = "スライム";
        m_nHp = 5L;
        m_nAtk = 5L;
        m_nDef = 5L;
        m_lpType = new CGu();
        m_lpWaza1 = new CKnuckle();
    }
};

class CSlimeBes : public CSlime {
public:
    CSlimeBes() {
        m_strName = "スライムベス";
        m_nHp *= 2L;
        m_nAtk *= 2;
        m_nDef *= 2;
        m_lpType2 = new CPa();
    }
};

class CDrakee : public CMonster {
    public:
    CDrakee() {
        m_strName = "ドラキー";
        m_nHp = 4L;
        m_nAtk = 6L;
        m_nDef = 5L;
        m_lpType = new CCho();
        m_lpWaza1 = new CKirisaku();
    }
};

class CNyan : public CMonster {
    public:
    CNyan() {
        m_strName = "プリズニャン";
        m_nHp = 10L;
        m_nAtk = 3L;
        m_nDef = 2L;
        m_lpType = new CPa();
    }
};

// 上で書けなかった CWazaの _do()の実装
int CWaza::_do(CMonster &_m, CMonster &_e)
{
    cout << _m.m_strName.c_str() << "の" << m_strName.c_str() << "!" << endl;
    
    string wazatype = _m.m_lpType->m_strName;
    string entype = _e.m_lpType->m_strName;
    int result = judge(_m.m_lpType->m_strName,_e.m_lpType->m_strName);
    switch(result) {
    case 1:
        cout << "勝ち" << endl;
        cout << "攻撃力×2!" << endl;
        _e.damage(_m.m_nAtk*2);
        break;
    case -1:
        cout << "負け" << endl;
        _e.damage(_m.m_nAtk/2);
        break;
    default:
        cout << "あいこ" << endl;
    }
    return result;
}

int judge(const string &_cstrJ1, const string &_cstrJ2)
{
    
    if (_cstrJ1.compare("gu")==0) {
        if (_cstrJ2.compare("gu")==0) {
            return 0;
        } else if(_cstrJ2.compare("cho")==0) {
            return 1;
        } else if(_cstrJ2.compare("pa")==0) {
            return -1;
        }
    } else if (_cstrJ1.compare("cho")==0) {
        if (_cstrJ2.compare("gu")==0) {
            return -1;
        } else if(_cstrJ2.compare("cho")==0) {
            return 0;
        } else if(_cstrJ2.compare("pa")==0) {
            return 1;
        }
    } else if (_cstrJ1.compare("pa")==0) {
        if (_cstrJ2.compare("gu")==0) {
            return 1;
        } else if(_cstrJ2.compare("cho")==0) {
            return -1;
        } else if(_cstrJ2.compare("pa")==0) {
            return 0;
        }
    }
    return 0;
}



int main(int argv, char *argc[])
{
    CMonster *s = new CSlime();
    CMonster *d = new CDrakee();
    CMonster *b = new CSlimeBes();
    CNyan *p = new CNyan();
    
    d->show_status();
    s->show_status();
    d->m_lpWaza1->_do(*d,*s);
    s->m_lpWaza1->_do(*s,*d);
    d->show_status();
    s->show_status();
    
    delete s;
    delete d;
    delete b;
    delete p;
    
    return 0;
}