#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

//주어진 자료대로 구조체 생성.
struct Subject
{                   // 과목 정보
    string SubName; // 과목이름
    int Hakjum;     // 과목학점
    string Grade;   // 과목등급
    float GPA;      // 과목 평점
};
struct Student
{                        // 학생 정보
    string StdName;      // 학생 이름
    int Hakbun;          // 학번
    struct Subject *Sub; // 과목
    //동적할당 받을 과목 수
    int SubNum;
    float AveGPA; // 교과목 평균 평점
};

inline int printMenu();                                            //메뉴 출력 함수
void inputStudentInfo(struct Student *student, int studentNum);    //학생 정보 입력 함수
float calGrade(Subject &Sub);                                      //학점과 등급으로 평점을 구하는 함수
void printAllStudentInfo(struct Student *student, int studentNum); // 모든 학생의 성적을 출력하는 함수
//총 학생수는 상수로 선언했기 때문에 인자로 넣어주지 않음.

void printEachStudentInfo(struct Student &eachStd);                     // 한 학생의 성적을 출력하는 함수
float gradeAverage(struct Student *eachStd);                            // 평점을 평균내는 함수
Student *StdSearch(Student *stList, string searchName, int studentNum); // 학생 검색 함수. 학생의 리스트를 받고 학생의 위치 주소를 리턴함!
void printAllStdList(Student *stList, int stdNum = 0);                  //전체 학생 리스트 출력
void modify(Student *stdInfo);
Subject *subSearch(const Student &stdInfo);

inline void inputValue(string str)
{
    getline(cin, str);
}; //오버로딩한 inline함수. 입력들을 대체한다.
inline void inputValue(string *str)
{
    getline(cin, *str);
};
inline void inputValue(int &num)
{
    cin >> num;
    cin.ignore();
};

int main()
{
    int select = 0;     //사용자가 메뉴에서 선택하는 값
    int studentNum = 0; //동적할당 받을 학생 수
    string searchName;
    Student *searchResult = NULL;
    //학생 선언

    cout << "2018038074 임종훈\n"
         << endl;
    cout << "성적 관리할 학생 수를 입력하세요 : ";
    inputValue(studentNum);

    struct Student *stList = new Student[studentNum];

    while (select != 6)
    { //3이 나올 때까지 메뉴 반복 출력
        //1,2,3 이외의 값을 입력하면 프로그램 종료.
        select = printMenu();

        if (select == 1)
        {
            for (int i = 0; i < studentNum; i++)
            {
                cout << i + 1 << "번째 학생 이름과 학번을 입력하세요." << endl;
                inputStudentInfo(&stList[i], studentNum);
            }
        }
        else if (select == 2)
        {
            printAllStudentInfo(stList, studentNum);
        }
        else if (select == 3)
        { //학생 검색 후 출력
            cout << "검색 할 학생 이름 : ";
            inputValue(&searchName);

            searchResult = StdSearch(stList, searchName, studentNum);
            if (searchResult == NULL)
            {
                cout << "학생을 찾을 수 없습니다.\n"
                     << endl;
            }
            else
            {
                printEachStudentInfo(*searchResult);
            }
        }
        else if (select == 4)
        {
            printAllStdList(stList, studentNum);
        }
        else if (select == 5)
        {
            cout << "검색 할 학생 이름 : ";
            inputValue(&searchName);

            searchResult = StdSearch(stList, searchName, studentNum);
            if (searchResult == NULL)
            {
                cout << "학생을 찾을 수 없습니다.\n"
                     << endl;
            }
            else
            {
                modify(searchResult); //주소
            }
        }
    }

    cout << "\n프로그램을 종료합니다.";

    //free(stList);
    for (int a = 0; a < studentNum; a++)
    {
        delete[] stList[a].Sub;
    }
    delete[] stList;
    return 0;
}

inline int printMenu()
{
    int num = 0;
    cout << "===== 메뉴 =====\n";
    cout << "1. 학생 성적 입력\n";
    cout << "2. 전체 학생 성적 보기\n";
    cout << "3. 학생 이름 검색\n";
    cout << "4. 전체 학생 목록 보기\n";
    cout << "5. 학생 정보 수정\n";
    cout << "6. 프로그램 종료\n\n";
    cout << "원하는 기능을 입력하세요: ";

    inputValue(num);
    //cin.fail()은 cin 명령이 실패하면 true를 반환

    /*if(cin.fail()){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
위의 코드를 사용하려고 했으나 repl에서는 정상작동하고 vsc에서는 오류가 발생하는 현상 때문에 사용하지 못 함.
max에 인자 전달이 부족하다는데 구글링 해봐도 비슷한 사례를 찾지 못해 옳지 못한 값을 입력하면 강제종료하게끔 프로그램 수정*/
    if (cin.fail())
    {
        cout << "옳지 않은 형식입니다. 프로그램을 종료합니다." << endl;
        exit(1);
    }
    if (num < 0 || num > 6)
    {
        cout << "옳지 않은 형식입니다. 프로그램을 종료합니다." << endl;
        exit(1);
    }

    return num;
}

void inputStudentInfo(struct Student *std, int studentNum)
{
    cout << "먼저 과목의 수를 입력하세요 : ";
    inputValue(std->SubNum);
    std->Sub = new Subject[std->SubNum]; //과목 수만큼 동적할당

    cout << "이름 : ";
    //cin>>std->StdName;
    inputValue(&(std->StdName));

    cout << "학번 : ";
    //cin>>std->Hakbun;
    inputValue(std->Hakbun);

    cout << "* 수강한 과목 " << std->SubNum << "개와 각각 교과목명, 과목학점, 과목등급을 입력하세요." << endl;

    for (int i = 0; i < std->SubNum; i++)
    {
        cout << "교과목명 : ";
        //cin>>std->Sub[i].SubName;
        inputValue(&(std->Sub[i].SubName));

        cout << "과목 몇 학점 : ";
        //cin>>std->Sub[i].Hakjum;
        inputValue(std->Sub[i].Hakjum);

        if (cin.fail() || std->Sub[i].Hakjum <= 0)
        {
            cout << "잘못된 형식의 학점입니다. 프로그램을 종료합니다.";
            exit(1);
        }

        //ABC같은 등급 입력
        cout << "과목 등급 : ";
        //cin>>std->Sub[i].Grade;
        inputValue(&(std->Sub[i].Grade));

        //과목 평점 계산
        std->Sub[i].GPA = calGrade(std->Sub[i]);

        if (cin.fail() || std->Sub[i].GPA < 0)
        {
            cout << "잘못된 형식의 등급입니다. 프로그램을 종료합니다.";
            exit(1);
        }
        cout << endl;
    }
}
float calGrade(Subject &Sub)
{ // 특정 학생의 특정 '과목'을 인자로 받는다. 이후 이 과목의 학점 * '과목의 성적'을 변환, 곱해서 반환.
    //(주의!)Sub.Grade == "A+"와 같이 직접 비교하면 배열의 크기가 달라서 거짓판정
    /*cout<<typeid(Sub.Grade).name()<<endl;
    cout<<typeid("A").name()<<endl;*/

    string temp_grade = Sub.Grade;

    if (temp_grade == "A+")
    {
        return 4.5 * Sub.Hakjum;
    }
    else if (temp_grade == "A0" || temp_grade == "A")
    {
        return 4.0 * Sub.Hakjum;
    }
    else if (temp_grade == "B+")
    {
        return 3.5 * Sub.Hakjum;
    }
    else if (temp_grade == "B0" || temp_grade == "B")
    {
        return 3.0 * Sub.Hakjum;
    }
    else if (temp_grade == "C+")
    {
        return 2.5 * Sub.Hakjum;
    }
    else if (temp_grade == "C0" || temp_grade == "C")
    {
        return 2.0 * Sub.Hakjum;
    }
    else if (temp_grade == "D+")
    {
        return 1.5 * Sub.Hakjum;
    }
    else if (temp_grade == "D0" || temp_grade == "D")
    {
        return 1.0 * Sub.Hakjum;
    }
    else if (temp_grade == "F")
    {
        return 0.0;
    }
    else
    {
        return -1;
    }
}

void printAllStudentInfo(struct Student *student, int studentNum)
{
    cout << "          전체 학생 성적 보기" << endl;
    cout << "==================================================" << endl;
    for (int i = 0; i < studentNum; i++)
    {
        printEachStudentInfo(student[i]);
    }
}

void printEachStudentInfo(struct Student &eachStd)
{
    cout << "이름 : " << eachStd.StdName << " 학번 : " << eachStd.Hakbun << endl;
    cout << "==================================================" << endl;
    cout << "      과목명     과목학점     과목등급     과목평점" << endl;
    cout << "==================================================" << endl;

    //width() 대신 setw 사용.
    //setprecision(2); ???????????????? 반복문 안에 밖에 다 써줘도 해결 X
    for (int i = 0; i < eachStd.SubNum; i++)
    {
        //cout.precision(2);
        cout << right << setw(12) << eachStd.Sub[i].SubName << setw(12) << eachStd.Sub[i].Hakjum << setw(12) << eachStd.Sub[i].Grade << setw(12) << eachStd.Sub[i].GPA << endl;
    }

    cout << "==================================================" << endl;
    cout.width(50);
    cout.precision(2);
    // fixed를 써주지 않으면 뒤의 0은 출력되지 않음.
    cout << "평균평점   " << fixed << setprecision(2) << gradeAverage(&eachStd) << endl;
}

float gradeAverage(struct Student *eachStd)
{
    float sum = 0;
    float average = 0;

    for (int i = 0; i < eachStd->SubNum; i++)
    {
        sum = sum + eachStd->Sub[i].GPA;
    }
    average = sum / eachStd->SubNum;
    return average;
}

Student *StdSearch(Student *stList, string searchName, int studentNum)
{

    for (int a = 0; a < studentNum; a++)
    {
        if (searchName == stList[a].StdName)
        {
            return &stList[a];
        }
    }

    return NULL;
}

void printAllStdList(Student *stList, int stdNum)
{
    cout << "==================================================" << endl;
    cout << "         학번            이름" << endl;
    cout << "==================================================" << endl;
    for (int a = 0; a < stdNum; a++)
    {
        cout << right << setw(12) << stList[a].Hakbun << setw(14) << stList[a].StdName << endl;
    }

    cout << "==================================================" << endl;
}

void modify(Student *stdInfo)
{
    string select;
    cout << "수정<StudentInfo/SubjectInfo> : ";

    while (1)
    {
        inputValue(&select);
        if (select == "SubjectInfo")
        {
            Subject *searchSub = subSearch(*stdInfo);
            if (searchSub == NULL)
            {
                return;
            }
            else
            {
                cout << "*<" << searchSub->SubName << ", 학점 : " << searchSub->Hakjum << ", 등급 : " << searchSub->Grade << ">의 정보를 수정하세요" << endl;
                cout << "교과목명 : ";
                inputValue(&(searchSub->SubName));

                cout << "과목학점 : ";
                inputValue(searchSub->Hakjum);

                cout << "과목등급 : ";
                inputValue(&(searchSub->Grade));

                searchSub->GPA = calGrade(*searchSub);
            }
            break;
        }
        else if (select == "StudentInfo")
        {
            //학생 정보를 수정하는 함수
            cout << "*<" << stdInfo->StdName << ", " << stdInfo->Hakbun << ">의 정보를 수정하세요" << endl;
            cout << "이름 : ";
            inputValue(stdInfo->StdName);
            cout << "학번 : ";
            inputValue(stdInfo->Hakbun);
            break;
        }
        else
        {
            cout << "입력 오류입니다. 다시 입력해주세요.\n\n";
        }
    }
}

Subject *subSearch(const Student &stdInfo)
{
    string input_sub; //입력받은 과목
    int sub_num;
    int is_find = 0; //과목 찾았는지 여부 확인

    cout << "검색 할 과목 이름 : ";
    inputValue(&input_sub);

    for (sub_num = 0; sub_num < stdInfo.SubNum; sub_num++)
    {
        if (input_sub == stdInfo.Sub[sub_num].SubName)
        {
            is_find = 1;
            break;
        }
    }

    if (is_find == 0)
    {
        cout << "입력한 과목이 없습니다.";
        return NULL;
    }

    return &(stdInfo.Sub[sub_num]);
}