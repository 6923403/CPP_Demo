#ifndef BRASS_H
#define BRASS_H

#include <string>
#include <iostream>
using namespace std;

class Brass
{
    private:
        string ClientName;
        long NumCard;
        double Balance;

    public:
        virtual ~Brass();
        Brass(const string & name, long numcard, double balance);

        void setAccount();
        virtual void Deposit();
        virtual void DrawMoney();
        virtual void Show() const;
};

class BrassPlus : public Brass
{
    private:
        double rate;
        double BeyondBalance;
        double CurrentBeyond;
        bool Debt;
        Brass * br;

    public:
//        BrassPlus(cosnt string & name, double NumCard = -1, double balance = 0.0, double rate = 0, double BeyondBalance = 0.0, double CurrentBeyond = 0.0, bool Debt) : Brass(name, NumCard, Balance);
        ~BrassPlus();

        virtual void Show() const;
        virtual void Deposit();
        virtual void DrawMoney();
};

#endif
