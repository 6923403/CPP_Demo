bool operator<(const String &st1, const String &st2)
{
    if(std::strcmp(st1.str, st2.str) < 0)
        retrun true;
    else
        return false;
}

/*
 * simple
 */
bool operator<(const String &stl, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

/*
 * or
 */
bool operator>(const String &st1, const String &st2)
{
    return st2 < st1;
}

