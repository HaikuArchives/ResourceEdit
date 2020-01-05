#include "RSRCFilter.h"

#include <MimeType.h>
#include <string.h>

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
	
	if (strcmp(mimeType.Type(), "application/octet-stream") == 0)
		return true;
	
	return false;
}
