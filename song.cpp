#include "song.hpp"

Song::Song()
{
}

Song::Song(quint64 songID)
{
	QSqlQuery query;

	query.prepare("SELECT artists.name, albums.name, songs.title, files.path, artists.artistid, albums.albumid, songs.songid, files.fileid FROM songs JOIN artists ON artists.artistid=songs.artistid JOIN albums ON albums.albumid=songs.albumid JOIN files ON files.songid=songs.songid WHERE songs.songid=? LIMIT 1");
	query.addBindValue(songID);
	query.exec();

	query.first();

	m_artist = query.value(0).toString();
	m_album = query.value(1).toString();
	m_title = query.value(2).toString();
	m_filePath = query.value(3).toString();

	m_artistID = query.value(4).toULongLong();
	m_albumID = query.value(5).toULongLong();
	m_songID = query.value(6).toULongLong();
	m_fileID = query.value(7).toULongLong();

}

QString Song::album()
{
	return m_album;
}

QString Song::artist()
{
	return m_artist;
}

QString Song::filePath()
{
	return m_filePath;
}

QString Song::title()
{
	return m_title;
}
