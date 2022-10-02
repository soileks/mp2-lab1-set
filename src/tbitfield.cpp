// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
using namespace std;

TBitField::TBitField(int len)

{  
    if (len < 0)throw std::length_error("negative length"); 
    int s = sizeof(TELEM) * 8;
    BitLen = len;
    MemLen = (BitLen + s ) >> sizeof(TELEM);
    pMem  = new TELEM[MemLen];
   
       
       for (int i = 0; i < MemLen; i++) {
            pMem[i] =0;
       }
   
   
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    //int s = sizeof(TELEM) * 8;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
} 

//TBitField:: TBitField (TBitField&& bf) noexcept {
//    pMem = nullptr;
//    swap(*this,bf);
//}


TBitField::~TBitField()
{
    delete[]pMem;
   // pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    //int k = n / 32;

    //return k;
    return (n >> sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n > BitLen)||(n<0))throw std::length_error("error");
   // int k = n / 32;
    TELEM mask = 1<<(n%32);  
    //TELEM m = pMem[k]&(1 <<n);
    //int s = sizeof(TELEM) * 8;
    

    return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) throw std::out_of_range("Negative length");
    if (n >= BitLen) throw std::out_of_range("Too large ind");
    // pMem[GetMemIndex(n)] |= (1 << n);
    //pMem[GetMemIndex(n)]= pMem[GetMemIndex(n)] | (1 << n);
     
     pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) throw std::out_of_range("Negative length");
    if (n >= BitLen) throw std::out_of_range("Too large ind");
    pMem[GetMemIndex(n)] &= ~(1<<n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) throw std::out_of_range("Negative length");
    if (n >= BitLen) throw std::out_of_range("Too large ind");
    

  return pMem[GetMemIndex(n)] &= GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
        
        return *this;
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen!=bf.BitLen) {
        return false;
    }
    
   else if (MemLen != bf.MemLen) { return false; }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return false;
    }
  return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) {
        return true;
    }

    else if (MemLen != bf.MemLen) { return true; }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return true;
    }
  return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen != bf.BitLen) throw std::length_error("TBitField objects have different size");
for (int i = 0; i < MemLen; i++) {
    pMem[i] |= bf.pMem[i];
}
return *this;

    /*int mlenr;
    if (bf.MemLen > MemLen) {
        mlenr = bf.MemLen;
    }
    else { mlenr = MemLen; }
    TBitField result(mlenr);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = pMem[i];
    }

    for (int i = 0; i < bf.MemLen; i++) {
        result.pMem[i] |= bf.pMem[i];
    }
    return result;*/
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen != bf.BitLen) throw std::length_error("TBitField objects have different size");
    for (int i = 0; i < MemLen; i++) {
        pMem[i] &= bf.pMem[i];
    }
    return *this;

    /*int mlenr;
    if (bf.MemLen > MemLen) {
        mlenr = bf.MemLen;
    }
    else { mlenr = MemLen; }
    TBitField result(mlenr);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = pMem[i];
    }

    for (int i = 0; i < bf.MemLen; i++) {
        result.pMem[i] &= bf.pMem[i];
}
    return result;*/
}

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 0; i < BitLen; i++) {
        if (this->GetBit(i)==1) {
            ClrBit(i);
        }
        else {
            SetBit(i);
        }
    }
    return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i = 0;
    char c;

    istr >> c;
    while (c != ' ') {
        istr >> c;
    }

    while (1)
    {
        istr >> c;
        if (c == '0') bf.ClrBit(i++);
        else
            if (c == '1') bf.SetBit(i++);
            else
                break;
    }
    
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    int l = bf.GetLength();
    for (int i = 0; i < l; i++)
        if (bf.GetBit(i)) ostr << '1';
        else ostr << '0';
    return ostr;
}
