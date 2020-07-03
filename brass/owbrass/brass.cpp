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

/*
 * Brass Plus
 */

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
         * cout << "You also need to pay interest according to the interest rate: " << [m_debt, this->rate](double m_rate) -> double {
            return m_rate = m_debt * this->rate;
        } << endl;
        */

        cout << "You return after ." << endl;
        cout << "Current Balance: " << br->Balance << endl;
        cout << "Current BeyondBalancei: " << br->CurrentBeyond << endl;
    }
    else
    {
        cout << "Balance: " << Balance << endl;
        cout << "CurrentBeyond: " << CurrentBeyond << "  " << "You not have Debt ." << endl;

    }

}
