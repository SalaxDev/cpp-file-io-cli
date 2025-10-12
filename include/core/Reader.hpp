#ifndef READER_HPP
#define READER_HPP

enum class eDefArg {
    NO_ARG, INVALID_ARG, MKDIR,
    DELETE, FILE_CREATE, FILE_OPEN, HAVE_ARGS,
    SINGLE_FLAG, LONG_FLAG, HELP, VERSION
};

enum class eException {
    UNEXCEPTED_ERR, INVALID_COMMAND, NO_ERR, EXIT, ALLOC_FAILED, DEVELOPER_FAULT
};

class Reader {
private :
    // Private Vars
    // Args
    const int argc ;
    const char **argv ;
    
    static const int ARR_SIZE = 6 ;
    const char *SINGLE_CMD[ARR_SIZE] {
        "v",
        "h",
        "n",
        "f",
        "o",
        "d"
    };
    
    const char *LONG_CMD[ARR_SIZE] {
        "version",
        "help",
        "new-folder",
        "file-create",
        "open-file",
        "delete"
    };
    
    const eDefArg ARR_EVENT[ARR_SIZE] {
        eDefArg::VERSION,
        eDefArg::HELP,
        eDefArg::MKDIR,
        eDefArg::FILE_CREATE,
        eDefArg::FILE_OPEN,
        eDefArg::DELETE
    };
    
    const char *CMD_DESCRIPTION[ARR_SIZE] {
        "Shows The Name and Version of Program",
        "Shows Command Line Arguments What is Available",
        "Creates New Folder",
        "Creates a file",
        "Opens a File and Displays It",
        "Delete a Folder or File in the current Executable"
    };
    
    
    
    // Enums
    eDefArg eArg = eDefArg::NO_ARG ;
    eException eCommand = eException::NO_ERR ;
    
    // Buffer Data
    const int buffer_size = 256 ;
    const char *buffer = nullptr ;
    const char *msg_err ;
    
    // Private Functions
    
    eDefArg readArgs() ;
    void readCommand() ;
    eException execute_arg() ;
public :
    // Constructor
    Reader(const int argc, const char ** argv) ;
    // Destructor
    ~Reader() ;
    
    // Functions
    int start() ;
};


#endif // READER_HPP