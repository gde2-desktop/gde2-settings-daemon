NULL =

SUBDIRS =		\
	data		\
	$(NULL)

plugin_LTLIBRARIES = \
	libxrdb.la		\
	$(NULL)

libxrdb_la_SOURCES = 		\
	msd-xrdb-plugin.h	\
	msd-xrdb-plugin.c	\
	msd-xrdb-manager.h	\
	msd-xrdb-manager.c	\
	$(NULL)

libxrdb_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon		\
	-DSYSCONFDIR=\""$(sysconfdir)"\"	\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

libxrdb_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(AM_CFLAGS)

libxrdb_la_LDFLAGS = 		\
	$(MSD_PLUGIN_LDFLAGS)	\
	$(NULL)

libxrdb_la_LIBADD  = 		\
	$(SETTINGS_PLUGIN_LIBS)	\
	$(NULL)

plugin_in_files = 		\
	xrdb.gde2-settings-plugin.in	\
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
