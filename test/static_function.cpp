#include <iostream>
#include <string>
//http://c.biancheng.net/view/2228.html

class People
{
public:
    People(std::string name, int age);
    void show();
    static int get_age();
    static int get_people();

public:
    static int sum_age;
    static int sum_people;

private:
    std::string m_name;
    int m_age;
};

int People::sum_age = 0;
int People::sum_people = 0;

People::People(std::string name, int age) : m_name(name), m_age(age) {
    sum_age += age;
    sum_people++;
}

void People::show() {
    std::cout << "m_name = " << m_name << " m_age = " << m_age << std::endl;
}

int People::get_age() {
    return sum_age;
}
int People::get_people() {
    return sum_people;
}

int main(int argc, char** argv)
{
    (new People("张", 20)) ->show();
    (new People("李", 10)) ->show();
    (new People("王", 29)) ->show();
    (new People("赵", 18)) ->show();

    int total_age = People::get_age();
    int total_people = People::get_people();
    std::cout << "总年龄 = " << total_age << " 总人数 = " << total_people << " 平均年龄 = " << total_age / total_people << std::endl;

    return 0;
}