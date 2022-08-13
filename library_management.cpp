#include <iostream>
#include<conio.h>
#include <stdlib.h>
#include<iomanip>
#include<cstring>
#include<fstream>
using namespace std;

class Books{
    private :
        char Bookid[6];
        char Bookname[50];
        char Author[20];
    public :
    void viewbook()
        {
            cout << this->Bookname << endl;
            cout << this->Author << endl;
        }

    void createbook()
        {
            cout << "Book_id : " ;
            cin >> this->Bookid;
            cout << endl;

            cout << "Bookname : " ;
            cin >> this->Bookname;
            cout << endl;

            cout << "Author : " ;
            cin >> this->Author;
            cout << endl;
        }
    char* retbook_id()
    {
        return this->Bookid;
    }   

    void modifybook()
    {
        cout << "BOOK ID : " << this->Bookid;
        cout << "Modify Book Name : " ;
        cin >> this->Bookname;
        cout << "Modify Author Name : " ;
        cin >> this->Author;
    } 
    void report()
        {
            cout << Bookid << setw(30)<< Bookname << setw(30) << Author << endl; 
        }

};
    
class Student {
    private:
        char Name[20];
        char Roll_no[6];
        char Book_borrowed_no[6];
        int token;
    public:
        void createstudent()
        {
            cout << "Student Name : " ;
            cin >> this->Name;
            cout << endl;
            
            cout << "Roll_no : ";
            cin >> this->Roll_no ;
            cout << endl;

            token = 0;
            Book_borrowed_no[0]= '/0';
        }
        void ViewStudentData()
        {
            cout << "Name : " << this->Name << endl;
            // cout << "Phone : " << this->Phone << endl;

            cout << "Roll no : " << this->Roll_no << endl;
            if(token == 1)
            {
                cout << "Book_borrowed_no : "<< this->Book_borrowed_no << endl;
            }
        }
        char* ret_Roll_no()
        {
            return this->Roll_no;
        }

        char* ret_book_borrowed_no()
        {
            return this->Book_borrowed_no;
        }

        int ret_token()
        {
            return this->token;
        }

        void add_token()
        {
            token = 1;
        }

        void reset_token()
        {
            token =0;
        }

        void get_book_borrowed_no(char t[])
        {
            strcpy(Book_borrowed_no,t);
        }

        void modifystudent()
        {
            cout << "Roll no of the student : " << this->Roll_no << endl;
            cout << "Enter Modified Name : " ;
            cin >> this->Name;

            cout << "Modify Book_borrowed_no : " ;
            cin >> this->Book_borrowed_no ;
        }
        void report()
        {
            cout << "\t" << Roll_no << setw(20) << Name << setw(10) << token << endl ;
        }
};

fstream fp, fp1;
Books bk;
Student st;

void writebook()
{
    char ch;
    fp.open("bookdata.dat",ios::out|ios::app);
    do
    {
        system("cls");
        bk.createbook();
        fp.write((char*)&bk,sizeof(Books));
        cout << "Do you want add more record...(y/n) "<< endl;
        cin >> ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void get_spec_book(char* n)
{
    int flag = 0;

    fp.open("bookdata.dat",ios::in);

    while(fp.read((char*)&bk,sizeof(Books)))
    {
        if(strcmpi(bk.retbook_id(),n)==0)
        {
            bk.viewbook();
            flag = 1;
        }
    }
    fp.close();
    if(flag == 0)
    {
        cout << endl << "Book does not exist" << endl;
        getch();
    }
}

void modifybook()
{
    char n[10];
    int found = 0;

    cout << "Enter the bookid : " ;
    cin >> n;
    fp.open("bookdata.dat",ios::in | ios::out) ;
    while(fp.read((char*)&bk, sizeof(Books)) && found==0 )
    {
        if(strcmpi(bk.retbook_id(),n)==0)
        {
            bk.viewbook();
            cout <<  "\nNew Details of the Book : " << endl;
            bk.modifybook();
            int pos= -1*sizeof(bk);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&bk, sizeof(Books));
            cout << "\n\n Record Updated..!"<< endl;
            found = 1;
        }
    }
    fp.close();
    if(found==0)
    {
        cout << "\n\n Record not found "<< endl;    
    }
    getch();
}

void Deletebook()
{
    char n[10];
    int flag = 0;
    system("cls");
    cout << "\n\nDelete Book... " << endl;
    cout << "Enter the Bookid: ";
    cin >> n;
    fp.open("bookdata.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(Books)))
    {
        if(strcmpi(bk.retbook_id(),n)!=0)
        {
            fp2.write((char*)&bk,sizeof(Books));
        }
        else
        {
            flag=1;
        }
    }
    fp2.close();
    fp.close();
    remove("bookdata.dat");
    rename("temp.dat","bookdata.dat");
    if(flag==1)
    {
        cout << "\n\n Record Deleted.." << endl;
    }
    else
    {
        cout << "\nRecord no Found..." << endl;
    }
    getch();
}

void Display_book_list()
{
    system("cls");
    fp.open("bookdata.dat",ios::in);
    if(!fp)
    {
        cout << "File Not Found "<< endl;
        getch();
        return;
    }

    cout << "\n\n\t\tBook List\n" << endl;
    cout << "\tBook no." << setw(20)<< "Book Name"<< setw(25) << "Author"<< endl;

    while(fp.read((char*)&bk, sizeof(Books)))
    {
        bk.report();
    } 
    fp.close();
    getch();
}

void book_issue()
{
    char sn[10],bn[10];
    int flag = 0, found=0;
    system("cls");
    cout << "\n\nBook Issue..."<< endl;
    cout << "\n\n\tEnter Rollno of Student : ";
    cin >> sn;
    fp.open("studentdata.dat",ios::in|ios::out);
    fp1.open("boodata.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(Student)) && found == 0)
    {
        if(strcmpi(st.ret_Roll_no(),sn)==0)
        {
            found = 1;
            if(st.ret_token() == 0)
            {
                cout <<"\n\n\tEnter the Book no : ";
                cin >> bn;
                while(fp1.read((char*)&bk,sizeof(Books)) && flag == 0)
                {
                    if(strcmpi(bk.retbook_id(),bn)==0)
                    {
                        flag=1;
                        st.add_token();
                        st.get_book_borrowed_no(bk.retbook_id());
                        int pos = -1*sizeof(st);
                        fp.seekg(pos,ios::cur);
                        fp.write((char*)&st,sizeof(Student));
                        cout << "\n\n\tBook Issued Successfully....";
                    }
                }
                if (flag == 0)
                {
                    cout << "Book does not exist.. " << endl;
                }
            }
            else
            {
                cout << "You havent returned the last book" << endl;
            }
        }
    }
    if(found==0)
    {
        cout << "Student does not exist" << endl;
    }
    getch();
    fp.close();
    fp1.close();
}

void book_deposit()
{
    char sn[10],bn[10];
    int flag = 0, found=0, day,fine;
    system("cls");
    cout << "\n\nBook Deposit..."<< endl;
    cout << "\n\n\tEnter Rollno of Student : ";
    cin >> sn;
    fp.open("studentdata.dat",ios::out|ios::out);
    fp1.open("boodata.dat",ios::out|ios::out);
    while(fp.read((char*)&st,sizeof(Student)) && found == 0)
    {
        if(strcmpi(st.ret_Roll_no(),sn)==0)
        {
            found = 1;
            if(st.ret_token() == 1)
            {
                while(fp1.read((char*)&bk,sizeof(Books)) && flag == 0)
                {
                    if(strcmpi(bk.retbook_id(),st.ret_book_borrowed_no())==0)
                    {
                        flag=1;
                        bk.viewbook();
                        cout << "book returned in no of days : ";
                        cin >> day;
                        if(day>10)
                        {
                            fine = 2*(day - 10);
                            cout << "Fine to be deposited : " << fine;
                        }
                        st.reset_token();
                        int pos = -1*sizeof(st);
                        fp.seekg(pos,ios::cur);
                        fp.write((char*)&st,sizeof(Student));
                        cout << "\n\n\tBook deposited Successfully....";
                    }
                }
                if (flag == 0)
                {
                    cout << "Book does not exist.. " << endl;
                }
            }
            else
            {
                cout << "No book is issued" << endl;
            }
        }
    }
    if(found==0)
    {
        cout << "Student does not exist" << endl;
    }
    getch();
    fp.close();
    fp1.close();
}

void writestudent()
{
    char ch;
    fp.open("studentdata.dat",ios::out|ios::app);
    do
    {
        system("cls");
        st.createstudent();
        fp.write((char*)&st,sizeof(Student));
        cout << "Do you want add more record...(y/n) "<< endl;
        cin >> ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void get_spec_student(char* n)
{
    int flag = 0;

    fp.open("studentdata.dat",ios::in);

    while(fp.read((char*)&st,sizeof(Student)))
    {
        if(strcmpi(st.ret_Roll_no(),n)==0)
        {
            st.ViewStudentData();
            flag = 1;
        }
    }
    fp.close();
    if(flag == 0)
    {
        cout << endl << "Student does not exist" << endl;
        getch();
    }
}

void modifystudent()
{
    char n[10];
    int found = 0;

    cout << "Enter the Rollno : " ;
    cin >> n;
    fp.open("studentdata.dat",ios::in | ios::out) ;
    while(fp.read((char*)&st, sizeof(Student)) && found==0 )
    {
        if(strcmpi(st.ret_Roll_no(),n)==0)
        {
            st.ViewStudentData();
            cout <<  "\nNew Details of the Student : " << endl;
            st.modifystudent();
            int pos= -1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st, sizeof(Student));
            cout << "\n\n Record Updated..!"<< endl;
            found = 1;
        }
    }
    fp.close();
    if(found==0)
    {
        cout << "\n\n Record not found "<< endl;    
    }
    getch();
}

void Deletestudent()
{
    char n[10];
    int flag = 0;
    system("cls");
    cout << "\n\nDelete Student... " << endl;
    cout << "Enter the Rollno: ";
    cin >> n;
    fp.open("studentdata.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(Student)))
    {
        if(strcmpi(st.ret_Roll_no(),n)!=0)
        {
            fp2.write((char*)&st,sizeof(Student));
        }
        else
        {
            flag=1;
        }
    }
    fp2.close();
    fp.close();
    remove("studentdata.dat");
    rename("temp.dat","studentdata.dat");
    if(flag==1)
    {
        cout << "\n\n Record Deleted.." << endl;
    }
    else
    {
        cout << "\nRecord no Found..." << endl;
    }
    getch();
}

void Display_student_list()
{
    system("cls");
    fp.open("studentdata.dat",ios::in);
    if(!fp)
    {
        cout << "File Not Found "<< endl;
        getch();
        return;
    }

    cout << "\n\n\t\tStudent List\n" << endl;
    cout << "\tRoll no." << setw(13)<< "Name"<< setw(20) << "Book issued"<< endl;

    while(fp.read((char*)&st, sizeof(Student)))
    {
        st.report();
    } 
    fp.close();
    getch();
}

void student(){
    system("cls");

    cout << "STUDENT MENU" << endl << endl ;

    cout << "( 1 ) BOOK ISSUE " << endl << endl ;

    cout << "( 2 ) BOOK DEPOSIT " << endl << endl;

    cout << "( 3 ) BOOK LIST " << endl << endl;

    cout << "( 4 ) MAIN MENU " << endl << endl; 
    
    cout << "( 5 ) QUIT " << endl << endl;

    cout << "Enter Option : " ;
    int c;
    cin >> c;

    switch(c){

        case 1 :
            book_issue();
            break;

        case 2 :
            book_deposit();
            break;

        case 3:
            Display_book_list();
            break;

        case 4:
            cout << "Press enter to go to main menu" << endl;
            break;

        case 5:
            exit (0);
            break;

        default:
            cout << "Please enter valid input..." << endl << "press any key to re enter the choice" << endl;
            getch();
            student();
            getch();
    }

}

void librarian()
{
    system("cls");

    cout << "Librarian MENU" << endl << endl ;

    cout << "( 1 ) CREATE STUDENT " << endl << endl ;

    cout << "( 2 ) DISPLAY ALL STUDENTS " << endl << endl;

    cout << "( 3 ) DISPLAY SPECIFIC STUDENT " << endl << endl;

    cout << "( 4 ) MODIFY STUDENT " << endl << endl; 
    
    cout << "( 5 ) DELETE STUDENT " << endl << endl;

    cout << "( 6 ) CREATE BOOK " << endl << endl;

    cout << "( 7 ) DISPLAY ALL BOOKS " << endl << endl;

    cout << "( 8 ) DISPLAY SPECIFIC BOOK " << endl << endl;

    cout << "( 9 ) MODIFY BOOK " << endl << endl;
    
    cout << "( 10 ) DELETE BOOK " << endl << endl;

    cout << "( 11 ) BACK TO MAIN MENU " << endl << endl;

    cout << "( 12 ) QUIT " << endl << endl;


    cout << "Enter Option : " ;
    int c;
    cin >> c;

    switch(c){

        case 1 :
            writestudent();
            break;

        case 2 :
            Display_student_list();
            break;

        case 3:
            char n[10];
            cout << "enter roll no of the student : ";
            cin >> n;
            get_spec_student(n);
            break;

        case 4:
            modifystudent();
            break;

        case 5:
            Deletestudent();
            break;

        case 6 :
            writebook();
            break;

        case 7 :
            Display_book_list();
            break;

        case 8:
            char bid[10];
            cout << "enter book id of the book : ";
            cin >> bid;
            get_spec_book(bid);
            break;

        case 9:
            modifybook();
            break;

        case 10:
            Deletebook();
            break;

        case 11:
            cout << "Press enter to go to main menu" << endl;
            break;

        case 12:
            exit (0);
            break;

        default:
            cout << "Please enter valid input..." << endl << "press any key to re enter the choice" << endl;
            getch();
            librarian();
            getch();
    }
}

int main(){
    int ch;
    while(1)
    {
        system("cls");
        cout << setw(25) << "-------------" << endl

        << setw( 25 ) << "| MAIN MENU |" << endl

        << setw( 25 ) << "-------------" << endl << endl

        << setw( 52 )

        << "Please choose one of the options below: "

        << endl << setw( 71 )

        << "--------------------------------------------------------------"

        << endl << endl

    

        << setw( 29 ) << "( 1 ) Student" << endl << endl

        << setw( 31 ) << "( 2 ) Librarian" << endl << endl

	    << setw( 26 ) << "( 0 ) Quit" << endl << endl
	    <<setw( 32 ) << "Enter Option  : " ;

        cin >> ch;
              // system("cls");
        
        switch(ch)
		{
			
		 	case 1 :
                student();
                getch();
                break;
         
			
		 	case 2 : 
                librarian();
                getch();
                break;
		 
		 	
		 	case 0 :
                exit(0);
                break;
         
		 	default:
			    puts("\n\n \t\tSelect only from the given menu.....\n \t\tpress enter to to go to main menu......");
			    getch();
       } //end switch
            
    }
    // getch();      
    return 0;
}
