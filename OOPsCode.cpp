#include<bits/stdc++.h>

using namespace std;

class Books{
    public:
        int id;
        string author;
        string genre;
        string name;
        float rating;
        int quantity;

        Books(int id=0,string author=" ",string genre=" ",string name=" ",float rating=0, int quantity=0) : id(id),
        author(author),genre(genre),name(name),rating(rating),quantity(quantity) {}

        bool isAvailable(){
            return quantity>0 ;
        }
        friend ostream & operator <<(ostream & out, const Books &book);
        friend istream & operator >>(istream & in, Books &book);

};

ostream &operator<<(ostream &out, const Books &book){
    out << "ID: " << book.id << endl;
    out << "Author: " << book.author <<endl;
    out << "Genre: " << book.genre <<endl;
    out << "Name: " << book.name <<endl;
    out << "Rating: " << book.rating <<endl;
    out << "Quantity: " << book.quantity <<endl;
    return out;

}

istream &operator >>(istream &in, Books &book){

    cout << "Enter id: ";
    in >> book.id;
    cout <<"enter author: ";
    in.ignore();
    getline(in, book.author);
    cout<<"Enter genre:";
    getline(in,book.genre);
    cout<<"Enter name:";
    getline(in,book.name);
    cout<<"rating:";
    in>>book.rating;
    cout<<"quantity:";
    in >> book.quantity;

    return in;

    
}


enum USER_TYPE{
    STUDENT,FACULTY
};

class user{
    public:

        int Id;
        string name;
        int age;
        int issueLimit;

        user(int id=0, string name="", int age=0, int issueLimit=0) : Id(id),
        name(name) ,age(age), issueLimit(issueLimit) {}

        virtual USER_TYPE Authorisation() = 0;

        bool CanIssue()
        {
            return issueLimit>0 ;
        }
    
};

class Student : public user{
    public:
        int scholar_No;

        Student(int scholar_No=0,int id=0, string name=" ", int age=0, int issueLimit=0 ) : 
        scholar_No(scholar_No),user(id,name,age,issueLimit) {}

        USER_TYPE Authorisation(){
            return STUDENT;
        }

        friend istream & operator >>(istream & in, Student &student);
};

istream &operator >>(istream &in, Student &student)
{
    cout<<"Enter id:";
    in >> student.Id;
    cout <<"Enter Name:";
    in.ignore();
    getline(in,student.name);
    cout << "Enter age:";
    in >> student.age;
    cout << "Enter issueLimit:";
    in>> student.issueLimit;
    cout << "Enter Scholar_No:";
    in>> student.scholar_No;


    return in;
}

class Faculty : public user{
    public:
        int Faculty_No;

        Faculty(int Faculty_No=0,int id=0, string name=" ", int age=0, int issueLimit=0 ) : 
        Faculty_No(Faculty_No),user(id,name,age,issueLimit) {}

        USER_TYPE Authorisation(){
            return FACULTY;
        }
};

istream &operator >>(istream &in, Faculty &faculty)
{
    cout<<"Enter id:";
    in >> faculty.Id;
    cout <<"Enter Name:";
    in.ignore();
    getline(in,faculty.name);
    cout << "Enter age:";
    in >> faculty.age;
    cout << "Enter issueLimit:";
    in>> faculty.issueLimit;
    cout << "Enter Faculty_No:";
    in>> faculty.Faculty_No;


    return in;
}

class BookIssued {
    public:
        Books* books;
        user* User;
        string issued_date;
        string return_date;

        BookIssued(Books* books, user* User, string issued_date, string return_date) : books(books),
         User(User), issued_date(issued_date), return_date(return_date) {
            books->quantity--;
            User->issueLimit--;
        }
        ~BookIssued()
        {
            books->quantity++;
            User->issueLimit++;
        }
        friend ostream & operator <<(ostream & out, const BookIssued &bookIssued);


};

ostream & operator <<(ostream & out, const BookIssued &bookIssued){
    out << "Book Id:" << bookIssued.books->id << endl;
    out << "User Id:" << bookIssued.User->Id << endl;
    out << "Issue Date" << bookIssued.issued_date << endl;
    out << "Return Date" << bookIssued.return_date << endl;
    return out;
}

class Library{
    public:
        map<int,Books*>books;
        map<int, user*>users;
        vector<BookIssued*>issueBooks;

        void IssueBook();
        void CreatUser();
        void AddBook();
        void PrintAvailableBooks();
        void PrintIssueBook();
};

void Library:: IssueBook(){
    int b_id, u_id;
    string issue_date, return_date;
    cout <<"Enter book id:";
    cin >> b_id;
    cout << "Enter user id:";
    cin >> u_id;
    cout << "Enter issue date:";
    cin>> issue_date;
    cout << "Enter return date";
    cin >> return_date;

    BookIssued* ib = new BookIssued(books[b_id],users[u_id],issue_date,return_date);
    issueBooks.push_back(ib);
}

void Library::CreatUser(){
    int opt;
    Student* s_user;
    Faculty* f_user;
    cout << "1. New Student"<< endl;
    cout << "2. New Faculty"<< endl;
    cout << "3. Go back"<< endl;
    cout << "Enter choice";
    cin >> opt;

    switch(opt){
        case 1:
            s_user=new Student();
            cin >>*s_user;
            users[s_user->Id] = s_user;
            break;
        case 2:
            f_user = new Faculty();
            cin >> *f_user;
            users[f_user->Id] = f_user;
            break;
        case 3:
            return;
        default:
            cout << "Invalid input"<< endl;
            return; 
    }
}

void Library::AddBook(){
    Books* b= new Books();
    cin >>*b;
    books[b->id]=b;
}

void Library:: PrintAvailableBooks(){
    for(auto it:books){
        cout<<*(it.second)<<endl;
    }
}

void Library::PrintIssueBook(){
    for(auto it:issueBooks){
        cout<< *it<< endl;
    }
}

int main(){

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int choice=0;
    Library library;

    do{
        cout<< "1. Add new book" <<endl;
        cout<< "2. Register New User" <<endl;
        cout<< "3. Issue Book" <<endl;
        cout<< "4. Print Available Books" <<endl;
        cout<< "5. Print Issued Books" <<endl;
        cout<< "6. Exit" <<endl;
        cout<< "Enter appropriate choice:";
        cin>> choice;
        switch(choice){
            case 1:
                library.AddBook();
                break;
            case 2:
                library.CreatUser();
                break;
            case 3:
                library.IssueBook();
                break;
            case 4:
                library.PrintAvailableBooks();
                break;
            case 5:
                library.PrintIssueBook();
                break;
            case 6:
                break;
            default:
                cout<<"Invalid input" <<endl;
                break;
        }
    }while(choice!=6);


    return 0;
}