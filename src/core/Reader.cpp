#include "Reader.hpp"
#include "app_conf.hpp"
#include "NHFS.hpp"

#include <cstring>
#include <cstdio>

// Private Functions
eDefArg Reader::readArgs() {
    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i] ;
        if (strlen(arg) >= 1) {
            if (strncmp(arg, "--", 2) == 0) {
                arg += 2 ;
                eArg = eDefArg::LONG_FLAG ;
            } else if (arg[0] == '-') {
                arg += 1 ;
                eArg = eDefArg::SINGLE_FLAG ;
            }
            
            switch(eArg) {
                case eDefArg::SINGLE_FLAG: {
                    for (int i = 0; i < ARR_SIZE; ++i) {
                        if (strcmp(arg, SINGLE_CMD[i]) == 0) {
                            return ARR_EVENT[i] ;
                        }
                    }
                    break ;
                }
                
                case eDefArg::LONG_FLAG: {
                    for (int i = 0; i < ARR_SIZE; ++i) {
                        if (strcmp(arg, LONG_CMD[i]) == 0) {
                            return ARR_EVENT[i] ;
                        }
                    }
                    break ;
                }
                
                default: {
                    msg_err = "Invalid Argument Passed" ;
                    eArg = eDefArg::INVALID_ARG ;
                    break ;
                }
            }
        }
    }
    
    msg_err = "Invalid Argument" ;
    return eDefArg::INVALID_ARG ;
}

void Reader::readCommand() {
    eCommand = eException::UNEXCEPTED_ERR ;
}

eException Reader::execute_arg() {
    using enum eDefArg ;
    switch (eArg) {
        case MKDIR: {
            if (argc > 2) {
                NHFS(NHFS::CreateDir(argv[2], "")) ;
            }
            break ;
        }
        
        case DELETE: {
            if (argc > 2) {
                if (remove(argv[2]) == 0) {
                    printf("A File Named [%s] Successfully Deleted\n", argv[2]) ;
                } else {
                    perror("Error While Removing File") ;
                }
            }
            break ;
        }
        
        case FILE_CREATE: {
            if (argc > 2) {
                const char *arg = argv[2] ;
                if (strcmp(arg, "-h") == 0) {
                    printf("First Command Takes the File Name[Example.txt], Second Will Store The Data[Hello World]\n") ;
                    return eException::NO_ERR;
                }
                
                FILE *file = fopen(argv[2], "a") ;
                if (file) {
                    if (argc > 3) {
                        fseek(file, SEEK_END, 0) ;
                        fwrite(argv[3], 1, strlen(argv[3]), file) ;
                    }
                    printf("File Sussesfully Created Named [%s] With [%s] Data\n", argv[2], argv[3]) ;
                    fclose(file) ;
                } else {
                    perror("Failed To Create File") ;
                }
            }
            
            break ;
        }
        
        case FILE_OPEN: {
            if (argc > 2) {
                FILE *file = fopen(argv[2], "rb") ;
                if (file) {
                    fseek(file, 0, SEEK_END) ;
                    long int file_size = ftell(file) ;
                    rewind(file) ;
                    
                    if (file_size > 8192) {
                        msg_err = "Can't Read More Than 8192 Byte!" ;
                        return eException::INVALID_COMMAND ;
                    }
                    
                    char *file_data = new char[file_size + 1] ;
                    size_t bytes_read = fread(file_data, 1, file_size, file) ;
                    if (bytes_read != static_cast<size_t>(file_size)) {
                        printf("Expected %ld, Got %zu", file_size, bytes_read) ;
                        msg_err = "Answered" ;
                        fclose(file) ;
                        return eException::INVALID_COMMAND ;
                    }
                    
                    file_data[file_size] = '\0' ;
                    
                    printf("Size: %ld\n", file_size) ;
                    printf("%s: %s", argv[2], file_data) ;
                    
                    fclose(file) ;
                } else {
                    perror("Failed To Open File") ;
                }
            }
            break ;
        }
        
        case HELP: {
            printf("Welcome To My Program! There Are Currently [%d] Command Available:\n", ARR_SIZE) ;
            for (int i = 0; i < ARR_SIZE; ++i) {
                printf("%s | %-20s %s\n", SINGLE_CMD[i], LONG_CMD[i], CMD_DESCRIPTION[i]) ;
            }
            break ;
        }
        
        case VERSION: {
            printf("File I/O\nVersion: %s\n", app::Ver::string()) ;
            break ;
        }
        
        default: {
            msg_err = "Uncatched Event, Developer's Fault" ;
            return eException::DEVELOPER_FAULT ;
        }
    }
    
    return eException::NO_ERR ;
}

// Constructor
Reader::Reader(const int argc, const char ** argv) 
    : argc(argc), argv(argv), buffer(new char[buffer_size]), msg_err("No Error") {
    if (!buffer) {
        eCommand = eException::ALLOC_FAILED ;
        msg_err = "Failed To Allocate Buffer!" ;
    }
    if (argc > 1) eArg = eDefArg::HAVE_ARGS ;
}
// Destructor
Reader::~Reader() {
    if (buffer) {
        delete[] buffer ;
        buffer = nullptr ;
    }
}


// Functions
int Reader::start() {
    if (eCommand == eException::ALLOC_FAILED) {
        fprintf(stderr, "ALLOC_FAILED, ERROR: %s\n", msg_err) ;
        return 1 ;
    }
    
    if (eArg == eDefArg::HAVE_ARGS) {
        eArg = readArgs() ;
        if (eArg == eDefArg::INVALID_ARG) {
            fprintf(stderr, "ERROR: %s\n", msg_err) ;
            return 1 ;
        }
        eException e = execute_arg() ;
        if (e != eException::NO_ERR) {
            if (!(strcmp(msg_err, "Answered") == 0)) {
                printf("ERROR: %s\n", msg_err) ;
            }
        }
        return 0 ;
    }
    
    printf("File I/O Version: %s\nType -h | --help for more information Alongside Executable\n", app::Ver::string()) ;
    
    return 0 ;
}