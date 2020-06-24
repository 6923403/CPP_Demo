#include "Student.h"

using namespace std;

Student::Student()
{
    StuListHead = new StuNode;
    StuListHead->next = nullptr;
}

Student::~Student()
{
    StuNode * p;
    p = StuListHead;
    while(StuListHead->next != nullptr)
    {
        p = StuListHead;
        StuListHead = StuListHead->next;
        delete p;
    }
}

void Student::ShowMenu()
{
    time_t result = std::time(nullptr);

    cout << "********************************************" << endl;
    cout << "******     学  生  信  息  系  统    ******" << endl;
    cout << "******       0.安全退出系统          ******" << endl;
    cout << "******       1.文件读入学生信息      ******" << endl;
    cout << "******       2.录入新的学生信息      ******" << endl;
    cout << "******       3.删除已有学生信息      ******" << endl;
    cout << "******       4.查找已有学生信息      ******" << endl;
    cout << "******       5.修改已有学生信息      ******" << endl;
    //cout << "******       7.已有学生信息排序      ******" << endl;
    //cout << "******       8.分类合计学生信息      ******" << endl;
    cout << "******       6.输出所有学生信息      ******" << endl;
    cout << "******       7.保存现有学生信息      ******" << endl;
    cout << endl << asctime(std::localtime(&result));
    cout << " 请选择：";
    Selectcase();

}

void Student::Selectcase()
{
    int n;
    cin >> n;
    switch(n)
    {
        case 0:
            exit(-1);
            break;
        case 1:
            setFileStu(); //从文件读信息
            break;
        case 2:
            CreateStuinfo(); //手动设置信息
            break;
        case 3:
            StuDelete(); //删除指定学号
            break;
        case 4:
            StuFind();//查找已有学生信息
            break;
        case 5:
             StuInfoModify();//修改已有学生信息
            break;
        case 6:
            ShowInfo();
            break;
        case 7:
            saveFileStu();//保存现有学生信息
            break;
    }
}

void Student::saveFileStu()
{
    ofstream on;
    char result = time(nullptr);
    on.open("..\\StudentInfo.txt", ios::out);
    StuNode * p, * s;
    p = StuListHead->next;
    while(p->next != nullptr)
    {
        s = p;
        on << s->num << " " << s->math << " " << s->eng << " " << s->chinese << " " << s->sum << endl;
        cout << s->num << endl;
        p = p->next;
    }

    cout << "生成文件完成" << endl;
    on.close();
}

void Student::StuInfoModify()
{
    int num;
    cout << "请输入学号: ";
    cin >> num;
    StuNode * p, * s;
    p = StuListHead;
    s = p;

    while(p->next != nullptr)
    {
        if(p->num == num)
        {
            CreateStuinfo(p);
            p = p->next;
        }
        else
        {
            s = p;
            p = p->next;
        }
    }
}

void Student::CreateStuinfo(StuNode * q) const
{
    int n;
    StuNode * p;
    cout << "分别输入学号 数学成绩 英语成绩 语文成绩";
    cin >> q->num >> q->math >> q->eng >> q->chinese;
    q->sum = q->math + q->eng + q->chinese;
    p = StuListHead;
    q->next = p->next;
    //p = q;
    p->next = q;
    p = p->next;

    if(p == nullptr)
    {
        cout << "创建失败" << endl;
        CreateStuinfo(q);
    }
}

void Student::StuFind()
{
    int num;
    cout << "请输入学号: ";
    cin >> num;
    StuNode * p, * s;
    p = StuListHead;
    s = p;

    while(p->next != nullptr)
    {
        if(p->num == num)
        {
            ShowInfo(p);
            p = p->next;
        }
        else
        {
            s = p;
            p = p->next;
        }
    }
}

void Student::ShowInfo(StuNode * s) const
{
    cout << "学号: " << s->num << " 数学: " << s->math << " 英语: " << s->eng << " 语文: " << s->chinese << " 总分: " << s->sum << endl;
    return;
}

void Student::StuDelete()
{
    begin:
    int num;
    cout << "请输入学号: ";
    cin >> num;
    StuNode * p, * s;
    p = StuListHead;
    s = p;

    while(p->next != nullptr)
    {
        if(p->num == num)
        {
            s->next = p->next;
            delete p;
            cout << "删除成功!" << endl;
            return;
        }
        else
        {
            s = p;
            p = p->next;
        }
    }

    cout << "Not found the num. " << endl;
}

void Student::ShowInfo()
{
    StuNode * s;
    for(s = StuListHead->next; s != nullptr; s = s->next)
    {
        cout << "学号: " << s->num << " 数学: " << s->math << " 英语: " << s->eng << " 语文: " << s->chinese << " 总分: " << s->sum << endl;
    }
}

void Student::CreateStuinfo()
{
    int n;
    StuNode * q, * p;
    q = new StuNode;
    cout << "分别输入学号 数学成绩 英语成绩 语文成绩";
    cin >> q->num >> q->math >> q->eng >> q->chinese;
    q->sum = q->math + q->eng + q->chinese;
    p = StuListHead;
    q->next = p->next;
    //p = q;
    p->next = q;
    p = p->next;

    if(p == nullptr)
    {
        cout << "创建失败" << endl;
        CreateStuinfo();
    }
}

void Student::setFileStu() {
    ifstream infile;
    infile.open("N:\\codes\\Cplusplus\\stu1\\obj.txt", ios::in | ios::binary);

    if (!infile)
    {
        cout << "Error: No Open File." << endl;
        return;
    }
    while(!infile.eof())
    {
        int num, math, eng, chinese;
        infile >> num >> math >> eng >> chinese;
        StuInsert(num, math, eng, chinese);
    }

    infile.close();
}

void Student::StuInsert(int num, int math, int eng, int chinese) //头插
{
    StuNode * s, * p;
    s = new StuNode;
    s->num = num;
    s->math = math;
    s->eng = eng;
    s->chinese = chinese;
    s->sum = math + eng + chinese;
    p = StuListHead;
    s->next = p->next;
    p->next = s;
}


