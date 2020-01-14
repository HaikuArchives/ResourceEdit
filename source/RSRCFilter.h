/*
 * Copyright 2020 Raheem Idowu <raheemidowu.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef RSRC_FILTER_H
#define RSRC_FILTER_H

#include <FilePanel.h>

class RSRCFilter : public BRefFilter {
public:
	bool	Filter(const entry_ref* ref, BNode* node,
				struct stat_beos* st, const char* filetype);
};

#endif
