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
	void scan ( const QString & directory = NULL );
	void readtags ( const QString & file );
};


#endif // LIBRARYSCANNER_HPP
