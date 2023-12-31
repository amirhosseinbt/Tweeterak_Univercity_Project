#include "user.h"
#include <QDebug>
User::User()
{
}

User::~User()
{

}


QString User::Get_Name()
{
    return Name;
}

QString User::Get_Username()
{
    return Username;
}


bool User::Set_Username(const QString &username) // validation of username occurs here
{
    QString message;
    QValidator::State st;
    if (username.size() < 5)
    {
        message="! Username must contain at least 5 character.";
        st = QValidator::Invalid;
        emit Validate(message,st);
        return 0;
    }

    for (int i = 0; i < username.size(); i++)
    {

        if(username.at(i).isSpace())
        {
            message="! Username must be without space.";
            st = QValidator::Invalid;
            emit Validate(message,st);
            return 0;
        }
        if (username.at(0).isNumber())
        {
            message="! Username can not start with number.";
            st = QValidator::Invalid;
            emit Validate(message,st);
            return 0;
        } // if

        if(!username.at(i).isLetterOrNumber())
        {

            message="! Username just contains numbers and English letters.";
            st = QValidator::Invalid;
            emit Validate(message,st);
            return 0;
        }
    }
        st = QValidator::Acceptable;
        message ="";
        Username = username;
        emit Validate(message,st);
        return 1;
}

Organization_User::Organization_User()
{

}

Organization_User::~Organization_User()
{

}
bool Organization_User::Set_Biography(const QString biography) // validation of bio occurs here
{
        QString message;
        QValidator::State st;
        if(biography.size() > 1100)
        {
            message="! Biography must has less than 1100 characters.";
            st = QValidator::Invalid;
            emit Validate(message,st);
            return 0;
        }
        st = QValidator::Acceptable;
        message ="";
        Biography = biography;
        emit Validate(message,st);
        return 1;
}

Personal_User::Personal_User()
{

}

Personal_User::~Personal_User()
{

}

bool Personal_User::Set_Biography(const QString biography) // validation of bio occurs here
{
        QString message;
        QValidator::State st;
        if(biography.size() > 160)
        {
            message="! Biography must has less than 160 characters.";
            st = QValidator::Invalid;
            emit Validate(message,st);
            return 0;
        }
        st = QValidator::Acceptable;
        message ="";
        Biography = biography;
        emit Validate(message,st);
        return 1;
}

Anonymous_User::Anonymous_User()
{        

}

Anonymous_User::~Anonymous_User()
{

}

bool Anonymous_User::Set_Biography(const QString biography) // validation of bio occurs here
{
        QString message;
        QValidator::State st;
        if(biography.size() > 160)
        {
            message="! Biography must has less than 160 characters.";
            st = QValidator::Invalid;
            emit Validate(message,st);
            return 0;
        }
        st = QValidator::Acceptable;
        message ="";
        Biography = biography;
        emit Validate(message,st);
        return 1;
}


QString User::Get_Biography()
{
        return Biography;
}


void User::Set_Country(const QString country)
{
        Country = country;
}

QString User::Get_Country()
{
        return Country;
}

void User::Set_Link(QString link)
{
    QString https = "https://";
    if(!link.contains(https))
    {
            link = https + link;
    }
    Link = link;
}
QString User::Get_Link()
{
        return Link;
}

void Organization_User::Set_Birthday(QDate birthday)
{
        return;
}
void Personal_User::Set_Birthday(QDate birthday)
{
        BirthdayDate = birthday;
}
void Anonymous_User::Set_Birthday(QDate birthday)
{
        return;
}
void Organization_User::Set_Name(const QString &name)
{
        Name =name;
}

void Organization_User::Set_Admin_id(int userid)
{
        Admin_id = userid;
}

int Organization_User::Get_Admin_id()
{
        return Admin_id;
}

QString Organization_User::Get_Admin_Username()
{
        QFile Users ("User_file.txt");
        if(!Users.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            QMessageBox::information(0,"Warning","! File can not open.");
        }
        else
        {

            QTextStream file(&Users);
            QStringList list;
            while(!file.atEnd())
            {
                list = file.readLine().split("%$%");
                if(list.at(0) == "P" && list.at(15).toInt() == Admin_id)
                {
                    QString name=list.at(1);
                    Users.close();
                    return name;
                }
            }
            Users.close();
        }
        return "";
}

void Organization_User::Set_Type()
{
        User_Type ="O";
}


void Organization_User::My_overload(QTextStream & out)
{
        out << User_Type <<"%$%"<<Username<<"%$%"<<Password<<"%$%"<<Name<<"%$%"<<PhoneNumber<<"%$%"<<Biography<<"%$%"<<
        Country<<"%$%"<<Link<<"%$%"<<Header<<"%$%"<<Picture_path<<"%$%"<<BirthdayDate.toString("yyyy.MM.dd")<<"%$%"<<N_Followers<<"%$%"<<
            N_Followings<<"%$%"<<Admin_id<<"%$%"<<Last_Tweet_id<<"%$%"<<User_id<<"%$%";
        for(auto &F:Followers)
        {
            if(F != 0)
            {

                out<<F<<",";
            }
        }
        out<<"%$%";;
        for(auto &F:Followings)
        {
            if(F != 0)
            {

                out<<F<<",";
            }
        }
        out<<"%$%"<<'\n';
}

void Organization_User::My_Read_Overload(QStringList &list)
{
        this->Set_Type();
        this->Set_Username(list.at(1));
        this->Set_Secret_Pass(list.at(2));
        this->Set_Name(list.at(3));
        this->Set_Phonenumber(list.at(4));
        this->Set_Biography(list.at(5));
        this->Set_Country(list.at(6));
        this->Set_Link(list.at(7));
        this->Set_Header(list.at(8));
        this->Set_Picture_Path(list.at(9));
        this->Set_Birthday(QDate::fromString(list.at(10),"yyyy.MM.dd"));
        this->Set_N_Followers(list.at(11).toInt());
        this->Set_N_Followings(list.at(12).toInt());
        this->Set_Admin_id(list.at(13).toInt());
        this->Set_Last_Tweet_id(list.at(14).toInt());
        this->Set_Userid(list.at(15).toInt());

        QStringList follower,following;
        follower =list.at(16).split(",");
        for(int i = 0; i < follower.size() ;i++)
        {
            this->Set_Followers(follower.at(i).toInt());
        }

        following =list.at(17).split(",");
        for(int i = 0; i < following.size() ;i++)
        {
            this->Set_Followings(following.at(i).toInt());
        }
}

void Organization_User::Set_Picture_Path(QString path)
{
        Picture_path = path;
}

void Organization_User::Set_Header(QString color)
{
        Header = color;
}
void Personal_User::Set_Name(const QString &name)
{
        Name = name;
}

void Personal_User::Set_Type()
{
        User_Type = "P";
}

void Personal_User::Set_Organ_id(int userid)
{
        Organid = userid;
}

int Personal_User::Get_Organ_id()
{
        return Organid;
}

QString Personal_User::Get_Organ_Uname()
{
        if(Organid == 0)
        {
            return "";
        }
        QFile Users ("User_file.txt");
        if(!Users.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            QMessageBox::information(0,"Warning","! File can not open.");
        }
        else
        {

            QTextStream file(&Users);
            QStringList list;
            while(!file.atEnd())
            {
                list = file.readLine().split("%$%");
                if(list.at(0) == "O"&&list.at(15).toInt() == Organid )
                {
                    QString name=list.at(1);
                    Users.close();
                    return name;
                }
            }
            Users.close();
        }
        return "";
}


void Personal_User::My_overload(QTextStream & out)
{
        out << User_Type <<"%$%"<<Username<<"%$%"<<Password<<"%$%"<<Name<<"%$%"<<PhoneNumber<<"%$%"<<Biography<<"%$%"<<
            Country<<"%$%"<<Link<<"%$%"<<Header<<"%$%"<<Picture_path<<"%$%"<<BirthdayDate.toString("yyyy.MM.dd")<<"%$%"<<N_Followers<<"%$%"<<
            N_Followings<<"%$%"<<Organid<<"%$%"<<Last_Tweet_id<<"%$%"<<User_id<<"%$%";
        for(auto &F:Followers)
        {
            if(F != 0)
            {

                out<<F<<",";
            }
        }
        out<<"%$%";;
        for(auto &F:Followings)
        {
            if(F != 0)
            {

                out<<F<<",";
            }
        }
        out<<"%$%"<<'\n';
}

void Personal_User::My_Read_Overload(QStringList &list)
{
        this->Set_Type();
        this->Set_Username(list.at(1));
        this->Set_Secret_Pass(list.at(2));
        this->Set_Name(list.at(3));
        this->Set_Phonenumber(list.at(4));
        this->Set_Biography(list.at(5));
        this->Set_Country(list.at(6));
        this->Set_Link(list.at(7));
        this->Set_Header(list.at(8));
        this->Set_Picture_Path(list.at(9));
        this->Set_Birthday(QDate::fromString(list.at(10),"yyyy.MM.dd"));
        this->Set_N_Followers(list.at(11).toInt());
        this->Set_N_Followings(list.at(12).toInt());
        this->Set_Organ_id(list.at(13).toInt());
        this->Set_Last_Tweet_id(list.at(14).toInt());
        this->Set_Userid(list.at(15).toInt());

        QStringList follower,following;
        follower =list.at(16).split(",");
        for(int i = 0; i < follower.size() ;i++)
        {
            this->Set_Followers(follower.at(i).toInt());
        }

        following =list.at(17).split(",");
        for(int i = 0; i < following.size() ;i++)
        {
            this->Set_Followings(following.at(i).toInt());
        }
}

void Personal_User::Set_Picture_Path(QString path)
{
        Picture_path = path;
}

void Personal_User::Set_Header(QString color)
{
        Header = color;
}
void Anonymous_User::Set_Name(const QString &name)
{
        Name = "Anonymous User";
}

void Anonymous_User::Set_Type()
{
        User_Type = "A";
}



void Anonymous_User::My_overload(QTextStream & out)
{
        out << User_Type <<"%$%"<<Username<<"%$%"<<Password<<"%$%"<<Name<<"%$%"<<PhoneNumber<<"%$%"<<Biography<<"%$%"<<
            Country<<"%$%"<<Link<<"%$%"<<Header<<"%$%"<<Picture_path<<"%$%"<<BirthdayDate.toString("yyyy.MM.dd")<<"%$%"<<N_Followers<<"%$%"<<
            N_Followings<<"%$%"<<Last_Tweet_id<<"%$%"<<User_id<<"%$%";
        for(auto &F:Followers)
        {
            if(F != 0)
            {

                out<<F<<",";
            }
        }
        out<<"%$%";;
        for(auto &F:Followings)
        {
            if(F != 0)
            {

                out<<F<<",";
            }
        }
        out<<"%$%"<<'\n';
}

void Anonymous_User::My_Read_Overload(QStringList &list)
{
        this->Set_Type();
        this->Set_Username(list.at(1));
        this->Set_Secret_Pass(list.at(2));
        this->Set_Name(list.at(3));
        this->Set_Phonenumber(list.at(4));
        this->Set_Biography(list.at(5));
        this->Set_Country(list.at(6));
        this->Set_Link(list.at(7));
        this->Set_Header(list.at(8));
        this->Set_Picture_Path(list.at(9));
        this->Set_Birthday(QDate::fromString(list.at(10),"yyyy.MM.dd"));
        this->Set_N_Followers(list.at(11).toInt());
        this->Set_N_Followings(list.at(12).toInt());
        this->Set_Last_Tweet_id(list.at(13).toInt());
        this->Set_Userid(list.at(14).toInt());

        QStringList follower,following;
        follower =list.at(15).split(",");
        for(int i = 0; i < follower.size() ;i++)
        {
            this->Set_Followers(follower.at(i).toInt());
        }

        following =list.at(16).split(",");
        for(int i = 0; i < following.size() ;i++)
        {
            this->Set_Followings(following.at(i).toInt());
        }
}

void Anonymous_User::Set_Picture_Path(QString path)
{
        path =":/icons/img/Anonymous.png";
        Picture_path = path;
}

void Anonymous_User::Set_Header(QString color)
{
        Header = color;
}

QDate User::Get_Birthday()
{
        return BirthdayDate;

}
bool User::Set_Phonenumber(QString phonenumber) // validation of phonenumber occurs here
{

        QString message;
        QValidator::State st;
        for (int i = 0; i < phonenumber.size(); i++)
        {
            if(phonenumber.at(i).isSpace())
            {
                st = QValidator::Invalid;
                message ="! Phonenumber must be without space.";
                emit Validate(message,st);
                return 0;
            }
            if(!phonenumber.at(i).isNumber())
            {
                st = QValidator::Invalid;
                message ="! Phonenumber just contains numbers.";
                emit Validate(message,st);
                return 0;
            }
        }
        st = QValidator::Acceptable;
        message ="";
        PhoneNumber = phonenumber;
        emit Validate(message,st);
        return 1;
}
QString User::Get_Phonenumber()
{
        return PhoneNumber;
}
bool User::Set_Password(QString password) // validation of password occurs here

// if password just contain letter or just number or just unnormal char it is weak
// if contains upper or lower letter and number but length of it be less than 7 it is weak
// if contains upper or lower letter and number and unnormal char but its length be less than 6 it is weak
// if contains upper and lower letter and number and unnormal char but its length be less than 5 it is weak
{
        bool ContainUpper = false;
        bool ContainLower = false;
        bool ContainNumber = false;
        bool ContainUnnormalchar = false;
        QString message;
        QValidator::State st;
        for(int i = 0; i < password.size() ; i++)
        {
            if(password.at(i).isSpace())
            {
                st = QValidator::Invalid;
                message ="! Password must be without space.";
                emit Validate(message,st);
                return 0;
            }
            if(password.at(i).isUpper())
            {
                ContainUpper = true;
            }
            if(password.at(i).isLower())
            {
                ContainLower = true;
            }
            if(password.at(i).isNumber())
            {
                ContainNumber = true;
            }
            if(!password.at(i).isLetterOrNumber())
            {
                ContainUnnormalchar = true;
            }
        }
        SHA256 pass; // use for making secret password
        if(ContainUpper && ContainLower && ContainNumber && ContainUnnormalchar && password.size() >4)
        {
            Password =QString::fromStdString(pass(password.toStdString()));
        }
        else if((ContainUpper || ContainLower) && ContainNumber && ContainUnnormalchar && password.size() >5)
        {
            Password = QString::fromStdString(pass(password.toStdString()));
        }
        else if((ContainUpper || ContainLower) && (ContainNumber || ContainUnnormalchar) && password.size() >6)
        {
            Password = QString::fromStdString(pass(password.toStdString()));
        }
        else
        {
            st = QValidator::Invalid;
            message ="! Password is Weak.";
            emit Validate(message,st);
            return 0;
        }
        st = QValidator::Acceptable;
        message ="";
        emit Validate(message,st);
        return 1;

}

void User::Set_Secret_Pass(QString pass)
{
        Password = pass;
}
//SetPassword
QString User::Get_Password()
{
        return Password;
}

//GetPassword
void User::Change_N_Followers()
{
        N_Followers++;
        QFile Users ("User_file.txt");
        if(!Users.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            QMessageBox::information(0,"Warning","! File can not open.");
            return;
        }
        else
        {
            QString str="";
            QTextStream file(&Users);
            while(!file.atEnd())
            {
                QString line = file.readLine();
                QStringList list = line.split("%$%");
                if(list.at(1) != Username)
                {
                    str.append(line+'\n');
                }
            }
            Users.resize(0);
            file << str;
            file << this;
            Users.close();
        }
}
//ChangeNFollowers
void User::Set_N_Followers(int num)
{
        N_Followers = num;
}
int User::Get_N_Followers()
{
        return N_Followers;
}

void User::Set_Followers(int id)
{
        Followers.push_back(id);
}//GetNFollowers

void User::Change_N_Followings()
{
        N_Followings++;
        QFile Users ("User_file.txt");
        if(!Users.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            QMessageBox::information(0,"Warning","! File can not open.");
            return;
        }
        else
        {
            QString str="";
            QTextStream file(&Users);
            while(!file.atEnd())
            {
                QString line = file.readLine();
                QStringList list = line.split("%$%");
                if(list.at(1) != Username)
                {
                    str.append(line+'\n');
                }
            }
            Users.resize(0);
            file << str;
            file << this;
            Users.close();
        }
}
//ChangeNFolowings
void User::Set_N_Followings(int num)
{
        N_Followings = num;
}
int User::Get_N_Followings()
{
        return N_Followings;
}

void User::Set_Followings(int id)
{
        Followings.push_back(id);
}

std::vector<int> User::Get_Followings()
{
        return Followings;
}

QString User::Get_Type()
{
        return User_Type;
}

QString User::Get_Picture_Path()
{
        return Picture_path;
}

QString User::Get_Header()
{
        return Header;
}

void User::Set_Last_Tweet_id(int id)
{
        Last_Tweet_id = id;
}

void User::Add_Last_Tweet_id() // we need to store last tweet id to giving id to new tweets
{
    Last_Tweet_id++;
    QFile Users ("User_file.txt");
    if(!Users.open(QIODevice::ReadWrite|QIODevice::Text))
    {
            QMessageBox::information(0,"Warning","! File can not open.");
            return;
    }
    else
    {
        QString str="";
        QTextStream file(&Users);
        while(!file.atEnd())
        {
                QString line = file.readLine();
                QStringList list = line.split("%$%");
                if(list.at(1) != Username)
                {
                    str.append(line+'\n');
                }
        }
        Users.resize(0);
        file << str;
        file << this;
        Users.close();
    }

}

int User::Get_Last_Tweet_id()
{
    return Last_Tweet_id;
}

void User::Set_Userid(int id)
{
    User_id = id;
}

int User::Get_Userid()
{
    return User_id;
}

bool User::Check_Password_History(QString pass)
{
    QFile History("PassHistory.txt");
    if(!History.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QMessageBox::information(0,"Warning","! File can not open.");
        return 0;
    }
    else
    {
        SHA256 secretpass;
        QTextStream file(&History);
        QStringList list;
        while(!file.atEnd())
        {
                list = file.readLine().split("%$%");
                if(list.at(0).toInt() == this->Get_Userid() && list.at(1) ==QString::fromStdString(secretpass(pass.toStdString())))
                {
                    History.close();
                    return 0;
                }
        }
        History.close();
        return 1;

    }
}

void User::Set_Password_History(QString pass)
{
    QFile History("PassHistory.txt");
    if(!History.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append))
    {
        QMessageBox::information(0,"Warning","! File can not open.");
        return;
    }
    else
    {
        QTextStream file(&History);
        file << this->Get_Userid()<<"%$%"<<pass<<'\n';
        History.close();
    }
}

void User::Erase_Follower(int id)
{
    for (int i = 0; i < Followers.size(); i++)
    {
        if (Followers[i] == id)
        {
            Followers.erase(Followers.begin()+i);
            N_Followers--;
        }
    }
    QFile Users ("User_file.txt");
    if(!Users.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QMessageBox::information(0,"Warning","! File can not open.");
        return;
    }
    else
    {
        QString str="";
        QTextStream file(&Users);
        while(!file.atEnd())
        {
            QString line = file.readLine();
            QStringList list = line.split("%$%");
            if(list.at(1) != Username)
            {
                    str.append(line+'\n');
            }
        }
        Users.resize(0);
        file << str;
        file << this;
        Users.close();
    }
}

void User::Erase_Following(int id)
{
    for (int i = 0; i < Followings.size(); i++)
    {
        if (Followings[i] == id)
        {
            Followings.erase(Followings.begin()+i);
            N_Followings--;
        }
    }
    QFile Users ("User_file.txt");
    if(!Users.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QMessageBox::information(0,"Warning","! File can not open.");
        return;
    }
    else
    {
        QString str="";
        QTextStream file(&Users);
        while(!file.atEnd())
        {
            QString line = file.readLine();
            QStringList list = line.split("%$%");
            if(list.at(1) != Username)
            {
                    str.append(line+'\n');
            }
        }
        Users.resize(0);
        file << str;
        file << this;
        Users.close();
    }
}




