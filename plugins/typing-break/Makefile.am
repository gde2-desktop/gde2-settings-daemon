NULL =

plugin_LTLIBRARIES = \
	libtyping-break.la		\
	$(NULL)

libtyping_break_la_SOURCES = 		\
	msd-typing-break-plugin.h	\
	msd-typing-break-plugin.c	\
	msd-typing-break-manager.h	\
	msd-typing-break-manager.c	\
	$(NULL)

libtyping_break_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon		\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

libtyping_break_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(AM_CFLAGS)

libtyping_break_la_LDFLAGS = 		\
	$(MSD_PLUGIN_LDFLAGS)	\
	$(NULL)

libtyping_break_la_LIBADD  = 		\
	$(SETTINGS_PLUGIN_LIBS)	\
	$(NULL)

plugin_in_files = 		\
	typing-break.gde2-settings-plugin.in	\
	$(NULL)

plugin_DATA = $(plugin_in_files:.gde2-settings-plugin.in=.gde2-settings-plugin)

EXTRA_DIST = 			\
	$(plugin_in_files)	\
	$(NULL)

CLEANFILES = 			\
	$(plugin_DATA)		\
	$(NULL)

DISTCLEANFILES =		\
	$(plugin_DATA)		\
	$(NULL)

@MSD_INTLTOOL_PLUGIN_RULE@
