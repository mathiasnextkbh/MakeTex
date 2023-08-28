#include <bits/stdc++.h>
#include <direct.h>

class Project {
    public:
    std::string DOCUMENT_TITLE, DOCUMENT_AUTHOR, DOCUMENT_SUBJECT, DOCUMENT_SCHOOL, FORMAT_DATE;

    std::string get_month_name ( int month ) {
        switch (month+1) {  // fucking what???
            case 1:     return "Januar";
            case 2:     return "Februar";
            case 3:     return "Marts";
            case 4:     return "April";
            case 5:     return "Maj";
            case 6:     return "Juni";
            case 7:     return "Juli";
            case 8:     return "August";
            case 9:     return "September";
            case 10:    return "Oktober";
            case 11:    return "November";
            case 12:    return "December";
        }
        return NULL;
    };

    std::string get_formatted_date () {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,80,"%m/%d/%Y",timeinfo);
        std::string str(buffer);
        str.erase(6, 2);
        
        std::locale loc;
        const std::time_get<char>& tmget = std::use_facet <std::time_get<char> > (loc);

        std::ios::iostate state;
        std::istringstream iss (str);

        std::tm when;
        tmget.get_date (iss, std::time_get<char>::iter_type(), iss, state, &when);

        std::string date = "d. " + std::to_string(when.tm_mday) + ". " + get_month_name(when.tm_mon) + ", 20" + std::to_string(when.tm_year);

        return date;
    };

    std::string current_working_directory () {
        char* cwd = _getcwd( 0, 0 ) ; // **** microsoft specific ****
        std::string working_directory(cwd) ;
        std::free(cwd) ;
        return working_directory ;
    };

    std::string FORMAT_CONTENT ( Project Current ) {
        return "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
        "\n\n% Document variables"
        "\n\n\\renewcommand{\\title}{" + Current.DOCUMENT_TITLE + "}"
        "\n\n\\renewcommand{\\author}{" + Current.DOCUMENT_AUTHOR + "}"
        "\n\n\\newcommand{\\subject}{" + Current.DOCUMENT_SUBJECT + "}"
        "\n\n\\renewcommand{\\date}{" + Current.FORMAT_DATE + "}"
        "\n\n\\newcommand{\\school}{" + Current.DOCUMENT_SCHOOL + "} \n \n";
    };

    void CREATE_DOCUMENT ( Project Current ) {
        std::string dir_rev = current_working_directory();
        std::string dir_raw = dir_rev + "/src";
        const char* directory = dir_raw.c_str();
        _mkdir(directory);
        _chdir(directory);

        std::ifstream original ("C:/Program Files/MakeTex/LaTeX/config.txt");
        std::ofstream copy (dir_raw + "/config.tex");

        std::string content((std::istreambuf_iterator<char>(original)), (std::istreambuf_iterator<char>()));

        copy << FORMAT_CONTENT(Current);
        copy << content;

        original.close();
        copy.close();
        
        std::ifstream original_st ("C:/Program Files/MakeTex/LaTeX/standard.txt");
        std::ofstream standard (dir_rev + "/" + Current.DOCUMENT_TITLE + ".tex");

        std::string content_st((std::istreambuf_iterator<char>(original_st)), (std::istreambuf_iterator<char>()));

        standard << content_st;

        original_st.close();
        standard.close();
    };

    Project ( std::string title, std::string author, std::string subject, std::string school ) {
        this -> DOCUMENT_TITLE = title;
        this -> DOCUMENT_AUTHOR = author;
        this -> DOCUMENT_SUBJECT = subject;
        this -> DOCUMENT_SCHOOL = school;
        this -> FORMAT_DATE = get_formatted_date();

        CREATE_DOCUMENT ( *this );
    };
};


int main () {    
    std::cout << "Document title: ";
    std::string document_title;
    std::getline ( std::cin, document_title );

    std::cout << "Document author: ";
    std::string document_author;
    std::getline ( std::cin, document_author );

    std::cout << "Document subject: ";
    std::string document_subject;
    std::getline ( std::cin, document_subject );

    std::cout << "School: ";
    std::string document_school;
    std::getline ( std::cin, document_school );


    Project LaTeX_Project = Project ( document_title, document_author, document_subject, document_school );

    std::cout << LaTeX_Project.FORMAT_DATE << std::endl;

    return 0;
}
