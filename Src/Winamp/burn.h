#define BURNCALLBACK_DIALOGOPEN (WM_USER + 0x500)
#define BURNCOMMAND (WM_USER + 32)
#define BURN_SETERRORPARENT (WM_USER+111)
 #define BURNCOMMAND_GETSTATUS  1
 #define BURNCOMMAND_GETPERCENT  2
 #define BURNCOMMAND_CANCEL 666

#define BURNTICK 0x123
#define CANCELTICK 0x124


#define STATUS_BURNING_DONE 7
#define STATUS_BURNING_COMPLETE 100
#define STATUS_START_BURNING 5
#define STATUS_ERROR 999
#define STATUS_BURNING 6