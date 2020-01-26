/*
 * Copyright 2020 Raheem Idowu <abdurraheemidowu@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "RSRCFilter.h"

#include <MimeType.h>
#include <NodeInfo.h>
#include <string.h>

#include <compat/sys/stat.h>

bool
RSRCFilter::Filter(const entry_ref* ref, BNode* node, struct stat_beos* st,
	const char* filetype)
{
	BEntry entry(ref, true);
	if (entry.InitCheck() != B_OK)
		return false;
	if (entry.IsDirectory())
		return true;

	entry_ref entryRef;
	if (entry.GetRef(&entryRef) != B_OK)
		return false;

	char mimeType[B_MIME_TYPE_LENGTH];

	//Check if ref is a symlink
	if (S_ISLNK(st->st_mode)) {
		BNode traversedNode(&entry);
		BNodeInfo nodeInfo(&traversedNode);
		if (nodeInfo.GetType(mimeType) != B_OK)
			return false;
		filetype = mimeType;
	}

	//All files of non-BFS drives report as octet-stream or empty
	if ((strcasecmp(filetype, "application/octet-stream") == 0
		|| filetype[0] == '\0') && filetype) {
		BMimeType mimeType;
		if (BMimeType::GuessMimeType(&entryRef, &mimeType) != B_OK)
			return false;
		filetype = mimeType.Type();
	}


	if (strcasecmp(filetype, "application/x-vnd.be-elfexecutable") != 0)
		return false;
	if (strlen(entryRef.name) < 3)
		return true;
	const char* secondToLast = &entryRef.name[strlen(entryRef.name) - 2];
	return strcmp(secondToLast, ".o") != 0;
}
