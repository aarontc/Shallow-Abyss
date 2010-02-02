#ifndef LIBRARYSCANNER_HPP
#define LIBRARYSCANNER_HPP

#include <QThread>

//stuff

class LibraryScanner : public QThread {

public:
	LibraryScanner ();
	~LibraryScanner ();

protected:
	void run();
	void scan ( QString directory = NULL );

};


#endif // LIBRARYSCANNER_HPP
