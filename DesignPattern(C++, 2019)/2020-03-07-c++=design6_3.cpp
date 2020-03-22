#include <iostream>
#include <vector>
#include <map>
#include "Singleton.h"
using namespace std;

#define TEST (5)
// Factory
#if TEST == 1
/* 참고 소스 */
class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl;}
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl;}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Circle Rect" << endl;}
};

int main()
{
    vector<Shape*> v;

    while( 1 )
    {
        int cmd;
        cin >> cmd;

        //
        if      ( cmd == 1 ) v.push_back( new Rect );
        else if ( cmd == 2 ) v.push_back( new Circle );
        else if ( cmd == 9 )
        {
            for ( auto p : v )
                p->Draw(); // 다형성
        }
    }
}
#elif TEST == 2
/*
    * Factory class
        * 객체의 생성을 한 곳에서 관리 할 수 있다.
        * 새로운 도형이 추가 될 경우 한 곳만 코드를 수정하면 된다. 
*/
class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl;}
};
 
class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl;}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Circle Rect" << endl;}
};

class ShapeFactory
{
    MAKE_SINGLETON(ShapeFactory);
public:
    Shape* CreateShape(int type)
    {
       Shape* p = 0;
        if      ( type == 1 ) p = new Rect;
        else if ( type == 2 ) p = new Circle;

        return p;
    }
};
int main()
{
    ShapeFactory& factory = ShapeFactory::getInstance();
    vector<Shape*> v;

    while( 1 )
    {
        int cmd;
        cin >> cmd;

        //
        if ( cmd >=1 && cmd <= 5 )
        {
            Shape* p = factory.CreateShape(cmd);

            if ( p != 0 )
                v.push_back( p );
        }
        else if ( cmd == 9 )
        {
            for ( auto p : v )
                p->Draw(); // 다형성
        }
    }
}
#elif TEST == 3
/*
    * Factory 생성에 함수를 등록
        * Factory 에서 등록 된 도형에 대한 다양한 정보를 관리 할 수 있다. 
*/
class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl;}
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl;}

    static Shape* Create() { return new Rect;}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Circle Rect" << endl;}

    static Shape* Create() { return new Circle;}
};

// new Circle;
// Circle::Create()
class ShapeFactory
{
    MAKE_SINGLETON(ShapeFactory)

    typedef Shape* (*CREATOR)();

    map<int, CREATOR> create_map;

public:
    void Register( int type, CREATOR f )
    {
        create_map[type] = f;
    }

    Shape* CreateShape(int type )
    {
        Shape* p = 0;
        auto ret = create_map.find( type );
        if ( ret == create_map.end() )
            return 0;
        p = create_map[type]();

        return p;
    }
};

int main()
{
    ShapeFactory& factory = ShapeFactory::getInstance();

    // 공장에 제품을 등록한다.
    factory.Register( 1, &Rect::Create);
    factory.Register( 2, &Circle::Create);

    //factory.ShowProduct();

    vector<Shape*> v;

    while( 1 )
    {
        int cmd;
        cin >> cmd;

        //
        if ( cmd >=1 && cmd <= 5 )
        {
            Shape* p = factory.CreateShape(cmd);

            if ( p != 0 )
                v.push_back( p );
        }
        else if ( cmd == 9 )
        {
            for ( auto p : v )
                p->Draw(); // 다형성
        }
    }
}
#elif TEST == 4
class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl;}
};

class ShapeFactory
{
    MAKE_SINGLETON(ShapeFactory)
    typedef Shape* (*CREATOR)();
    map<int, CREATOR> create_map;

public:
    void Register( int type, CREATOR f )
    {
        create_map[type] = f;
    }

    Shape* CreateShape(int type )
    {
        Shape* p = 0;
        auto ret = create_map.find( type );
        if ( ret == create_map.end() )
            return 0;
        p = create_map[type]();

        return p;
    }
};

struct RegisterShape
{
    RegisterShape(int type, Shape*(*f)())
    {
        ShapeFactory& factory = ShapeFactory::getInstance();
        factory.Register(type, f);
    }
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl;}
    static Shape* Create() { return new Rect;}
    static RegisterShape rs;
};

RegisterShape Rect::rs(1, &Rect::Create);

// 모든 도형이 지켜야 하는 규칙을 매크로로 제공
#define DECLARE_SHAPE( classname )                  \
    static Shape* Create() { return new classname;}      \
    static RegisterShape rs;

#define IMPLEMENT_SHAPE( type, classname )                \
    RegisterShape classname::rs(type, &classname::Create);

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Circle Rect" << endl;}

    DECLARE_SHAPE( Circle )
};
IMPLEMENT_SHAPE( 2, Circle )


class Triangle : public Shape
{
public:
    virtual void Draw() { cout << "Triangle Rect" << endl;}

    DECLARE_SHAPE( Triangle )
};
// new Circle;
// Circle::Create()

int main()
{
    ShapeFactory& factory = ShapeFactory::getInstance();

    // 공장에 제품을 등록한다.
    // factory.Register( 1, &Rect::Create);
    // factory.Register( 2, &Circle::Create);

    //factory.ShowProduct();

    vector<Shape*> v;

    while( 1 )
    {
        int cmd;
        cin >> cmd;

        //
        if ( cmd >=1 && cmd <= 5 )
        {
            Shape* p = factory.CreateShape(cmd);

            if ( p != 0 )
                v.push_back( p );
        }
        else if ( cmd == 9 )
        {
            for ( auto p : v )
                p->Draw(); // 다형성
        }
    }
}
#elif TEST == 5
// Factory 3
/*
    * 클래스가 아닌 객체를 등록하는 factory
        * 자주 사용하는 견본품을 등록해서 복사 생성한다.
        * **Prototype** 패턴
*/
class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl;}
    virtual Shape* Clone() = 0;
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl;}
    static Shape* Create() { return new Rect;}
    virtual Shape* Clone() { return new Rect(*this);}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Circle Rect" << endl;}
    static Shape* Create() { return new Circle;}
    virtual Shape* Clone() { return new Circle(*this);}
};



class ShapeFactory
{
    MAKE_SINGLETON(ShapeFactory)
    map<int, Shape*> protype_map;

public:
    void Register( int type, Shape* sample )
    {
        protype_map[type] = sample;
    }

    Shape* CreateShape(int type )
    {
        Shape* p = 0;
        auto ret = protype_map.find( type );
        if ( ret == protype_map.end() )
            return 0;

        p = protype_map[type]->Clone();

        return p;
    }
};



int main()
{
    ShapeFactory& factory = ShapeFactory::getInstance();

    // 공장에 제품을 등록한다.
    //        클래스 등록
    //factory.Register( 1, &Rect::Create);
    //factory.Register( 2, &Circle::Create);

    Rect* r1 = new Rect;// 빨간색 크기 5 // clone이라는 함수를 제공해야한다.
    Rect* r2 = new Rect;// 파란색 크기 10

    // 공장에 객체 등록
    factory.Register( 1, r1);
    factory.Register( 2, r2);

    //factory.ShowProduct();



    vector<Shape*> v;

    while( 1 )
    {
        int cmd;
        cin >> cmd;

        //
        if ( cmd >=1 && cmd <= 5 )
        {
            Shape* p = factory.CreateShape(cmd);

            if ( p != 0 )
                v.push_back( p );
        }
        else if ( cmd == 9 )
        {
            for ( auto p : v )
                p->Draw(); // 다형성
        }
    }
}
#endif