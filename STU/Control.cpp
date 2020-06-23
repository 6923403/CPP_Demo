#include "Control.h"

Control::Control()
{
    Stuchioce = 0;
}

Control::~Control()
{

}

Control::Control(int Ch)
{
    Stuchioce = Ch;

    Controlcase(Stuchioce);
}

Control::Controlcase(int Stuchioce)
{
    switch(Stuchioce)
    {
        case 1:

            break;

    }
}

void Control::changeStu_info()
{

}

void Control::ChangeStu_grade()
{

}
