/*
 * Copyright 2020 Raheem Idowu <abdurraheemidowu@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "RSRCFilter.h"

#include <MimeType.h>
#include <NodeInfo.h>
#include <string.h>

#include <compat/sys/stat.h>

static const char* supported_types[] = {
	"application/x-vnd.be-elfexecutable",
	NULL
};

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
	bool isLink = S_ISLNK(st->st_mode);
	if (isLink) {
		BNode traversedNode(&entry);
		BNodeInfo * nodeInfo = new BNodeInfo(&traversedNode);
		if (nodeInfo->GetType(mimeType) != B_OK) {
			delete nodeInfo;
			return false;
		} else {
			delete nodeInfo;
			filetype = mimeType;
		}
	}

	//All files of non-BFS drives report as octet-stream or empty
	if (strcasecmp(filetype, "application/octet-stream") == 0
		|| filetype[0] == '\0') {
		BMimeType mimeType;
		if (BMimeType::GuessMimeType(&entryRef, &mimeType) != B_OK)
			return false;
		filetype = mimeType.Type();
	}

	for (int i = 0; supported_types[i] != NULL; i++) {
		if (strcasecmp(filetype, supported_types[i]) != 0)
			continue;
		if (strlen(entryRef.name) < 3)
			return true;
		const char* secondToLast = &entryRef.name[strlen(entryRef.name) - 2];
			return strcmp(secondToLast, ".o") != 0;
	}

	return false;
}
