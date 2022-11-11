// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
#include<gtest.h>
#include "tset.h"
#include"tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;

}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower ( bf.GetLength()), BitField(bf){}

   

TSet::operator TBitField()
{
    /*TBitField tmp(BitField);
    return tmp;*/
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int  TSet::IsMember(const int Elem) const // элемент множества?
{//if(BitField.GetBit(Elem))
    return BitField.GetBit(Elem);
//else { return 0; }
    //return -1;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
   // if ((Elem > MaxPower) || (Elem < 0)) throw std::out_of_range("elem is out of universe");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    //if ((Elem > MaxPower)||(Elem<0)) throw std::out_of_range("elem is out of universe");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (!(*this == s)) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
        return *this;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tField(std::max(MaxPower, s.MaxPower));
    tField.BitField = BitField | s.BitField;
    return tField;
    /*if (MaxPower != s.MaxPower) throw std::length_error("TSet objects have different size");
    TSet tmp(BitField | s.BitField);
    return tmp;*/
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tField(*this);
    tField.BitField.SetBit(Elem);
    return tField;

    /*TSet tmp(BitField);
    tmp.InsElem(Elem);
    return tmp;*/
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tField(*this);
    tField.BitField.ClrBit(Elem);
    return tField;


    /*TSet tmp(BitField);
    tmp.DelElem(Elem);
    return tmp;*/
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(BitField & s.BitField);
    return res;

}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(MaxPower);
    tmp.BitField = ~BitField;
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
   
    

    return ostr;
}
