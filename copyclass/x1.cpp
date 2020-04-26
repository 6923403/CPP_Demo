class X
{
    public:
        X()
        {
            cout << "X()" << endl;
        }

        X(const X &)
        {
            cout << "X(csont X&)" << endl;
        }

        X operator=(const X&)
        {
                
        }

        ~X()
        {}
};
