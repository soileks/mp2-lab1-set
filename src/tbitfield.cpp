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

    if (len <= 0)throw std::logic_error("negative length"); 
    int s = sizeof(TELEM) * 8;
    BitLen = len;
    MemLen = len / (sizeof(TELEM) * 8) + 1;
    //MemLen = (BitLen + s ) >> sizeof(TELEM);
    pMem  = new TELEM[MemLen];
       
       for (int i = 0; i < MemLen; i++) {
            pMem[i] =0;
       }
   
   
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    if (bf.BitLen < 0) throw "error";
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
    pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    //int k = n / 32;

    //return k;
    if ((n < 0) || (n > BitLen))
        throw std::out_of_range("Input error: invalide value of bitfield in GetMemIndex");
    else
        //return(n / (sizeof(TELEM) * 8));
       
    return (n >> (sizeof(TELEM)+1));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n>BitLen)&&(n<0))throw std::length_error("error");
   // int k = n / 32;
      //TELEM mask = 1<<(n%32);  
    //TELEM m = pMem[k]&(1 <<n);
    //int s = sizeof(TELEM) * 8;
    
    int tmp = n % (sizeof(int) * 8);
    TELEM mask = 1 << tmp;
    return mask;
   // return 1 << (n & 31);

     // return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) throw std::out_of_range("Negative length");
    if (n > BitLen) throw std::out_of_range("Too large ind");
     //pMem[GetMemIndex(n)] |= (1 << n);
    //pMem[GetMemIndex(n)]= pMem[GetMemIndex(n)] | (1 << n);
     
     pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) throw std::out_of_range("Negative length");
    if (n > BitLen) throw std::out_of_range("Too large ind");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
   // pMem[GetMemIndex(n)] &= ~(1<<n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) throw std::out_of_range("Negative length");
    if (n > BitLen) throw std::out_of_range("Too large ind");
    

  return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

    if (this == &bf)
        return *this;
    else
    {
        delete[] pMem;
        MemLen = bf.MemLen;
        BitLen = bf.BitLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
        return *this;
    }


    //if (!(*this == bf)) {
    //    if (MemLen != bf.MemLen)
    //    {
    //        delete[] pMem;
    //        MemLen = bf.MemLen;
    //        pMem = new TELEM[MemLen];
    //    }
    //    //delete[] pMem;
    //    BitLen = bf.BitLen;
    //   // MemLen = bf.MemLen;
    //    //pMem = new TELEM[MemLen];
    //    for (int i = 0; i < MemLen; i++)
    //    {
    //        pMem[i] = bf.pMem[i];
    //    }
    //    
    //    return *this;
    //}
    //return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (MemLen != bf.MemLen || BitLen != bf.BitLen)
        return 0;
    else
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
    return 1;



  //  if (BitLen!=bf.BitLen) {
  //      return false;
  //  }
  //  
  // else if (MemLen != bf.MemLen) { return false; }
  //  for (int i = 0; i < MemLen; i++) {
  //      if (pMem[i] != bf.pMem[i])
  //          return false;
  //  }
  //return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    //return !(*this == bf);

    if (!(*this == bf))
        return 1;
    else return 0;



    /*if (BitLen != bf.BitLen) {
        return true;
    }

    else if (MemLen != bf.MemLen) { return true; }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return true;
    }
  return false;*/
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    /*if (BitLen != bf.BitLen) throw std::length_error("TBitField objects have different size");
for (int i = 0; i < MemLen; i++) {
    pMem[i] |= bf.pMem[i];
}
return *this;*/

    int blen;
    if (bf.BitLen > BitLen) {
        blen = bf.BitLen;
    }
    else { blen = BitLen; }
    TBitField result(blen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = pMem[i];
    }

    for (int i = 0; i < bf.MemLen; i++) {
        result.pMem[i] |= bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    /*if (BitLen != bf.BitLen) throw std::length_error("TBitField objects have different size");
    for (int i = 0; i < MemLen; i++) {
        pMem[i] &= bf.pMem[i];
    }
    return *this;*/

    int blen;
    if (bf.BitLen > BitLen) {
        blen = bf.BitLen;
    }
    else { blen = BitLen; }
    TBitField result(blen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = pMem[i];
    }

    for (int i = 0; i < bf.MemLen; i++) {
        result.pMem[i] &= bf.pMem[i];
}
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen); 
   // int t = BitLen - (MemLen - 1) * sizeof(int) * 8;
   // int t = (tmp.MemLen) *32 - tmp.BitLen ;
    //int k = tmp.MemLen * 32;
    for (int i = 0; i < MemLen; i++)
    {                                             //00000 110
        tmp.pMem[i] = ~pMem[i];                  // 11111 001
   
        //tmp.pMem[i] &= (1 <<( i%32));
    }
        /*if (tmp.GetBit(i))
        {
           
            tmp.ClrBit(i);
        }
        else
        {*/
           // int tm = tmp.BitLen % (sizeof(int) * 8);
            //tmp. = 1 << tm -1;
          // tmp.SetBit(i);

      //  }
    * this = tmp;

    int numb = BitLen - (MemLen - 1) * (sizeof(TELEM) * 8); //последний номер бита
    if (numb < sizeof(TELEM) * 8) {
        int mask = (1 << numb) - 1;
        tmp.pMem[MemLen - 1] &= mask;
    }
   
     return tmp;

   // }
   //tmp.pMem &= (1 << tmp.BitLen - 1);
   



    /*for (int i = 0; i < BitLen; i++) {
        if (GetBit(i)==1) {
            ClrBit(i);
        }
        else {
            SetBit(i);
        }
    }
    return *this;*/
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    
    
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
