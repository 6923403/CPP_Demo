#include "test.h"

namespace de
{
    unsigned decode(unsigned w, unsigned h, State st)
    {
        st.sum = w * h;
        return st.sum;
    }
}
