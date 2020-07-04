#include "brass.h"

Brass::~Brass()
{

}

Brass::Brass(const string & name = "NoBody", long numcard = -1, double balance = 0.0) : ClientName(name), NumCard(numcard), Balance(balance)
{

}

void Brass::Deposit()
{
    cout << "Current Balance: " << Balance << endl;
    cout << "Deposit: ";
    double tmp = 0.0;
    cin >> tmp;
    Balance += tmp;
    cout << "Current Balance: " << Balance << endl;
}

void Brass::DrawMoney()
{
    cout << "Need Num: ";
    double tmp = 0.0;
    cin >> tmp;
    if(Balance >= tmp)
    {
        Balance -= tmp;
        cout << "Current Balance: " << Balance << endl;
    }
    else
    {
        cout << "You imposible haven't enough Balance ." << endl;
    }
}

void Brass::Show() const
{
    cout << "ClientName: " << ClientName << endl;
    cout << "NumCard: " << NumCard << endl;
    cout << "Balance: " << Balance << endl;
}

void Brass::setAccount()
{
    cout << "Set client name: ";
    cin >> ClientName;
    cout << "Set NumCard: ";
    cin >> NumCard;
    cout << "Set Balance: ";
    cin >> Balance;
    cout << endl;
}

void Brass::DrawMoney(double drawtmp)
{
    Balance = Balance - drawtmp;
}

double Brass::getBalance() const
{
    return Balance;
}

/*
 * Brass Plus
 */
BrassPlus::BrassPlus(const string & name, long numcard, double balance, double BeyondBalance, double CurrentBeyond)
    : Brass(name, numcard, balance), BeyondBalance(BeyondBalance), CurrentBeyond(CurrentBeyond)
{
    rate = 0.11125;
    Debt = false;
}

BrassPlus::~BrassPlus()
{}

void BrassPlus::Deposit()
{
    if(Debt) //if have debt
    {
        cout << "You beyond is: " << BeyondBalance << endl;
        cout << "You beyond current is: " << CurrentBeyond << endl;

        double m_debt = CurrentBeyond - BeyondBalance;
        cout << "You have return Beyond is: " << m_debt << endl;
      /* 
        cout << "You also need to pay interest according to the interest rate: " << [m_debt, this->rate](double m_rate) -> double {
            return m_rate = m_debt * this->rate;
        } << endl;
        */
        /*
         * lambda用的不熟练 今晚复习下 本功能先暂停
         */

        cout << "You return after ." << endl;
        Brass::Show();
        cout << "Current BeyondBalance: " << CurrentBeyond << endl;
    }
    else
    {
        //cout << "Balance: " << br->Balance << endl;
        Brass::Show();
        cout << "CurrentBeyond: " << CurrentBeyond << "  " << "You not have Debt ." << endl;
    }
}

void BrassPlus::DrawMoney()
{
    double batmp = Brass::getBalance(); 
    cout << "You Can Draw: " << (batmp + CurrentBeyond)<< endl; 
    double drawtmp;
    cout << "You need Num: ";
    cin >> drawtmp;
    if(drawtmp <= (batmp + CurrentBeyond))
    {
        if(drawtmp <= batmp)
        {
            Brass::DrawMoney(drawtmp);
        }
        else
        {
            drawtmp = drawtmp - batmp;
            Brass::DrawMoney(batmp);
            DrawMoney(drawtmp);
        }
    }
    else
    {
        cout << "Sorry, You Balance No enough ." << endl;
    }
}

void BrassPlus::DrawMoney(double drawtmp)
{
    CurrentBeyond = CurrentBeyond - drawtmp;
}

void BrassPlus::Show() const
{
    Brass::Show();
    cout << "BeyondBalance sum: " << BeyondBalance << endl;
    cout << "CurrentBeyond: " << CurrentBeyond << endl;
}
