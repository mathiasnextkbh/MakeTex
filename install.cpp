#include <bits/stdc++.h>
#include <direct.h>

class File {
    public:
    std::string NAME, CONTENT, PATH, RELATIVE_PATH;

    std::string get_content ( std::ifstream FILE ) {
        std::string content (
            (std::istreambuf_iterator<char>(FILE)), (std::istreambuf_iterator<char>())
        );
        return content;
    };
    
    File ( std::string name, std::string path, std::string relative_path ) {
        this -> NAME = name;
        this -> PATH = path;
        this -> RELATIVE_PATH = relative_path;
        this -> CONTENT = get_content( std::ifstream ( path + "\\" + name ) );
    };
};

class FileSystem {
    public:
    std::string INSTALL_PATH;
    std::vector < File > FILE_LIST;

    void InstallFile ( File FILE, std::string INSTALL_PATH ) {
        if ( FILE.RELATIVE_PATH != "" ) {
            std::string dir_raw = INSTALL_PATH + FILE.RELATIVE_PATH;
            const char* directory = dir_raw.c_str();
            _mkdir(directory);
            std::cout << "Created new directory: " << directory << std::endl;
        }
        std::ofstream NEW_FILE (INSTALL_PATH + FILE.RELATIVE_PATH + "\\" + FILE.NAME);
        NEW_FILE << FILE.CONTENT;
        NEW_FILE.close();
        std::cout << "Installed file " << FILE.NAME << " at " << INSTALL_PATH + FILE.RELATIVE_PATH << std::endl;
    };

    void Install ( FileSystem Current ) {
        for ( int i = 0; i < Current.FILE_LIST.size(); i ++ ) {
            std::cout << "Installing file " << i + 1 << " of " << Current.FILE_LIST.size() << ": " << std::endl;
            InstallFile ( Current.FILE_LIST [i], Current.INSTALL_PATH );
        };
        std::cout << "\n\nInstalled succesfully..\n" << std::endl;
    };

    FileSystem ( std::vector < File > file_list, std::string install_path ) {
        this -> FILE_LIST = file_list;
        this -> INSTALL_PATH = install_path;
        std::cout << "\nInstall PATH: " << this -> INSTALL_PATH << std::endl << std::endl;
    };
};

std::string current_working_directory () {
    char* cwd = _getcwd( 0, 0 ) ; // **** microsoft specific ****
    std::string working_directory(cwd) ;
    std::free(cwd) ;
    return working_directory ;
};

int main () {
    std::string ORG_PATH = current_working_directory() + "\\src";

    std::vector < File > Bundled_Files = {
        File ( "source.cpp", ORG_PATH, ""),
        File ( "maketex.exe", ORG_PATH, ""),
        File ( "config.tex", ORG_PATH, "\\LaTeX"),
        File ( "standard.tex", ORG_PATH, "\\LaTeX")
    };

    std::cout << "Choose an install path: ";
    std::string INST_PATH;
    std::getline ( std::cin, INST_PATH );

    try {
        std::string dir_raw = INST_PATH + "\\MakeTex";
        const char* directory = dir_raw.c_str();
        _mkdir(directory);
        std::cout << "Created new directory: " << directory << std::endl;
        FileSystem Installer = FileSystem ( Bundled_Files, dir_raw );
        Installer.Install(Installer);
    } catch ( const std::exception& e ) {
        std::cerr << e.what() << '\n';
    }

    return 0;
};