NULL =

noinst_PROGRAMS = 			\
	test-background			\
	$(NULL)

test_background_SOURCES = 		\
	test-background.c		\
	msd-background-manager.h	\
	msd-background-manager.c	\
	$(NULL)

test_background_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon		\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

test_background_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(GDE2_DESKTOP_CFLAGS)		\
	$(AM_CFLAGS)

test_background_LDADD =		\
	$(top_builddir)/gde2-settings-daemon/libmsd-profile.la	\
	$(SETTINGS_PLUGIN_LIBS)	\
	$(GDE2_DESKTOP_LIBS)		\
	$(X11_LIBS) \
	$(NULL)

plugin_LTLIBRARIES = \
	libbackground.la		\
	$(NULL)

libbackground_la_SOURCES = 		\
	msd-background-plugin.h		\
	msd-background-plugin.c		\
	msd-background-manager.h	\
	msd-background-manager.c	\
	$(NULL)

libbackground_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon		\
	-I$(top_srcdir)/plugins/background/libbackground   \
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

libbackground_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(GDE2_DESKTOP_CFLAGS)		\
	$(AM_CFLAGS)

libbackground_la_LDFLAGS = 		\
	$(MSD_PLUGIN_LDFLAGS)		\
	$(NULL)

libbackground_la_LIBADD  = 		\
	$(SETTINGS_PLUGIN_LIBS)		\
	$(GDE2_DESKTOP_LIBS)		\
	$(NULL)

plugin_in_files = 		\
	background.gde2-settings-plugin.in	\
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
