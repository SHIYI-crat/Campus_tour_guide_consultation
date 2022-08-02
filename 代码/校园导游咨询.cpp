#include <iostream>
#include <cstring>
#include <iomanip>
#include <conio.h>
using namespace std;

#define Max 11    //�������
#define MX 999999 //���������

int D[Max][Max]; //��ʾ���㵽��������·��Ȩֵ�͵ľ���
int path[Max][Max]; //��ʾ���ڶ������С·��ǰ������

struct Users //�˺�����
{
    char account[30];
    char password[30];
} use[50];
typedef struct Ver //������Ϣ
{
    char num[4];        //�������
    char name[41];      //��������
    char instruct[401]; //����˵��
} Ver;
typedef struct //�ڽӾ���
{
    Ver vex[Max];       //�����
    int arcs[Max][Max]; //�ڽӾ���
    int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͱ���
} AMGragh;

int Login_System();                           //���Ϲ�ҵ��ѧУ԰������ѯϵͳ��¼ϵͳ
int Administrator_Login();                    //����Ա��¼����
int Registered_Account();                     //����Աע���˺�
int Login();                                  //����Ա�˺������¼
void CreateUDG(AMGragh &G);                   //���ݻ�����Ϣ��ͼ
int Administrators();                         //����Ա����(�������й���)
int User();                                   //�û�����(���Ų��ֹ���)
void Administrators_Menu();                   //����Ա�˵�����
void User_Menu();                             //�οͲ˵�����
void Introduce();                             //���Ϲ�ҵ��ѧ���
void Map();                                   //���Ϲ�ҵ��ѧƽ���ͼ
void Query(AMGragh G);                        //��ѯ���������Ϣ
void All_Print(AMGragh G);                    //������о�����Ϣ
void Modify_vertex(AMGragh &G);               //���������Ϣ����
void Modify_Edge(AMGragh &G);                 //·��������Ϣ����
void Floyd(AMGragh G);                        //���������㷨����������·��
void Ask(AMGragh G);                          //�û���ѯ���·��
void Path_Out(AMGragh G, int start, int end); //��þ���·��

int main(void) //������
{
    system("color F0"); //����Ϊ�ڣ�����Ϊ����ɫ
    Login_System();
    return 0;
}

int Login_System() //���Ϲ�ҵ��ѧУ԰������ѯϵͳ��¼ϵͳ
{
    int select;
    cout << "**********��ӭʹ�ú��Ϲ�ҵ��ѧУ԰������ѯϵͳ**********" << endl;
    cout << "*                                                      *" << endl;
    cout << "*                   ��ѡ���¼��ʽ                     *" << endl;
    cout << "*                                                      *" << endl;
    cout << "*     ��1.����Ա��¼   ��2.�ο���ʱ��¼   ��3.�˳�     *" << endl;
    cout << "*                                                      *" << endl;
    cout << "********************************************************" << endl;
    cout << "������Ҫѡ��ı��:" << endl;
    cin >> select;
    switch (select)
    {
    case 1:
        Administrator_Login();
        break;
    case 2:
        system("pause");
        system("cls");
        User();
        break;
    case 3:
        cout << "�ɹ��˳�����ӭ�´�ʹ��..." << endl;
        system("pause");
        return 0;
        break;
    default:
        cout << "�������û�и�ѡ���Ӧ�Ĳ�����" << endl;
        break;
    }
    return 0;
}

int Administrator_Login() //����Ա��¼����
{
    int select;
    while (select != 3)
    {
        system("cls");
        cout << "*********************����Ա��¼����*********************" << endl;
        cout << "*                                                      *" << endl;
        cout << "*               ��1.�˺�����ֱ�ӵ�¼                   *" << endl;
        cout << "*                                                      *" << endl;
        cout << "*               ��2.��������˺�����                   *" << endl;
        cout << "*                                                      *" << endl;
        cout << "*               ��3.�˳�                               *" << endl;
        cout << "*                                                      *" << endl;
        cout << "********************************************************" << endl;
        cout << "������Ҫѡ��ı��:" << endl;
        cin >> select;
        switch (select)
        {
        case 1:
            Login();
            break;
        case 2:
            Registered_Account();
            break;
        case 3:
            cout << "�ɹ��˳�����ӭ�´�ʹ��..." << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "�������û�и�ѡ���Ӧ�Ĳ�����" << endl;
            system("pause");
            break;
        }
    }
    return 0;
}

int Registered_Account() // ע���˺Ź���
{
    char account[30];
    char password[6], pd[6];
    int i, a = 0, flag = 0;

    cout << "ע���ʺ�..." << endl;
    cout << "�������û��˺ź�����(�˺š��������Ϊ����,������ĸ,Ӣ����ĸ,����,�������6λ)" << endl;
    cout << "�������˺ţ�" << endl;
    cin >> account;

    FILE *fp = fopen("Date.txt", "a+");
    while (!feof(fp))
    {
        fscanf(fp, "%s %sn", &use[a].account, &use[a].password);
        if ((strcmp(account, use[a].account) == 0))
        {
            cout << "ע��ʧ��,���˺��Ѵ��ڣ����������룡" << endl;
            system("pause");
            flag = 1;
            fclose(fp);
            break;
        }
        a++;
    }

    if (flag == 1)
        return 0;

    strcpy(use[a].account, account);
    cout << "�����������룺" << endl;
    for (i = 0; i < 6; i++)
    {
        password[i] = _getch();
        cout << "*";
        use[a].password[i] = password[i];
        if (password[i] == '\r')
        {
            cout << "ע��ʧ�ܣ�������ע���˺�" << endl;
            return 0;
        }
    }
    cout << endl;
    cout << "�ٴ�ȷ�����룺" << endl;
    for (i = 0; i < 6; i++)
    {
        pd[i] = _getch();
        cout << "*";
        if (use[a].password[i] != pd[i])
        {
            cout << "���벻�ԣ�������ע���˺�" << endl;
            return 0;
        }
    }
    fprintf(fp, "�˺�\t����\n");
    fprintf(fp, "%s\t%s\n", use[a].account, use[a].password);
    printf("\nע��ɹ�!!!\n");
    fclose(fp);
    system("pause");
    system("cls");
}

int Login() //��¼�˺Ź���
{
    char account[30];
    char ad[20], password;
    int i, j, a = 0;
    int flag = 0;

    cout << "**********************��¼�˺�**********************" << endl;
    for (i = 0; i < 3; i++)
    {
        cout << "�������ʺ�:" << endl;
        cin >> account;
        cout << "����������:" << endl;
        for (j = 0; j < 6; j++)
        {
            password = _getch();
            cout << "*";
            ad[j] = password;
        }
        FILE *fp;
        fp = fopen("Date.txt", "r"); //��ȡ�ļ�����
        while (!feof(fp))
        {
            fscanf(fp, "%s %sn", &use[a].account, &use[a].password);
            if ((strcmp(account, use[a].account) == 0) && (strcmp(ad, use[a].password) == 0))
            {
                flag = 1;
                fclose(fp);
                break;
            }
            a++;
        }
        cout << endl;
        if (flag == 1)
        {
            cout << "��¼�ɹ�!" << endl;
            system("pause");
            system("cls");
            Administrators();
            break;
        }
        else
        {
            cout << "�˺Ż���������������㻹��" << 2 - i << "�λ��ᣬ���������룺" << endl;
        }
    }
    if (i == 3)
    {
        cout << "��¼ʧ��" << endl;
        system("pause");
        return 0;
    }
}

void CreateUDG(AMGragh &G) //���ݻ�����Ϣ��ͼ
{
    G.vexnum = 10;
    strcpy(G.vex[0].num, "01");
    strcpy(G.vex[1].num, "02");
    strcpy(G.vex[2].num, "03");
    strcpy(G.vex[3].num, "04");
    strcpy(G.vex[4].num, "05");
    strcpy(G.vex[5].num, "06");
    strcpy(G.vex[6].num, "07");
    strcpy(G.vex[7].num, "08");
    strcpy(G.vex[8].num, "09");
    strcpy(G.vex[9].num, "10");
    strcpy(G.vex[0].name, "�³��㳡");
    strcpy(G.vex[1].name, "ͼ���");
    strcpy(G.vex[2].name, "4�Ž�ѧ¥");
    strcpy(G.vex[3].name, "�� ��");
    strcpy(G.vex[4].name, "��¥�㳡");
    strcpy(G.vex[5].name, "�� ��");
    strcpy(G.vex[6].name, "ѧ������");
    strcpy(G.vex[7].name, "�� ��");
    strcpy(G.vex[8].name, "����ѵ������");
    strcpy(G.vex[9].name, "ʵ��ʵѵ����");
    strcpy(G.vex[0].instruct, "�³��㳡��������ĳ�����Ҳ��ٰ�һЩ��������У԰��Ƹ�ᣬ�����ֻ������ߵ���԰��");
    strcpy(G.vex[1].instruct, "ͼ��ݻ������ʣ�����ḻ���䱸�ִ���������ʩ�����Ķ��鼮��ĩ��ϰ��ս���еľ��ѳ�����");
    strcpy(G.vex[2].instruct, "4�Ž�ѧ¥�ǡ���Ҫ��ѧ��¥���䱸�ִ�����ѧ��ʩ������ʦ�Ͽκ�ѧ����ϰ�ĳ�����ѧϰ��ΧŨ��!");
    strcpy(G.vex[3].instruct, "������ˮ�峺���ף������ܿ��������õ�С�㣬���м�ֻ���ŵ�ѼѼ��");
    strcpy(G.vex[4].instruct, "ʳ�ð�����һ���ڶ�������ʳ��,�������ʳ����ḻ����������󱥿ڸ�!");
    strcpy(G.vex[5].instruct, "��¥�㳡��ƽʱ���žٰ��ĳ�����������ٰ�һЩ���ͻ!");
    strcpy(G.vex[6].instruct, "ѧ������Ϊ��׼��/���˼䣬�����䱸�յ�ů������ů�������ռ��ԣ����ס���ʣ�");
    strcpy(G.vex[7].instruct, "�ٳ��������򳡣����򳡣����򳡵ȣ���������ﾶ��������ˮ�����Ͽ��ܻ�ٰ����ֻ�Ŷ��");
    strcpy(G.vex[8].instruct, "��������ʩ��ȫ������ƹ���򳡣���ë�򳡣����ҳ��صȣ������ʹ��һ���˶��ɣ�");
    strcpy(G.vex[9].instruct, "ʵ��ʵѵ�����ṩ���غ���ʩ��ѧ��������������ʵ��ͽ𹤡����ӹ���ʵϰ��");
    G.arcs[1][2] = G.arcs[2][1] = 8;
    G.arcs[1][3] = G.arcs[3][1] = 3;
    G.arcs[2][5] = G.arcs[5][2] = 17;
    G.arcs[2][4] = G.arcs[4][2] = 4;
    G.arcs[2][10] = G.arcs[10][2] = 31;
    G.arcs[3][6] = G.arcs[6][3] = 21;
    G.arcs[4][5] = G.arcs[5][4] = 12;
    G.arcs[5][6] = G.arcs[6][5] = 6;
    G.arcs[5][7] = G.arcs[7][5] = 5;
    G.arcs[5][9] = G.arcs[5][9] = 27;
    G.arcs[7][8] = G.arcs[8][7] = 21;
    G.arcs[8][9] = G.arcs[9][8] = 13;
    G.arcs[9][10] = G.arcs[10][9] = 18;
    for (int i = 1; i <= 10; i++) //��ʼ��·������
        for (int j = 1; j <= 10; j++)
        {
            if (G.arcs[i][j] == 0 && i != j)
                G.arcs[i][j] = MX;
        }
    G.arcnum = 13;        
}

int Administrators() //����Ա����(�������й���)
{
    AMGragh G;
    memset(G.arcs, 0, sizeof(G.arcs));
    CreateUDG(G);
    int m;
    while (m != 8)
    {
        Administrators_Menu();
        cin >> m;
        switch (m)
        {
        case 1:
            Introduce();
            break;
        case 2:
            Map();
            break;
        case 3:
            Query(G);
            break;
        case 4:
            All_Print(G);
            break;
        case 5:
            Ask(G);
            break;
        case 6:
            Modify_vertex(G);
            break;
        case 7:
            Modify_Edge(G);
            break;
        case 8:
            cout << "��л����ʹ�ã�" << endl;
            return 0;
        default:
            cout << "û�и�ѡ�" << endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}

int User() //�û�����(���Ų��ֹ���)
{
    AMGragh G;
    memset(G.arcs, 0, sizeof(G.arcs));
    CreateUDG(G);
    int m;
    while (m != 5)
    {
        User_Menu();
        cin >> m;
        switch (m)
        {
        case 1:
            Introduce();
            break;
        case 2:
            Map();
            break;
        case 3:
            Query(G);
            break;
        case 4:
            Ask(G);
            break;
        case 5:
            cout << "��л����ʹ�ã�" << endl;
            return 0;
        default:
            cout << "û�и�ѡ�" << endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}

void Administrators_Menu() //����Ա�˵�����
{
    cout << "***************��ӭ��**************" << endl;
    cout << "*       ��1���鿴У԰��ϸ��Ϣ     *" << endl;
    cout << "*       ��2���鿴��У԰ƽ��ͼ     *" << endl;
    cout << "*       ��3��У԰������Ϣ��ѯ     *" << endl;
    cout << "*       ��4��������о�����Ϣ     *" << endl;
    cout << "*       ��5���������·����ѯ     *" << endl;
    cout << "*       ��6���޸ľ��������Ϣ     *" << endl;
    cout << "*       ��7���޸�·��������Ϣ     *" << endl;
    cout << "*       ��8�� ������һ���˵�      *" << endl;
    cout << "***********************************" << endl;
    cout << "��ѡ��..." << endl;
}

void User_Menu() //�û��˵�����
{
    cout << "***************��ӭ��**************" << endl;
    cout << "*       ��1���鿴У԰��ϸ��Ϣ     *" << endl;
    cout << "*       ��2���鿴��У԰ƽ��ͼ     *" << endl;
    cout << "*       ��3��У԰������Ϣ��ѯ     *" << endl;
    cout << "*       ��4���������·����ѯ     *" << endl;
    cout << "*       ��5���˳�                 *" << endl;
    cout << "***********************************" << endl;
    cout << "��ѡ��..." << endl;
}

void Introduce() //���Ϲ�ҵ��ѧ���
{
    cout << endl;

    cout << "���Ϲ�ҵ��ѧ��Henan University of Technology��λ�ں���ʡ��֣���У��Ǻ���ʡ���������͹�����ʳ�ֹ�����У;ʼ����1956�꣬�Ⱥ�����������ʳ������ҵ���͹���ó�ײ���1959�꿪չ���ƽ�����1981�꿪ʼ˶ʿ�о���������2013�꿪ʼ��ʿ�о���������2017�����˶ʿ�о��������ʸ�2018�������ʿѧλ���赥λ�� 1998�껮�����ʡ��������ʡ���������͹�����ʳ����2010��ǩԼ�������Ϲ�ҵ��ѧ��" << endl;

    cout << "��У����ѧУ��֡�������ԭ��������ҵ������ȫ�����������硱�İ�ѧ��λ�����ء�����Ϊ����������У����ɫ��չ���İ�ѧ������С����¡����ǡ����¡����С���Уѵ������������п�ѧ������̽����������ѧ����ǿ��Ϣ���Ĺ����������γ��ˡ��Ž��ȡ����ʵ��Ч����У�硢����ѧ���ס��Ľ̷�͡��ڷܳ��š���ѧ�硣" << endl;

    cout << "�������������˵�����ͼ�κ�н�𴫳У�ѧУ�Ѿ���չ��Ϊһ���Թ�ѧΪ����������ѧ������ѧ������ѧ����ѧ����ѧ������ѧ��ũѧ��ѧ��Э����չ�Ķ���Դ�ѧ�������߱�������ѧʿ��˶ʿ����ʿ�����˲�������ϵ��������Ϊ�ڶ���λ�ɹ���ѡ���������� 2011Эͬ���¼ƻ������ǽ���������������У�����������蹤�̡��͡�׿Խ����ʦ���������ƻ��������У�����ƶ���ҵ������͹��Ҿ�����ᷢչ��ʵ�ֽ������˵Ĺ�����������Ӧ�й��ף����˲���������ѧ�о���������ȷ����ȡ��������ɼ��� " << endl;

    cout << endl;
}

void Map() //���Ϲ�ҵ��ѧƽ���ͼ
{
    cout << " ��������������������������������������������������������" << endl;
    cout << "|                   ���Ϲ�ҵ��ѧƽ��ͼ                  |" << endl;
    cout << " ��������������������������������������������������������" << endl;
    cout << "|                           ����                        |" << endl;
    cout << "|           [8]�ٳ�����������������[7]����              |" << endl;
    cout << "|            |                      |                   |" << endl;
    cout << "|            |                      |                   |" << endl;
    cout << "|            |������������������[5]��¥�㳡����         |" << endl;
    cout << "|            |                  |      |       |        |" << endl;
    cout << "|          [9]��������          |      |     [6]����    |" << endl;
    cout << "|����       |                   |      |       |    ����|" << endl;
    cout << "|           |             [4]����      |       |        |" << endl;
    cout << "|           |                 |        |       |        |" << endl;
    cout << "|           |               [2]ͼ��ݡ�        |        |" << endl;
    cout << "|   [10]����ʵѵ���� ����������|               |        |" << endl;
    cout << "|        ��                    |������[3]4�Ž�ѧ¥      |" << endl;
    cout << "|        ��                    |                        |" << endl;
    cout << "|  �� �� �� ����             [1]�³��㳡                |" << endl;
    cout << "|        ��                                             |" << endl;
    cout << "|        ��                  ����                       |" << endl;
    cout << " ��������������������������������������������������������" << endl;
}

void Query(AMGragh G) //��ѯ���������Ϣ
{
    cout << "�������ѯ����Ĵ���(���� 06)��";
    char c[5];
    cin >> c;
    int i;
    for (i = 0; i < G.vexnum; i++) // n��С������˳����Ҽ���
    {
        if (strcmp(c, G.vex[i].num) == 0)
        {
            cout << "���ţ�" << G.vex[i].num << endl;
            cout << "��������:" << G.vex[i].name << endl;
            cout << "��飺" << G.vex[i].instruct << endl;
            break;
        }
    }
    if (i == G.vexnum)
    {
        cout << "�ô��Ų�����!" << endl;
    }
}

void All_Print(AMGragh G) //������о�����Ϣ
{
    cout << "----------------------------------���Ϲ�ҵ��ѧ������Ϣ----------------------------------" << endl;
    cout << setw(16) << setiosflags(ios::left) << "��������"
         << setw(8) << setiosflags(ios::left) << "����"
         << setw(16) << setiosflags(ios::left) << "���" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        cout << setw(16) << G.vex[i].name << setw(8) << G.vex[i].num << setw(60) << G.vex[i].instruct << endl;
    }
    cout << endl;
}

void Modify_vertex(AMGragh &G) //���������Ϣ����
{
    All_Print(G);
    int flag = 0;
    cout << "������Ҫ�޸���Ϣ�Ĵ���(���� 06)��";
    char c[5];
    cin >> c;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (strcmp(c, G.vex[i].num) == 0) //�ַ����Ƚϵķ������в���
        {
            flag = 1;
            memset(G.vex[i].name, 0, sizeof(G.vex[i].name)); //��G.vex[i].**�������ֽڻ����ַ���0�������ַ����ĳ�ʼ��
            memset(G.vex[i].instruct, 0, sizeof(G.vex[i].instruct));
            char name1[41];
            char instruct1[401];
            cout << "�������޸ĺ�ľ�����Ϣ��" << endl;
            cout << "�������ƣ�";
            cin >> name1;
            cout << "��飺";
            cin >> instruct1;
            strcpy(G.vex[i].name, name1); //�ַ�����������
            strcpy(G.vex[i].instruct, instruct1);
            cout << "�޸ĳɹ���" << endl;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "�������" << endl;
    }
}

void Modify_Edge(AMGragh &G) //·��������Ϣ����
{
    Map();
    int i, j, k;
    cout << "��������޸ĵı�(����5 8):" << endl;
    cin >> i >> j;
    if ((G.arcs[i][j] != MX && G.arcs[j][i] != MX) && (i >= 1 && i <= 10) && (j >= 1 && j <= 10))
    {
        cout << "�������޸ĺ�ı߳�(���� 6)��";
        cin >> k;
        G.arcs[i][j] = G.arcs[j][i] = k;
        cout << "�޸ĳɹ���" << endl;
    }
    else
    {
        cout << "�������" << endl;
    }
}

void Ask(AMGragh G) //�û���ѯ���·��
{
    Map();
    cout << "����������Ŀ�ĵ�(����06 08):";
    int i, j;
    cin >> i >> j;
    if ((i >= 1 && i <= 10) && (j >= 1 && j <= 10))
    {
        Floyd(G);
        cout << endl
             << endl
             << "��" << G.vex[i - 1].name << "��" << G.vex[j - 1].name << ":" << endl
             << endl
             << "���·�����ȣ�" << D[i][j] * 10 << "��" << endl; //���·��Ϊ��С10���ľ��룬�������߻�ԭ
        cout << endl;
        Path_Out(G, i, j);
    }
    else
    {
        cout << "�������" << endl;
    }
    cout << endl;
}

void Floyd(AMGragh G) //���������㷨������������·��
{
    int i, j, k;
    for (i = 1; i <= G.vexnum; ++i) //��ʼ��
        for (j = 1; j <= G.vexnum; j++)
        {
            D[i][j] = G.arcs[i][j];
            if (D[i][j] < MX && i != j)
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    for (k = 1; k <= G.vexnum; k++) //�������·��
        for (i = 1; i <= G.vexnum; ++i)
            for (j = 1; j <= G.vexnum; j++)
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = path[k][j];
                }
}

void Path_Out(AMGragh G, int start, int end) //��þ���·��
{
    int p[Max];
    p[0] = end;
    int i = 1;
    while (start != end)
    {
        end = path[start][end];
        p[i] = end;
        ++i;
    }
    cout << "·��:" << G.vex[start - 1].name;
    i = i - 2;
    while (i >= 0)
    {
        cout << "��" << G.vex[p[i] - 1].name;
        --i;
    }
    cout << endl;
}
