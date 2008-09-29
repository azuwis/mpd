/* the Music Player Daemon (MPD)
 * Copyright (C) 2003-2007 by Warren Dukes (warren.dukes@gmail.com)
 * This project's homepage is: http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "song_print.h"
#include "songvec.h"
#include "directory.h"
#include "tag_print.h"
#include "client.h"

void printSongUrl(struct client *client, Song * song)
{
	if (song->parentDir && song->parentDir->path) {
		client_printf(client, "%s%s/%s\n", SONG_FILE,
			      getDirectoryPath(song->parentDir), song->url);
	} else {
		client_printf(client, "%s%s\n", SONG_FILE, song->url);
	}
}

int printSongInfo(struct client *client, Song * song)
{
	printSongUrl(client, song);

	if (song->tag)
		tag_print(client, song->tag);

	return 0;
}

int songvec_print(struct client *client, const struct songvec *sv)
{
	int i;
	Song **sp = sv->base;

	for (i = sv->nr; --i >= 0;)
		if (printSongInfo(client, *sp++) < 0)
			return -1;

	return 0;
}