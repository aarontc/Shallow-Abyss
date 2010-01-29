/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool db_createConnection() {

	// Setup database connection
	QSqlDatabase db = QSqlDatabase::addDatabase ( "QPSQL" );
	db.setHostName ( "epic.aaronnet.lan" );
	db.setDatabaseName ( "acdj" );
	db.setUserName ( "acdj" );
	db.setPassword ( "acdj" );
	db.setConnectOptions ( "requiressl=1" );
	if ( ! db.open () ) {
		QMessageBox::critical ( 0, qApp->tr("Cannot open database"),
			qApp->tr("Unable to establish a database connection.\n"
					 "\n"
					 "Click Cancel to exit."), QMessageBox::Cancel);
		return false;
	}

	return true;

	QSqlQuery query;

	query.exec("create table artists (id int primary key, "
									 "artist varchar(40), "
									 "albumcount int)");

	query.exec("insert into artists values(0, '<all>', 0)");
	query.exec("insert into artists values(1, 'Ane Brun', 2)");
	query.exec("insert into artists values(2, 'Thomas Dybdahl', 3)");
	query.exec("insert into artists values(3, 'Kaizers Orchestra', 3)");

	query.exec("create table albums (albumid int primary key, "
									 "title varchar(50), "
									 "artistid int, "
									 "year int)");

	query.exec("insert into albums values(1, 'Spending Time With Morgan', 1, "
					   "2003)");
	query.exec("insert into albums values(2, 'A Temporary Dive', 1, 2005)");
	query.exec("insert into albums values(3, '...The Great October Sound', 2, "
					   "2002)");
	query.exec("insert into albums values(4, 'Stray Dogs', 2, 2003)");
	query.exec("insert into albums values(5, "
		"'One day you`ll dance for me, New York City', 2, 2004)");
	query.exec("insert into albums values(6, 'Ompa Til Du D\xf8r', 3, 2001)");
	query.exec("insert into albums values(7, 'Evig Pint', 3, 2002)");
	query.exec("insert into albums values(8, 'Maestro', 3, 2005)");

	return true;
}

#endif