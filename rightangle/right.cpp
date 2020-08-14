template <typename T>
struct Foo
{
      typedef T type;
};
template <typename T>
class A
{
    // ...
};
int main(void)
{
    Foo<A<int>>::type xx;  //编译出错
    return 0;
}
