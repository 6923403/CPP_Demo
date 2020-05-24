
class Bank
{
    private:
        string m_name;
        string m_cardid;
        double m_save;

    public:
        Bank() 
        {
            m_name = "";
            m_cardid = "";
            m_save = 0.0;
        };

        Bank(const string name, const string cardid, double price):m_name(name), m_cardid(cardid), m_save(price)
        {
        };
        void show() const;
        void addsave(const double & n);
        void carrysave(const double & s);
};
