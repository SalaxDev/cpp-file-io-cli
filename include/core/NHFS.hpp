#ifndef FSIMPL_HPP
#define FSIMPL_HPP

// Stands For No Header Overhead File System
class NHFS {
private :
    // Vars
    const char *dirPath = nullptr ;
    const char *dirName = nullptr ;
public :
    // Tags
    
    // Creates Directory
    struct CreateDir {
        const char *path ;
        const char *name ;
        CreateDir(const char * const path, const char * const name) ;
    };
    
    struct NO_LOG {};
    
    // constructor
    NHFS(NHFS::CreateDir tag) ;
    NHFS() ;
    
    // Setters
    void set_dirName(const char *name) ;
    void set_dirPath(const char *path) ;
    // Getters
    const char * const get_dirName() ;
    const char * const get_dirPath() ;
    
    const char * const get_dirName(NHFS::NO_LOG) ;
    const char * const get_dirPath(NHFS::NO_LOG) ;
    
    // Functions
    void reset() ;
    
    void createDirectory() ;
    void createDirectory(const char *path, const char *name) ;
    
    void removeDir(const char *name) ;
};

#endif // FSIMPL_HPP