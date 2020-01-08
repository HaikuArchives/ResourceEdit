#include "RSRCFilter.h"

#include <MimeType.h>
#include <string.h>

static const char* supported_types[] = {
	"application/x-vnd.be-elfexecutable",
	"application/octet-stream",
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

	BMimeType mimeType;
	if (BMimeType::GuessMimeType(&entryRef, &mimeType) != B_OK)
		return false;

	if (strcasecmp(filetype, supported_types[0]) == 0 ||
		filetype == "" || strcasecmp(filetype, supported_types[1]) == 0) {
		for (int i = 0; supported_types[i] != NULL; i++) {
			if (strcasecmp(mimeType.Type(), supported_types[i]) != 0)
				continue;
			if (strlen(entryRef.name) < 3)
				return true;
			const char* secondToLast = &entryRef.name[strlen(entryRef.name) - 2];
				return strcmp(secondToLast, ".o") != 0;
		}
	}

	return false;
}
