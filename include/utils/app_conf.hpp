#ifndef APP_CONF_HPP
#define APP_CONF_HPP

namespace app {
    // App Version
    struct Ver {
    private :
        static char buffer[64] ;
    public :
        
        // Public Vars
        static constexpr int MAIN = 1 ;
        static constexpr int MAJOR = 0 ;
        static constexpr int MINOR = 0 ;
        static constexpr bool SNAPSHOT = false ;
        
        // Functions
        static const char *string() ;
    };
}

#endif // APP_CONF_HPP
