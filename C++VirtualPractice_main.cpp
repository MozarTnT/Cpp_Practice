#include <iostream>

using namespace std;

class Parent
{
public:
    virtual void speak()
    {
        cout << "Parent Hello ! " << endl;
    }

};


class Child : public Parent
{
public:
    void speak() override 
    {
        cout << "Child Hello ! " << endl;
    }

};

class Animal
{
public:
    virtual void bark()
    {
        std::cout << "동물이 소리를 냅니다." << std::endl;
    }
};

class Dog : public Animal
{
public:
    void bark() override
    {
        std::cout << "강아지가 짖습니다." << std::endl;
    }
};


int main()
{
    Parent Father;
    Child Baby;
   
    Parent* ptr_F = &Father;
    Child* ptr_B = &Baby;

    cout << ptr_F << endl;
    cout << ptr_B << endl;
    
    ptr_F->speak();
    ptr_B->speak();
    cout << "--------------" << endl;
    ptr_F->speak();
    ptr_F = &Baby;
    ptr_F->speak();

    Animal zoo;
    Dog woo;

    zoo.bark();
    woo.bark();

    Animal* ptr_Z = &zoo;
    Dog* ptr_D = &woo;

    ptr_Z->bark();
    ptr_Z = &woo;
    ptr_Z->bark();



    return 0;
}

