template <typename R = int, typename U>
R func(U val)
{
    return val;
}

int main()
{
    func(97);               // R=int, U=int
    func<char>(97);         // R=char, U=int
    func<double, int>(97);  // R=double, U=int
    return 0;
}
