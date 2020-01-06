#include "RSRCFilter.h"

#include <MimeType.h>
#include <string.h>

static const char* supported_types[] = {
	"application/x-vnd.Be-elfexecutable",
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

	for (int i = 0; supported_types[i] != nullptr; i++) {
		if (strcmp(mimeType.Type(), supported_types[i]) == 0)
			return true;
	}
	
	return false;
}
