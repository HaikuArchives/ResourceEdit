NAME= ResourceEdit
TYPE= APP
SRCS= DefaultTypes.cpp EditWindow.cpp main.cpp MainWindow.cpp ResourceEdit.cpp \
	ResourceListView.cpp edits/NormalEdit.cpp edits/EditView.cpp \
	edits/BooleanEdit.cpp edits/AppFlagsEdit.cpp interface/ImageButton.cpp \
	interface/ColumnListView.cpp \
	interface/ColumnTypes.cpp \
	interface/AboutWindow.cpp \
	settings/GenericSettingsView.cpp ResourceRow.cpp support/UndoContext.cpp \
	SettingsWindow.cpp SettingsFile.cpp
RSRCS=
LIBS= be root $(STDCPPLIBS) translation tracker
RDEFS= ResourceEdit.rdef
LIBPATHS=
SYSTEM_INCLUDE_PATHS= \
	/system/develop/headers/private/interface \
	/system/develop/headers/private/support \
	/system/develop/headers/private/shared \
	/system/develop/headers/private/locale
LOCAL_INCLUDE_PATHS= support settings interface edits
OPTIMIZE=NONE
#	specify any preprocessor symbols to be defined.  The symbols will not
#	have their values set automatically; you must supply the value (if any)
#	to use.  For example, setting DEFINES to "DEBUG=1" will cause the
#	compiler option "-DDEBUG=1" to be used.  Setting DEFINES to "DEBUG"
#	would pass "-DDEBUG" on the compiler's command line.
DEFINES=
#	specify special warning levels
#	if unspecified default warnings will be used
#	NONE = supress all warnings
#	ALL = enable all warnings
WARNINGS =
# Build with debugging symbols if set to TRUE
SYMBOLS=
COMPILER_FLAGS=

## include the makefile-engine
DEVEL_DIRECTORY := \
	$(shell findpaths -r "makefile_engine" B_FIND_PATH_DEVELOP_DIRECTORY)
include $(DEVEL_DIRECTORY)/etc/makefile-engine
