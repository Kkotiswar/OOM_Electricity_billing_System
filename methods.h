#include<string>
extern void newEntry();
extern void view();
extern void changeRates();
extern void getRates();
extern int openFile(std::string, bool);
extern void write(std::string, int, bool);
extern int search(int);
extern int search(std::string);
extern void modifyEntry(int, int);
extern int numline();
extern int rmrn(const char *, const char *);
extern void viewline(int);
extern void header();
extern void pull(int);
