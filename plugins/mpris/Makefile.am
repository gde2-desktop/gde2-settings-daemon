plugin_LTLIBRARIES = \
	libmpris.la

libmpris_la_SOURCES = 		\
	msd-mpris-manager.c	\
	msd-mpris-manager.h	\
	msd-mpris-plugin.c	\
	msd-mpris-plugin.h

libmpris_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon		\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

libmpris_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(AM_CFLAGS)

libmpris_la_LDFLAGS = 		\
	$(MSD_PLUGIN_LDFLAGS)

libmpris_la_LIBADD  = 		\
	$(SETTINGS_PLUGIN_LIBS)

plugin_in_files = 		\
	mpris.gde2-settings-plugin.in

plugin_DATA = $(plugin_in_files:.gde2-settings-plugin.in=.gde2-settings-plugin)

EXTRA_DIST = 			\
	$(plugin_in_files)

CLEANFILES = 			\
	$(plugin_DATA)

DISTCLEANFILES =		\
	$(plugin_DATA)

@MSD_INTLTOOL_PLUGIN_RULE@

