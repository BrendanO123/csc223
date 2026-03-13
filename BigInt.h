#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <bit>

using namespace std;

template <size_t length>
struct BigInt{
    private:
        size_t len;
        inline BigInt scaleToMax(BigInt num){
            if(!num.nonNeg()){return minValue(num);}
            if(num == 0){return 1;}
            return maxValue(num);
        }
    public:
        unsigned char arr[length];
        BigInt maxValue(BigInt num){
            BigInt<num.len> result = BigInt<num.len>();
            result[num.len-1]=128;
            result.Invert();
            return result;
        }
        BigInt minValue(BigInt num){
            BigInt<num.len> result = BigInt<num.len>();
            result[num.len-1]=128;
            return result;
        }

        /*-------------------------------------*/

        //Constructors
        BigInt(size_t inLength, char* num) : len(length){
            copy((num), (num)+min(len, inLength), arr);
            if(inLength < len){memset((void*)(arr + min(len, inLength)), 0, len-min(len, inLength));}
        }
        BigInt(const BigInt& other) : BigInt(other.len, other.arr){}
        BigInt() : len(length){}

        /*-------------------------------------*/
        
        //Access
        inline long long getLong(size_t offset = 0) const{
            long long returnInt = 0L;
            if(offset<0){offset=0;}
            copy(arr + min(length, offset), arr + min(length, offset+sizeof(long long)), (char*)(&returnInt));
            return returnInt;
        }
        inline char safeAccess(const size_t index) const{
            if(index>=0 && index<length*8){
                return ((char)(((arr[index>>3]) & (1<<(index&7)))!=0));
            }
            return 0;
        }
        
        inline unsigned char operator[](const size_t i) const{
            if(i>=0 && i<length){return arr[i];}
            return 0;
        }

        /*-------------------------------------*/
        
        //Shift Opps
        inline BigInt<length> operator>>(const size_t rshift) const{
            BigInt other = *this;
            other>>=rshift;
            return other;
        }
        inline BigInt<length> operator<<(const size_t lshift) const{
            BigInt other = *this;
            other<<=lshift;
            return other;
        }
        inline void operator>>=(const size_t rshift){
            copy(arr + min(length, rshift), arr + length, arr);
            memset(arr + length - min(length, rshift), 0, min(length, rshift));
        }
        inline void operator<<=(const size_t lshift){
            reverse_copy(arr, arr + length - min(length, lshift), arr + min(length, lshift));
            memset(arr, 0, min(length, lshift));
        }

        //Leading Zeros
        inline int leadingZeros() const{
            size_t offset = 0;
            for(int i = length-1; i > 0; i--){
                if(arr[i]!=0){return __countl_zero(arr[i])+offset;}
                offset+=8;
            }
            return __countl_zero(arr[0]) + offset;
        }

        /*-------------------------------------*/

        //Normal Bit Opps
        inline BigInt<length> operator~() const{
            BigInt<length> result = BigInt<length>();
            for(int i=0; i<length; i++){
                result.arr[i] = ~arr[i];
            }
            return result;
        }
        inline BigInt<length> operator&(const BigInt& other) const{
            BigInt<length> result = BigInt<length>();
            for(int i=0; i<length; i++){
                result.arr[i] = arr[i] & other.arr[i];
            }
            return result;
        }
        inline BigInt<length> operator|(const BigInt& other) const{
            BigInt<length> result = BigInt<length>();
            for(int i=0; i<length; i++){
                result.arr[i] = arr[i] | other.arr[i];
            }
            return result;
        }
        inline BigInt<length> operator^(const BigInt& other) const{
            BigInt<length> result = BigInt<length>();
            for(int i=0; i<length; i++){
                result.arr[i] = arr[i] ^ other.arr[i];
            }
            return result;
        }

        /*-------------------------------------*/

        //Bit Opp Assignments
        inline void operator&=(const BigInt& other){for(int i=0; i<length; i++){arr[i] &= other.arr[i];}}
        inline void operator|=(const BigInt& other){for(int i=0; i<length; i++){arr[i] |= other.arr[i];}}
        inline void operator^=(const BigInt& other){for(int i=0; i<length; i++){arr[i] ^= other.arr[i];}}
        inline void Invert(){for(int i=0; i<length; i++){arr[i] = ~arr[i];}}

        /*-------------------------------------*/

        //Basic Math
        inline BigInt<length> operator+(const BigInt& other) const{
            BigInt<length> result = BigInt<length>(*this);
            result += other;
            return result;
        }
        inline BigInt<length> operator-(const BigInt& other) const{
            BigInt<length> result = BigInt<length>(*this);
            result -= other;
            return result;
        }

        //Increment and Decrement
        void operator+=(const BigInt& other){
            unsigned char carry = 0;
            unsigned char currentSelf, currentOther;
            unsigned char halfAdded;
            constexpr const unsigned char mask = (1<<7)-1;
            for(int i=0; i<length; i++){
                currentSelf = arr[i]; currentOther = (i < other.len ? other.arr[i] : 0);
                halfAdded = (currentSelf&mask) + (currentOther&mask);
                bool c1 = currentSelf>>7; bool c2 = currentOther>>7; bool c3 = halfAdded>>7;
                carry = (unsigned char)((c1 && c2) || (c2 && c3) || (c1 && c3));
                arr[i]=currentSelf+currentOther+carry;
            }
        }
        void operator-=(const BigInt& other){
            unsigned char carry = 1;
            unsigned char currentSelf, currentOther;
            unsigned char halfAdded;
            constexpr const unsigned char mask = (1<<7)-1;
            for(int i=0; i<length; i++){
                currentSelf = arr[i]; currentOther = ~(i < other.len ? other.arr[i] : 0);
                halfAdded = (currentSelf&mask) + (currentOther&mask) + carry;
                bool c1 = currentSelf>>7; bool c2 = currentOther>>7; bool c3 = halfAdded>>7;
                carry = (unsigned char)((c1 && c2) || (c2 && c3) || (c1 && c3));
                arr[i]=currentSelf+currentOther+carry;
            }
        }

        /*-------------------------------------*/

        //Pos/Neg
        inline bool nonNeg(){
            return (arr[length-1]&(128))==0;
        }

        //Comparison
        inline bool operator>=(const BigInt& other) const{return (this->operator-(other)).nonNeg();}
        inline bool operator<=(const BigInt& other) const{return other>=*this;}
        inline bool operator<(const BigInt& other) const{return !this->operator>=(other);}
        inline bool operator>(const BigInt& other) const{return other<*this;}
        inline bool operator==(const BigInt& other) const{return this->operator>=(other) && this->operator<=(other);}
        inline bool operator==(const int& other) const{
            BigInt<length> comp = BigInt<length>(sizeof(int), (char*)&other);
            return this->operator>=(comp) && this->operator<=(comp);
        }

        /*-------------------------------------*/

        //Division
        BigInt operator%(const BigInt div) const{
            BigInt<length> num = BigInt<length>(*this);
            BigInt<length> diff = BigInt<length>(*this);
            BigInt<length> l = BigInt<length>(div);

            l <<= min(div.leadingZeros(), div.leadingZeros()-leadingZeros()+1);
            if(div == 0 || l == 0){return num;}

            while(l>=div){
                diff -= l;
                if(diff.nonNeg()){num = diff;}
                else{diff = num;}

                l>>=1;
            }

            return num;
        }
        BigInt operator/(const BigInt div) const{
            BigInt<length> num = BigInt<length>(*this);
            if(div ==0){return scaleToMax(num);}

            BigInt<length> diff = BigInt<length>(*this);
            BigInt<length> q = BigInt<length>();
            BigInt<length> l = BigInt<length>(div);

            size_t i = min(div.leadingZeros(), div.leadingZeros()-leadingZeros()+1);
            l <<= i;

            while(l>=div){
                diff -= l;
                if(diff.nonNeg()){num = diff; q[i>>3] |= 1<<(i&7);}
                else{diff = num;}

                l>>=1;
                i--;
            }

            return q;
        }
        pair<BigInt<length>, BigInt<length>> divMod(const BigInt div) const{

            BigInt<length> num = BigInt<length>(*this);
            if(div ==0){return pair<BigInt<length>, BigInt<length>>(scaleToMax(num), num);}

            BigInt<length> diff = BigInt<length>(*this);
            BigInt<length> q = BigInt<length>();
            BigInt<length> l = BigInt<length>(div);

            size_t i = min(div.leadingZeros(), div.leadingZeros()-leadingZeros()+1);
            l <<= i;

            while(l>=div){
                diff -= l;
                if(diff.nonNeg()){num = diff; q[i>>3] |= 1<<(i&7);}
                else{diff = num;}

                l>>=1;
                i--;
            }

            return pair<BigInt<length>, BigInt<length>>(q, num);
        }

        //Multiplication
        BigInt operator*(const BigInt b) const{
            BigInt<length> num = BigInt<length>();

            for(size_t i=0; i<length; i++){
                if(safeAccess(i)){num+=(b<<i);}
            }
            return num;
        }
};