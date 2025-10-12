#include "NHFS.hpp"
#include <filesystem>

namespace fs = std::filesystem ;

// Tags
NHFS::CreateDir::CreateDir(const char * const path, const char * const name) 
    : path(path), name(name) {  
}

// constructor
NHFS::NHFS(NHFS::CreateDir tag) 
    : dirPath(tag.path), dirName(tag.name) {
    // Creating Full Directory
    fs::path fullPath = fs::path(dirPath) / dirName ;
    
    fs::create_directories(fullPath) ;
}

NHFS::NHFS() {}

// Setters
void NHFS::set_dirName(const char *name) {
    dirName = name ;
}

void NHFS::set_dirPath(const char *path) {
    dirPath = path ;
}

// Getters
const char * const NHFS::get_dirName() {
    if (!dirName) {
        printf("LOG:\tDirectory Name Not Setted\n\tWill Return Empty\n") ;
        return "" ;
    }
    return dirName ;
}

const char * const NHFS::get_dirPath() {
    if (!dirPath) {
        printf("LOG:\tDirectory Path Not Setted\n\tWill Return Empty\n") ;
        return "" ;
    }
    return dirPath ;
}

const char * const NHFS::get_dirName(NHFS::NO_LOG) {
    if (dirName) return dirName ;
    return "" ;
}

const char * const NHFS::get_dirPath(NHFS::NO_LOG) {
    if (dirPath) return dirPath ;
    return "" ;
}


// Functions
void NHFS::reset() {
    dirName = nullptr ;
    dirPath = nullptr ;
}


void NHFS::createDirectory() {
    if (dirPath && dirName) {
        fs::path fullPath = fs::path(dirPath) / dirName ;
        fs::create_directories(fullPath) ;
    } else {
        printf("Directory Not Setted\n") ;
        return ;
    }
}

void NHFS::createDirectory(const char *path, const char *name) {
    fs::path fullPath = fs::path(path) / name ;
    fs::create_directories(fullPath) ;
}

void NHFS::removeDir(const char *name) {
    fs::path path(name) ;
    if (fs::exists(path)) {
        fs::remove_all(path) ;
    } else {
        printf("Path Does Not Exist.\n") ;
        return ;
    }
}